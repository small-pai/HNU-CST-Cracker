#include<cstdio>
#include<cstdlib>
#include<iostream>
/***************************************************************
	1.这是使用不带表头节点的单链表实现的栈
	2.应该知道的是，用数组实现与用链表实现只是实现栈的储存结构不同，栈的意义是没有变的，一样是后进先出的顺序
	3.实际上这份代码就是对单链表的一些操作，不过对于栈的push()相当于对这个链表的头插入，pop()相
	当于从头部删除，top()相当于这个链表的第一个节点的值
	4.链栈看看相应的实现就好了，实际上单链表的操作如果熟练的话，链栈只用知道栈的意义便可以很轻松的实现出来 
*****************************************************************/ 
typedef struct Node{
	int data;
	Node* next;
} sNode,*link_stack;
sNode* Malloc_Node(int v,sNode* next){ //申请一节点sNode,sNode->data = v,sNode -> next = next 
	sNode* p = (sNode*)malloc(sizeof(sNode));
	p->data = v;
	p->next = next;
	return p;
}
bool top(link_stack s,int& ret){
	if(s) ret = s->data;
	else return false;
	return true;
} 
void push(link_stack& s,int v){ // 将元素v放入链栈s，实际上就是头插入 
	sNode* p = Malloc_Node(v,s);
	s = p;
	return ;
}
void pop(link_stack& s){ // 将链栈s的top元素弹出,若s为空则不做操作，实际上就是删去头节点 
	if(s) {
		sNode* del = s;
		s = s->next;
		free(del);
	}
	return ;
}
bool empty(link_stack s){
	return s == NULL;
}
void ini(link_stack& s){ // 初始化链栈s,s = NULL; 
	s = NULL;
	return ;
}
void disp(link_stack& s){ // 从栈s的栈顶打印栈中的元素 
	sNode* p = s;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
	puts("");
	return ;
}
int main(){
	puts("输入元素,并输入0表示输入结束");
	int v;
	link_stack s;
	ini(s);
	while(1){
		cin>>v;
		if(!v) break;
		push(s,v);
	}
	puts("栈中元素");
	disp(s);
	puts("pop出两个元素之后");
	pop(s);
	pop(s);
	disp(s);
	return 0;
}
