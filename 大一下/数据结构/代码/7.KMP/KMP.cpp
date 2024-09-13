#include<iostream>
#include<cstring> 
#define maxn 1000
using namespace std;
void get_moveto(char* s,int moveto[]){
	int lenth = strlen(s+1);
	moveto[1] = 0;
	for(int i=2; i<=lenth; i++){
		int j = moveto[i-1];
		while(j && s[j] != s[i-1]) j = moveto[j];
		moveto[i] = j+1;
	}
	return ;
}
int main(){
	puts("请输入模式串P和匹配串S，将返回S串在P串中的位置");
	char p[maxn];
	char s[maxn];
	int moveto[maxn];
	scanf("%s",p+1);
	scanf("%s",s+1);
	get_moveto(s,moveto);
	//匹配
	int i=1,j=1;
	int len_p = strlen(p+1);
	int len_s = strlen(s+1);
	bool flag = false; //标志没有找到 
	while(i<=len_p){
		if(j == 0 || p[i] == s[j]){
			i++;
			j++;
		}
		else j = moveto[j];
		if(j == len_s+1){
			cout<<"在P串中找到了S串，从P串的"<<i-len_s<<"位置开始出现了S串"<<endl;
			flag = true;
			break;
		}
	}
	if(!flag) cout<<"没有找到S串"<<endl;
	
	return 0;
}
