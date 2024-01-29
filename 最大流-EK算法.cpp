#include <bits/stdc++.h>
#define int long long 
const int N=2e3+10,M=5e3+10;
int n,m,r,t; //点数，边数，起点，汇点
struct Edge{
    int to,c,next; //c为这条边的流量上限
}edge[M<<2];
int head[M<<2],cnt=1; //从2开始
int mf[N],pre[N]; //mf表示到当前点为止的流量 pre记录！！！！前驱边！！！！！
int ans=0;
void add_edge(int u,int v,int c){
    edge[++cnt].to=v;
    edge[cnt].c=c;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
bool bfs(){
    memset(mf,0,sizeof(mf));
    std::queue<int> q;
    q.push(r);
    mf[r]=1e9;
    while (!q.empty()){
        auto u=q.front();
        q.pop();
        for (int i=head[u];i;i=edge[i].next){
            int v=edge[i].to,c=edge[i].c; 
            if (!mf[v] && c){ //如果当前点没有访问过并且还能流，那么就流
                mf[v]=std::min(mf[u],c); //记录最大流量：在当前的实际流量和最大流量上限取最小值
                pre[v]=i; //记录前驱边！！！！！
                q.push(v); //入队
                if (v==t){ //到达终点
                    return true;
                }
            }
        }   
    }
    return false;
}
void EK(){
    while (bfs()){
        int v=t; //从汇点回溯
        while (v!=r){
            int i=pre[v]; //i是当前点的前驱边
            edge[i].c-=mf[t];  //正向边减小
            edge[i^1].c+=mf[t];//反向边增加
            v=edge[i^1].to; //回到上一点
        }
        ans+=mf[t]; //累加这条路的最大流
    }
}
signed main(){
    std::cin>>n>>m>>r>>t;
    for (int i=1;i<=m;i++){
        int u,v,c;
        std::cin>>u>>v>>c;
        add_edge(u,v,c); //有向边
        add_edge(v,u,0); //容量为0的反向边 
    }
    EK();
    std::cout<<ans;
    return 0;
}