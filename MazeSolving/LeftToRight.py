import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from collections import deque
from matplotlib.animation import FuncAnimation

dx = [-1, 0, 1, 0, -1, 1, -1, 1]
dy = [0, 1, 0, -1, -1, -1, 1, 1]

#DIS = [(0, -1), (-1, 0), (0, 1)]

# def update_matrix(frame):
#     global count  # 使用 global 声明 count 是全局变量
#     # 前两个值在 0 到 5 之间随机生成
#     input_list[:2] = np.random.uniform(0, 27, size=2)
#     # 后三个值在 0 到 2 之间随机生成
#     #input_list[2:] = np.random.uniform(1, 2, size=3)
    
#     # 更新矩阵并更新灰度图
#     rx = int(input_list[0])
#     ry = int(input_list[1])

#     # i = 2
#     # for (dx, dy) in DIS:
#     #     new_x, new_y = int(rx + dx), int(ry + dy)
#     #     if new_y < 0:
#     #         new_y = 0
#     #     elif new_y >= input_matrix.shape[1]:
#     #         new_y = input_matrix.shape[1] - 1
#     #     input_matrix[new_x, new_y] = input_list[i]  # 更新矩阵数据
#     #     i = i + 1
#     input_matrix[rx, ry] = 0
#     img.set_array(input_matrix)  # 更新灰度图像数据
    
#     count += 1  # 更新计数器
#     if count >= 400:  # 达到 5 个 input_list 后停止循环
#         animation.event_source.stop()  # 停止动画循环
#     return input_matrix
def update_matrix(frame):
    global count  # 使用 global 声明 count 是全局变量
    # 前两个值在 0 到 5 之间随机生成
    input_list[:2] = np.random.uniform(0, 27, size=2)
    # 后三个值在 0 到 2 之间随机生成
    #input_list[2:] = np.random.uniform(1, 2, size=3)
    
    # 更新矩阵并更新灰度图
    rx = int(input_list[0])
    ry = int(input_list[1])

    # i = 2
    # for (dx, dy) in DIS:
    #     new_x, new_y = int(rx + dx), int(ry + dy)
    #     if new_y < 0:
    #         new_y = 0
    #     elif new_y >= input_matrix.shape[1]:
    #         new_y = input_matrix.shape[1] - 1
    #     input_matrix[new_x, new_y] = input_list[i]  # 更新矩阵数据
    #     i = i + 1
    input_matrix[rx, ry] = 0
    img.set_array(input_matrix)  # 更新灰度图像数据
    
    count += 1  # 更新计数器
    if count >= 400:  # 达到 5 个 input_list 后停止循环
        animation.event_source.stop()  # 停止动画循环
    return input_matrix

def print_matrix():
    np.savetxt('final_matrix.txt', input_matrix, fmt='%d')
    with open('final_matrix.txt', 'r') as f:
        matrix_data = f.readlines()
    matrix_rows = len(matrix_data)
    matrix_columns = len(matrix_data[0].split())
    matrix_data = [row.strip().replace(",", "") for row in matrix_data]
    matrix_data = "\n".join(matrix_data)
    return matrix_rows,matrix_columns,matrix_data

# algorithm for shortest path
def bfs():
    queue = deque()
    d = [[-1] * ny for _ in range(nx)]
    Prev = [[None] * ny for _ in range(nx)]
    d[nx-1][ny-1] = 0
    queue.append((nx-1, ny-1))

    while queue:
        t = queue.popleft()
        for i in range(8):
            x = t[0] + dx[i]
            y = t[1] + dy[i]
            
            if 0 <= x < nx and 0 <= y < ny and g[x][y] == 0 and d[x][y] == -1:
                d[x][y] = d[t[0]][t[1]] + 1
                Prev[x][y] = t  
                queue.append((x, y))

    return Prev

count = 0
# 创建初始二维矩阵
# input_matrix = np.array([[0, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
#                          [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],])

rows = 27
columns = 18

matrix = [[1] * columns for _ in range(rows)]
matrix[0][0] = 0
matrix[-1][-1] = 0

input_matrix = np.array(matrix)
print(type(input_matrix))

# 模拟实时 input list
input_list = np.zeros(5)

# 将二维矩阵绘制成灰度图
colors = ['white', 'black']
cmap = ListedColormap(colors)

fig, ax = plt.subplots()
img = ax.imshow(input_matrix, cmap=cmap, vmin=0, vmax=1)

# 设置初始标题
ax.set_title('Map')
animation = FuncAnimation(fig, update_matrix, interval=100)

plt.show()

nx,ny,matrix_data = print_matrix()
print(matrix_data)

#print('n=', n)
g = []

for line in matrix_data.split("\n"):
    row = list(map(int, line.strip().split()))
    g.append(row)

#print(g)
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
    shortest_path.append(end)
    if end == (nx-1, ny-1):
        break
    end = Prev[end[0]][end[1]]  

# modify path and original maze
for i in range(nx):
    for j in range(ny):
        if g[i][j] == 0 and (i, j) not in shortest_path:
            g[i][j] = 1

new_matrix = []

#create output maze
for i in range(nx): 
    row = []
    for j in range(ny):
        row.append(g[i][j])
    new_matrix.append(row)

print(new_matrix)

# Plot the second matrix with Greens colormap and reduced alpha
ax.imshow(new_matrix, cmap=cmap0, alpha=0.3)
# Set the title
ax.set_title('Overlay')

plt.show()