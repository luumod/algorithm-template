#include <bits/stdc++.h>

typedef long long ll;
//1. 试除法求欧拉函数：某一个确切的值
ll fun1(int n){
    ll phi=n;
    for (int i=2;1ll*i*i<=n;i++){
        if (n%i==0){ 
            phi=phi/i*(i-1);
            while (n%i==0){
                n/=i;
            }
        }
    }
    if (n>1){
        phi=phi/n*(n-1);
    }
    return phi;
}
//2. 筛法求欧拉函数：任意范围内的数值
const int N=1e8+10;
int primes[N];
bool vis[N];
int phi[N]; //每个数字的欧拉哈数
std::vector<int> vec;
void fun2(int n){
    int cnt=0;
    for (int i=2;i<=n;i++){
        if (!vis[i]){
            primes[++cnt]=i;
            //质数i的欧拉函数就是i-1
            phi[i]=i-1;
        }
        for (int j=1;1ll*i*primes[j]<=n;j++){
            int m=i*primes[j];
            vis[m]=true;
            if (i%primes[j]==0){
                phi[m]=phi[i]*primes[j];
                break; //整除中断
            }
            else{
                phi[m]=phi[i]*(primes[j]-1);
            }
        }
    }
}