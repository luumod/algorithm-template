#include <bits/stdc++.h>

const int N=1e3;
int n,m;
struct Edge{
    int to,next;
}edge[N<<2];
int dfn[N],low[N],tot;
int head[N],cnt=1; //边的编号从2开始
std::vector<std::pair<int,int>> ans;
void add_edge(int u,int v){
    edge[++cnt].to=v;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
/*tarjan割边*/
void tarjan(int now,int in_edge){
    //now表示当前点，in_edge表示其对应的反边
    dfn[now]=low[now]=++tot;
    for (int i=head[now];i;i=edge[i].next){ //i表示当前边对应的编号
        int v=edge[i].to; //对应的边的邻点
        if (!dfn[v]){
            tarjan(v,i);
            low[now]=std::min(low[now],low[v]);
            if (low[v]>dfn[now]){
                //是一条割边
                ans.push_back({now,v});
            }
        }
        else if(i!=(in_edge^1)){ //不是一条反边: 2 3: 10 11 是反边
            low[now]=std::min(low[now],dfn[v]);
        }
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
            tarjan(i,head[i]);
        }
    }
    //排序并且输出割边
    std::sort(ans.begin(),ans.end());
    for (auto& x:ans){
        std::cout<<x.first<<" "<<x.second<<'\n';
    }
    return 0;
}