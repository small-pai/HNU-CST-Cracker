#include<iostream>
#define maxn 100
using namespace std;
const int INF = 0x3f3f3f3f;
int main(){
	int G[maxn][maxn];
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
	for(int k=1; k<=n; k++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				G[i][j] = min(G[i][j],G[i][k]+G[k][j]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(G[i][j] == INF) printf("%-5s ","INF");
			else printf("%-5d ",G[i][j]);
		}
		puts("");
	}
	return 0;
}
