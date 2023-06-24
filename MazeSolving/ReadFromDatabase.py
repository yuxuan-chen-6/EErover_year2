import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from collections import deque
from matplotlib.animation import FuncAnimation
from scipy.optimize import fsolve
import math
import mysql.connector

cnx = mysql.connector.connect(
    host='3.95.210.12',
    user='ethanchen',
    password='cyx',
    database='Persondb'
)


dx = [-1, 0, 1, 0, -1, 1, -1, 1]
dy = [0, 1, 0, -1, -1, -1, 1, 1]

DIS = [(0, -1), (-1, 0), (0, 1)]

<<<<<<< HEAD:MazeSolving/ReadFromDatabase.py
=======
def process_input():
    file_path = 'matrix.txt'  # 文件路径
>>>>>>> 63fafb2 (done):MazeSolving/ReadFromFile.py

cursor = cnx.cursor()

query = "SELECT Dif1, Dif2 FROM Angle WHERE ID = 1"
cursor.execute(query)

result = cursor.fetchone()
dif1_value = result[0]
dif2_value = result[1]

print("Dif1:", dif1_value)
print("Dif2:", dif2_value)

cursor.close()
cnx.close()

def update_matrix(frame):
    try:
        rx = x
        ry = y  

        if 0 <= rx < len(input_matrix) and 0 <= ry < len(input_matrix[0]):
            input_matrix[rx, ry] = 0
            img.set_array(input_matrix)
        else:
            print(f"Warning: Coordinate ({rx}, {ry}) out of bounds.")
    except Exception as e:
        print(f"Warning: Unable to parse coordinates: ({x}, {y}). Error: {str(e)}")

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
    d[nx - 1][ny - 1] = 0
    queue.append((nx - 1, ny - 1))

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


def equations(vars, m, n, alpha, beta):
    x, y = vars
    eq1 = n**2 - (m - y)**2 - x**2 - (m - y)**2 - (n - x)**2 + 2 * np.sqrt((m - y)**2 + x**2) * np.sqrt((m - y)**2 + (n - x)**2) * np.cos(beta)
    eq2 = m**2 - x**2 - y**2 - x**2 - (m - y)**2 + 2 * np.sqrt(x**2 + y**2) * np.sqrt(x**2 + (m - y)**2) * np.cos(alpha)
    return [eq1, eq2]

m = 27
n = 18
alpha = dif1_value #读取左下角beacon和左上角的夹角
beta = dif2_value #读取左上角和右上角

initial_guess = [0, 0]  
x, y = fsolve(equations, initial_guess, args=(m, n, np.deg2rad(alpha), np.deg2rad(beta)))

x=round(x)
y=26-round(y)

rows = 27
columns = 18

matrix = [[1] * columns for _ in range(rows)]
matrix[0][0] = 0
matrix[-1][-1] = 0

input_matrix = np.array(matrix)
print(type(input_matrix))
input_list = np.zeros(5)

colors = ['white', 'black']
cmap = ListedColormap(colors)

fig, ax = plt.subplots()
img = ax.imshow(input_matrix, cmap=cmap, vmin=0, vmax=1)

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
    
colors = ['green', 'white']
cmap0 = ListedColormap(colors)

fig, ax = plt.subplots()

ax.imshow(g, cmap='binary', vmin=0, vmax=1)      

Prev = bfs()
end = (0, 0)

shortest_path = []
while True:
    shortest_path.append(end)
    if end == (nx - 1, ny - 1):
        break
    end = Prev[end[0]][end[1]]

for i in range(nx):
    for j in range(ny):
        if g[i][j] == 0 and (i, j) not in shortest_path:
            g[i][j] = 1

new_matrix = []

# create output maze
import numpy as np

new_matrix = []

# create output maze
for i in range(nx):
    row = []
    for j in range(ny):
        row.append(g[i][j] )
    new_matrix.append(row)

array_matrix = np.array(new_matrix)
<<<<<<< HEAD:MazeSolving/ReadFromDatabase.py
#np.savetxt('D:/new_matrix.txt', new_matrix, fmt='%d')
=======

# Convert array_matrix to string with desired format
new_matrix = np.array2string(array_matrix, separator=', ', formatter={'int': lambda x: str(x)})
np.savetxt('matrix.txt', new_matrix, fmt='%d')
>>>>>>> 63fafb2 (done):MazeSolving/ReadFromFile.py

# Convert array_matrix to string with desired format
new_matrix = np.array2string(array_matrix, separator=', ', formatter={'int': lambda x: str(x)})
np.savetxt('matrix.txt', new_matrix, fmt='%d')

ax.imshow(new_matrix, cmap=cmap0, alpha=0.3)

ax.set_title('Overlay')

plt.show()
