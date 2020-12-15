#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int belong[110000], a[100100], v[100100], t[100100], cnt[100100], cnt2[100100], rb[100100], n, m;
long long ans[100100];

// 访问单元
struct query {
    int l, r, id;
    bool operator<(const query& other) const {
        return belong[l] ^ belong[other.l] ? belong[l] < belong[other.l] : r < other.r;
    }
} q[100100];

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
void write(long long x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

// 回滚莫队
void MoQue() {
    // 分块
    int size = sqrt(n), bnum = ceil((double)n / size);
    for (int i = 1; i <= bnum; ++i) {
        rb[i] = i * size;   // 记录快右端
        for (int j = (i - 1) * size + 1; j <= rb[i]; ++j)
            belong[j] = i;
    }
    rb[bnum] = n;
    sort(q + 1, q + 1 + m);
    int i = 1;
    for (int k = 0; k <= bnum; ++k) {
        int l = rb[k] + 1, r = rb[k];   // 预处理
        long long now = 0;
        memset(cnt, 0, sizeof(cnt));
        for (; belong[q[i].l] == k; ++i) {
            long long tmp;
            if (belong[q[i].l] == belong[q[i].r]) { // 同一块，暴力
                tmp = 0;
                for (int j = q[i].l; j <= q[i].r; ++j)
                    cnt2[v[j]] = 0;
                for (int j = q[i].l; j <= q[i].r; ++j) {
                    ++cnt2[v[j]];
                    tmp = max(tmp, (long long)a[j] * cnt2[v[j]]);
                }
                ans[q[i].id] = tmp;
                continue;
            }
            while (r < q[i].r) {
                ++cnt[v[++r]];
                now = max(now, (long long)a[r] * cnt[v[r]]);
            }
            tmp = now;
            while (l > q[i].l) {    // 回滚
                ++cnt[v[--l]];
                now = max(now, (long long)a[l] * cnt[v[l]]);
            }
            ans[q[i].id] = now;
            while (l < rb[k] + 1) --cnt[v[l++]];
            now = tmp;  // 回滚
        }
    }
}

int main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        t[i] = a[i] = read();
    sort(t + 1, t + 1 + n);
    for (int i = 1; i <= n; ++i)
        v[i] = lower_bound(t + 1, t + 1 + n, a[i]) - t;
    for (int i = 1; i <= m; ++i) {
        q[i].l = read(), q[i].r = read();
        q[i].id = i;
    }

    MoQue();
    for (int i = 1; i <= m; ++i)
		write(ans[i]), putchar('\n');
	return 0;
}