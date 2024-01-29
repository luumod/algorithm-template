#include <bits/stdc++.h>

const int N=2e4+10;
int n,m;
std::vector<int> vec[N];
int dfn[N],low[N],tot;
bool fg[N]; //割点
int root,cnt;
void tarjan(int now){
    //盖戳
    dfn[now]=low[now]=++tot;
    /*
    1. now不是根节点：当low[x]>=low[now] 时now是割点
    2. now是根节点：当check>=2个点满足以上条件时 now是割点
    */
    int check=0; 
    for (auto& x:vec[now]){
        if (!dfn[x]){
            tarjan(x);
            //回now，更新low回溯值，判断割点
            low[now]=std::min(low[now],low[x]);
            //孩子节点与当前节点
            if (low[x]>=dfn[now] && now!=root){
                fg[now]=true; //标记为割点
            }
            //父节点
            if (now==root){
                check++;
            }
        }
        else{
            low[now]=std::min(low[now],dfn[x]);
        }
    }
    if (now==root && check>=2){
        fg[now]=true;
    }
}
int main(){
    std::cin>>n>>m;
    for (int i=1;i<=m;i++){
        int x,y;
        std::cin>>x>>y;
        vec[x].push_back(y);
        vec[y].push_back(x);
    }
    for (int i=1;i<=n;i++){
        if (!dfn[i]){
            root=i;
            tarjan(i);
        }
    }
    //统计割点数量
    for (int i=1;i<=n;i++){
        if (fg[i]){
            ++cnt;
        }
    }   
    std::cout<<cnt<<'\n';
    for (int i=1;i<=n;i++){
        if (fg[i]){ 
            std::cout<<i<<' ';
        }
    }
    return 0;
}