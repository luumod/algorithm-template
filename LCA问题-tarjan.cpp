#include <bits/stdc++.h>

const int N = 5e5 + 10;
/*
2. targan算法：深搜，回标记，离查询
*/
int n, m, s;
std::vector<int> vec[N];
std::vector<std::pair<int, int>> query[N];
int parent[N + 10]; //并查集
bool vis[N]; //标记访问
int ans[N]; //答案数组
int find(int now){
    if (now!=parent[now]){
        return parent[now]=find(parent[now]);
    }
    return now;
}
void targan(int now) {
    vis[now] = true;
    for (auto& x : vec[now]) {
        if (!vis[x]) {
            targan(x);
            parent[x] = now; //标记父节点为now
        }
    }
    for (auto& x : query[now]) {
        int to = x.first, i = x.second;
        if (vis[to]) { //必须是已经访问过的点
            ans[i] = find(to); //并查集中查询并且维护
        }
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> s;
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        std::cin >> x >> y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        query[x].push_back({ y,i });
        query[y].push_back({ x,i });
    }
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    targan(s);
    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << '\n';
    }
    return 0;
}