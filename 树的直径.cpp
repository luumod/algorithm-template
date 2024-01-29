#include <bits/stdc++.h>

const int N=3e3+10,M=N;
struct Node{
    int to,next,w; 
}edge[M];
int n;
int head[M],cnt=1;
int d1[N],d2[N],vis[N];
int ans; //直径长度
void add_edge(int u,int v,int w){
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
/*
求树的直径：某节点的最大长度+次大长度
*/
int dfs(int now){
    vis[now]=true; //标记点被搜过
    int d1=0;
    int d2=0;
    for (int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if (!vis[v]){
            int sum=dfs(v)+edge[i].w;
            if (sum>=d1){
                d2=d1,d1=sum;
            }
            else if (sum>d2){
                d2=sum;
            }
        }
    }
    ans=std::max(ans,d1+d2);
    return d1; //返回最大长度
}
int main(){
    std::cin>>n;
    for (int i=1;i<n;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dfs(1); //任意取一个点开始深搜
    std::cout<<ans;
    return 0;
}