#include<cstdio>
#include<cstdlib>
#include<iostream>
/***************************************************************
	1.����ʹ�ò�����ͷ�ڵ�ĵ�����ʵ�ֵ�ջ
	2.Ӧ��֪�����ǣ�������ʵ����������ʵ��ֻ��ʵ��ջ�Ĵ���ṹ��ͬ��ջ��������û�б�ģ�һ���Ǻ���ȳ���˳��
	3.ʵ������ݴ�����ǶԵ������һЩ��������������ջ��push()�൱�ڶ���������ͷ���룬pop()��
	���ڴ�ͷ��ɾ����top()�൱���������ĵ�һ���ڵ��ֵ
	4.��ջ������Ӧ��ʵ�־ͺ��ˣ�ʵ���ϵ�����Ĳ�����������Ļ�����ջֻ��֪��ջ���������Ժ����ɵ�ʵ�ֳ��� 
*****************************************************************/ 
typedef struct Node{
	int data;
	Node* next;
} sNode,*link_stack;
sNode* Malloc_Node(int v,sNode* next){ //����һ�ڵ�sNode,sNode->data = v,sNode -> next = next 
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
void push(link_stack& s,int v){ // ��Ԫ��v������ջs��ʵ���Ͼ���ͷ���� 
	sNode* p = Malloc_Node(v,s);
	s = p;
	return ;
}
void pop(link_stack& s){ // ����ջs��topԪ�ص���,��sΪ������������ʵ���Ͼ���ɾȥͷ�ڵ� 
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
void ini(link_stack& s){ // ��ʼ����ջs,s = NULL; 
	s = NULL;
	return ;
}
void disp(link_stack& s){ // ��ջs��ջ����ӡջ�е�Ԫ�� 
	sNode* p = s;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
	puts("");
	return ;
}
int main(){
	puts("����Ԫ��,������0��ʾ�������");
	int v;
	link_stack s;
	ini(s);
	while(1){
		cin>>v;
		if(!v) break;
		push(s,v);
	}
	puts("ջ��Ԫ��");
	disp(s);
	puts("pop������Ԫ��֮��");
	pop(s);
	pop(s);
	disp(s);
	return 0;
}
