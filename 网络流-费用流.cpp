#include <bits/stdc++.h>
#define int long long
const int N=5e3+10,M=5e4+10;
struct Node{
    int to,next,c,p; 
}edge[M<<2];
int head[M],cnt=1;
int n,m,s,t;
int mf[N],vis[N],dis[N],pre[M];
int ans,cost;
void add_edge(int u,int v,int c,int p){
    edge[++cnt].to=v;
    edge[cnt].c=c;
    edge[cnt].p=p;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
bool bfs(){ 
    memset(mf,0,sizeof(mf));
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    std::queue<int> q;
    q.push(s);
    mf[s]=1e9;
    dis[s]=0;
    vis[s]=true;
    while (!q.empty()){
        auto u=q.front();
        q.pop();
        vis[u]=false;
        for (int i=head[u];i;i=edge[i].next){
            int v=edge[i].to,c=edge[i].c,d=edge[i].p;
            if (dis[v]>dis[u]+d && c){
                dis[v]=dis[u]+d;
                mf[v]=std::min(mf[u],c);
                pre[v]=i; //记录前驱边
                if (!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
    return mf[t]>0; //true表示存在可行流能够到达t
}
void EK(){
    while (bfs()){
        for (int v=t;v!=s;){
            int i=pre[v]; //i对应前驱边
            edge[i].c-=mf[t];
            edge[i^1].c+=mf[t];
            v=edge[i^1].to;
        }
        ans+=mf[t]; //累加最大流
        cost+=mf[t]*dis[t]; //累加费用
    }
}
signed main(){
    std::cin>>n>>m>>s>>t;
    for (int i=1;i<=m;i++){
        int a,b,c,d;
        std::cin>>a>>b>>c>>d;
        add_edge(a,b,c,d);
        add_edge(b,a,0,-d); //-d的目的是退费
    }   
    EK();
    std::cout<<ans<<' '<<cost<<'\n';
    return 0;
}