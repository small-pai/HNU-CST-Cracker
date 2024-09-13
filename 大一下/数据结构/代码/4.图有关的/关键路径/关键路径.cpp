#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct edge{
	int end;
	int w;
	int Ee;
	int El;
	edge * next_edge;
};
struct vertex{
	int ind;
	int outd;
	int Ve;
	int Vl;
	edge* first_edge;
};
//int max(int a,int b){
//	return a>b?a:b;
//}
struct path{
	int s;
	int e;
	int w;
};
int main(){
	//��ͼ
	vertex G[100];
	for(int i = 0;i<100;++i){
		G[i].ind = 0;
		G[i].outd = 0;
		G[i].first_edge = NULL;
	}
	int n,m;
	puts("������ڵ���n�ͱ���m");
	cin>>n>>m;
	int u,v,w;
	for(int i=0;i<m;++i){
		cin>>u>>v>>w;
		edge * now = new edge;
		now->end = v;
		now->w = w;
		now->next_edge = G[u].first_edge;
		G[u].first_edge = now;
		G[u].outd++;
	}

	//�������
	int inde;
	for(int i=1;i<=n;++i){
		edge * p = G[i].first_edge;
		while(p){
			G[p->end].ind++;
			p = p->next_edge;
		}
	}
	//����
	int que[100], head = 0, tail = 0; //����
	int sta[100], top = 0; // ����Ԫ�����ջ
		//ini
	for(int i=1; i<=n; i++){
		G[i].Ve = 0;
		G[i].Vl = INF;
	}
	// ������
	for(int i = 1;i<=n;++i){
		if(G[i].ind == 0){
			que[tail] = i;
			tail++;
		}
	}
	// ��ÿ��������緢��ʱ�� Ve //ʵ��Ϊ��������Ĺ���
	while(head < tail){
		int now = que[head++];
		sta[top++] = now;
		edge *p = G[now].first_edge;
		while(p){
			p->Ee = G[now].Ve;
			G[p->end].Ve = max(G[p->end].Ve,G[now].Ve+p->w);
//			if(G[now].Ve+p->w > G[p->end].Ve) G[p->end].Ve = G[now].Ve+p->w;
			G[p->end].ind--;
			if(G[p->end].ind == 0) que[tail++] =p->end;

			p = p->next_edge;
		}
	}
	//���յ�
//	int end = -1;
//	for(int i=1; i<=n; i++){
//		if(G[i].outd == 0){
//			end = i;
//			break;
//		}
//	}

	int end = que[tail-1];
	int T = G[end].Ve;
	G[end].Vl = T;
	path key_path[200]; int key_path_index = 0;
	while(top){ // top != 0;
		int now = sta[--top];
		edge *p = G[now].first_edge;
		while(p){
			p->El = G[p->end].Vl - p->w;
			if(p->Ee == p->El) { //�ж�����p��ָ��ı��ǲ��ǹؼ�·��
				path e;
				e.s = now;
				e.e = p->end;
				e.w = p->w;
				key_path[key_path_index++] = e;
			}
			G[now].Vl = min(G[now].Vl,G[p->end].Vl-p->w);
			p = p->next_edge;
		}
	}
	puts("��Щ·���ǹؼ�·��");
	for(int i = 0; i<key_path_index; i++){
		printf("%d -> %d w = %d\n",key_path[i].e,key_path[i].s,key_path[i].w);
	}
	return 0;
}

