#include<iostream>
#define maxn 100010
using namespace std;
/*********************************************************************************************************
	1.����������Ҳ������Ϊ��ѡ�������һ�֣���Ϊ������Ҳ��ÿ�ν���ǰ�������������ͬ��ͨѡ������һ����
	2.���������Ч�ʺ����㣬��������ѡ����������˶ѣ�ÿ��ѡ��֮��ά���ѵĹ���ֻ��logn������������Ӷ�Ϊnlogn
	3.������Ҫע�����Ϊ���������ѵĽṹ�����Ǵ�������ݱ����1��ʼ 
*********************************************************************************************************/
void swap(int *p,int *q){
	int t = *p;
	*p = *q;
	*q = t;
	return ;
}
void mt(int R[],int rt_id,int max_son){
	for(int son = rt_id*2; son <= max_son; son *= 2){
		if((son+1)<=max_son && R[son] < R[son+1]) son = son+1;
		if(R[son] > R[rt_id]) {
			swap(&R[son],&R[rt_id]);
			rt_id = son;
		}
		else break;
	}
	return ;
} 
int main(){
	int n;
	int R[maxn];
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	for(int i=n/2; i>=1; i--) mt(R,i,n);
	for(int i=n; i>=2; i--){ // ����ǰ����������i��λ�� 
		swap(&R[1],&R[i]);
		mt(R,1,i-1);
	}
	//��� 
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
