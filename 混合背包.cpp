#include <bits/stdc++.h>

int main(){
    int n,m;
    std::cin>>n>>m;
    std::vector<int> dp(m+1),W,V,S;
    int w,v,s;
    for (int i=1;i<=n;i++){
        std::cin>>w>>v>>s;
        if (s==0){
            //完全背包
            W.push_back(w);
            V.push_back(v);
            S.push_back(0);
        }
        else{
            if (s==-1){
                //01背包转换为只有1件的多重背包
                s=1;
            }
            //多重背包转换为k件01背包
            for (int k=1;k<=s;k<<=1){//拆分系数k
                W.push_back(k*w);
                V.push_back(k*v);
                S.push_back(1);
                s-=k;
            }
            if (s){
                W.push_back(s*w);
                V.push_back(s*v);
                S.push_back(1);
            }
        }
    }
    for (int i=0;i<W.size();i++){
        if (S[i]==0){
            //完全背包
            for (int j=W[i];j<=m;j++){
                dp[j]=std::max(dp[j],dp[j-W[i]]+V[i]);
            }
        }
        else{
            //多重01背包
            for (int j=m;j>=W[i];j--){
                dp[j]=std::max(dp[j],dp[j-W[i]]+V[i]);
            }
        }
    }
    std::cout<<dp[m];
	return 0;   
}