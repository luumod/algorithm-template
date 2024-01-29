#include "bits/stdc++.h"

/*
3. floyd算法
*/
const int N=1e3+10;
int dp[N][N];
int n,m;
memset(dp,0x3f,sizeof(dp));
void floyd(){
    for (int k=1;k<=n;k++){
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                dp[i][j]=std::min(dp[i][j],dp[i][k]+dp[k][j]);
            }
        }
    }
}