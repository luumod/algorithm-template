#include<bits/stdc++.h>
#if 1
    #define int long long
#endif
template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::pair<T1,T2>pa){out<<"{fi: "<<pa.first<<", se: "<<pa.second<<"}\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::vector<T>vec){for(auto&x:vec){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::deque<T>deq){for(auto&x:deq){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::queue<T>q){std::queue<T>t=q;while(!q.empty()){out<<q.front()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename pred>std::ostream&operator<<(std::ostream&out,std::priority_queue<T1,std::vector<T1>,pred>q){auto t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::stack<T>q){std::stack<T>t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::unordered_map<T1,T2>ump){for(auto&x:ump){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::unordered_set<T1>ust){for(auto&x:ust){out<<x<<" ";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::set<T1>st){for(auto&x:st){out<<x<<" ";}out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::map<T1,T2>mp){for(auto&x:mp){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T>void show(T a[],int beg,int end){for(int i=beg;i<=end;i++){std::cout<<a[i]<<" ";}std::cout<<"\n";}

const int N=1e3+10;
int n,m,k,pi[N]; //pi[i]表示故障原因i发生的概率
int pj[N][N]; //p[i][j]表示故障原因i发生的条件下j现象发生的概率
int fg[N]; //故障编号
double sum;
struct Node{
    int id;
    double dp;
    bool operator<(const Node& p){
        if (dp==p.dp){
            return id<p.id;
        }
        return dp>p.dp;
    }
}node[N];
signed main(){
    std::cin>>n>>m;
    for (int i=1;i<=n;i++){
        std::cin>>pi[i]; 
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            std::cin>>pj[i][j]; //i发生下j的概率
        }
    }
    std::cin>>k;
    for (int i=1;i<=k;i++){
        int x;
        std::cin>>x; 
        fg[x]=1;
    }
    /*
    P(B): 故障现象出现的概率
    P(A): 故障原因出现的概率
    */
    for (int i=1;i<=n;i++){
        node[i].id=i,node[i].dp=pi[i]; //P(A)
        for (int j=1;j<=m;j++){
            if (fg[j]){
                node[i].dp*=pj[i][j]; //P(A)*P(B|A)
            }
            else{
                node[i].dp*=(100-pj[i][j]); //没有发生
            }
        }
        sum+=node[i].dp;
    }
    std::sort(node+1,node+1+n);
    for (int i=1;i<=n;i++){
        printf("%lld %.2lf\n",node[i].id,node[i].dp/sum*100);
    }
    return 0;
}