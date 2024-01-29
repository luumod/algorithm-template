#include <bits/stdc++.h>

const int N=110;
int n;
std::vector<int> vec[N],val(N);
/*
Rsum表示包含当前节点的节点数
size表示当前节点的最大子树的节点数
n-Rsum:除了当前节点的子树之外的所有节点数
ans:答案，即剩余各个连通块中点数的最大值
*/
std::vector<bool> vis(N);
int ans=1e9;
int dfs(int now){
    //树的重心：去掉某个节点之后，树中剩余连通块的最大节点数量最少，这个点是重心
    vis[now]=true;
    int size=0;
    int sum=1;//当前节点所在子树的节点数
    for (auto& x:vec[now]){
        if (!vis[x]){//遍历它的孩子
            int num=dfs(x);
            sum+=num; //累加当前子树的节点数
            size=std::max(size,num); //孩子节点部分连通块最大节点数
        }
    }
    //要么取now某个子树的连通块的最大值，要么取其上方的所有的最大值
    ans=std::min(ans,std::max(size,n-sum));
    return sum;
}
int main(){
    std::cin>>n;
    for (int i=1;i<n;i++){
        int u,v;
        std::cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1);
    std::cout<<ans;
	return 0;
}