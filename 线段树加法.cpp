#include <bits/stdc++.h>
#define int long long 
using ll=long long;
const int N=1e5+10;
int n,m;
int nums[N],tree[N<<2],tag[N<<2];
void push_up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}
void push_down(int i,int pl,int pr){
    if (tag[i]){
        int mid=pl+pr>>1;
        tag[i<<1]+=tag[i];
        tree[i<<1]+=(mid-pl+1)*tag[i];

        tag[i<<1|1]+=tag[i];
        tree[i<<1|1]+=(pr-(mid+1)+1)*tag[i];
        tag[i]=0;
    }
}
void build(int i,int pl,int pr){
    if (pl==pr){
        tree[i]=nums[pl];
        return;
    }
    int mid=pl+pr>>1;
    build(i<<1,pl,mid);
    build(i<<1|1,mid+1,pr);
    push_up(i);
}   
void update(int i,int pl,int pr,int L,int R,int k){
    if (L<=pl && pr<=R){
        tree[i]+=(pr-pl+1)*k;
        tag[i]+=k;
        return;
    }
    push_down(i,pl,pr);
    int mid=pl+pr>>1;
    if (L<=mid) update(i<<1,pl,mid,L,R,k);
    if (R>mid) update(i<<1|1,mid+1,pr,L,R,k);
    push_up(i);
}
ll query(int i,int pl,int pr,int L,int R){
    if (L<=pl && pr<=R){
        return tree[i];
    }
    push_down(i,pl,pr);
    ll ans=0;
    int mid=pl+pr>>1;
    if (L<=mid) ans+=query(i<<1,pl,mid,L,R);
    if (R>mid) ans+=query(i<<1|1,mid+1,pr,L,R);
    return ans;
}
signed main(){
    std::cin>>n>>m;
    for (int i=1;i<=n;i++){
        std::cin>>nums[i];
    }
    build(1,1,n);
    for (int i=1;i<=m;i++){
        int op,l,r,k;
        std::cin>>op;
        if (op==1){
            std::cin>>l>>r>>k;
            update(1,1,n,l,r,k);
        }
        else{
            std::cin>>l>>r;
            std::cout<<query(1,1,n,l,r)<<'\n';
        }
    }
    return 0;
}