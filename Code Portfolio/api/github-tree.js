// Vercel serverless function: keeps GITHUB_TOKEN on the server.
// Fine-grained token should have read-only Contents and Metadata access
// and be restricted to the Code-Vault repository.
export default async function handler(req, res) {
  if (req.method !== 'GET') {
    res.setHeader('Allow', 'GET');
    return res.status(405).json({ error: 'Method not allowed' });
  }

  const token = process.env.GITHUB_TOKEN;
  if (!token) {
    return res.status(500).json({ error: 'GITHUB_TOKEN is not configured in Vercel.' });
  }

  const owner = String(req.query.owner || 'Ritik-0102');
  const repo = String(req.query.repo || 'Code-Vault');
  const branch = String(req.query.branch || 'main');

  // Prevent this endpoint from becoming a general-purpose authenticated proxy.
  // The token should be scoped only to this repository.
  if (owner.toLowerCase() !== 'ritik-0102' || repo.toLowerCase() !== 'code-vault') {
    return res.status(400).json({ error: 'This API endpoint is configured for Ritik-0102/Code-Vault only.' });
  }

  const headers = {
    Accept: 'application/vnd.github+json',
    Authorization: `Bearer ${token}`,
    'X-GitHub-Api-Version': '2022-11-28'
  };
  const base = `https://api.github.com/repos/${encodeURIComponent(owner)}/${encodeURIComponent(repo)}`;

  try {
    // GitHub code search requires authentication; proxy it through this function
    // so the token is never exposed to the browser.
    if (req.query.q) {
      const query = String(req.query.q).slice(0, 200);
      const searchUrl = `https://api.github.com/search/code?q=${encodeURIComponent(query)}+repo:${encodeURIComponent(owner)}/${encodeURIComponent(repo)}`;
      const searchRes = await fetch(searchUrl, { headers });
      const searchData = await searchRes.json().catch(() => ({}));
      if (!searchRes.ok) {
        return res.status(searchRes.status).json({ error: searchData.message || `Code search failed: HTTP ${searchRes.status}` });
      }
      return res.status(200).json({ items: Array.isArray(searchData.items) ? searchData.items : [] });
    }
    const [repoRes, treeRes, languagesRes] = await Promise.all([
      fetch(base, { headers }),
      fetch(`${base}/git/trees/${encodeURIComponent(branch)}?recursive=1`, { headers }),
      fetch(`${base}/languages`, { headers })
    ]);

    const repoData = await repoRes.json().catch(() => ({}));
    if (!repoRes.ok) {
      return res.status(repoRes.status).json({ error: repoData.message || `Repository request failed: HTTP ${repoRes.status}` });
    }

    const treeData = await treeRes.json().catch(() => ({}));
    if (!treeRes.ok) {
      return res.status(treeRes.status).json({ error: treeData.message || `Tree request failed: HTTP ${treeRes.status}` });
    }

    const languages = languagesRes.ok ? await languagesRes.json().catch(() => null) : null;
    res.setHeader('Cache-Control', 's-maxage=60, stale-while-revalidate=300');
    return res.status(200).json({
      repo: repoData,
      tree: Array.isArray(treeData.tree) ? treeData.tree : [],
      truncated: Boolean(treeData.truncated),
      languages,
      branch: repoData.default_branch || branch
    });
  } catch (error) {
    console.error('GitHub tree API error:', error);
    return res.status(500).json({ error: 'Unable to connect to GitHub from the server.' });
  }
}
