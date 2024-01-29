#include <bits/stdc++.h>

std::string a,b;
std::vector<int> A,B,ans;
//高精度+法
void big_add(){
    int ne=0;
    for (int i=0;i<A.size() || i<B.size();i++){
        if (i<A.size()){
            ne+=A[i];
        }
        if (i<B.size()){
            ne+=B[i];
        }
        ans.push_back(ne%10);
        ne/=10;
    }
    if (ne){
        ans.push_back(ne%10);
    }
    //高位在前，低位在后
    std::reverse(ans.begin(),ans.end());
}
void mainAdd(){
    std::cin>>a>>b;
    //转换为低位在前，高位在后，方便计算
    for (int i=a.size()-1;~i;i--){
        A.push_back(a[i]-'0');
    }
    for (int i=b.size()-1;~i;i--){
        B.push_back(b[i]-'0');
    }
    big_add();
    for (auto& x:ans){
        std::cout<<x;
    }
}

//高精度-法
std::string a,b;
std::vector<int> A,B,ans;
bool comp(){
    if (a.size()!=b.size()){
        return a.size()<b.size(); //true 交换
    }
    //sizeA==sizeB
    for (int i=0;i<A.size();i++){
        if (A[i]!=B[i]){
            return A[i]<B[i]; //true
        }
    }
    return false;
}
void big_minus(){
    for (int i=0;i<A.size();i++){
        int t=A[i];
        if (i<B.size()){
            t-=B[i];
        }
        if (t<0){ //借位
            t+=10;
            A[i+1]-=1;
        }
        ans.push_back(t);
    }
    while (ans.size()>1 && ans.back()==0){
        ans.pop_back();
    }
    //高位在前，低位在后
    std::reverse(ans.begin(),ans.end());
}
void mainMinus(){
    std::cin>>a>>b;
    //转换为低位在前，高位在后，方便计算
    for (int i=a.size()-1;~i;i--){
        A.push_back(a[i]-'0');
    }
    for (int i=b.size()-1;~i;i--){
        B.push_back(b[i]-'0');
    }
    //规定始终是大数减小数，如果A是一个小数，则我们交换。然后输出一个 '-'
    if (comp()){
        std::swap(A,B);
        std::cout<<"-";
    }
    big_minus();
    for (auto& x:ans){
        std::cout<<x;
    }
}

//高精度*法
std::string n,m;
std::vector<int> A,B,ans;
void big_mul(){
    for (int i=0;i<A.size();i++){
        for (int j=0;j<B.size();j++){
            ans[i+j]+=A[i]*B[j];
            ans[i+j+1]+=ans[i+j]/10; //进位
            ans[i+j]%=10;  //当前位
        }
    }
    //处理前导0
    while (ans.size()>1 && !ans.back()){
        ans.pop_back();
    }
    std::reverse(ans.begin(),ans.end());
}
void mainMul(){
    std::cin>>n>>m;
    for (int i=n.size()-1;i>=0;i--){
        A.push_back(n[i]-'0');
    }
    for (int j=m.size()-1;j>=0;j--){
        B.push_back(m[j]-'0');
    }
    ans.resize(A.size()+B.size());
    big_mul();
    for (auto& x:ans){
        std::cout<<x;
    }
}

//高精度/法
std::string a;
int b;
std::vector<int> A;
std::deque<int> ans;
//大数除以小数
void big_div(){
    long long cur=0;
    std::reverse(A.begin(),A.end());
    //除法进行时高位在前
    for (int i=0;i<A.size();i++){
        cur=cur*10+A[i];
        ans.push_back(cur/b); //存商
        cur%=b; //更新余数
    }
    //转换为
    while (ans.size()>1 && !ans.front()){
        ans.pop_front();
    }
}
void mainDiv(){
    std::cin>>a>>b;
    for (int i=a.size()-1;i>=0;i--){
        A.push_back(a[i]-'0');
    }
    big_div();
    for (auto& x:ans){
        std::cout<<x;
    }
}