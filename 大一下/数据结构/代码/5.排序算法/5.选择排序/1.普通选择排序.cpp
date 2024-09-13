#include<iostream>
#define maxn 100010
using namespace std;
const int INF = 0x3f3f3f3f;
/*********************************
	1.这是普通选择排序，想法十分简单，就是每一次选择当前最大的数放在最后 
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
		int pos,m = -INF; // 0x3f3f3f3f是一个很大的数 
		for(int j=1; j<=i; j++){ //循环找到[1,i]区间中最大的数的位置(pos)
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
