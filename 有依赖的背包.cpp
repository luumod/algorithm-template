const int N=110;
std::vector<int> tree[N];
std::vector<int> W(N),V(N);//体积和价值
int dp[N][N]; //dp[i][j]：当前节点为i 背包容量为j时的最大价值
int n,M;//物品种类数量和背包容量
void dfs(int now){
    //首先对自身初始化，即只装自己节点的情况下的背包不同容量最大值
    for (int i=W[now];i<=M;i++){
        dp[now][i]=V[now];
    }
    for (auto& son:tree[now]){
        dfs(son);
        //分组背包
        for (int i=M;i>=W[now];i--){//倒叙遍历背包容量
            for (int j=0;j<=i-W[now];j++){//除去当前节点，遍历可以选择其他节点的不同容量
                dp[now][i]=std::max(dp[now][i],dp[now][i-j]+dp[son][j]);
            }
        }
    }
}