#include<bits/stdc++.h>
using namespace std;;
const int maxn = 1000;
void merge(int R[],int tem[],int s,int m,int e){
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
void gb_sort(int R[],int tem[],int s,int e){ // 对区间[s,e]排好序 
	if(s == e) return ;
	
	int m = (s+e)/2;// 还可以写成 m = (s+e)>>1; 
	gb_sort(R,tem,s,m);
	gb_sort(R,tem,m+1,e);
	merge(R,tem,s,m,e);//将区间[s,m],[m+1,e]合并 
	return ;
}
int main(){
	int n;
	int R[maxn];
	int tem[maxn];
	//输入数据
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	gb_sort(R,tem,1,n);
	//康康结果
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl; 
	return 0;
}
