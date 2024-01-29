#include <bits/stdc++.h>

const int N=1e4+10;
int n,m;
struct Node{
    int to,w,next;
}edge[N];
int head[N],cnt;
//染色法所需要的color数组
int color[N]; //染色1或者2
void add_edge(int u,int v,int w){
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
bool dfs(int now,int col){
    color[now]=col;
    for (int i=head[now];i;i=edge[i].next){
        int v=edge[i].to;
        if (!color[v]){ //如果没有染过色
            if (dfs(v,3-col)){
                return 1;
            }
        }
        else if(color[v]==col){
            //如果当前点的颜色与他的相邻的点颜色相同，则存在奇环
            return 1;    
        }
    }
    //正常，没有奇环
    return 0;
}
int main(){ 
    std::cin>>n>>m;
    for (int i=1;i<=m;i++){
        int a,b,c;
        std::cin>>a>>b>>c;
        add_edge(a,b,c);
        add_edge(b,a,c);
    }
    bool fg=false;
    for (int i=1;i<=n;i++){
        if (!color[i]){
            if (dfs(i,1)){
                fg=true;
                break;
            }
        }
    }
    if (!fg){
        std::cout<<"不是二分图，有奇环\n";
    }
    else{
        std::cout<<"是二分图\n";
    }
    return 0;
}