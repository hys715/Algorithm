#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long LL;

// 顶点数n，边数m，源点s，汇点t，深度depth
int head[210], depth[210], cnt = 1, n, m, s, t;

// 前向星
struct edge {
    int to, next;
    LL w;
} e[10010];

void add(int u, int v, LL w) {
    e[++cnt].to = v, e[cnt].w = w, e[cnt].next = head[u];   // 添加正向边
    head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = 0, e[cnt].next = head[v];   // 添加反向边
    head[v] = cnt;
}

// 广搜分层
bool bfs() {
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    depth[s] = 1;   // 源点层数为1
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            if (e[i].w && !depth[v]) {  // v点可达且未访问
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }
    return depth[t];    // t是否可达
}

// 深搜，增广路径
LL dfs(int u, LL in) {
    if (u == t) return in;
    LL ans = 0;
    for (int i = head[u]; i && in; i = e[i].next) {
        int v = e[i].to;    // 下一层顶点
        if (e[i].w && depth[v] == depth[u] + 1) {
            int k = dfs(v, min(in, e[i].w));
            e[i].w -= k;    // 正向边减少容量
            e[i ^ 1].w += k;    // 反向边增加容量
            in -= k;    // 流入量减少
            ans += k;   // 可流量增加
        }
    }
    if (ans == 0) depth[u] = 0; // 此路不通
    return ans;
}

int main() {
    int u, v;
    LL w, ans = 0;
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    // 如果有增广路径，就搜索
    while (bfs()) ans += dfs(s, 1e18);
    cout << ans << endl;
    return 0;
}