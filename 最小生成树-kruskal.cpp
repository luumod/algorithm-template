#include "bits/stdc++.h"

using ll=long long;
const int N=5010,INF=0x3f3f3f3f;
int n,m;
ll ans;
int cnt;
struct Node{
    int u,to,w;
    bool operator<(Node& r)const{
        return w<r.w;
    }
};
std::vector<Node> vec(N);
// kruskal算法
int parent[N];
int find(int now){
    if (now!=parent[now]){
        parent[now]=find(parent[now]);
    }
    return parent[now];
}
bool kruskal(){
    for (int i=1;i<=n;i++){
        parent[i]=i; //初始化
    }      
    std::sort(vec.begin(),vec.end());
    for (int i=0;i<vec.size();i++){
        int p1=find(vec[i].u);
        int p2=find(vec[i].to);
        if (p1!=p2){
            parent[p1]=p2; //并查集合并
            ans+=vec[i].w;
            cnt++;
        }
    }
    return cnt==n-1; //n-1条边
}