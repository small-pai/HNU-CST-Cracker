#include<iostream>
#include<cstdio>
#define maxn_row 100
#define maxn_col 100
using namespace std;
/*****************************************************************************************************************
	1.用队列走迷宫，就是层序搜索，或者叫广度优先搜索（BFS）
	2.广度优先搜索就是一层一层的搜索，从这一点出发，你便会发现，我第一次搜索到终点，那么这一条路径一定是长度最短的
*******************************************************************************************************************/
struct Status{
	int x,y;
	int from;//代表自己这个状态是由哪一个状态来的 
};
void find_one_shortest_path(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
	bool vis[maxn_row][maxn_col];
	Status q[maxn_row*maxn_col];
	int head = 0, tail = 0;
	//起点入队 
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
		if(e.x == ex && e.y == ey){ //走到了终点，结束 
			//这样输出是倒序的
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
				//入队
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
	const int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};//4个方向 上下左右
	int G[maxn_row][maxn_col]; //定义出地图 maxn_row 1000,maxn_col 1000 int n,m; //地图的大小
	int sx,sy,ex,ey; // (sx,sy)表示入口坐标 (ex,ey)表示出口坐标 
	int n,m;
	puts("请输入地图的行数n以及列数m,以及这个地图，规定1代表此处不可走，0代表此处可走");
	//用户输入地图
	cin>>n>>m;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			cin>>G[i][j];
		}
	}
	puts("请输入入口和出口的坐标，请保证入口，出口是合法的");
	cin>>sx>>sy>>ex>>ey;
	
	//为了程序更加的简洁，我们在地图的最外面加一圈不可走的点 
	for(int i=0; i<=n+1; i++) G[i][0] = G[i][m+1] = 1;
	for(int j=0; j<=m+1; j++) G[0][j] = G[n+1][j] = 1;
	
	//
	find_one_shortest_path(G,n,m,sx,sy,ex,ey,dir); 
	return 0;
}
