#include <bits/stdc++.h>

#define int long long 
const int N=1e5+10;
struct Edge{
    int to,next;
}edge[N<<1];
int head[N<<1],cnt=1; //双向边从1开始
int n,vis[N];
int r1,r2,visEdge[N<<1]; //分别表示环中的两个点及其对应边
double w[N],k;
double dp[N][2];
void add_edge(int u,int v){
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
//基环树
//1. 断环为树，进行深搜
bool dfs(int now,int in_edge){
    vis[now]=true;
    for (int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if (i==(in_edge^1)){ //不能走反边
            continue;
        }
        if (!vis[v]){ 
            if (dfs(v,i)){ 
                return true; //已经找到环了
            }
        }
        else{
            //绕了一个圈，然后访问到了已经标记过的now，证明是一个环
            r1=now,r2=v,visEdge[i]=1,visEdge[i^1]=1; //记录这个环的边是一个断边
            return true;
        }
    }
    return false;
}
//2. 在树上做树形dp，选择或者不选某个节点
double dfs2(int now,int in_edge){
    vis[now]=true; //必须要这个
    dp[now][0]=0,dp[now][1]=w[now]*k; //now选择或者不选
    for (int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if (i==(in_edge^1) || visEdge[i]){ //不能走反边或者是断环边
            continue;
        }
        dfs2(v,i);
        dp[now][0]+=std::max(dp[v][1],dp[v][0]);
        dp[now][1]+=dp[v][0]; 
    }
    return dp[now][0]; //不选这个节点
}
signed main(){ 
    std::cin>>n;
    for (int i=1;i<=n;i++){
        std::cin>>w[i];
    }
    for (int i=1;i<=n;i++){
        int u,v;
        std::cin>>u>>v;
        u+=1,v+=1;  //让节点号从1开始
        //双向边
        add_edge(u,v);
        add_edge(v,u);
    }
    std::cin>>k;
    double ans=0;
    for (int i=1;i<=n;i++){
        if (!vis[i]){
            r1=r2=0;
            dfs(i,0);
            if (r1 && r2){
                ans+=std::max(dfs2(r1,0),dfs2(r2,0));
            }
        }
    }
    printf("%.1lf\n",ans);
    return 0;
}