#include<bits/stdc++.h>
#if 1
    #define int long long
#endif
template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::pair<T1,T2>pa){out<<"{fi: "<<pa.first<<", se: "<<pa.second<<"}\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::vector<T>vec){for(auto&x:vec){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::deque<T>deq){for(auto&x:deq){out<<x<<' ';}out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::queue<T>q){std::queue<T>t=q;while(!q.empty()){out<<q.front()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename pred>std::ostream&operator<<(std::ostream&out,std::priority_queue<T1,std::vector<T1>,pred>q){auto t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T>std::ostream&operator<<(std::ostream&out,std::stack<T>q){std::stack<T>t=q;while(!q.empty()){out<<q.top()<<" ";q.pop();}q=t;out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::unordered_map<T1,T2>ump){for(auto&x:ump){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::unordered_set<T1>ust){for(auto&x:ust){out<<x<<" ";}out<<"\n";return out;}template<typename T1>std::ostream&operator<<(std::ostream&out,std::set<T1>st){for(auto&x:st){out<<x<<" ";}out<<"\n";return out;}template<typename T1,typename T2>std::ostream&operator<<(std::ostream&out,std::map<T1,T2>mp){for(auto&x:mp){out<<"key: "<<x.first<<", val: "<<x.second<<"\n";}out<<"\n";return out;}template<typename T>void show(T a[],int beg,int end){for(int i=beg;i<=end;i++){std::cout<<a[i]<<" ";}std::cout<<"\n";}

const int N=1e5+10;
int h,x,y,z;
struct Node{
    int to,next,w;
}edge[N<<2];
int head[N],cnt,dis[N],vis[N];
void add_edge(int u,int v,int w){
    edge[++cnt].to=v;
    edge[cnt].w=w;
    edge[cnt].next=head[u];
    head[u]=cnt;
}
void spfa(){
	memset(dis,0x3f,sizeof(dis));
	std::queue<int> q;
	q.push(0);
	dis[0]=1;   //当前满足模x等于0的最小楼层是1，因为当前位于第1层
	vis[0]=true; 
	while (!q.empty()){
		auto p=q.front();
		q.pop();
		vis[p]=false;
		for (int i=head[p];i;i=edge[i].next){
			int to=edge[i].to,w=edge[i].w;
			if (dis[to]>dis[p]+w){
				dis[to]=dis[p]+w;
				if (!vis[to]){
					q.push(to);
					vis[to]=true;
				}
			}
		}
	}
}
signed main(){
    std::cin>>h>>x>>y>>z;
    if (x==1 || y==1 ||z==1){
        std::cout<<h; //所有均可达
        return 0;
    }
    /*
    在只走y和z的情况下，mod x能够到达的最短路: dis[x] mod x
    dis[i+y] mod x=dis[i]+y;
    dis[i+z] mod x=dis[i]+z;
    */ 
   	for (int i=0;i<x;i++){
    	add_edge(i,(i+y)%x,y);
		add_edge(i,(i+z)%x,z);
	}
	spfa();
	int ans=0;
	for (int i=0;i<x;i++){
		if (dis[i]<=h){
			ans+=(h-dis[i])/x+1;
		}
	}
	std::cout<<ans;
    return 0;
}