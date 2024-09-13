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
	puts("���������n�ͱ���m���Լ���m���ߣ�����ߣ���ı�Ŵ�1��ʼ��");
	cin>>n>>m;
	//��ʼ��G
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
	//��ʼ��D��vis
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
			if(!vis[j] && G[p][j] < D[j]){ //ֻ�ж���û������MIST�ĵ�Ž��и��� 
				D[j] = G[p][j];
				F[j] = p;
			}
		}
	}
	cout<<"��С��������ȨֵΪ"<<endl;
	cout<<MIST<<endl;
	 
	return 0;
}
