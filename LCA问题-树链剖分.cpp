#include <bits/stdc++.h>
/*
3. 树链剖分
*/
const int N=1e5+10;
int n,m,s;
std::vector<int> vec[N];
int fa[N],son[N],sz[N],top[N],dep[N]; //标记父节点；标记重孩子；标记节点数；标记重链起点；标记当前深度
//1. dfs1求fa dep sz son数组
void dfs1(int now,int father){
    fa[now]=father;
    dep[now]=dep[father]+1;
    sz[now]=1;
    for (auto& x:vec[now]){
        if (x!=father){
            dfs1(x,now);
            sz[now]+=sz[x];
            //确定当前点的重孩子
            if (sz[son[now]]<sz[x]){
                son[now]=x;   
            }
        }
    }
}
//2. dfs2求top数组
void dfs2(int now,int t){
    top[now]=t;
    //回溯：叶子节点没有重孩子
    if (!son[now]){
        return;
    }
    dfs2(son[now],t);
    //遍历轻儿子
    for (auto& x:vec[now]){
        if (x==fa[now] || x==son[now]){
            continue;
        }
        dfs2(x,x); //叶子节点的重链起点为其自身
    }
}
int lca(int x,int y){
    while (top[x]!=top[y]){
        //指定x为较深的那一个，类似于倍增的跳跃
        if (dep[top[x]]<dep[top[y]]){
            std::swap(x,y);
        }
        x=fa[top[x]]; //跳跃到重链起点的父节点位置
    }
    return dep[x]<dep[y]?x:y; //返回深度较小的那一个
}
int main() {
    std::cin >> n >> m >> s;
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    dfs1(s,0);
    dfs2(s,s);
    for (int i = 1; i <= m; i++) {
        int x, y;
        std::cin >> x >> y;
        printf("%d\n",lca(x,y));
    }
    return 0;
}