#include<iostream>
#define maxn 100010 
using namespace std;
/**************************************************************
	1.冒泡排序就是每一轮通过相邻元素的交换，将当前最大的元素（或者最小的元素）像冒泡一样浮动到数组的最后面 
***************************************************************/
void swap(int* p,int* q){
	int t = *p;
	*p = *q;
	*q = t;
	return ;
}
int main(){
	int R[maxn];
	int n;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	for(int i=n; i>=2; i--){
		bool flag = false;
		for(int j=1; j<i; j++){
			if(R[j] > R[j+1]) {
				swap(&R[j],&R[j+1]);
				flag = true;
			}
		}
		if(!flag) break;
	}
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
