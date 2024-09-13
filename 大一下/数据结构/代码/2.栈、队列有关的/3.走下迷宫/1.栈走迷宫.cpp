#include<iostream>
#define maxn_row 100
#define maxn_col 100
#define maxn_capacity maxn_row*maxn_col 
using namespace std;
/*
	第一种find_one_path() 见15行
	第二种find_one_path() 见74行
	
	第一种find_all_paths() 见141行
	第二种find_all_paths() 见201行 
*/
struct Status{ //栈里面储存的数据，我们将其称为状态，栈里面储存了状态，栈里面储存的所有状态表示了我从起点走到当前位置的路径，包括在每个点是往哪一个方向前进的 
	int x,y,d;
};
bool is_ok(int G[][maxn_col],bool vis[][maxn_col],int x,int y){
	return G[x][y] == 0 && vis[x][y] == false;
}
//// @第一种 find_one_path函数 ， 我更倾向于第二种find_one_path的逻辑（见71行） 
//void find_one_path(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
//	bool vis[maxn_row][maxn_col]; //vis数组是用来标记当前已经走过的点
//	Status s[maxn_capacity]; //把栈定义出来，注意栈的大小应该至少为地图的方格数，即maxn_row*maxn_col，或者说用户输入的地图的n，m，那么最大至少为n*m 
//	int tail = 0;
//	//初始化 vis
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			vis[i][j] = false;
//		}
//	}
//	/*********************************************
//		走迷宫的逻辑就是我的栈里面储存我走到当前点(now_x,now_y)的路径上的点以及其状态（就是方向）
//	***********************************************/
//
//	Status e;
//	// 起点入栈 
//	e.x = sx;
//	e.y = sy;
//	e.d = -1;
//	s[tail++] = e;
//	vis[sx][sy] = true;
//	
//	int now_x = 0,now_y = 0; //当前所在的位置 
//	while(tail){
//		if(is_ok(G,vis,now_x,now_y)){ //当前位置可以走则继续走 
//			if(now_x == ex && now_y == ey){ //走到了终点，输出这条路径 
//				puts("找到了一条路径"); 
//				for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y); //！！最好不要这样输出，尽管很方便，但是我觉得还是老老实实的倒叙输出 
//				printf("(%d,%d)\n",ex,ey); //把终点补上 
//				return ;
//			}
//			//没走到终点继续走
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
//			while(tail){ //退栈，找到第一个4个方向没有被搜索完的 
//				e = s[--tail]; //注意这里与找所有路径时的vis的区别！！！ 
//				if(e.d < 3) break;
//			}
//			if(e.d < 3){
//				e.d++;
//				//走到下一步 
//				now_x = e.x + dir[e.d][0];
//				now_y = e.y + dir[e.d][1];
//				s[tail++] = e; //入栈 
//			}
//		}
//	}
//	return ; 
//}
//// @第二种find_one_path()函数，我认为这个想法更加的清晰一些 ， 具体看自己的理解 
//void find_one_path(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
//	bool vis[maxn_row][maxn_col]; //vis数组是用来标记当前已经走过的点
//	Status s[maxn_capacity]; //把栈定义出来，注意栈的大小应该至少为地图的方格数，即maxn_row*maxn_col，或者说用户输入的地图的n，m，那么最大至少为n*m 
//	int tail = 0;
//	//初始化 vis
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			vis[i][j] = false;
//		}
//	}
//	/*********************************************
//		走迷宫的逻辑就是我的栈里面储存我走到当前点(now_x,now_y)的路径上的点以及其状态（就是方向）
//	***********************************************/
//
//	Status e;
//	// 起点入栈 
//	e.x = sx;
//	e.y = sy;
//	e.d = -1;
//	s[tail++] = e;
//	vis[sx][sy] = true;
//	
//	int now_x = 0,now_y = 0; //当前所在的位置 
//	while(tail){
//		//找到下一步往哪里走，即(now_x,now_y)应该是多少 
//		e = s[--tail];
//		if(e.d == 3) continue;
//		e.d++;
//		now_x = e.x + dir[e.d][0];
//		now_y = e.y + dir[e.d][1];
//		s[tail++] = e;
//		//
//		if(now_x == ex && now_y == ey){ //找到了，输出这一条路径 
//		/*	
//			for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y); 
//			这样输出路径是可以的，就直接是正确的顺序，但是对于一个栈而言，我们这样做有点不合规矩，因为一个栈
//			我们是不应该取访问除栈顶以外的元素的，所以这里我们就直接倒叙输出
//		*/	
//			puts("倒叙输出这一条路径");
//			printf("(%d,%d) ",ex,ey);
//			while(tail){
//				e = s[--tail];
//				printf("(%d,%d) ",e.x,e.y);
//			}
//			puts("");																			 
//			return ;
//		}
//		if(is_ok(G,vis,now_x,now_y)){ //如果这一点可以走，那么我们就将其加入栈中 
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
	1.找所有路径的函数其实就是找一条路径的函数做一些修改
	2.找所有路径的代码与找一天路径差不多，细节在于vis，找到了不要返回（这是找所有路的关键） 
	3.我仍然觉得实现起来第二种的逻辑更加的清晰，实现起来代码量也更小，具体看自己的理解
	4.(now_x,now_y)仍然表示当前走到的位置 
**********************************************************************************************************************/
// @第一种find_all_paths()的写法
void find_all_paths(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
	
	bool vis[maxn_row][maxn_col]; //vis数组是用来标记当前已经走过的点
	Status s[maxn_capacity]; //把栈定义出来，注意栈的大小应该至少为地图的方格数，即maxn_row*maxn_col，或者说用户输入的地图的n，m，那么最大至少为n*m 
	int tail = 0;
	int num = 0; // 统计路径的数量 
	//初始化 vis
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			vis[i][j] = false;
		}
	}
	Status e;
	// 起点入栈 
	e.x = sx;
	e.y = sy;
	e.d = -1;
	s[tail++] = e;
	vis[sx][sy] = true;
	
	int now_x = 0,now_y = 0; //当前所在的位置 
	while(tail){
		if(is_ok(G,vis,now_x,now_y) && !(now_x == ex && now_y == ey)){ //(now_x,now_y)可以走并且不是终点 
			e.x = now_x;
			e.y = now_y;
			e.d = 0;
			s[tail++] = e;
			vis[e.x][e.y] = true;
			//走到下一步
			now_x = now_x + dir[0][0];
			now_y = now_y + dir[0][1];
		}
		else { //(now_x,now_y)不可走或者是(now_x,now_y)是终点 
			if(now_x == ex && now_y == ey){ //找到一条路径，输出 
				num++;
				for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y);
				printf("(%d,%d)",ex,ey);
				puts("");
			}
			while(tail){ //退栈，找到第一个四个方向没有搜索完的状态e 
				e = s[--tail];
				vis[e.x][e.y] = false;
				if(e.d < 3) break;
			}
			if(e.d < 3){
				//走向下一步 
				e.d++;
				now_x = e.x + dir[e.d][0];
				now_y = e.y + dir[e.d][1];
				//当前状态入栈
				s[tail++] = e;
				vis[e.x][e.y] = true; 
			}
		}
	}
	printf("一共有%d条路径\n",num); 
	return ; 
}
//// @第二种find_all_paths()的写法 
//void find_all_paths(int G[][maxn_col],int n,int m,int sx,int sy,int ex,int ey,const int dir[][2]){
//	
//	bool vis[maxn_row][maxn_col]; //vis数组是用来标记当前已经走过的点
//	Status s[maxn_capacity]; //把栈定义出来，注意栈的大小应该至少为地图的方格数，即maxn_row*maxn_col，或者说用户输入的地图的n，m，那么最大至少为n*m 
//	int tail = 0;
//	int num = 0; // 统计路径的数量 
//	//初始化 vis
//	for(int i=1; i<=n; i++){
//		for(int j=1; j<=m; j++){
//			vis[i][j] = false;
//		}
//	}
//	Status e;
//	// 起点入栈 
//	e.x = sx;
//	e.y = sy;
//	e.d = -1;
//	s[tail++] = e;
//	vis[sx][sy] = true;
//	
//	int now_x = 0,now_y = 0; //当前所在的位置 
//	while(tail){
//		//找到下一步走哪里 即 (now_x,now_y)的值是多少 
//		e = s[--tail];
//		vis[e.x][e.y] = false; //第一处不一样 
//		if(e.d == 3) continue; //该点所有方向都被搜索了，直接continue，继续弹出下一个状态 
//		e.d++;
//		now_x = e.x + dir[e.d][0];
//		now_y = e.y + dir[e.d][1];
//		s[tail++] = e;
//		vis[e.x][e.y] = true; //第二处不一样
//		
//		//
//		if(now_x == ex && now_y == ey){ //找到了，输出这一条路径 
//		/*	
//			for(int i=0; i<tail; i++) printf("(%d,%d) ",s[i].x,s[i].y); 
//			这样输出路径是可以的，就直接是正确的顺序，但是对于一个栈而言，我们这样做有点不合规矩，因为一个栈
//			我们是不应该取访问除栈顶以外的元素的
//		*/	
//			num++; 		// 计数加一 
//			//因为在这里我们为了输出所有的路径，需要保留栈里面的信息，不能让栈直接退栈把元素都退完了，所以我们就直接输出，虽然很不好qwq 
//			for(int i=0; i<tail; i++)printf("(%d,%d) ",s[i].x,s[i].y); //我们能这样做的原因是我们直接使用数组模拟栈，所以输出栈里面所有的元素是很轻松的，但是总感觉有点不好 
//			printf("(%d,%d)",ex,ey);
//			puts("");
//			//仅仅输出，不要return 
//			continue;     //第三处不一样！！！ 不要return来直接结束函数，而是应该继续找下一条路径，所以continue就行了 
//		}
//		if(is_ok(G,vis,now_x,now_y)){ //如果这一点可以走，那么我们就将其加入栈中 
//			e.x = now_x;
//			e.y = now_y;
//			e.d = -1;
//			s[tail++] = e;
//			vis[now_x][now_y] = true;
//		}
//	}
//	printf("一共有%d条路径\n",num); 
//	return ; 
//}
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
//	puts("其中一条可行路径");
//	find_one_path(G,n,m,sx,sy,ex,ey,dir);
	puts("所有路径");
	find_all_paths(G,n,m,sx,sy,ex,ey,dir);
	return 0;
}
