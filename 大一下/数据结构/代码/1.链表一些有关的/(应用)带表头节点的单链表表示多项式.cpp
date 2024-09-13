#include<cstdio>
#include<cstdlib>
/*********************************************************************************************
	1.这是使用带表头节点的单链表表示多项式
	2.实际上就是单链表的一些操作
	3.coffecient表示这一项的系数，exponent是这一项的指数
	4.Polynomial实际上就是前面写链表的时候的那个 L
	5.malloc_Node() 函数不用管，实际上这是我写的时候为了偷懒，所以把申请节点的操作最为一个函数独立出来了，其实就是正常的申请节点 
***********************************************************************************************/
typedef struct Node{
	int coffecient;
	int exponent;
	Node* next;
} Node,*Polynomial;
void InitPolynomial(Polynomial& a){ //初始化，实际上就是建立表头节点 
	Node* p = (Node*)malloc(sizeof(Node));//申请出来表头节点 
	p->coffecient = -1;
	p -> exponent = -1;
	p -> next = NULL;
	a = p;
	return ;
}
Node* malloc_Node(const int coffecient,const int exponent){ //这个函数不用管 
	Node* ret = new Node;
	ret -> coffecient = coffecient;
	ret -> exponent = exponent;
	ret -> next = NULL;
	return ret;
}
void orderinsert(const int coffecient,const int exponent,Polynomial a){ //将这一项(coffecient,exponent)这一项插入到正确的位置，按照降序插入 
	Node* p = a;
	while(p -> next && exponent<(p->next)->exponent)p = p->next; //找到要插入的位置，插入到p节点的后面 
	if(p -> next && (p -> next)->exponent == exponent){ //判断如果是指数相等推出的，那么要先合并，再做相应的操作 
		p->next->coffecient += coffecient;
		if(!(p->next->coffecient)){ //合并完了没有了，删除该节点 
			Node* del = p->next;
			p -> next = del -> next;
			delete del;
		}
	}
	else{ 												//此时p为改该多项式末尾，或者p->next->exponent < exponent，不管哪一种情况，但是插入到p节点后面 
		Node* q = malloc_Node(coffecient,exponent);
		q -> next = p -> next;
		p -> next = q;
	}
	return ;
}
void read(Polynomial a){ //读入多项式 
	int n;
	scanf("%d",&n);
	int coffecient,exponent;
	for(int i=0; i<n; i++){
		scanf("%d%d",&coffecient,&exponent);
		if(coffecient) orderinsert(coffecient,exponent,a);
	}
	return ;
}
void destroy(Polynomial a){ //销毁多项式 
	Node* p = a;
	while(p){
		Node* del = p;
		p = p->next;
		free(del);
	}
	return ;
}
void disp(Polynomial a){ //打印多项式 
	Node*p = a->next;
	while(p){
		printf("(%d,%d)",p->coffecient,p->exponent);
		p = p->next;
	}
	puts("");
	return ;
}
void Polynomial_Plus(Polynomial a,Polynomial b){ //将两个多项式相加 
	Node* pa = a;
	Node* pb = b->next;
	//相加的逻辑就是将b中的每一项插入到a的对应位置就行了 
	while(pb){ //while(pb)遍历b的每一项，将其加入a中 
		while(pa->next && pb->exponent < pa->next->exponent) pa = pa->next;
		if(pa->next && pa->next->exponent == pb->exponent){
			pa->next->coffecient += pb->coffecient;
			if(!(pa->next->coffecient)){
				Node* del = pa->next;
				pa->next = del->next;
				delete del;
			}
		}
		else{
			Node* q = malloc_Node(pb->coffecient,pb->exponent);
			q->next = pa->next;
			pa->next = q;
		}
		pb = pb->next;
	}
	return ;
}
void reverse(Polynomial a){ // 反转多项式，实际上就是反转链表 
	Node* pre = NULL;
	Node* now = a->next;
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
int main(){
	puts("请输入多项式的项数n,并在后面输入n个二元组,表示每一项的系数以及其指数");
	Polynomial a;
	InitPolynomial(a);
	read(a);
	puts("该多项式为");
	disp(a);
	destroy(a);
	puts("请输入多项式a的项数n,并在后面输入n个二元组,表示每一项的系数以及其指数");
	InitPolynomial(a);
	read(a);
	puts("请输入多项式b的项数n,并在后面输入n个二元组,表示每一项的系数以及其指数");
	Polynomial b;
	InitPolynomial(b);
	read(b);
	puts("这是多项式a和b的和");
	Polynomial_Plus(a,b);
	disp(a);
	destroy(a);
	return 0;
}
