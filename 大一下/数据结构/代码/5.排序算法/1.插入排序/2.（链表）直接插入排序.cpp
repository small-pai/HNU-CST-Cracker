#include<iostream>
using namespace std;
/******************************************************
	1.实际上的链表的插入排序也就是一个单链表操作
	2.思想同数组的插入排序是一样的，我们将每一个节点一次往前面插入，最后形成的链表就是排好序的链表
	3.因为有这种插入操作，我们最好使用带表头节点的单链表，代码实现起来会更加的容易一点
	 
********************************************************/
struct Node{ //链表的节点 
	int v;
	Node* next;
};
int main(){
	Node* L = NULL;
	//将表头节点申请出来
	Node* q = new Node;
	q->v = -1;
	q->next = NULL;
	L = q;
	
	//输入数据
	puts("请输入元素的个数，以及这n个元素的值");
	int n,val;
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>val;
		//申请节点 
		Node* t = new Node;
		t->v = val;
		t->next = NULL;
		//头插入
		t->next = L->next;
		L->next = t; 
	}
	//将链表分成两段，一段为L指向的（这一段代表已经排好序的）， 一段为p指向的（这一段代表待排序的）
	Node* p = L->next;
	L->next = NULL;
	//开始排序，将p中的每一个节点插入到L的这一条链中
	Node* next; 
	Node* t; //用于遍历L指向的链表 
	while(p){
		next = p->next; //先记录下p节点后面是哪一个节点，不然之后无法往后移动，因为此时p所指向的节点会被插入到 L 中的某一个位置 
		t = L;  // 使用t来遍历L所指向的链表 
		while(t->next && (t->next)->v < p->v) t = t->next;
		//p指向的节点插入到t所指向的节点的后面
		p->next = t->next;
		t->next = p;
		//p移动到下一个节点
		p = next;
	}
	//看看排序的效果
	Node* r = L->next;
	while(r){
		cout<<r->v<<" ";
		r = r->next;
	}
	cout<<endl;
	return 0;
}
