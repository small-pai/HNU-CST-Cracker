#include<iostream>
#define maxn_capacity 100000 
using namespace std;
/**************************************************************************************************
	1.这个循环队列与普通队列在大体上是一样的，主要是在达到maxn_capacity的时候回到0开始，即循环起来 
	2.实际上的循环就是利用取模，容量为maxn_capacity的循环队列可以在[0,maxn_capacity-1]位置储存数据， 
	3.看看相应函数与不循环的队列的差别
	4.注意判满的条件 
	5.看完之后，你会发现所谓循环队列，他就是在尝试能否能使用已经被弹出元素的空间，而不像前面的普通数组一样，tail一直在 tail++ head也一直在head++ 
***************************************************************************************************/
struct loop_queue{
	int data[maxn_capacity]; //maxn_capacity 100000
	int head,tail;
};
void ini(loop_queue& q){ //初始化 即head = tail = 0 
	q.head = q.tail = 0;
	return ;
}
bool empty(loop_queue& q){
	return q.head == q.tail;
}
bool full(loop_queue& q){
	/*
		每一次往队列里面加入元素的位置应该是q.tail处，放完元素之后
		tail应该变为 (q.tail+1)%maxn_capacity，如果此时tail加1且取模之后发现与head相等，说明此时队列已经慢了，不能往里面放元素了
		我们相当于浪费一个空间来判定是否此时队列已经满了
		比如 循环队列的maxn_capacity为5
 		此时head = 0，tail = 4，如果要往这里面放入元素，则放在tail（4号位置上），放完之后tail = (4+1)%5 = 0，此时tail == head了
		尽管4号位置本身是没有放入元素的，但是我们认为此时循环队列还是满了，因为4号位置放完元素之后tail就等于head了，所以我们认为此时不能
		再往循环队列中加入元素
		做这样的目的主要是要是判队列为空（tail == head）和判队列为满的条件分开，不然我们无法在循环队列中判断到底是空还是满 
		!!!在这种意义下，容量为maxn_capacity的循环队列实际上只能储存这maxn_capacity-1 个数据，因为有一个空间不会被使用 
	*/
	return (q.tail+1)%maxn_capacity == q.head; 
}
bool push(loop_queue& q,int val){
	if(!full(q)) {
		q.data[q.tail] = val;
		q.tail = (q.tail+1)%maxn_capacity;
	}
	else return false; //此时队列已经满了，无法再放入元素
	 
	return true;
}
bool top(loop_queue& q,int& ret){
	if(!empty(q)) ret = q.data[q.head];
	else return false; //此时队列为空，根本就没有首元素
	 
	return true;
}
bool pop(loop_queue& q){
	if(!empty(q)){
		q.head = (q.head+1)%maxn_capacity; //始终要注意，此时队列是循环起来的，所以一定要记得取模 
	}
	else return false; //队列为空，根本就没有元素可以弹出 
	
	return true;
}
int main(){
	loop_queue q;
	ini(q);
	
	//输入一些元素试试
	cout<<"请输入元素的个数n，以及这n个元素"<<endl;
	int n,val;
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>val;
		push(q,val);
	}
	//弹出这些元素 
	cout<<"弹出这些元素"<<endl;
	int r;
	while(!empty(q)){
		top(q,r);
		pop(q);
		cout<<r<<" ";
	}
	cout<<endl;
	return 0;
}
