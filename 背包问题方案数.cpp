void numOfFangan(){
    for (int i=0;i<=M;i++){
        cnt[i]=1;
    }
    for (int i=1;i<=n;i++){
        for (int j=M;j>=W[i];j--){
            if (dp[j-W[i]]+V[i]>dp[j]){ //更新所需要得到的最大价值
                dp[j]=dp[j-W[i]]+V[i];
                cnt[j]=cnt[j-W[i]];
            }
            else if (dp[j-W[i]]+V[i]==dp[j]){ //更新最大价值对应的cnt
                cnt[j]=(cnt[j]+cnt[j-W[i]])%mod;
            }
        }
    }
    std::cout<<cnt[M];
}