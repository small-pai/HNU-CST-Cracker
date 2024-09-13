#include<iostream>
#include<cstdio>
#define maxn_row 100
#define maxn_col 100
using namespace std;
/*****************************************************************************************************************
	1.�ö������Թ������ǲ������������߽й������������BFS��
	2.���������������һ��һ�������������һ����������ᷢ�֣��ҵ�һ���������յ㣬��ô��һ��·��һ���ǳ�����̵�
*******************************************************************************************************************/
struct Status{
	int x,y;
	int from;//�����Լ����״̬������һ��״̬���� 
};
void find_one_shortest_path(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
	bool vis[maxn_row][maxn_col];
	Status q[maxn_row*maxn_col];
	int head = 0, tail = 0;
	//������ 
	Status e;
	e.x = sx;
	e.y = sy;
	e.from = -1;
	q[tail++] = e;
	vis[sx][sy] = true;
	
	int nx,ny;
	Status next;
	while(tail - head){
		e = q[head++];
		if(e.x == ex && e.y == ey){ //�ߵ����յ㣬���� 
			//��������ǵ����
			printf("(%d,%d) ",ex,ey);
			while(e.from != -1){
				e = q[e.from];
				printf("(%d,%d) ",e.x,e.y);
			}
			puts("");
			return ;
		}
		for(int i=0; i<=3; i++){
			nx = e.x + dir[i][0];
			ny = e.y + dir[i][1];
			if(G[nx][ny] == 0 && vis[nx][ny] == false){
				//���
				next.x = nx;
				next.y = ny;
				next.from = head-1;
				q[tail++] = next;
				vis[nx][ny] = true; 
			}
		}
	}
	return ;
}
int main(){
	const int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};//4������ ��������
	int G[maxn_row][maxn_col]; //�������ͼ maxn_row 1000,maxn_col 1000 int n,m; //��ͼ�Ĵ�С
	int sx,sy,ex,ey; // (sx,sy)��ʾ������� (ex,ey)��ʾ�������� 
	int n,m;
	puts("�������ͼ������n�Լ�����m,�Լ������ͼ���涨1����˴������ߣ�0����˴�����");
	//�û������ͼ
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			cin>>G[i][j];
		}
	}
	puts("��������ںͳ��ڵ����꣬�뱣֤��ڣ������ǺϷ���");
	cin>>sx>>sy>>ex>>ey;
	
	//Ϊ�˳�����ӵļ�࣬�����ڵ�ͼ���������һȦ�����ߵĵ� 
	for(int i=0; i<=n+1; i++) G[i][0] = G[i][m+1] = 1;
	for(int j=0; j<=m+1; j++) G[0][j] = G[n+1][j] = 1;
	
	//
	find_one_shortest_path(G,n,m,sx,sy,ex,ey,dir); 
	return 0;
}
