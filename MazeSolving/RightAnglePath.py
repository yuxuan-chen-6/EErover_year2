from collections import deque
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

def bfs():
    queue = deque()
    d = [[-1] * n for _ in range(n)]
    Prev = [[None] * n for _ in range(n)]
    d[n-1][n-1] = 0
    queue.append((n-1, n-1))

    while queue:
        t = queue.popleft()
        for i in range(4):
            x = t[0] + dx[i]
            y = t[1] + dy[i]
            if 0 <= x < n and 0 <= y < n and g[x][y] == 0 and d[x][y] == -1:
                d[x][y] = d[t[0]][t[1]] + 1
                Prev[x][y] = t
                queue.append((x, y))

    return Prev

n = int(input())
g = []
for _ in range(n):
    row = list(map(int, input().split()))
    g.append(row)
    
# Define custom colormap
colors = ['green', 'white']
cmap0 = ListedColormap(colors)

# Create the figure and subplot
fig, ax = plt.subplots()

# Plot the first matrix with grayscale colormap
ax.imshow(g, cmap='binary', vmin=0, vmax=1)    
   

Prev = bfs()
end = (0, 0)

shortest_path = []
while True:
    print(end[0], end[1])
    shortest_path.append(end)
    if end == (n-1, n-1):
        break
    end = Prev[end[0]][end[1]]

for i in range(n):
    for j in range(n):
        if g[i][j] == 0 and (i, j) not in shortest_path:
            g[i][j] = 1

# print("Modified Matrix:")
# for i in range(n):
#     for j in range(n):
#         print(g[i][j], end=' ')
#     print()
    
new_matrix = []

for i in range(n):
    row = []
    for j in range(n):
        row.append(g[i][j])
    new_matrix.append(row) 
    
    
# Plot the second matrix with Greens colormap and reduced alpha
ax.imshow(new_matrix, cmap=cmap0, alpha=0.3)

# Set the title
ax.set_title('Overlay')

# Display the plot
plt.show()    
