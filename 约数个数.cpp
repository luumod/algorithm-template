
const int N=1e6+10;
int vis[N],p[N],a[N],d[N];
void find(int n){
    int c=0;
    for (int i=2;i<=n;i++){
        if (!vis[i]){
            p[++c] = i;
            //质数的质因子个数为1，约数个数为2
            a[i]=1,d[i]=2;
        }
        for (int j=1;i*p[j]<=n;j++){
            int m=i*p[j];
            vis[m]=true;
            if (i%p[j]==0){
                a[m]=a[i]+1;
                d[m]=d[i]/a[m]*(a[m]+1);
                break;      
            }
            else{
                //m=2*5=10 是一个合数：质因子只有一个，约数个数为d[i]*2   
                a[m]=1,d[m]=d[i]*2;
            }
        }
    }
}