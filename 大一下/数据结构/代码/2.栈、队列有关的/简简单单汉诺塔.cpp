#include<iostream>

using namespace std;
void dfs(int n,char x,char y,char z,int& ans){//ans纪律移动的步数 
	if(n == 0) return ;
	// 从x移动到z
	dfs(n-1,x,z,y,ans);
	printf("从%c柱子上移动编号为%d的盘子到%c柱子上\n",x,n,z);
	ans++;
	dfs(n-1,y,x,z,ans);
	return ; 
}
int main(){
	char x = '1',y ='2',z = '3'; 
	int n;
	int ans = 0;
	scanf("%d",&n);
	dfs(n,x,y,z,ans);
	cout<<ans<<endl;
	return 0;
}
