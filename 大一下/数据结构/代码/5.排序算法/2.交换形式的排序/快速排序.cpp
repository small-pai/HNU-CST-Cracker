#include<iostream>
#define maxn 100010
using namespace std;
/******************************************************************************
	1.快速排序也属于交换的排序
	2.虽然叫做快排但是不优化的就很慢 
********************************************************************************/ 
void fast_sort(int R[],int s,int e){
	int l = s,r = e;
	if(l >= r) return ;
	int t = R[l];
	while(l < r){
		while(l < r){ //从右边扔向左边 
			if(R[r]<t){
				R[l] = R[r];
				break;
			}
			r--;
		}
		while(l < r){
			if(R[l] >= t){ //从左边扔向右边 
				R[r] = R[l];
				break;
			}
			l++;
		}
	}
	int gap = l;
	R[gap] = t;
	fast_sort(R,s,gap-1);
	fast_sort(R,gap+1,e);
	return ;
}
int main(){
	int n;
	int R[maxn];
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	fast_sort(R,1,n);
	//
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
