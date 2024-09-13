#include<cstdio>
#include<iostream>
using namespace std;
/***********************************************
	1.���Ǵ���ͷ�ڵ�ĵ�������ÿ��԰�����Ͳ�����ͷ�ڵ�ĵ�������жԱȣ��������ܺܺõ�������ͷ�ڵ�ĵ�����Դ���ļ�
	2.�󲿷ִ����û�б�ͷ�ڵ��࣬��ע��һЩϸ�ڣ�����˵����Ĳ��������ǻ����еĺ����������û���˵ָ�������� 
	3.��ᷢ��Ϊʲô����ͷ�ڵ�ĵ�������ٺܶ���жϣ� 
	4.�ⲿ�ֵĴ����ע���Ҿ�д��û�в�����ͷ�ڵ�ĵ��������ô��ϸ�ˣ� 
************************************************/
/*
	ʵ����ɾ����ĸ��������Լ�����ķ�ת����reverse()
	�������������������� ����ͷ�ڵ�ĵ����� ��ʾ����ʽ�� 
*/
typedef struct Node{
	int data;
	Node* next;
} Node,*List;
bool Linsert(List L,int pos,int val){ //ע�������ֱ�Ӵ�List L�����ˣ���û�д�List& L��  
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
	else return false; //˵������λ�ò��Ϸ�������false 
	
	return true;
}
bool Lremove(List L,int pos,int* rem){
	Node* p = L;
	for(int i=0; p&&i<pos-1; i++) p = p->next;
	if(p && p->next){
		//ɾ���ڵ�p->next
		Node* d = p->next;
		p->next = d->next;
		*rem = d->data;
		delete d;
	}
	else return false; //p �� p->next ������һ��Ϊ�ն�˵���޷�ɾ������ɾ��λ�ò��Ϸ�
	
	return true;
}
Node* Lat(List L,int pos){ //�������λ���ϵĽڵ��ָ�룬����������򷵻ؿ� 
	Node* p = L;
	for(int i=0; p&&i<pos; i++) p = p->next;
	return p;
}
bool Lmodify(List L,int pos,int new_val){
	Node* p = L;
	for(int i=0; p&&i<pos; i++) p = p->next;
	if(p) p->data = new_val;
	else return false; // pΪ�գ�˵���޸�λ�ò��Ϸ�������false 
	
	return true;
}
void reverse(List L){//������ת
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
	//����������ע���ʱ����ͷ�ڵ� 
	List L;
	L = new Node;   //ָ���ͷ�ڵ� 
	L->data = -1;   //��ͷ�ڵ������壬���ǽ���ͷ�ڵ��ֵ��Ϊ-1�����ֵ�����Լ����� 
	L->next = NULL; //next�ÿ� 
	
	//���ǿ��Բ���һЩ����
	int n,val;
	puts("����Ԫ�صĸ���n���Լ���n��Ԫ��");
	cin>>n;
	for(int i=0; i<n; i++){
		cin>>val;
		Linsert(L,1,val);// ͷ���� 
	}
	cout<<"���������LΪ : ";
	disp(L);
	cout<<endl;
	
	//��ת����reverse
	cout<<"������ת"<<endl;
	reverse(L);
	disp(L);
	cout<<endl;
	 
	//��һЩ����
	//��2��λ�ò���һ��999
	cout<<"��2��λ�ò���һ��999"<<endl;
	Linsert(L,2,999);
	disp(L);
	cout<<endl;
	//��3�Žڵ�ɾ�� 
	cout<<"��3�Žڵ�ɾ��" <<endl;
	int r;
	Lremove(L,3,&r);
	disp(L);
	cout<<endl;
	//��ѯ4��λ����ʲô
	cout<<"��ѯ4��λ����ʲô"<<endl;
	Node* ret = Lat(L,4);
	if(ret) cout<<"�� "<<ret->data<<endl;
	else cout<<"û��4��λ��"<<endl;
	//��2��λ�õ�ֵ��Ϊ88888
	cout<<"��2��λ�õ�ֵ��Ϊ88888"<<endl;
	Lmodify(L,2,88888);
	disp(L);
	cout<<endl;
	
	return 0;
}
