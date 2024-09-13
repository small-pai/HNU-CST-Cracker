#include<bits/stdc++.h>
using namespace std;
int get_figure(int x){
	int base = 1;
	for(int i=1; ;i++){
		base = base*10;
		if(x/base == 0) return i; 
	}
}
int get_digit(int x,int p){//x 的 第p位数 
	int base = 1;
	for(int i=1; i<=p-1; i++){
		base = base*10;
	}
	return x/base%10; 
}
struct Bucket{
	int f;
	int e; 
};
int main(){
	int n;
	int R[1000];
	//读入数据
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	// 建链 
	int L[1000];
	for(int i=0; i<n; i++) L[i] = i+1;
	L[n] = -1;// L[n] = 0;
	// 最多有多少位 
	int max_figure = 0;
	for(int i=1; i<=n; i++) max_figure = max(max_figure,get_figure(R[i]));
//	for(int i=1; i<=n; i++){
//		if(max_figure < get_figure(R[i])) max_figure =  get_figure(R[i]);
//	}
	//建桶
	Bucket T[10];
	// 
	for(int i=1; i<=max_figure; i++){
		//将桶清空
		for(int i=0; i<=9; i++) T[i].f = T[i].e = -1;
		//
		int p = L[0];
		while(p != -1){
			int t = get_digit(R[p],i);
			//将R[p]这个数放入t号桶
			if(T[t].f == -1){
				T[t].f = p;
				T[t].e = p;
			}
			else{
				L[T[t].e] = p;
				T[t].e = p;
			}
			p = L[p];
		}
		//每个桶的元素链起来起来
		int pre = 0;//当前链的最后一个是第几号元素 
		for(int i=0; i<=9; i++){
			if(T[i].f != -1){
				L[pre] = T[i].f;
				pre = T[i].e;
			}
		}
		L[pre] = -1;
	}
	
//	int p = L[0];
//	while(p != -1){
//		cout<<R[p]<<"  ";
//		p = L[p];
//	}
//	cout<<endl;
//	cout<<"R[] = ? "<<endl;
//	for(int i=1; i<=n; i++) cout<<R[i]<<" ";cout<<endl;
//	
	// 新开的数组
//	int temp[1000];
//	int index = 1;
//	int p = L[0];
//	while(p != -1){
//		temp[index++] = R[p];
//		p = L[p];
//	}
//	for(int i=1; i<=n; i++) cout<<temp[i]<<" "; cout<<endl;
//	for(int i=1; i<=n; i++) R[i] = temp[i];
//	for(int i=1; i<=n; i++) cout<<R[i]<<" "; cout<<endl;
	// 只在R中进行交换操作 - “搬家” 
	int i = 1;
	int p = L[0];
	while(p != -1){
		if(i == p){
			p = L[p];
			i++;
		}
		else if(i < p){
			int p_next = L[p];
			swap(R[i],R[p]);
			L[p] = L[i];
			L[i] = p;
			p = p_next;
			i++;
		}
		else if(i > p){
			while(p < i) p = L[p];
		}
	}
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";cout<<endl; 
	return 0;
}
