#include<iostream>
#define maxn 100
using namespace std;
const int INF = 0x3f3f3f3f;
int get_D_min(int D[],bool vis[],int n){
	int pos,min_ = INF;
	for(int i=1; i<=n; i++){
		if(!vis[i] && min_ > D[i]){
			min_ = D[i];
			pos = i;
		}
	}
	return pos;
}
int main(){
	int G[maxn][maxn];
	int D[maxn];
	int F[maxn];
	bool vis[maxn];
	int n,m; 
	puts("请输入点数n和边数m，以及这m条边（无向边，点的编号从1开始）");
	cin>>n>>m;
	//初始化G
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i == j) G[i][j] = 0;
			else G[i][j] = INF;
		}
	}
	int u,v,w;
	for(int i=1; i<=m; i++) {
		cin>>u>>v>>w;
		G[u][v] = w; 
		G[v][u] = w;
	}
	//初始化D，vis
	for(int i=1; i<=n; i++){
		D[i] = INF;
		F[i] = -1;
		vis[i] = false;
	}
	int MIST = 0;
	D[1] = 0;
	for(int i=1; i<=n; i++){
		int p = get_D_min(D,vis,n);
		vis[p] = true;
		MIST += D[p];
		for(int j=1; j<=n; j++){
			if(!vis[j] && G[p][j] < D[j]){ //只有对于没有纳入MIST的点才进行更改 
				D[j] = G[p][j];
				F[j] = p;
			}
		}
	}
	cout<<"最小生成树的权值为"<<endl;
	cout<<MIST<<endl;
	 
	return 0;
}
