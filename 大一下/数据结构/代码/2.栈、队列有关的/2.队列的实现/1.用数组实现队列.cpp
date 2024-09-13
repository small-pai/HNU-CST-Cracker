#include<iostream>
#define maxn_capacity 100000 
using namespace std;
/*******************************************************************************************************
	1.队列和栈的区别就是，队列是先进先出的 
	2.实现的时候用一个数组和两个小标head，tail就可以了 
	3.同队列一样，我们实际上使用的时候不用把队列封装成这样，这些对应操作的函数都是一行代码就可以解决的
	4.所以也只用看看实现就好，后面具体应用的时候，比如走迷宫，比如层
	序遍历这些，我们都只用定义一个数组，一个head一个tail就可以解决了！！ 
	
*********************************************************************************************************/
struct queue{
	int data[maxn_capacity];  //maxn_capacity决定了这个队列最大的储存数量，这里我们使用的是宏定义，认为最大为100000 
	int head,tail;           //head指向当前队列的第一个元素，tail指向第一个不存数据的位置，即 [head,tail) 的范围内表示当前队列中的元素 
};
void ini(queue& q){//队列的初始化 
	q.head = q.tail = 0;
	return ;
}
bool empty(queue& q){ // 返回是否队列q为空 
	return q.head == q.tail;
}
bool push(queue& q,int v){ //从队尾加入，如果装不下了，就返回false 
	if(q.tail < maxn_capacity) q.data[q.tail++] = v;
	else return false;
	
	return true;
}
bool front(queue& q,int& ret){ //ret中带出队首元素，如果队列为空，即head == tail，则返回false 
	if(!empty(q)) ret = q.data[q.head];
	else return false;
	
	return true;
}
bool pop(queue& q){ //弹出队首元素，如果队列为空，则弹出失败，返回false 
	if(!empty(q)) q.head++;
	else return false;
	
	return true;
}
int main(){
	queue q;
	ini(q);
	
	//输入一些元素
	cout<<"请输入元素的数量n，以及这n个元素"<<endl;
	int n,val;
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>val;
		push(q,val);
	}
	cout<<"将队列中的元素全部弹出"<<endl;
	int r;
	while(!empty(q)){
		front(q,r);
		pop(q);
		cout<<r<<" ";
	}
	cout<<endl;
	return 0;
} 
