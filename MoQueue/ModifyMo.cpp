#include <cstdio>
#include <cmath>
#include <algorithm>
using std::sort;
using std::swap;

int n, m, qcnt, pcnt, block[150000], col[150000], cnt[1000010], ans[150000];

// 访问单元
struct query {
	int l, r, t, id;
	bool operator<(const query& other) const {
		return (block[l] ^ block[other.l]) ? block[l] < block[other.l] :
			   (block[r] ^ block[other.r]) ? block[r] < block[other.r] :
			   t < other.t;
	}
} q[150000];

// 修改单元
struct modify {
	int pos, col;
} p[150000];

// 快读
inline int read() {
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ '0');
		c = getchar();
	}
	return x;
}

// 快写
void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

// 带修莫队
void MoQue() {
	int size = pow(n, 2.0 / 3.0);
	int bnum = ceil((double)n / size);
	for (int i = 1; i <= bnum; ++i) // 分块
		for (int j = (i - 1) * size + 1; j <= i * size; ++j)
			block[j] = i;
	sort(q + 1, q + 1 + qcnt);  // 排序
	int l = 1, r = 0, t = 0, now = 0;
	for (int i = 1; i <= qcnt; ++i) {
        // 修改区间
		while (l < q[i].l) now -= !--cnt[col[l++]];
		while (r > q[i].r) now -= !--cnt[col[r--]];
		while (l > q[i].l) now += !cnt[col[--l]]++;
		while (r < q[i].r) now += !cnt[col[++r]]++;
        // 更正修改
		while (t < q[i].t) {
			++t;
			if (l <= p[t].pos && p[t].pos <= r)
				now -= !--cnt[col[p[t].pos]] - !cnt[p[t].col]++;
			swap(col[p[t].pos], p[t].col);
		}
		while (t > q[i].t) {
			if (l <= p[t].pos && p[t].pos <= r)
				now -= !--cnt[col[p[t].pos]] - !cnt[p[t].col]++;
			swap(col[p[t].pos], p[t].col);
			--t;
		}
		ans[q[i].id] = now; // 结果
	}
}

int main() {
    // n个单元，m次操作
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) col[i] = read();
	char c;
	for (int i = 1; i <= m; ++i) {
		scanf(" %c", &c);
		if (c == 'Q') { // 访问
			q[++qcnt].l = read();
			q[qcnt].r = read();
			q[qcnt].t = pcnt;
			q[qcnt].id = qcnt;
		}
		else {  // 修改
			p[++pcnt].pos = read();
			p[pcnt].col = read();
		}
	}
	MoQue();
	for (int i = 1; i <= qcnt; ++i) {
		write(ans[i]);
		putchar('\n');
	}
	return 0;
}