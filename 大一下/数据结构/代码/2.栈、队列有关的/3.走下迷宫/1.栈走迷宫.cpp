#include<iostream>
#define maxn_row 100
#define maxn_col 100
#define maxn_capacity maxn_row*maxn_col 
using namespace std;
/*
	��һ��find_one_path() ��15��
	�ڶ���find_one_path() ��74��
	
	��һ��find_all_paths() ��141��
	�ڶ���find_all_paths() ��201�� 
*/
struct Status{ //ջ���洢������ݣ����ǽ����Ϊ״̬��ջ���洢����״̬��ջ���洢�������״̬��ʾ���Ҵ�����ߵ���ǰλ�õ�·����������ÿ����������һ������ǰ���� 
	int x,y,d;
};
bool is_ok(int G[][maxn_col],bool vis[][maxn_col],int x,int y){
	return G[x][y] == 0 && vis[x][y] == false;
}
//// @��һ�� find_one_path���� �� �Ҹ������ڵڶ���find_one_path���߼�����71�У� 
//void find_one_path(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
//	bool vis[maxn_row][maxn_col]; //vis������������ǵ�ǰ�Ѿ��߹��ĵ�
//	Status s[maxn_capacity]; //��ջ���������ע��ջ�Ĵ�СӦ������Ϊ��ͼ�ķ���������maxn_row*maxn_col������˵�û�����ĵ�ͼ��n��m����ô�������Ϊn*m 
//	int tail = 0;
//	//��ʼ�� vis
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			vis[i][j] = false;
//		}
//	}
//	/*********************************************
//		���Թ����߼������ҵ�ջ���洢�����ߵ���ǰ��(now_x,now_y)��·���ϵĵ��Լ���״̬�����Ƿ���
//	***********************************************/
//
//	Status e;
//	// �����ջ 
//	e.x = sx;
//	e.y = sy;
//	e.d = -1;
//	s[tail++] = e;
//	vis[sx][sy] = true;
//	
//	int now_x = 0,now_y = 0; //��ǰ���ڵ�λ�� 
//	while(tail){
//		if(is_ok(G,vis,now_x,now_y)){ //��ǰλ�ÿ������������ 
//			if(now_x == ex && now_y == ey){ //�ߵ����յ㣬�������·�� 
//				puts("�ҵ���һ��·��"); 
//				for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y); //������ò�Ҫ������������ܷܺ��㣬�����Ҿ��û�������ʵʵ�ĵ������ 
//				printf("(%d,%d)\n",ex,ey); //���յ㲹�� 
//				return ;
//			}
//			//û�ߵ��յ������
//			e.x = now_x;
//			e.y = now_y;
//			e.d = 0;
//			s[tail++] = e;
//			vis[now_x][now_y] = true;
//			
//			now_x = now_x+dir[0][0];
//			now_y = now_y+dir[0][1];
//		}
//		else {
//			while(tail){ //��ջ���ҵ���һ��4������û�б�������� 
//				e = s[--tail]; //ע��������������·��ʱ��vis�����𣡣��� 
//				if(e.d < 3) break;
//			}
//			if(e.d < 3){
//				e.d++;
//				//�ߵ���һ�� 
//				now_x = e.x + dir[e.d][0];
//				now_y = e.y + dir[e.d][1];
//				s[tail++] = e; //��ջ 
//			}
//		}
//	}
//	return ; 
//}
//// @�ڶ���find_one_path()����������Ϊ����뷨���ӵ�����һЩ �� ���忴�Լ������ 
//void find_one_path(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
//	bool vis[maxn_row][maxn_col]; //vis������������ǵ�ǰ�Ѿ��߹��ĵ�
//	Status s[maxn_capacity]; //��ջ���������ע��ջ�Ĵ�СӦ������Ϊ��ͼ�ķ���������maxn_row*maxn_col������˵�û�����ĵ�ͼ��n��m����ô�������Ϊn*m 
//	int tail = 0;
//	//��ʼ�� vis
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			vis[i][j] = false;
//		}
//	}
//	/*********************************************
//		���Թ����߼������ҵ�ջ���洢�����ߵ���ǰ��(now_x,now_y)��·���ϵĵ��Լ���״̬�����Ƿ���
//	***********************************************/
//
//	Status e;
//	// �����ջ 
//	e.x = sx;
//	e.y = sy;
//	e.d = -1;
//	s[tail++] = e;
//	vis[sx][sy] = true;
//	
//	int now_x = 0,now_y = 0; //��ǰ���ڵ�λ�� 
//	while(tail){
//		//�ҵ���һ���������ߣ���(now_x,now_y)Ӧ���Ƕ��� 
//		e = s[--tail];
//		if(e.d == 3) continue;
//		e.d++;
//		now_x = e.x + dir[e.d][0];
//		now_y = e.y + dir[e.d][1];
//		s[tail++] = e;
//		//
//		if(now_x == ex && now_y == ey){ //�ҵ��ˣ������һ��·�� 
//		/*	
//			for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y); 
//			�������·���ǿ��Եģ���ֱ������ȷ��˳�򣬵��Ƕ���һ��ջ���ԣ������������е㲻�Ϲ�أ���Ϊһ��ջ
//			�����ǲ�Ӧ��ȡ���ʳ�ջ�������Ԫ�صģ������������Ǿ�ֱ�ӵ������
//		*/	
//			puts("���������һ��·��");
//			printf("(%d,%d) ",ex,ey);
//			while(tail){
//				e = s[--tail];
//				printf("(%d,%d) ",e.x,e.y);
//			}
//			puts("");																			 
//			return ;
//		}
//		if(is_ok(G,vis,now_x,now_y)){ //�����һ������ߣ���ô���Ǿͽ������ջ�� 
//			e.x = now_x;
//			e.y = now_y;
//			e.d = -1;
//			s[tail++] = e;
//			vis[now_x][now_y] = true;
//		}
//	}
//	return ; 
//}

/**********************************************************************************************************************
	1.������·���ĺ�����ʵ������һ��·���ĺ�����һЩ�޸�
	2.������·���Ĵ�������һ��·����࣬ϸ������vis���ҵ��˲�Ҫ���أ�����������·�Ĺؼ��� 
	3.����Ȼ����ʵ�������ڶ��ֵ��߼����ӵ�������ʵ������������Ҳ��С�����忴�Լ������
	4.(now_x,now_y)��Ȼ��ʾ��ǰ�ߵ���λ�� 
**********************************************************************************************************************/
// @��һ��find_all_paths()��д��
void find_all_paths(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
	
	bool vis[maxn_row][maxn_col]; //vis������������ǵ�ǰ�Ѿ��߹��ĵ�
	Status s[maxn_capacity]; //��ջ���������ע��ջ�Ĵ�СӦ������Ϊ��ͼ�ķ���������maxn_row*maxn_col������˵�û�����ĵ�ͼ��n��m����ô�������Ϊn*m 
	int tail = 0;
	int num = 0; // ͳ��·�������� 
	//��ʼ�� vis
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			vis[i][j] = false;
		}
	}
	Status e;
	// �����ջ 
	e.x = sx;
	e.y = sy;
	e.d = -1;
	s[tail++] = e;
	vis[sx][sy] = true;
	
	int now_x = 0,now_y = 0; //��ǰ���ڵ�λ�� 
	while(tail){
		if(is_ok(G,vis,now_x,now_y) && !(now_x == ex && now_y == ey)){ //(now_x,now_y)�����߲��Ҳ����յ� 
			e.x = now_x;
			e.y = now_y;
			e.d = 0;
			s[tail++] = e;
			vis[e.x][e.y] = true;
			//�ߵ���һ��
			now_x = now_x + dir[0][0];
			now_y = now_y + dir[0][1];
		}
		else { //(now_x,now_y)�����߻�����(now_x,now_y)���յ� 
			if(now_x == ex && now_y == ey){ //�ҵ�һ��·������� 
				num++;
				for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y);
				printf("(%d,%d)",ex,ey);
				puts("");
			}
			while(tail){ //��ջ���ҵ���һ���ĸ�����û���������״̬e 
				e = s[--tail];
				vis[e.x][e.y] = false;
				if(e.d < 3) break;
			}
			if(e.d < 3){
				//������һ�� 
				e.d++;
				now_x = e.x + dir[e.d][0];
				now_y = e.y + dir[e.d][1];
				//��ǰ״̬��ջ
				s[tail++] = e;
				vis[e.x][e.y] = true; 
			}
		}
	}
	printf("һ����%d��·��\n",num); 
	return ; 
}
//// @�ڶ���find_all_paths()��д�� 
//void find_all_paths(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
//	
//	bool vis[maxn_row][maxn_col]; //vis������������ǵ�ǰ�Ѿ��߹��ĵ�
//	Status s[maxn_capacity]; //��ջ���������ע��ջ�Ĵ�СӦ������Ϊ��ͼ�ķ���������maxn_row*maxn_col������˵�û�����ĵ�ͼ��n��m����ô�������Ϊn*m 
//	int tail = 0;
//	int num = 0; // ͳ��·�������� 
//	//��ʼ�� vis
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			vis[i][j] = false;
//		}
//	}
//	Status e;
//	// �����ջ 
//	e.x = sx;
//	e.y = sy;
//	e.d = -1;
//	s[tail++] = e;
//	vis[sx][sy] = true;
//	
//	int now_x = 0,now_y = 0; //��ǰ���ڵ�λ�� 
//	while(tail){
//		//�ҵ���һ�������� �� (now_x,now_y)��ֵ�Ƕ��� 
//		e = s[--tail];
//		vis[e.x][e.y] = false; //��һ����һ�� 
//		if(e.d == 3) continue; //�õ����з��򶼱������ˣ�ֱ��continue������������һ��״̬ 
//		e.d++;
//		now_x = e.x + dir[e.d][0];
//		now_y = e.y + dir[e.d][1];
//		s[tail++] = e;
//		vis[e.x][e.y] = true; //�ڶ�����һ��
//		
//		//
//		if(now_x == ex && now_y == ey){ //�ҵ��ˣ������һ��·�� 
//		/*	
//			for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y); 
//			�������·���ǿ��Եģ���ֱ������ȷ��˳�򣬵��Ƕ���һ��ջ���ԣ������������е㲻�Ϲ�أ���Ϊһ��ջ
//			�����ǲ�Ӧ��ȡ���ʳ�ջ�������Ԫ�ص�
//		*/	
//			num++; 		// ������һ 
//			//��Ϊ����������Ϊ��������е�·������Ҫ����ջ�������Ϣ��������ջֱ����ջ��Ԫ�ض������ˣ��������Ǿ�ֱ���������Ȼ�ܲ���qwq 
//			for(int i=0; i<tail; i++)printf("(%d,%d) ",s[i].x,s[i].y); //��������������ԭ��������ֱ��ʹ������ģ��ջ���������ջ�������е�Ԫ���Ǻ����ɵģ������ܸо��е㲻�� 
//			printf("(%d,%d)",ex,ey);
//			puts("");
//			//�����������Ҫreturn 
//			continue;     //��������һ�������� ��Ҫreturn��ֱ�ӽ�������������Ӧ�ü�������һ��·��������continue������ 
//		}
//		if(is_ok(G,vis,now_x,now_y)){ //�����һ������ߣ���ô���Ǿͽ������ջ�� 
//			e.x = now_x;
//			e.y = now_y;
//			e.d = -1;
//			s[tail++] = e;
//			vis[now_x][now_y] = true;
//		}
//	}
//	printf("һ����%d��·��\n",num); 
//	return ; 
//}
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
//	puts("����һ������·��");
//	find_one_path(G,n,m,sx,sy,ex,ey,dir);
	puts("����·��");
	find_all_paths(G,n,m,sx,sy,ex,ey,dir);
	return 0;
}
