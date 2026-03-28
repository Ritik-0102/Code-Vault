# def capitalize_name(full_name):
#     # Split the full name into words
#     words = full_name.split()
#     # Capitalize the first alphabetic character of each word if it exists
#     capitalized_words = []
#     for word in words:
#         if word:  # Check if the word is not empty
#             # Capitalize the first character if it's alphabetic
#             capitalized_word = word[0].upper() + word[1:] if word[0].isalpha() else word
#             capitalized_words.append(capitalized_word)
#     # Join the capitalized words back into a single string
#     capitalized_name = ' '.join(capitalized_words)
#     return capitalized_name

# # Input
# full_name = input().strip()
# # Output
# print(capitalize_name(full_name))


# def solve(s):
#     li=s.split()
#     l1=[]
#     for i in li:
#         if i[0].isalpha:
#             j=i.title()
#             l1.append(j)
#         else:
#             l1.append(i)
#     s1=" ".join(l1)
#     return s1

# s=input()
# solve(s)




from collections import deque

def bfs(graph,start):
    visited = set()
    queue = deque([start])
    result = []

    while queue:
        node = queue.popleft()

        if node not in visited:
            visited.add(node)
            result.append(node)

            queue.extend(graph[node])

    return result


graph = {
    'A' : ['B' , 'C'] ,
    'B' : ['E' , 'F'] ,
    'C' : ['G'] ,
    'E' : ['G'] 
}

print(bfs(graph,0))