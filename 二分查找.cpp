#include <bits/stdc++.h>

int main(){
    int n,k;
    std::cin>>n>>k;
    std::vector<int> vec(n+1);
    for (int i=1;i<=n;i++){
        std::cin>>vec[i];
    }
    //切割成k段，需要得到尽可能大的长度
    auto check=[&](int mid){
        int sum=0;
        for (int i=1;i<=n;i++){
            sum+=vec[i]/mid; //可以切割成vec[i]/mid块mid长度的木块
        }
        return sum>=k; //总块数大于k，切割合法
    };
    int l=0,r=1e9;
    while (l+1<r){
        int mid=l+r>>1;
        if (check(mid)){
            l=mid; //寻找最大值 
        }
        else{
            r=mid;
        }
    }
    std::cout<<l;
	return 0;
}