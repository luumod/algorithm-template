#include<bits/stdc++.h>
#if 0
    #define int long long
#endif
template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::pair<T1,T2>pa){out<<"{fi: "<<pa.first<<", se: "<<pa.second<<"}\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::vector<T>vec){for(auto&x:vec){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::deque<T>deq){for(auto&x:deq){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::queue<T>q){std::queue<T>t=q;while(!q.empty()){out<<q.front()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename pred>std::ostream&operator<<(std::ostream&out,std::priority_queue<T1,std::vector<T1>,pred>q){auto t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::stack<T>q){std::stack<T>t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::unordered_map<T1,T2>ump){for(auto&x:ump){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::unordered_set<T1>ust){for(auto&x:ust){out<<x<<" ";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::set<T1>st){for(auto&x:st){out<<x<<" ";}out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::map<T1,T2>mp){for(auto&x:mp){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T>void show(T a[],int beg,int end){for(int i=beg;i<=end;i++){std::cout<<a[i]<<" ";}std::cout<<"\n";}

const int N=1e6+10;
char s1[N],s2[N];
int next[N];
void find_Netx(char s[],int n){
    next[1]=0;
    for (int i=2,j=0;i<=n;i++){
        while (j && s[i]!=s[j+1]){
            j=next[j];
        }
        if (s[i]==s[j+1]){
            j++;
        }
        next[i]=j;
    }
}
void match(char s1[],char s2[],int n1,int n2){
    for (int i=1,j=0;i<=n1;i++){
        while (j && s1[i]!=s2[j+1]){
            j=next[j];
        }
        if (s1[i]==s2[j+1]){
            j++;
        }
        if (j==n2){
            std::cout<<i-n2+1<<'\n';
        }
    }
}
signed main(){
    std::cin>>s1+1>>s2+1;
    int len1=strlen(s1+1),len2=strlen(s2+1);
    find_Netx(s2,len1);
    match(s1,s2,len1,len2);
    for (int i=1;i<=len2;i++){
        std::cout<<next[i]<<" ";
    }
    return 0;
}