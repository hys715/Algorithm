#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int head[40005], f[40005], depth[40005], sz[40005], top[40005], cnt;
int belong[100010], tmp[40005], ord[80010], st[40005], ed[40005], num;
int val[40005], ans[100005], counter[40005], n, m, now, u, v;
bool vis[40005];

struct edge {
    int to, next;
} e[80010];

// 访问单元
struct query {
	int l, r, id, lca;
	bool operator<(const query& other) const {
		return (belong[l] ^ belong[other.l]) ? belong[l] < belong[other.l] :
			   (belong[l] & 1) ? r < other.r : r > other.r;
	}
} q[100005];

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

// 深搜，分层，欧拉序
void dfs1(int u) {
	ord[++num] = u, st[u] = num;
    sz[u] = 1;
    depth[u] = depth[f[u]] + 1;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f[u]) {
            f[e[i].to] = u;
            dfs1(e[i].to);
            sz[u] += sz[e[i].to];
        }
	ord[++num] = u, ed[u] = num;
}

// 深搜，找轻重链
void dfs2(int u) {
    int v = 0;
    if (!top[u]) top[u] = u;
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f[u] && sz[e[i].to] > sz[v])
            v = e[i].to;
    if (v) {
        top[v] = top[u];
        dfs2(v);
    }
    for (int i = head[u]; i; i = e[i].next)
        if (e[i].to != f[u] && e[i].to != v)
            dfs2(e[i].to);
}

// 最近公共祖先
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (depth[top[x]] > depth[top[y]]) x = f[top[x]];
        else y = f[top[y]];
    }
    return depth[x] < depth[y] ? x : y;
}

// 区间计数
void calc(int x) {
	vis[x] ? now -= !--counter[val[x]] : now += !counter[val[x]]++;
	vis[x] = !vis[x];
}

// 树上莫队
void MoQue() {
	int size = sqrt(num), bnum = ceil((double)num / size), l = 1, r = 0;
	for (int i = 1; i <= bnum; ++i)
		for (int j = (i - 1) * size + 1; j <= i * size; ++j)
			belong[j] = i;
	sort(q + 1, q + 1 + m);
	for (int i = 1; i <= m; ++i) {
		while (l < q[i].l) calc(ord[l++]);
		while (l > q[i].l) calc(ord[--l]);
		while (r < q[i].r) calc(ord[++r]);
		while (r > q[i].r) calc(ord[r--]);
		if (q[i].lca) calc(q[i].lca);
		ans[q[i].id] = now;
		if (q[i].lca) calc(q[i].lca);
	}
}

int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		val[i] = read(), tmp[i] = val[i];
	sort(tmp + 1, tmp + 1 + n);
	for (int i = 1; i <= n; ++i)
		val[i] = lower_bound(tmp + 1, tmp + 1 + n, val[i]) - tmp;	// 离散化
	for (int i = 1; i < n; ++i) {
		u = read(), v = read();
		add(u, v);
	}

	dfs1(1);
	dfs2(1);

	for (int i = 1; i <= m; ++i) {
		u = read(), v = read();
		if (st[u] > st[v]) swap(u, v);
		q[i].id = i, q[i].lca = lca(u, v);
		if (q[i].lca == u) {
			q[i].l = st[u];
			q[i].r = st[v];
			q[i].lca = 0;
		}
		else {
			q[i].l = ed[u];
			q[i].r = st[v];
		}
	}

	MoQue();
	for (int i = 1; i <= m; ++i)
		write(ans[i]), putchar('\n');
	return 0;
}