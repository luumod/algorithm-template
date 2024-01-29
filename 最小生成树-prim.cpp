#include "bits/stdc++.h"

using ll=long long;
const int N=5010,INF=0x3f3f3f3f;
//prim 朴素版
struct Node{
    int to,w;
};
std::vector<Node> vec[N];
int n,m,s=1,d[N],vis[N],cnt;
std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> q;
ll ans;
//1. 暴力朴素prim算法
bool Prim1(){
    for (int i=0;i<=n;i++){
        d[i]=INF;
    }   
    d[s]=0; //标记起始点
    for (int i=1;i<=n;i++){
        int u=0;
        for (int j=1;j<=n;j++){
            //在未出圈的点中寻找距离最小的点
            if (!vis[j] && d[j]<d[u]){
                u=j;
            }
        }
        vis[u]=true; //标记出圈，即组成了最小生成树
        ans+=d[u]; //累加权值
        if (d[u]!=INF){
            cnt++;
        }
        for (auto &x:vec[u]){
            int to=x.to,w=x.w;
            if (d[to]>w){ //更新这个点在圈中的最小权值
                d[to]=w;
            }
        }
    }
    return cnt==n;
}
//2. 堆优化prim算法
bool Prim2(){
    for (int i=0;i<=n;i++){
        d[i]=INF;
    }
    q.push({0,s});
    d[s]=0;
    while (!q.empty()){
        auto p=q.top();
        q.pop();
        int u=p.second;
        if (vis[u]){
            continue; //这个点已经被松弛过了
        }
        vis[u]=true;
        ans+=p.first; //累加权值
        cnt++;
        for (auto& x:vec[u]){
            int to=x.to,w=x.w;
            if (d[to]>w){
                d[to]=w;
                q.push({d[to],to}); //入队
            }
        }
    }
    return cnt==n;
}