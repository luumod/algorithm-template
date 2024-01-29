#include <bits/stdc++.h>

//二进制优化
void Binary(){
    int n,W;
    std::cin>>n>>W;
    std::vector<int> w,v,dp(W+1);
    for (int i=1;i<=n;i++){
        int weight,value,number;
        std::cin>>weight>>value>>number;
        for (int j=1;j<=number;j<<=1){
            w.push_back(j*weight);
            v.push_back(j*value);
            number-=j;
        }
        if (number){
            w.push_back(number*weight);
            v.push_back(number*value);
        }   
    }
    for (int i=0;i<w.size();i++){
        for (int j=W;j>=w[i];j--){
            dp[j]=std::max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    std::cout<<dp[W];
}

//单调队列
void Deque(){
    int n,m;
    std::cin>>n>>m; //种类和背包容量    
    std::vector<int> dp(m+1),temp(m+1);
    int w,v,s;
    for (int i=1;i<=n;i++){
        std::copy(dp.begin()+1,dp.begin()+1+m,temp.begin()+1);
        std::cin>>w>>v>>s;//体积  价值  数量
        for (int j=0;j<w;j++){//分成w组
            std::deque<int> deq;
            for (int k=j;k<=m;k+=w){//对每组进行单调队列
                if (!deq.empty() && deq.front()<k-s*w){
                    deq.pop_front();
                }
                if (!deq.empty()){
                    dp[k]=std::max(temp[k],temp[deq.front()]+(k-deq.front())/w*v);
                }
                //当前k比队尾元素更具有价值，则更新
                while (!deq.empty() && temp[k]>=temp[deq.back()]+(k-deq.back())/w*v){
                    deq.pop_back();
                }
                deq.push_back(k);
            }
        }
    }
    std::cout<<dp[m];
}