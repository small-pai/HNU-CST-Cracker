#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int get_D_min_pos(int *D,int n,bool *vis){
	int min_ = INF;
	int pos = -1;
	//����D����,�ҵ���Сֵ����λ��pos
	for(int i=1; i<=n; i++){
		if(vis[i] == false){
			if(min_ > D[i]){
				min_ = D[i];
				pos = i;
			}
		}
	}
	return pos;
}
int main(){
//	freopen("in.txt","r",stdin);
	int G[100][100];
	puts("�������ж��ٸ��ڵ�n,�ж�������m,��������n���ߵ���Ϣ");
	int n;
	int m;
	int u,v,w;
	cin>>n;
	cin>>m;
	//ini 
	for(int i=1; i<=n; i++){
		cout<<i<<endl;
		for(int j=1; j<=n; j++){
			G[i][j] = INF;
		} 
	}
	for(int i=0; i<m; i++){
		cin>>u>>v>>w;
		G[u][v] = w;
		G[v][u] = w;
	}
	// ���Ϊ1
	int D[100];
	int p[100];
	bool vis[100]; //�жϽڵ�i�Ƿ����·���Ѿ�ȷ�� 
	//ini
	for(int i=1; i<=n; i++) D[i] = INF;
	for(int i=1; i<=n; i++) p[i] = -1;
	for(int i=1; i<=n; i++) vis[i] = false;
	D[1] = 0;
	
	for(int i=1; i<=n; i++){
		//�ҳ�D�����е���Сֵ
		int t = get_D_min_pos(D,n,vis);
		vis[t] = true; //�ڵ�t�����·��ȷ��,vis������Ϊtrue 
		for(int i=1; i<=n; i++){
			if(G[t][i] != INF){
				if(D[t]+G[t][i] < D[i]){
					D[i] = D[t] + G[t][i];
					p[i] = t;
				}
			}
		}
	}
	for(int i=1; i<=n ;i++) {
		printf("�����1���ڵ�%d����̾�����%d\n",i,D[i]);
	}
	return 0;
}
