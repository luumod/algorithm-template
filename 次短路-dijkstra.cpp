#include <bits/stdc++.h>
#if 0
    #define int long long
#endif
using ll=long long;

const int N=1e5+10,INF=0x3f3f3f3f,M=1e5+10;
int n,m;
struct Node{
    int to,w,next;
}edge[M<<2];
int head[N],cnt;
int dis[N][2],vis[N];
void add_edge(int u,int v,int w){
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> q;
void dijkstra(int s){
    for (int i=1;i<=n;i++){
        dis[i][0]=dis[i][1]=INF;
    }
    q.push({0,s});
    dis[s][0]=0;  //[0]: 到i的最短路
    while (!q.empty()){
        auto p=q.top();
        q.pop();
        int u=p.second;
        int len=p.first; //根据上一条最短路来更新
        for (int i=head[u];i;i=edge[i].next){
            int v=edge[i].to,w=edge[i].w;
            if (dis[v][0]>len+w){
                //更新最短路与次短路
                dis[v][1]=dis[v][0];
                dis[v][0]=len+w;
                q.push({dis[v][0],v});
            }
            if (dis[v][1]>len+w && dis[v][0]<len+w){
                //更新次短路，不用更新最短路
                dis[v][1]=len+w;
                q.push({dis[v][1],v});
            }
        }
    }
}
signed main(){
    std::cin>>n>>m;
    for (int i=1;i<=m;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dijkstra(1);
    std::cout<< dis[n][1];
    return 0;
}