#include <cstdio>

struct edge {
    int to, next;
} e[1000010];

int head[500005], f[500005], depth[500005], size[500005], top[500005], cnt;

// 加边
void add(int u, int v) {
    e[++cnt] = edge{v, head[u]}, head[u] = cnt;
    e[++cnt] = edge{u, head[v]}, head[v] = cnt;
}

// 快读
int read() {
    int x = 0;
    bool flag = false;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') flag = true;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ '0');
        ch = getchar();
    }
    return flag ? -x : x;
}

// 快输
void write(int x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

// 深搜，分层
void dfs1(int u) {
    size[u] = 1;
    depth[u] = depth[f[u]] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f[u]) {
            f[e[i].to] = u;
            dfs1(e[i].to);
            size[u] += size[e[i].to];
        }
}

// 深搜，找轻重链
void dfs2(int u) {
    int v = 0;
    if (!top[u]) top[u] = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f[u] && size[e[i].to] > size[v])
            v = e[i].to;
    if (v) {
        top[v] = top[u];
        dfs2(v);
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f[u] && e[i].to != v)
            dfs2(e[i].to);
}

// 查找最近公共祖先
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (depth[top[x]] > depth[top[y]]) x = f[top[x]];
        else y = f[top[y]];
    }
    return depth[x] < depth[y] ? x : y;
}

int main() {
    int n, m, s, u, v;
    n = read(), m = read(), s = read();
    for (int i = 1; i < n; ++i) {
        u = read(), v = read();
        add(u, v);
    }
    dfs1(s);
    dfs2(s);
    for (int i = 1; i <= m; ++i) {
        u = read(), v = read();
        write(lca(u, v));
        putchar('\n');
    }
    return 0;
}