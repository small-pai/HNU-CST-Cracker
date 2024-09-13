#include<bits/stdc++.h>
using namespace std;
struct edge{
	int end;
	edge * next_edge;
};
struct vertex{
	int ind;
	edge* first_edge;
};

int main(){
//	freopen("in.txt","r",stdin);
	// 建图
	vertex G[100];
	for(int i = 0;i<100;++i){
		G[i].ind = 0;
		G[i].first_edge = NULL;
	}
	int n,m;
	puts("请输入节点数n和边数m");
	cin>>n>>m;
	int u,v;
	for(int i=0;i<m;++i){
		cin>>u>>v;
		edge * now = new edge;
		now->end = v;
		now->next_edge = G[u].first_edge;
		G[u].first_edge = now;
	} 
	
	//计算入度
	int inde;
	for(int i=1;i<=n;++i){
		edge * p = G[i].first_edge;
		while(p){
			G[p->end].ind++;
			p = p->next_edge;
		}
	}
	//拓扑
	int index_tuopu = 0;
	int tuopu[100];
	int que[100];
	int head = 0;
	int tail = 0;
	for(int i = 1;i<=n;++i){
		if(G[i].ind == 0){
			que[tail] = i;
			tail++;
		}
	}
	while(head != tail){ //head < tail
		int now = que[head];
		head++;
		tuopu[index_tuopu] = now;
		index_tuopu++;
		edge * p = G[now].first_edge;
		while(p){
			G[p->end].ind--;
			if(G[p->end].ind == 0){
				que[tail] = p->end;
				tail++;
			}
			p = p->next_edge;
		}
	}
	for(int i=0;i<index_tuopu;++i){
		cout<<tuopu[i]<<" ";
	}
	cout<<endl;
	return 0;
}
