#include <cstdio>
#include <cstring>
#define swap(a, b) a = a ^ b, b = a ^ b, a = a ^ b

struct edge {
	int v, next;
} e[1000002];

int head[500002], depth[500002], f[500002][21], cnt = 1;

// 加边
void add(int u, int v) {
	e[cnt].v = v, e[cnt].next = head[u];
	head[u] = cnt++;
}

// 深搜，记录祖先
void dfs(int child, int parent) {
	f[child][0] = parent, depth[child] = depth[parent] + 1;
	for (int i = 1; (1 << i) <= depth[child]; ++i)
		f[child][i] = f[f[child][i - 1]][i - 1];
	for (int i = head[child]; i; i = e[i].next)
		if (e[i].v != parent)
			dfs(e[i].v, child);
}

// 查找最近公共祖先
int lca(int a, int b) {
	if (depth[a] < depth[b])
		swap(a, b);
	int d = depth[a] - depth[b];
	for (int i = 0; (1 << i) <= d; ++i)
		if ((1 << i) & d)
			a = f[a][i];
	if (a == b)
		return a;
	for (int i = 20; i >= 0; --i)
		if (f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}

int main() {
	int n, m, s, x, y;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i < n; ++i) {
		scanf("%d %d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(s, 0);
	while (m--) {
		scanf("%d %d", &x, &y);
		printf("%d\n", lca(x, y));
	}
	return 0;
}