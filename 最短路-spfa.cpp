#include "bits/stdc++.h"

/*
2. spfa算法
*/
using ll=long long;
const int N=2e3+10,INF=0x3f3f3f3f;
struct Node{
    int to,w;
};
std::vector<Node> vec[N];
ll dis[N];
int vis[N],cnt[N];
int n,m,s=1;
std::queue<int> q;
bool spfa(){
    for (int i=1;i<=n;i++){
        dis[i]=INF;
    }
    dis[s]=0;
    q.push(s);
    vis[s]=true;
    while (!q.empty()){
        auto u=q.front();
        q.pop();
        vis[u]=false; //消除当前标记
        for (auto& x:vec[u]){
            int v=x.to,w=x.w;
            if (dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                //记录松弛次数
                cnt[v]=cnt[u]+1;
                if (cnt[v]>=n){
                    //松弛超过了n次，则说明存在负环
                    return true;
                }
                if (!vis[v]){//进入队列并且标记为true
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return false;
}