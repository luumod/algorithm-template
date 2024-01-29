#include<bits/stdc++.h>
#if 1
    #define int long long
#endif
template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::pair<T1,T2>pa){out<<"{fi: "<<pa.first<<", se: "<<pa.second<<"}\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::vector<T>vec){for(auto&x:vec){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::deque<T>deq){for(auto&x:deq){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::queue<T>q){std::queue<T>t=q;while(!q.empty()){out<<q.front()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename pred>std::ostream&operator<<(std::ostream&out,std::priority_queue<T1,std::vector<T1>,pred>q){auto t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::stack<T>q){std::stack<T>t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::unordered_map<T1,T2>ump){for(auto&x:ump){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::unordered_set<T1>ust){for(auto&x:ust){out<<x<<" ";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::set<T1>st){for(auto&x:st){out<<x<<" ";}out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::map<T1,T2>mp){for(auto&x:mp){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T>void show(T a[],int beg,int end){for(int i=beg;i<=end;i++){std::cout<<a[i]<<" ";}std::cout<<"\n";}

const int N=1e5+10;
int c[4],d[4],n,s,dp[N+10];
void init(){
    dp[0]=1;
    for (int i=0;i<4;i++){
        for (int j=c[i];j<=N;j++){
            dp[j]+=dp[j-c[i]];
        }
    }
}
void solve(){
    for (int i=0;i<4;i++){
        std::cin>>d[i];
    }
    std::cin>>s;
    //预处理每种物品无限次数选的时候的方案数
    int res=0;
    for (int i=1;i<1<<4;i++){ //枚举状态
        int t=0,fg=-1;
        for (int j=0;j<4;j++){ //枚举位
            if (i & (1<<j)){
                t+=c[j]*(d[j]+1);
                fg=-fg;
            }
        }
        if (s>=t){
            res+=dp[s-t]*fg;
        }
    }
    std::cout<<dp[s]-res<<'\n';
}
signed main(){
    for (int i=0;i<4;i++){
        std::cin>>c[i];
    }
    init();
    std::cin>>n;
    while (n--){
        solve();
    }
    return 0;
}