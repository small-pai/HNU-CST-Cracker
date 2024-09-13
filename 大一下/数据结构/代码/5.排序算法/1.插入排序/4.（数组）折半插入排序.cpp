#include<iostream>
#define maxn 100010
using namespace std;
/*******************************************************************
	1.�۰�������򣬾��ǽ�������������������������Ҫ����λ�õĹ����ö��ֲ�������ɣ�ʹ��һ���ĸ��ӶȽ�Ϊlogn
	2.��ʵ������Ϊ����������Ҫ�ᶯ���ݣ�����������������ӶȻ��Ǵﵽ��n2�ļ��� 
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
		//Ҫ��R[i]����high+1��λ�ã����Խ�[high+1,i-1]�ϵ����ݶ�����ƶ�һλ 
		int t = R[i];
		for(int j = i-1; j>=high+1; j--) R[j+1] = R[j];
		R[high+1] = t;
	}
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
