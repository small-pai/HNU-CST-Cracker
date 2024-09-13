#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
struct edge{
	int u;
	int v;
	int w;
};
bool cmp(const edge& a,const edge& b){
	return a.w < b.w;
}
int get_ancester(int* F,int node){
	int t = node;
	while(F[t] != -1){
		t = F[t];
	}
	return t; 
}
int main(){
	edge e[1000];
	puts("请输入边的数量n，以及这n条边的信息");
	int n;
	cin>>n;
	int u,v,w;
	//读图 
	for(int i = 1; i<=n; i++){
		cin>>u>>v>>w;
		e[i].u = u;
		e[i].v = v;
		e[i].w = w;
	}
	//按边的权重从小到大排序 注意考试的时候可能不可以用STL里的sort，所以可以自己写排序，或者每一次for一遍所有边找出最短的边 
	sort(e+1,e+1+n,cmp);
	//
	for(int i=1; i<=n; i++){
		cout<<"i = "<<i<<"u : "<<e[i].u<<" v : "<< e[i].v << "w : "<< e[i].w<<endl; 
	}
	// define F ,ini
	int F[2000];
	for(int i=0; i<2000; i++) F[i] = -1;
	int sum = 0;
	// mist 储存 
	edge mist[1000];
	int index = 0;
	// 
	for(int i=1; i<=n; i++){
		edge now = e[i];
		int u = now.u;
		int v = now.v;
		int w = now.w;
		int ancester_u = get_ancester(F,u);
		int ancester_v = get_ancester(F,v);
		if(ancester_u == ancester_v) continue;
		else {
			F[ancester_u] = ancester_v;
			sum += w;
			mist[index] = now;
			index++;
//			mist[index++] = now;
		}
	}
	//out
	cout<<"MIST 的权值和为"<<sum<<endl;
	cout<<"将这几条边相连可以得到最小生成树"<<endl;
	for(int i=0; i<index; i++){
		cout<<"u = "<<mist[i].u<<"v = "<<mist[i].v <<"w = "<<mist[i].w<<endl; 
	}
	return 0;
}

