#include <bits/stdc++.h>
#define int long long

const int mod=1e9+7,N=110;
int n,k;
struct Node{
	int a[N][N];
	Node(){
		memset(a,0,sizeof(a));
	}
}A,ans;
Node operator*(Node& l,Node& r){
	Node res;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			for (int k=1;k<=n;k++){
				res.a[i][j]=(res.a[i][j]+l.a[i][k]*r.a[k][j])%mod;
			}
		}
	}
	return res;
}
void fast_pow(int k){
	for (int i=1;i<=n;i++){
		ans.a[i][i]=1; //构造单位矩阵 
	}
	while (k){
		if (k&1){
			ans=ans*A;
		} 
		A=A*A;
		k>>=1;
	}	
}
signed main(){
	std::cin>>n>>k;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			std::cin>>A.a[i][j];
		}
	}
	fast_pow(k);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			std::cout<<ans.a[i][j]<<" \n"[j==n];
		}
	}
	return 0; 
}