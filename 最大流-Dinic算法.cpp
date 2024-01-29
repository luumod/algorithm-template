#include <bits/stdc++.h>

#define int long long 
const int N=2e3+10,M=5e3+10;
int n,m,r,t; //点数，边数，起点，汇点
struct Edge{
    int to,c,next; //c为这条边的流量上限
}edge[M<<2];
int head[N],cnt=1; //从2开始
int dep[N],cur[N]; //记录深度 优化剪枝
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
    q.push(r);
    dep[r]=1; //初始化为1dep
    while (!q.empty()){
        auto u=q.front();
        q.pop();
        for (int i=head[u];i;i=edge[i].next){
            int v=edge[i].to,c=edge[i].c;
            if (!dep[v] && c){
                dep[v]=dep[u]+1; //记录图层深度
                q.push(v);
                if (v==t){
                    return true;
                }
            }
        }
    }
    return false;
}
int dfs(int now,int mf){ //mf表示到当前点为止的容量
    if (now==t){//到达汇点
        return mf; 
    }
    int sum=0;
    for (int i=cur[now];i;i=edge[i].next){
        //记录当前最后可以访问的点
        cur[now]=i; //1. 当前弧优化
        int v=edge[i].to;
        if (dep[v]==dep[now]+1 && edge[i].c){ //满足到达下一层的条件
            int val=dfs(v,std::min(mf,edge[i].c)); //在当前实际流量和上限容量中取最小值
            //回溯
            edge[i].c-=val; //正向边减小
            edge[i^1].c+=val; //反向边增加
            sum+=val; //累加容量
            mf-=val;  //上限流量减小 
            if (mf==0){ //2. 余量优化：上限流量为0，则当前点上一条路就断了，直接退出
                break; 
            }
        }
    }
    //离开
    if (sum==0){ //3. 残枝优化
        dep[now]=0; //这个点永远不会访问了，不会经过这个点之后的路径了
    }
    return sum;
}   
void getAns(){
    while (bfs()){
        memcpy(cur,head,sizeof(head));
        ans+=dfs(r,1e9); //进入时传入一个极大值
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
    getAns();
    std::cout<<ans;
    return 0;
}