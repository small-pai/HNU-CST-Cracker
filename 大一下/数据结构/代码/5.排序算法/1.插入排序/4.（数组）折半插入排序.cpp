#include<iostream>
#define maxn 100010
using namespace std;
/*******************************************************************
	1.折半插入排序，就是将插入排序中在有序区间中找要插入位置的过程用二分查找来完成，使这一步的复杂度将为logn
	2.但实际上因为插入排序需要搬动数据，导致这个排序的最坏复杂度还是达到了n2的级别 
********************************************************************/
int main(){
	int R[maxn];
	int n;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	for(int i=2; i<=n; i++){
		int low = 1,high = i-1,mid;
		while(low <= high){
			mid = (low+high)/2;
			if(R[i] < R[mid]) high = mid-1;
			else low = mid+1;
		}
		//要加R[i]放在high+1的位置，所以将[high+1,i-1]上的数据都向后移动一位 
		int t = R[i];
		for(int j = i-1; j>=high+1; j--) R[j+1] = R[j];
		R[high+1] = t;
	}
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
