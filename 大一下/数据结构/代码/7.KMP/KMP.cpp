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
	puts("������ģʽ��P��ƥ�䴮S��������S����P���е�λ��");
	char p[maxn];
	char s[maxn];
	int moveto[maxn];
	scanf("%s",p+1);
	scanf("%s",s+1);
	get_moveto(s,moveto);
	//ƥ��
	int i=1,j=1;
	int len_p = strlen(p+1);
	int len_s = strlen(s+1);
	bool flag = false; //��־û���ҵ� 
	while(i<=len_p){
		if(j == 0 || p[i] == s[j]){
			i++;
			j++;
		}
		else j = moveto[j];
		if(j == len_s+1){
			cout<<"��P�����ҵ���S������P����"<<i-len_s<<"λ�ÿ�ʼ������S��"<<endl;
			flag = true;
			break;
		}
	}
	if(!flag) cout<<"û���ҵ�S��"<<endl;
	
	return 0;
}
