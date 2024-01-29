/*
1. 队列实现
*/
void topoSort(int i){
    memcpy(tdin,din,sizeof(din));
    std::queue<std::pair<int,int>> q;
    int sum=0; //判断环
    for (int i=1;i<=n;i++){
        //当前点必须出现过，并且入度为0才能加入队列
        if (!tdin[i] && ust.count(i)){       
            q.push({i,1});
            sum++;
        }
    }
    int mx=0; //注意mx是寻找答案的关键：记录当前在第几层，如果层数等于n则说明找到了答案
    std::string s;
    while (!q.empty()){
        auto p=q.front();
        q.pop();
        s+=(p.first+'A'-1);
        for (auto& x:vec[p.first]){
            tdin[x]--;
            if (!tdin[x]){
                q.push({x,p.second+1}); //入度为0，则入队列
                sum++;
                //每次更新层数
                mx=std::max(mx,p.second+1);
            }
        }
    }
    //如果这里写s.size()==n是不可以的。
    if (mx==n){ //全部元素都找到了
        std::cout<<"Sorted sequence determined after "<<i<<" relations: "<<s<<".\n";
        exit(0);
    }
    else if (sum!=(int)ust.size()){
        std::cout<<"Inconsistency found after "<<i<<" relations.\n";
        exit(0);
    }
}

/*
2. dfs解法类似于二分图染色
*/
const int N=110;
std::vector<int> vec[N];
std::vector<int> ans;
int fg[N];
int n,m;
bool dfs(int i){
    fg[i]=-1; //走过的点标记为-1
    for (auto& x:vec[i]){
        if (fg[x]<0){
            //是一个环，之前出现过
            return false;
        }
        else if (!fg[x]){
            //为0说明之前未出现过
            if (!dfs(x)){ //染色
                return false;
            }
        }
    }
    fg[i]=1; //正确的点，标记为1然后加入答案(倒序，最后需要reverse)
    ans.push_back(i);
    return true;
}
bool solve(){
    for (int i=1;i<=n;i++){
        if (!fg[i]){
            //如果没有被标记过
            if (!dfs(i)){
                return false; //有环
            }
        }   
    }
    std::reverse(ans.begin(),ans.end());
    for (auto &x:ans){
        std::cout<<x<<' ';
    }
    std::cout<<'\n';
    return true;
}