#include <bits/stdc++.h>

const int N=5e5+10,M=2e6+10;
int n,m;
int dfn[N<<2],low[N<<2],tot; //dfn:时间戳 low:回溯值 tot:时间戳记录
int all; //边的双连通分量 eDCC的总个数
//前向星存图
struct Edge{
    int to,next;
}edge[M<<2];
int head[M],cnt=1; //让编号从2开始: 2 3: 10 11 -->用于判断反向边
std::stack<int> stk;//构造强连通分量需要的栈
bool bri[M<<2]; //割边
int edcc[N<<2]; //记录每个节点存储于哪一个eDCC中
std::vector<int> ans[N*2]; //答案，ans[i]输出第i个eDCC和其包含的原始的节点
void add_edge(int u,int v){
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
void tarjan(int now,int in_edge){
    dfn[now]=low[now]=++tot;
    stk.push(now);
    for (int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if (!dfn[v]){
            tarjan(v,i);
            low[now]=std::min(low[now],low[v]);
            //判断割边
            if (low[v]>dfn[now]){
                //从now到v是一条割边
                bri[i]=bri[i^1]=true; //对这条割边做标记
            }
        }
        else if (i!=(in_edge^1)){ //不是反边
            low[now]=std::min(low[now],dfn[v]);
        }
    }
    if (low[now]==dfn[now]){
        int y=0;
        ++all;
        do{
            y=stk.top();
            stk.pop();
            edcc[y]=all;
        }while (y!=now);
    }
}
int main(){
    std::cin>>n>>m;
    for (int i=1;i<=m;i++){
        int u,v;
        std::cin>>u>>v;
        add_edge(u,v);
        add_edge(v,u);
    }
    for (int i=1;i<=n;i++){
        if (!dfn[i]){
            tarjan(i,0);
        }
    }
    std::cout<<all<<'\n';
    //记录于ans中
    for (int i=1;i<=n;i++){ //cnt
        ans[edcc[i]].push_back(i);
    }
    for (int i=1;i<=all;i++){
        std::cout<<ans[i].size()<<" ";
        for (auto& x:ans[i]){
            std::cout<<x<<" ";
        }
        std::cout<<'\n';
    }
    return 0;
}