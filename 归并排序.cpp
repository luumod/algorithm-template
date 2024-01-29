#include<bits/stdc++.h>
#if 1
    #define int long long
#endif
template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::pair<T1,T2>pa){out<<"{fi: "<<pa.first<<", se: "<<pa.second<<"}\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::vector<T>vec){for(auto&x:vec){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::deque<T>deq){for(auto&x:deq){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::queue<T>q){std::queue<T>t=q;while(!q.empty()){out<<q.front()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename pred>std::ostream&operator<<(std::ostream&out,std::priority_queue<T1,std::vector<T1>,pred>q){auto t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::stack<T>q){std::stack<T>t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::unordered_map<T1,T2>ump){for(auto&x:ump){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::unordered_set<T1>ust){for(auto&x:ust){out<<x<<" ";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::set<T1>st){for(auto&x:st){out<<x<<" ";}out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::map<T1,T2>mp){for(auto&x:mp){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T>void show(T a[],int beg,int end){for(int i=beg;i<=end;i++){std::cout<<a[i]<<" ";}std::cout<<"\n";}

const int N=5e5+10;
int n;
int vec[N],ans,t[N];
void Sort(int l,int r){
    int m=l+r>>1;
    int i=l,j=m+1,idx=l;
    //t数组为归并数组
    while (i<=m && j<=r){
        if (vec[i]>vec[j]){
            /*
            统计逆序对的数量，如果[1,m][m+1,r]中 
            [1,m]中的某个值i 大于[m+1,r]中的某值，则[i,m] 中的所有值一定都满足，则总的数量就是m-i+1
            */
            ans+=m-i+1; 
            t[idx++]=vec[j++];
        }
        else{
            t[idx++]=vec[i++];
        }
    }
    while (i<=m){
        t[idx++]=vec[i++];
    }
    while (j<=r){
        t[idx++]=vec[j++];
    }   
    for (int i=l;i<=r;i++){
        //拷贝回原数组
        vec[i]=t[i];
    }
}
void Merge(int l,int r){
    if (l!=r){
        int mid=l+r>>1;
        Merge(l,mid);
        Merge(mid+1,r);
        Sort(l,r);
    }
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin>>n;
    for (int i=1;i<=n;i++){
        std::cin>>vec[i];
    }
    Merge(1,n);
    std::cout<<ans;
    return 0;
}