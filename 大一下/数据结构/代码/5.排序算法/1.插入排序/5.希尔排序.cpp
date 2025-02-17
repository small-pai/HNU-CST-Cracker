#include<iostream>
#define maxn 100010
using namespace std;
/****************************************************
	1.希尔排序也是插入排序的一种，当其间隔选取为1的时候就是普通插入排序
	2.它能加速的地方在于，在进行间隔为1的插入排序之前，我先进行间隔为其他更大的值的排序，这样我可能可以保证后面的排序的移动次数会很少，其实比较玄学，但是书上讲这个复杂度的证明
	是一个很难的问题，我们就不考虑了，就直接实现
	3.对于增量序列要注意的是，最后一个增量一定要为1，且增量序列中的值没有除1以外的公因子 
******************************************************/
int main(){
	int d[10] = {9,8,7,3,1} ;//这个间隔的数组由自己确定，但是一定要保证最后一个间隔一定要为1，且中间最好不要存在倍数（我觉得有倍数存在的话，间隔大的那一次没什么用）
	int R[maxn];
//	puts("输入元素的个数n以及这n个元素");
	int n;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	for(int m=0; m<5; m++){
		int delta = d[m]; //取出间隔 
		for(int i = 1+delta; i<=n; i++){
			int t = R[i];
			int j;
			for(j = i-delta; j>=1; j -= delta){
				if(t < R[j]) R[j+delta] = R[j];
				else break;
			}
			R[j+delta] = t;
		}
	}
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	return 0;
}
