#include <bits/stdc++.h>

const int N=10;
int n;
int dp[N][N]; //当前位数是i位，并且最高位数字为j 时的不降数的方案数
void init(){
	//预处理数字
	for (int i=0;i<N;i++){
		dp[1][i]=1; //个位数为其本身
	}
	for (int i=2;i<N;i++){ //遍历位数
		for (int j=0;j<N;j++){ //遍历i位数的最高位的数字
			for (int z=j;z<N;z++){ //遍历i-1位数的最高位数字 需要大于第i位数字的最高位，即z从j开始
				dp[i][j]+=dp[i-1][z];
			}
		}
	}
}
int solve(int num){
	if (!num){
		return 1;
	}
	std::vector<int> nums;
	while (num){ //存储每一位
		nums.push_back(num%10); //低位 --> 高位
		num/=10;
	}
	int ans=0;
	int last=0; //前一位数字，代表高位
	for (int i=nums.size();i>=1;i--){
		int now=nums[i-1];//取出当前位的数字
		for (int j=last;j<now;j++){ //j既要大于前一位数字，又要小于当前位数字
			ans+=dp[i][j];//位数为i，最高位为j数字 的数字个数
		}
		if (now<last){
			break; //下降了
		}
		last=now; //更新前一位数字的最高位数字
		if (i==1){
			ans++; //自身
		}
	}
	return ans;
}
int main(){	
	init();
	int l,r;
	while (std::cin>>l>>r){
		std::cout<<solve(r)-solve(l-1)<<'\n';
	}
}