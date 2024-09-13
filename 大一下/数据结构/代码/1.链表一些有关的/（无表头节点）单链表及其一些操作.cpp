#include<cstdio>
#include<iostream>
using namespace std;

/************************************************************************
	注意事项： 
	1.注意这个是不带表头节点的单链表，注意和有表头节点的单链表对比!!!
	两者对比，你应该可以理解这个表头节点（无实际意义的节点）的好处了 
	
	2.为了节省时间，像什么创建单链表的函数我就不单独写了（事实上这些函数也就一句话 List L = NULL）
	3.这个链表我默认的下边是从1开始，即 1号元素就是第一个元素，若你习惯从0开始（即0是第一个元素的话），做相应的更改即可
	 
**************************************************************************/

typedef struct Node{ //链表的节点的定义 
	int data;
	Node* next;
}Node,*List;
/*************************************************************************************
	1.这部分是往单链表中插入元素的操作
	实际上是一个insert函数便可以解决的
	但是可能到时候会考什么叫你写头插入，尾插入，所以我就把这两个函数单独拿出来写一遍
	但要明白，所谓头插入，尾插入，本质就是insert函数中 pos 的值
	3.注意为什么我这里的L传的引用类型（   或者说用c语言的话要传List*类型（注意List*类型实际是Node**类型） ） ， 
	这里从一个方面体现了不带表头节点的单链表比带表头节点所欠缺的东西（不带表头节点的单链表是什么辣鸡qwq）
	 
*********************************************************************************************/
void head_insert(List& L, int val){
	//常规操作，将节点先申请出来 
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	
	//将该节点放在头部 
	t->next = L;
	L = t; // 传引用的原因（或者c语言：传List*的原因） 注意！！！ 
	return ;
}
void tail_insert(List& L,int val){
	//常规操作，将节点先申请出来
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	
	//将节点放在尾部
	// 先找到尾巴在哪里
	Node* p = L; //使用指针p来寻找
	while(p && p->next){
		p = p->next;
	} 
	//循环结束的时候我们就找到了尾巴在那里，尾巴就是p，所以我们要将节点放在p指向节点的后面
	// 但是注意我们循环中还写了一个 p && p->next中判断p是否为空的条件，这个是为了防止本身L就是一个空链表，即L == NULL，那么此时的尾插入实际上就是赋值
	if(p) p->next = t; //p不为空，说明p是尾节点，那么我们将节点插入到p的后面 
	else L = t; //p为空，说明L本身就是空的，所以尾插入到L的链表中，实际上就是 L = t;
	 
	
	return ;
}
bool Linsert(List& L,int pos,int val){ //将值val插入到链表L的pos位置上即插入的节点变为链表L的第pos个节点，若pos位置不合法则返回false代表插入失败，同时不做任何操作
	//常规操作，先将节点申请出来
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	//特判是不是要插入到头部，即pos = 1
	if(pos == 1) {
		t->next = L;
		L = t;
	} 
	else {
		//找到要插入的位置，实际上是pos位置前面的那个节点 
		Node*p = L; //用p来找到位置 
		for(int i=1; i<pos-1 && p; i++){
			p = p->next;
		}
		if(p){ //节点插入在p和p->next之间 
			t->next = p->next;
			p->next = t;
		}
		else { //p为空，说明要插入的位置不合法 
			return false;
		}
	}
	return true;
}

//Lsize() 
int Lsize(List L){ //返回链表L的元素的大小 
	int cnt = 0;
	Node* p = L;
	while(p){
		cnt++;
		p = p->next;
	}
	return cnt;
}

//reverse()
void reverse(List& L){
	Node* pre = NULL;
	Node* now = L;
	Node* next;
	
	while(now){
		next = now->next;
		now->next = pre;
		pre = now;
		now = next;
	}
	L = pre;
	return ;
}

void disp(List L){ //打印链表 
	Node* p = L;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
	return ;
}
/**************************************************************************************************************
	这几个就是增（insert函数前面已经实现了）删查改函数，大致思路和insert函数都差不多，可以自己实现来练手，
	这几个函数返回值，传参都可以自己设计，不要拘泥与这个设计
	 
	bool remove(List L,int pos,int* del) 删除链表L第pos位置上的节点，并将删除的节点的值通过指针del带出来，返回是否删除成功
	Node* at(List L,int pos) 返回 指向链表L第pos位置上节点的指针，没有pos位置上的节点就返回空 
	bool modify(List L,int pos,int new_val) 将链表第pos位置上的节点的值改为new_val，修改成功就返回true，否则返回false 
***************************************************************************************************************/
Node* Lat(List L,int pos){
	Node* p = L;
	for(int i=1; p&&i<pos; i++) p = p->next;
	return p;
}
bool Lremove(List& L,int pos,int* del){ //注意为什么传引用 
	//特判是不是删除了头节点
	if(pos == 1){
		if(L == NULL) return false;//本身就是空节点，删除失败
		else {
			Node* t = L;
			L = L->next;
			*del = t->data;//把删除的节点的值带出来
			delete t;//删掉节点 
		}
	}
	else {
		Node* p = L;//找到要删除的节点的前面一个节点（即其前驱节点） 
		for(int i=1; p&&i<pos-1; i++) p = p->next;
		if(p && p->next){
			Node* t = p->next;
			p->next = t->next;
			*del = t->data;
			delete t;
		}
		else return false;//p或者p->next中有一个为空，都表明无法删除，即删除失败 
	}
	return true;
}
bool Lmodify(List L,int pos,int new_val){
	Node* p = L;
	for(int i=1; p&&i<pos; i++) p = p->next;
	if(p) p->data = new_val;
	else return false;//p为空，说明当前链表中根本就没有pos这个位置上的节点，所以修改失败，返回false
	 
	return true;
}
int main(){
	//创建一个单链表，空链表
	List L = NULL; // L的类型使List，实际上就是Node*类型
	
	//现在我们往这个链表里面加入一些数据
	int n,val;
	puts("请输入元素的个数n，以及这n个元素");
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>val;
		head_insert(L,val); //头插入
							//尾插入 则调用 tail_insert(L,val)
							//或者是insert(L,1,val) 
	}
	// 我们可以输出一下链表中元素的个数 用 Lsize() 函数
	// 可以想想我们一直按头插入插入进去，这个时候输出链表应该是什么样子！是不是会跟你想的不一样 
	cout<<"链表L中元素的个数为"<<Lsize(L)<<endl;
	cout<<"此时链表 : ";
	disp(L); 
	cout<<endl;
	
	// 将单链表L反转 reverse()函数，可能会考，也可能不会，看看吧
	reverse(L);
	cout<<"链表反转之后 : ";
	disp(L);
	cout<<endl;
	
	// 举几个使用的例子 
	// Lat
	Node* p = Lat(L,2);
	if(p) cout<<"at 2 "<<p->data<<endl;
	//Lremove
	int dele;
	bool f = Lremove(L,2,&dele);
	if(f) cout<<dele<<" is removed"<<endl;
	else cout<<"fail to remove"<<endl;
	disp(L); cout<<endl;
	//Lmodify
	int new_val = 100;
	f = Lmodify(L,2,new_val);
	if(f){
		Node* t = Lat(L,2);
		if(t) cout<<"节点2 "<<"has been modified to "<<t->data<<endl;
	}
	else cout<<"fail to modify"<<endl;
	disp(L); cout<<endl;
	return 0;
}
