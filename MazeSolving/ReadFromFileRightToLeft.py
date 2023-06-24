import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from collections import deque
from matplotlib.animation import FuncAnimation

dx = [-1, 0, 1, 0, -1, 1, -1, 1]
dy = [0, 1, 0, -1, 1, 1, -1, -1]

DIS = [(0, -1), (-1, 0), (0, 1)]

def process_input():
    file_path = 'D:/input_coordinates.txt'  # 文件路径

    with open(file_path, 'r') as file:
        # 读取文件内容
        content = file.read()
    return content


# def update_matrix(frame):
#     global count  # 使用 global 声明 count 是全局变量

#     # 从输入中读取字符串并将其解析为列表
#     input_str = process_input()
#     # if input_str.strip() == "-1":  # 如果文件内容为-1，则停止循环
#     #     animation.event_source.stop()  # 停止动画循环
#     #     ax_matrix.set_visible(False)  # 隐藏矩阵图
#     #     return
    

#     input_list[:2] = eval(input_str)

#     rx = int(input_list[0])
#     ry = int(input_list[1])

#     input_matrix[rx, ry] = 0

#     img.set_array(input_matrix)

#     return input_matrix
def update_matrix(frame):
    global count  # 使用 global 声明 count 是全局变量

    # 从输入中读取字符串并将其解析为列表
    input_str = process_input()
    # if input_str.strip() == "-1":  # 如果文件内容为-1，则停止循环
    #     animation.event_source.stop()  # 停止动画循环
    #     ax_matrix.set_visible(False)  # 隐藏矩阵图
    #     return

    try:
        input_list[:2] = eval(input_str)

        rx = int(input_list[0])
        ry = int(input_list[1])

        if 0 <= rx < len(input_matrix) and 0 <= ry < len(input_matrix[0]):  # 判断坐标是否在矩阵范围内
            input_matrix[rx, ry] = 0
            img.set_array(input_matrix)
        else:
            print(f"Warning: Coordinate ({rx}, {ry}) out of bounds.")
    except Exception as e:
        print(f"Warning: Unable to parse coordinates: {input_str}. Error: {str(e)}")

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


def bfs():
    queue = deque()
    d = [[-1] * ny for _ in range(nx)]
    Prev = [[None] * ny for _ in range(nx)]
    d[0][ny - 1] = 0
    queue.append((0, ny - 1))

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


rows = 27
columns = 18

matrix = [[1] * columns for _ in range(rows)]
matrix[0][17] = 0
matrix[-1][0] = 0

input_matrix = np.array(matrix)
# 模拟实时 input list
input_list = np.zeros(5)

# 将二维矩阵绘制成灰度图
colors = ['white', 'black']
cmap = ListedColormap(colors)

fig, ax = plt.subplots()
img = ax.imshow(input_matrix, cmap=cmap, vmin=0, vmax=1)

# 设置初始标题
ax.set_title('Matrix')

animation = FuncAnimation(fig, update_matrix, frames=range(10), interval=200)
plt.show()

nx,ny,matrix_data = print_matrix()
print(matrix_data)

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
end = (nx-1, 0)

# create shortest possible path
shortest_path = []
while True:
    shortest_path.append(end)
    if end == (0, ny - 1):
        break
    end = Prev[end[0]][end[1]]

# modify path and original maze
for i in range(nx):
    for j in range(ny):
        if g[i][j] == 0 and (i, j) not in shortest_path:
            g[i][j] = 1

new_matrix = []

# create output maze
for i in range(nx):
    row = []
    for j in range(ny):
        row.append(g[i][j] )
    new_matrix.append(row)

array_matrix = np.array(new_matrix)

# Convert array_matrix to string with desired format
new_matrix = np.array2string(array_matrix, separator=', ', formatter={'int': lambda x: str(x)})
np.savetxt('matrix.txt', new_matrix, fmt='%d')

# Plot the second matrix with Greens colormap and reduced alpha
ax.imshow(new_matrix, cmap=cmap0, alpha=0.3)

# Set the title
ax.set_title('Overlay')

plt.show()
