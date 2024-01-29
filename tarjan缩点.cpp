#include <bits/stdc++.h>

const int N=1e4+10;
int n,m;
int val[N];

//缩点需要用到的变量
std::vector<int> vec[N]; //题目告诉你了是一条有向边
int dfn[N],low[N],tot; //时间戳和回溯值 编号标记
std::stack<int> st; //缩点需要用到栈
int sz[N],scc[N],cnt,in_stk[N];//sz表示缩点之后的点的数量，scc记录每个点能缩成哪个点

//构造拓朴排序的变量
std::vector<int> topo[N];
int dp[N],nval[N]; //ans

//tarjan缩点：转换为有向无环图
void tarjin(int now){
    dfn[now]=low[now]=++tot;
    st.push(now);
    in_stk[now]=true;
    for (auto& x:vec[now]){
        if (!dfn[x]){ //如果没有访问过
            tarjin(x);
            low[now]=std::min(low[now],low[x]);
        }
        else if (in_stk[x]){ //如果这个点访问过并且在栈中
            low[now]=std::min(low[now],dfn[x]);
        }
    }
    //dfn的值等于low的值，说明这个点是一个连通环的根，可以把这个连通环缩为一个点
    if (dfn[now]==low[now]){
        int y=0;
        ++cnt;
        do
        {
            y=st.top();
            st.pop(),in_stk[y]=false;
            scc[y]=cnt;
            ++sz[cnt];
        } while (y!=now);
    }
}
signed main(){
    std::cin>>n>>m;
    for (int i=1;i<=n;i++){
        std::cin>>val[i];
    }
    for (int i=1;i<=m;i++){
        int x,y;
        std::cin>>x>>y;
        vec[x].push_back(y);
    }
    for (int i=1;i<=n;i++){
        if (!dfn[i]){
            tarjin(i);
        }
    }
    //缩点完成!------------------
    //缩点转化为逆序的《有向无环图》
    //构造DAG的topo序
    for (int i=1;i<=n;i++){
        nval[scc[i]]+=val[i]; //某缩点的总权值
        for (auto& x:vec[i]){   
            if (scc[i]!=scc[x]){
                topo[scc[i]].push_back(scc[x]); //对缩点进行建图
            }
        }
    }
    int ans=0;
    for (int i=cnt;i>=1;i--){ //倒序遍历cnt个缩点
        if (!dp[i]){
            dp[i]=nval[i];
        }
        for (auto& x:topo[i]){
            dp[x]=std::max(dp[x],dp[i]+nval[x]);
        }
    }
    for (int i=1;i<=cnt;i++){
        ans=std::max(ans,dp[i]);
    }
    std::cout<<ans;
    return 0;
}