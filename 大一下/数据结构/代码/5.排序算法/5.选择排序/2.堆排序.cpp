#include<iostream>
#define maxn 100010
using namespace std;
/*********************************************************************************************************
	1.堆排序我们也把他认为是选择排序的一种，因为它排序也是每次将当前最大的数放在最后，同普通选择排序一样。
	2.但堆排序的效率很优秀，在与他的选择过程利用了堆，每次选择之后维护堆的过程只有logn，所以其最坏复杂度为nlogn
	3.堆排序要注意的是为了这个二叉堆的结构，我们储存的数据必须从1开始 
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
	for(int i=n; i>=2; i--){ // 将当前最大的数放在i号位置 
		swap(&R[1],&R[i]);
		mt(R,1,i-1);
	}
	//输出 
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
