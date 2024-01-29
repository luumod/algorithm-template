const int N=110;
int n,M;
int dp[N]{}; 
int w[N][N]{},v[N][N]{},g[N]{};//体积 价值 组数
void GroupBag(){
    for (int i=1;i<=n;i++){//遍历物品
        for (int j=M;j>=1;j--){//倒叙遍历背包容量（转换为一维）
            for (int k=0;k<=g[i];k++){ //枚举选择每组内的物品，k=0表示不选这一组的物品
                if (j>=w[i][k]){
                    dp[j]=std::max(dp[j],dp[j-w[i][k]]+v[i][k]);
                }
            }
        }
    }
    std::cout<<dp[M];
}