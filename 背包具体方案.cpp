const int N=1010;
std::vector<int> W(N),V(N);
int dp[N][N]; //dp[i][j]表示选择 [从i开始到最后的物品] 装入容量为j时所具有的最大价值
int n,M;
void Example(){
    for (int i=n;i>=1;i--){ //从后往前逆序遍历物品
        for (int j=0;j<=M;j++){ //从0开始
            dp[i][j]=dp[i+1][j];  //不选第i个物品，上一行同一列转移
            if (j-W[i]>=0){
                //选择第i个物品，上一行前面的某一列转移得到
                dp[i][j]=std::max(dp[i][j],dp[i+1][j-W[i]]+V[i]);
            }
        }
    }
    //dp[1][M]就是最大价值
    int j=M; 
    for (int i=1;i<=n;i++){
        //选不选第i个物品都可以得到最优解，为了最小字典序因此必须选第i个物品
        if (j-W[i]>=0 && dp[i][j]==dp[i+1][j-W[i]]+V[i]){
            std::cout<<i<<' ';
            j-=W[i];
        }
    }
}