#include <bits/stdc++.h>

const int N=1e4+10;
int n;
struct Node{
    int to,w,next;
}edge[N]; //!
int head[N],cnt;
std::vector<bool> vis(N);
std::vector<int> d1(N),d2(N),up(N); //下行最长路径,次长路径,上行最长路径
std::vector<int> p1(N);     //记录下行路径最长的一条所经过的点
void add_edge(int u,int v,int w){
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
//第一次dfs: 求下行最长路径
int dfs_down(int now){
    vis[now]=true;
    d1[now]=d2[now]=0;
    for (int j=head[now];j;j=edge[j].next){
        int to=edge[j].to;
        if (!vis[to]){
            int len=dfs_down(to)+edge[j].w;
            if (len>=d1[now]){
                d2[now]=d1[now],d1[now]=len,p1[now]=to;
            }
            else{
                d2[now]=len;
            }
        }
    }
    return d1[now]; //返回当前点的最长下行路径
}
//第二次dfs: 求上行最长路径
void dfs_up(int now){
    vis[now]=true;
    //由根节点更新到叶子节点
    for (int j=head[now];j;j=edge[j].next){
        int to=edge[j].to;
        if (!vis[to]){
            if (p1[now]==to){
                up[to]=edge[j].w+std::max(up[now],d2[now]);
            }
            else{
                up[to]=edge[j].w+std::max(d1[now],up[now]);
            }
            dfs_up(to);
        }
    }
}
int main(){
    std::cin>>n;
    for (int i=1;i<n;i++){
        int x,y,w;
        std::cin>>x>>y>>w;
        add_edge(x,y,w);
        add_edge(y,x,w);
    }
    dfs_down(1); //p1: 2 3 4
    std::fill(vis.begin(),vis.end(),0);
    dfs_up(1);
    for (int i=1;i<=n;i++){
        std::cout<<up[i]<<' '<<d1[i]<<'\n';
    }
    int ans=1e9;
    for (int i=1;i<=n;i++){
        /*
        树的中心：这个节点到其他点的最远距离最小
        经过我们down和up分别求某点的 上升最大路径和下降最大路径 之后: up和d1数组
        std::max(up[i],d1[i])求路径最大值，min(std::max(up[i],d1[i]))求的就是最远距离的最小值，即树的中心
        */
        ans=std::min(ans,std::max(up[i],d1[i]));
    }
    //树的中心是2，到其他点的最远距离是2
    std::cout<<ans;
	return 0;
}