// Pascal's Triangle

vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        
        for (int i = 0; i < numRows; i++) {
            // Create a row of size i + 1, initialized entirely with 1s
            vector<int> row(i + 1, 1);
            
            // Calculate the inner elements (skipping the first and last indices)
            for (int j = 1; j < i; j++) {
                row[j] = res[i - 1][j - 1] + res[i - 1][j];
            }
            
            res.push_back(row);
        }
        
        return res;
    }