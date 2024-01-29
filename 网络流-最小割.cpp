#include <bits/stdc++.h>
#define int long long
const int N=1e4,M=2e4+10;
struct Node{
    int to,next,c;
}edge[M];
int U[N],V[N];
int head[M],cur[M],cnt=1;
int dep[N];
int n,m;
int ans=0;
void add_edge(int u,int v,int c){
    edge[++cnt].to=v;
    edge[cnt].c=c;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
bool bfs(){
    memset(dep,0,sizeof(dep));
    std::queue<int> q;
    q.push(1);
    dep[1]=1;
    while (!q.empty()){
        auto u=q.front();
        q.pop();
        for (int i=head[u];i;i=edge[i].next){
            int v=edge[i].to;
            if (!dep[v] && edge[i].c){
                dep[v]=dep[u]+1;
                q.push(v);
                if (v==n){
                    return true;
                }
            }
        }
    }
    return false;
}
int dfs(int now,int mf){
    if (now==n){
        return mf;
    }
    int sum=0;
    for (int i=cur[now];i;i=edge[i].next){
        cur[now]=i; //当前弧优化
        int v=edge[i].to;
        if (dep[v]==dep[now]+1 && edge[i].c){
            int val=dfs(v,std::min(edge[i].c,mf));
            edge[i].c-=val;
            edge[i^1].c+=val;
            sum+=val;
            mf-=val;
            if (!mf){ //余量优化 
                break; 
            } 
        }
    }
    if (sum==0){
        dep[now]=0;
    }
    return sum;
}
void Dinic(){
    while (bfs()){
        memcpy(cur,head,sizeof(head));
        ans+=dfs(1,1e9);
    }
}
signed main(){
    std::cin>>n>>m;
    for (int i=1;i<=m;i++){
        int u,v,c;
        std::cin>>U[i]>>V[i]>>c;
        add_edge(U[i],V[i],c);
        add_edge(V[i],U[i],0);
    }
    Dinic();
    std::cout<<ans<<' '; //最大流
    //最小割的数量
    memset(head,0,sizeof(head));
    cnt=1;
    for (int i=1;i<=m;i++){
        add_edge(U[i],V[i],1);
        add_edge(V[i],U[i],0);
    }
    ans=0;
    Dinic();
    std::cout<<ans<<'\n';
    return 0;
}