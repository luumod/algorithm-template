#include <bits/stdc++.h>

const int N=5e5+10;
std::vector<int> vec[N],vdcc[N]; //vec存图 vdcc记录最后的答案
int n,m;
int dfn[N],low[N],tot; //时间戳 回溯值 编号
std::stack<int> stk; //构造强连通分量需要的栈
int cnt,root; //cnt记录vDCC的个数  root记录每次tarjan时的根节点，用于判断割点
int cutPoint[N]; //记录某个点是不是割点
void tarjan(int now){
    dfn[now]=low[now]=++tot;
    stk.push(now);
    if (!vec[now].size()){
        //单独成块
        vdcc[++cnt].push_back(now); //单独记录为一个vDCC
        return;
    }
    int check=0;
    for (auto& x:vec[now]){
        if (!dfn[x]){
            tarjan(x);
            low[now]=std::min(low[now],low[x]);
            //判断割点并且合并成双连通分量
            if (low[x]>=dfn[now]){
                check++;
                if (now!=root || check>=2){
                    cutPoint[now]=true; //标记now为割点
                }
                //求vDCC
                cnt++;
                while (true){
                    int y=stk.top();
                    stk.pop(); 
                    vdcc[cnt].push_back(y); //其他点
                    if (y==x){
                        break;
                    }
                }
                vdcc[cnt].push_back(now); //割点
                //-------共同组成一个vdcc
            }
        }
        else{
            low[now]=std::min(low[now],dfn[x]);
        }
    }
}
int main(){
    std::cin>>n>>m;
    for (int i=1;i<=m;i++){
        int u,v;
        std::cin>>u>>v;
        if (u==v){
            continue;
        }
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for (int i=1;i<=n;i++){
        if (!dfn[i]){
            root=i;
            tarjan(i);
        }
    }
    std::cout<<cnt<<'\n';
    for (int i=1;i<=cnt;i++){
        std::cout<<vdcc[i].size()<<' ';
        for (auto& x:vdcc[i]){
            std::cout<<x<<' ';
        }
        std::cout<<'\n';
    }
    return 0;
}