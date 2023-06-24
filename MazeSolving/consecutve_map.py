import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from collections import deque
from matplotlib.animation import FuncAnimation

dx = [-1, 0, 1, 0, -1, 1, -1, 1]
dy = [0, 1, 0, -1, -1, -1, 1, 1]
DIS = [(0, -1), (-1, 0), (0, 1)]



def update_matrix(frame):
    global count  # 使用 global 声明 count 是全局变量

    # 前两个值在 0 到 5 之间随机生成
    input_list[:2] = np.random.uniform(0, 5, size=2)

    # 后三个值在 0 到 2 之间随机生成
    input_list[2:] = np.random.uniform(0, 2, size=3)

    # 更新矩阵并更新灰度图
    rx = input_list[0]
    ry = input_list[1]
    i = 2
    for (dx, dy) in DIS:
        new_x, new_y = int(rx + dx), int(ry + dy)
        if new_y < 0:
            new_y = 0
        elif new_y >= input_matrix.shape[1]:
            new_y = input_matrix.shape[1] - 1
        input_matrix[new_x, new_y] = input_list[i]  # 更新矩阵数据
        i = i + 1

    img.set_array(input_matrix)  # 更新灰度图像数据

    count += 1  # 更新计数器
    if count >= 5:  # 达到 5 个 input_list 后停止循环
        animation.event_source.stop()  # 停止动画循环
        output_matrix = input_matrix.copy()
    
    return output_matrix
        

def bfs():
    queue = deque()
    d = [[-1] * n for _ in range(n)]
    Prev = [[None] * n for _ in range(n)]
    d[n-1][n-1] = 0
    queue.append((n-1, n-1))

    while queue:
        t = queue.popleft()
        for i in range(8):
            x = t[0] + dx[i]
            y = t[1] + dy[i]
            if 0 <= x < n and 0 <= y < n and g[x][y] == 0 and d[x][y] == -1:
                d[x][y] = d[t[0]][t[1]] + 1
                Prev[x][y] = t
                queue.append((x, y))

    return Prev

#n = int(input())



count = 0
# 创建初始二维矩阵
input_matrix = np.array([[0, 1, 1, 1, 0],
                         [0, 0, 1, 0, 1],
                         [0, 1, 0, 0, 1],
                         [0, 0, 0, 0, 1],
                         [1, 1, 0, 1, 0]])

# 模拟实时 input list
input_list = np.zeros(5)

# 将二维矩阵绘制成灰度图
colors = ['grey', 'white']
cmap = ListedColormap(colors)

fig, ax = plt.subplots()
img = ax.imshow(input_matrix, cmap=cmap, vmin=0, vmax=1)

# 设置初始标题
ax.set_title('Matrix')

# Display the plot    
animation = FuncAnimation(fig, update_matrix, frames=range(10), interval=1000)


n = int(np.array(update_matrix))
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
    shortest_path.append(end)
    if end == (n-1, n-1):
        break
    end = Prev[end[0]][end[1]]

for i in range(n):
    for j in range(n):
        if g[i][j] == 0 and (i, j) not in shortest_path:
            g[i][j] = 1

new_matrix = []

for i in range(n):
    row = []
    for j in range(n):
        row.append(g[i][j])
    new_matrix.append(row) 



    


plt.show()

np.savetxt('final_matrix.txt', input_matrix, fmt='%d')

# 读取文件内容并以所需的格式打印
with open('final_matrix.txt', 'r') as f:
    matrix_data = f.readlines()

# 打印矩阵内容，去掉括号和逗号
print(len(matrix_data))

# 打印矩阵内容，保留空格并按照所需的格式进行格式化
for row in matrix_data:
    row = row.strip()
    row = ''.join(row)  # 将列表元素用空格连接成字符串
    print(row)
