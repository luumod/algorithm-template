#include <bits/stdc++.h>

const int N = 5e5 + 10;
/*
1. 倍增算法：深搜打表 跳跃查询
*/
int n, m, s;
std::vector<int> vec[N];
int depth[N], fa[N][25];
void init(int now, int father) {
    depth[now] = depth[father] + 1;
    fa[now][0] = father;
    for (int i = 1; i <= 20; i++) {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    }
    for (auto& x : vec[now]) {
        if (x != father) {
            init(x, now);
        }
    }
}
int lca(int x, int y) {
    //让x的深度最大
    if (depth[x] < depth[y]) {
        std::swap(x, y);
    }
    for (int i = 20; i >= 0; i--) {
        if (depth[fa[x][i]] >= depth[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) {
        return x;
    }
    for (int i = 20; i >= 0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i], y = fa[y][i];
        }
    }
    return fa[x][0];
}

int main() {
    std::cin >> n >> m >> s;
    vec[0].push_back(s);
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    init(s, 0);
    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        printf("%d\n", lca(x, y));
    }
    return 0;
}
