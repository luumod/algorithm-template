void TwoBag(){
    for (int i=1;i<=n;i++){
        for (int j=V;j>=Wei[i];j--){ //背包容量
            for (int z=M;z>=Zho[i];z--){ //背包重量
                dp[j][z]=std::max(dp[j][z],dp[j-Wei[i]][z-Zho[i]]+Val[i]);
            }
        }
    }
    std::cout<<dp[V][M];
}  