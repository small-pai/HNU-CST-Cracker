#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
// 归并排序 非递归实现
// 从小到大排序 
void merge(int R[],int tem[],int s,int m,int e){ // 将R数组[s,m]区间和[m+1,e]区间合并,(此时[s,m],[m+1,e]已经各自有序) 
	int pa = s;
	int pb = m+1;
	int index = s;
	// 正常归并排序步骤 
	while(pa <= m && pb <= e){
		if(R[pa] <= R[pb]) tem[index++] = R[pa++];
		else tem[index++] = R[pb++];
	}
	while(pa <= m) tem[index++] = R[pa++];
	while(pb <= e) tem[index++] = R[pb++];
	// copy
	for(int i=s; i<=e; i++) R[i] = tem[i];
	return ;
}
int main(){
	int n; // 数组的大小
	int R[maxn];
	int tem[maxn]; //归并排序必备的临时数组,就是老师讲的 R1数组
	// 输入数据
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	// for循环合并区间
	for(int len = 1; len<n; len <<= 1){ //len可以理解成对于当前数组R 每len 的区间已经有序了,所以我是想合并[1,1+len-1]与[1+len,len*2] 
		for(int i = 1; i+len<=n; i+=len*2){
			merge(R,tem,i,i+len-1,min(i+len*2-1,n)); // 仔细理解这一句话,想明白归并排序非递归实现就想明白大半了 
		}
	}
	// 让我们康康归并排序的结果怎么样
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl; 
	return 0; 
}
