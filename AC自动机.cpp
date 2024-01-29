#include <bits/stdc++.h>

//AC自动机
const int N=1e6+10;
int next[N];   //存节点i的回跳边的终点: 四边形
int tree[N][26]; //存节点i的树边的终点或者是转移边的终点：直线或三角形
int cnt[N];
int idx=0;
void insert(std::string s){
    int p=0;
    for (auto& x:s){
        int j=x-'a';
        if (!tree[p][j]){
            tree[p][j]=++idx;
        }
        p=tree[p][j];
    }   
    cnt[p]++;
}
void build(){
    std::queue<char> q;
    for (int i=0;i<26;i++){
        if (tree[0][i]){ //如果存在某一个字母节点
            q.push(tree[0][i]); //则入队，表示以某个字母开始
        }
    }
    while (!q.empty()){
        int p=q.front();
        q.pop();
        for (int i=0;i<26;i++){
            int j=tree[p][i];//当前儿子节点
            if (j){
                //如果儿子存在，则爹帮儿子建回跳边: 当前节点的父节点的回跳边的所指儿子
                next[j]=tree[next[p]][i];
                q.push(j);
            }
            else{
                //如果儿子不存在，则爹自建转移边: 当前节点的回跳边所指儿子
                tree[p][i]=tree[next[p]][i];
            }
        }
    }
}
int query(std::string s){
    int ans=0;
    for (int k=0,p=0;k<s.size();k++){
        p=tree[p][s[k]-'a'];
        for (int j=p;j&&~cnt[j];j=next[j]){ //~表示按位取反 -1则1111 -> 0000
            ans+=cnt[j];
            cnt[j]=-1; //答案只出现一次
        }
    }
    return ans;
}