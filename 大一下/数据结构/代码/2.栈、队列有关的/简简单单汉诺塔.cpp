#include<iostream>

using namespace std;
void dfs(int n,char x,char y,char z,int& ans){//ans�����ƶ��Ĳ��� 
	if(n == 0) return ;
	// ��x�ƶ���z
	dfs(n-1,x,z,y,ans);
	printf("��%c�������ƶ����Ϊ%d�����ӵ�%c������\n",x,n,z);
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
