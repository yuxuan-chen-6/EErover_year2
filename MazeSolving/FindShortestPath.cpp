#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
#define x first
#define y second
typedef pair<int, int> PII;

const int N = 1010;

int n, m;
int g[N][N], d[N][N];
PII Prev[N][N];

void bfs()
{
    queue<PII> q;

    memset(d, -1, sizeof d);
    d[n - 1][n - 1] = 0;
    q.push({n - 1, n - 1});

    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int x = t.first + dx[i], y = t.second + dy[i];

            if (x >= 0 && x < n && y >= 0 && y < n && g[x][y] == 0 && d[x][y] == -1)
            {
                d[x][y] = d[t.first][t.second] + 1;
                Prev[x][y] = t;
                q.push({x, y});
            }
        }
    }
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    bfs();
    PII end(0, 0); 

    // while (true)
    // {
    //     printf("%d %d\n", end.x, end.y);

    //     // 将最短路径上的坐标的值设置为0
    //     g[end.x][end.y] = 0;

    //     if (end.x == n-1 && end.y == n-1)
    //         break; // 修改终止条件为 (0, 0)

    //     end = Prev[end.x][end.y];
    // }

    // // 将整个矩阵 g 的元素修改为1，除了最短路径上的坐标为0
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (g[i][j] != 0) {
    //             g[i][j] = 1;
    //         }
    //     }
    // }

    vector<PII> shortestPath; // 存储最短路径的坐标

    while (true)
    {
        printf("%d %d\n", end.x, end.y);

        shortestPath.push_back(end); // 将坐标加入到最短路径中

        // 如果到达终点，则退出循环
        if (end.x ==n-1 && end.y == n-1)
            break;

        // 更新当前位置为上一个位置
        end = Prev[end.x][end.y];
    }

    // 将整个矩阵 g 的元素修改为1，除了最短路径上的坐标为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 0 && find(shortestPath.begin(), shortestPath.end(), make_pair(i, j)) == shortestPath.end()) {
                g[i][j] = 1;
            }
        }
    }


    printf("Modified Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }

    return 0;
}
