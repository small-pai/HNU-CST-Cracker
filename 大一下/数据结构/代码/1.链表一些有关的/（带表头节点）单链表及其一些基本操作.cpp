#include<cstdio>
#include<iostream>
using namespace std;
/***********************************************
	1.这是带表头节点的单链表，最好可以把这个和不带表头节点的单链表进行对比，这样便能很好的体会带表头节点的单链表对代码的简化
	2.大部分代码和没有表头节点差不多，但注意一些细节，比如说传入的参数，我们还用有的函数传入引用或者说指针类型吗？ 
	3.你会发现为什么代表头节点的单链表会少很多的判断！ 
	4.这部分的代码的注释我就写的没有不带表头节点的单链表的那么详细了！ 
************************************************/
/*
	实现增删查改四个函数，以及链表的翻转函数reverse()
	更多的其他的链表操作见 带表头节点的单链表 表示多项式！ 
*/
typedef struct Node{
	int data;
	Node* next;
} Node,*List;
bool Linsert(List L,int pos,int val){ //注意这里就直接传List L就行了，就没有传List& L了  
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	//
	Node* p = L;
	for(int i=0; p&&i<pos-1; i++) p = p->next;
	if(p){
		t->next = p->next;
		p->next = t;
	}
	else return false; //说明插入位置不合法，返回false 
	
	return true;
}
bool Lremove(List L,int pos,int* rem){
	Node* p = L;
	for(int i=0; p&&i<pos-1; i++) p = p->next;
	if(p && p->next){
		//删除节点p->next
		Node* d = p->next;
		p->next = d->next;
		*rem = d->data;
		delete d;
	}
	else return false; //p 和 p->next 其中任一个为空都说明无法删除，即删除位置不合法
	
	return true;
}
Node* Lat(List L,int pos){ //返回这个位置上的节点的指针，如果不存在则返回空 
	Node* p = L;
	for(int i=0; p&&i<pos; i++) p = p->next;
	return p;
}
bool Lmodify(List L,int pos,int new_val){
	Node* p = L;
	for(int i=0; p&&i<pos; i++) p = p->next;
	if(p) p->data = new_val;
	else return false; // p为空，说明修改位置不合法，返回false 
	
	return true;
}
void reverse(List L){//将链表反转
	Node* pre = NULL;
	Node* now = L->next;
	Node* next;
	while(now){
		next = now->next;
		now->next = pre;
		pre = now;
		now = next;
	}
	L->next = pre;
	return ;
}
void disp(List L){
	Node* p = L->next;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
	return ;
}
int main(){
	//建立起链表，注意此时带表头节点 
	List L;
	L = new Node;   //指向表头节点 
	L->data = -1;   //表头节点无意义，我们将表头节点的值赋为-1，这个值由你自己来定 
	L->next = NULL; //next置空 
	
	//我们可以插入一些数据
	int n,val;
	puts("输入元素的个数n，以及这n个元素");
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>val;
		Linsert(L,1,val);// 头插入 
	}
	cout<<"输入的链表L为 : ";
	disp(L);
	cout<<endl;
	
	//反转链表reverse
	cout<<"将链表反转"<<endl;
	reverse(L);
	disp(L);
	cout<<endl;
	 
	//举一些例子
	//在2号位置插入一个999
	cout<<"在2号位置插入一个999"<<endl;
	Linsert(L,2,999);
	disp(L);
	cout<<endl;
	//将3号节点删掉 
	cout<<"将3号节点删掉" <<endl;
	int r;
	Lremove(L,3,&r);
	disp(L);
	cout<<endl;
	//查询4号位置是什么
	cout<<"查询4号位置是什么"<<endl;
	Node* ret = Lat(L,4);
	if(ret) cout<<"是 "<<ret->data<<endl;
	else cout<<"没有4号位置"<<endl;
	//将2号位置的值改为88888
	cout<<"将2号位置的值改为88888"<<endl;
	Lmodify(L,2,88888);
	disp(L);
	cout<<endl;
	
	return 0;
}
