#include<iostream>
#define maxn 100010
using namespace std;
const int INF = 0x3f3f3f3f;
/*********************************
	1.������ͨѡ�������뷨ʮ�ּ򵥣�����ÿһ��ѡ��ǰ������������� 
**********************************/
void swap(int *p,int *q){
	int t = *p;
	*p = *q;
	*q = t;
	return ;
}
int main(){
	int n;
	int R[maxn];
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	for(int i=n; i>=2; i--) {
		int pos,m = -INF; // 0x3f3f3f3f��һ���ܴ���� 
		for(int j=1; j<=i; j++){ //ѭ���ҵ�[1,i]��������������λ��(pos)
			if(m < R[j]){
				m = R[j];
				pos = j;
			}
		}
		swap(&R[i],&R[pos]);
	}
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl; 
	return 0;
}
