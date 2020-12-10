#include <cstdio>
#include <cmath>
#include <algorithm>
using std::sort;

int n, m, a[1000010], belong[1000010], cnt[1000010], ans[1000010];

// 访问单元
struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        return (belong[id] ^ belong[other.id]) ? belong[id] < belong[other.id] : 
               (belong[id] & 1) ? r < other.r : r > other.r;
    }
} q[1000010];

// 快读
inline int read() {
    int num = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        num = (num << 3) + (num << 1) + (ch ^ '0');
        ch = getchar();
    }
    return num;
}

// 快写
inline void write(int x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

// 普通莫队
inline void MoQue() {
    int l = 1, r = 0, now = 0;
    int size = sqrt(n), bnum = ceil((double)n / size);
    for (int i = 1; i <= bnum; ++i) // 分块
        for (int j = (i - 1) * size + 1; j <= i * size; ++j)
            belong[j] = i;
    sort(q + 1, q + 1 + m); // 排序
    for (int i = 1; i <= m; ++i) {
        // 更新区间
        while (l < q[i].l) now -= !--cnt[a[l++]];
        while (r > q[i].r) now -= !--cnt[a[r--]];
        while (l > q[i].l) now += !cnt[a[--l]]++;
        while (r < q[i].r) now += !cnt[a[++r]]++;
        ans[q[i].id] = now; // 结果
    }
}

int main() {
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    m = read();
    for (int i = 1; i <= m; ++i)
        q[i].l = read(), q[i].r = read(), q[i].id = i;
    MoQue();
    for (int i = 1; i <= m; ++i) {
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}