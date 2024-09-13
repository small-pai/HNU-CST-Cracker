#include<cstdio>
#include<cstdlib>
/*********************************************************************************************
	1.����ʹ�ô���ͷ�ڵ�ĵ������ʾ����ʽ
	2.ʵ���Ͼ��ǵ������һЩ����
	3.coffecient��ʾ��һ���ϵ����exponent����һ���ָ��
	4.Polynomialʵ���Ͼ���ǰ��д�����ʱ����Ǹ� L
	5.malloc_Node() �������ùܣ�ʵ����������д��ʱ��Ϊ��͵�������԰�����ڵ�Ĳ�����Ϊһ���������������ˣ���ʵ��������������ڵ� 
***********************************************************************************************/
typedef struct Node{
	int coffecient;
	int exponent;
	Node* next;
} Node,*Polynomial;
void InitPolynomial(Polynomial& a){ //��ʼ����ʵ���Ͼ��ǽ�����ͷ�ڵ� 
	Node* p = (Node*)malloc(sizeof(Node));//���������ͷ�ڵ� 
	p->coffecient = -1;
	p -> exponent = -1;
	p -> next = NULL;
	a = p;
	return ;
}
Node* malloc_Node(const int coffecient,const int exponent){ //����������ù� 
	Node* ret = new Node;
	ret -> coffecient = coffecient;
	ret -> exponent = exponent;
	ret -> next = NULL;
	return ret;
}
void orderinsert(const int coffecient,const int exponent,Polynomial a){ //����һ��(coffecient,exponent)��һ����뵽��ȷ��λ�ã����ս������ 
	Node* p = a;
	while(p -> next && exponent<(p->next)->exponent)p = p->next; //�ҵ�Ҫ�����λ�ã����뵽p�ڵ�ĺ��� 
	if(p -> next && (p -> next)->exponent == exponent){ //�ж������ָ������Ƴ��ģ���ôҪ�Ⱥϲ���������Ӧ�Ĳ��� 
		p->next->coffecient += coffecient;
		if(!(p->next->coffecient)){ //�ϲ�����û���ˣ�ɾ���ýڵ� 
			Node* del = p->next;
			p -> next = del -> next;
			delete del;
		}
	}
	else{ 												//��ʱpΪ�ĸö���ʽĩβ������p->next->exponent < exponent��������һ����������ǲ��뵽p�ڵ���� 
		Node* q = malloc_Node(coffecient,exponent);
		q -> next = p -> next;
		p -> next = q;
	}
	return ;
}
void read(Polynomial a){ //�������ʽ 
	int n;
	scanf("%d",&n);
	int coffecient,exponent;
	for(int i=0; i<n; i++){
		scanf("%d%d",&coffecient,&exponent);
		if(coffecient) orderinsert(coffecient,exponent,a);
	}
	return ;
}
void destroy(Polynomial a){ //���ٶ���ʽ 
	Node* p = a;
	while(p){
		Node* del = p;
		p = p->next;
		free(del);
	}
	return ;
}
void disp(Polynomial a){ //��ӡ����ʽ 
	Node*p = a->next;
	while(p){
		printf("(%d,%d)",p->coffecient,p->exponent);
		p = p->next;
	}
	puts("");
	return ;
}
void Polynomial_Plus(Polynomial a,Polynomial b){ //����������ʽ��� 
	Node* pa = a;
	Node* pb = b->next;
	//��ӵ��߼����ǽ�b�е�ÿһ����뵽a�Ķ�Ӧλ�þ����� 
	while(pb){ //while(pb)����b��ÿһ��������a�� 
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
void reverse(Polynomial a){ // ��ת����ʽ��ʵ���Ͼ��Ƿ�ת���� 
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
	puts("���������ʽ������n,���ں�������n����Ԫ��,��ʾÿһ���ϵ���Լ���ָ��");
	Polynomial a;
	InitPolynomial(a);
	read(a);
	puts("�ö���ʽΪ");
	disp(a);
	destroy(a);
	puts("���������ʽa������n,���ں�������n����Ԫ��,��ʾÿһ���ϵ���Լ���ָ��");
	InitPolynomial(a);
	read(a);
	puts("���������ʽb������n,���ں�������n����Ԫ��,��ʾÿһ���ϵ���Լ���ָ��");
	Polynomial b;
	InitPolynomial(b);
	read(b);
	puts("���Ƕ���ʽa��b�ĺ�");
	Polynomial_Plus(a,b);
	disp(a);
	destroy(a);
	return 0;
}
