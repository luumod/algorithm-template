#define int long long
static const int N=1e5+10;
int idx=0;
int cnt[N];
int tree[N*31][2];
void update(int num){
    int p=0;
    for (int i=30;i>=0;i--){
        int j=num>>i&1;
        if (!tree[p][j]){
            tree[p][j]=++idx;
        }
        p=tree[p][j];
    }
}
int query(int num){
    int ans=0,p=0;
    for (int i=30;i>=0;i--){
        int j=num>>i&1;
        if (tree[p][!j]){
            ans+=1<<i;
            p=tree[p][!j];
        }
        else{
            p=tree[p][j];
        }
    }
    return ans;
}
