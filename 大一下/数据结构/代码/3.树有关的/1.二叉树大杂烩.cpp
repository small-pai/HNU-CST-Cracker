#include<iostream>
using namespace std;
/*************************************************************************
	1.�������Ľ���
	2.�����������ֱ����ĵݹ�ʵ���Լ��ǵݹ�ʵ�� �Լ�������� 
	3.һЩ�򵥵�Ӧ�ã�����ڵ�����������,�ȵȻ��кܶ࣬�����󲿷ֶ��ǵݹ�Ĺ��� 
	4.�����������򹹽�������
	5.�õ�������������Ҷ�ӽڵ�������������ҾͲ�д�ˣ�ʵ���Ͼ����ҵ�Ҷ�ӽڵ㣬֮��ľ�����������ˣ� 
**************************************************************************/
typedef struct Node{
	char c;
	Node *l,*r;
}Bnode,*Btree;
void create(Btree& T){
	char c;
	scanf("%c",&c);
	if(c == ' ') {
		T = NULL;
		return ;
	}
	T = new Bnode;
	T->c = c;
	T->l = NULL;
	T->r = NULL;
	create(T->l);
	create(T->r);
	return ;
}
//���ֱ���˳�� �ݹ�ʵ�� 
void pre_traverse(Btree T){
	if(T == NULL) return ;
	cout<<T->c<<" ";
	pre_traverse(T->l);
	pre_traverse(T->r);
	return ;
}
void inorder_traverse(Btree T){
	if(T == NULL) return ;
	inorder_traverse(T->l);
	cout<<T->c<<" ";
	inorder_traverse(T->r);
	return ;
}
void suf_traverse(Btree T){
	if(T == NULL) return ;
	suf_traverse(T->l); 
	suf_traverse(T->r);
	cout<<T->c<<" ";
	return ;
}
//���ֱ���˳�� �ǵݹ飨��ջʵ�֣�
struct Status{
	Bnode* p;
	bool r_search;
};
void pre_traverse_stack(Btree T){
	Bnode* s[1000];
	int tail = 0;
	Bnode* w = T;
	while(tail || w){
		while(w){
			cout<<w->c<<" ";
			s[tail++] = w;
			w = w->l;
		}
		if(tail){
			w = s[--tail];
			w = w->r;
		}
	}
	return ;
}
void inorder_traverse_stack(Btree T){
	Bnode* s[1000];
	int tail = 0;
	Bnode* w = T;
	while(tail || w){
		while(w){
			s[tail++] = w;
			w = w->l;
		}
		if(tail){
			w = s[--tail];
			cout<<w->c<<" ";
			w = w->r;
		}
	}
	return ;
}
void suf_traverse_stack(Btree T){
	Status s[1000]; //��Ϊ����������Ҫ�����Ҷ��Ӷ����֮��������Լ������Ա���Ҫ��һ�������Ա�����һ��
	int tail = 0;
	Bnode* w = T;
	Status e;
	while(tail || w){
		while(w){
			e.p = w;
			e.r_search = false;
			s[tail++] = e;
			w = w->l;
		}
		if(tail){
			e = s[--tail];
			w = e.p;
			if(e.r_search == false){
				w = w->r;
				e.r_search = true;
				s[tail++] = e;
			}
			else {
				cout<<w->c<<" ";
				w = NULL;
			}
		}
	} 
	return ;
}
//�������
void sequence_traverse(Btree T){
	Bnode* q[1000];
	int head = 0,tail = 0;
	Bnode* p = T;
	q[tail++] = p;
	while(tail - head){
		p = q[head++];
		cout<<p->c<<" ";
		if(p->l) q[tail++] = p->l;
		if(p->r) q[tail++] = p->r;
	}
	return ;
} 
//��ڵ�����������������Щ��Ҳ��д�ˣ������࣬����ʲô����ֵ��Щ��
int get_size(Btree T){
	if(T == NULL) return 0;
	int l_size = get_size(T->l);
	int r_size = get_size(T->r);
	return l_size + r_size + 1;
}
int get_height(Btree T){
	if(T == NULL) return 0;
	int l_h = get_height(T->l);
	int r_h = get_height(T->r);
	int max_ = (l_h>r_h)?l_h:r_h;
	return max_+1;
}
// ���������Լ����򹹽�������
int find(char in[],int l,int r,char x){ //������in[l.....r]���ҵ�x��λ�ò��������λ�� 
	int ret;
	for(int i=l; i<=r; i++){
		if(in[i] == x){
			ret = i;
			break;
		}
	}
	return ret;
}
void get_tree(Btree& T,char pre[],char in[],int& rt,int l,int r){ //��������pre[rt]Ϊ������������Ϊ[l,r]����
	if(l > r){
		T = NULL;
		return ; 
	}
	int gap = find(in,l,r,pre[rt]);
	T = new Bnode;
	T->c = pre[rt];
	T->l = NULL;
	T->r = NULL;
	rt++;
	get_tree(T->l,pre,in,rt,l,gap-1);
	get_tree(T->r,pre,in,rt,gap+1,r);
	return ;
} 
int main(){
	Btree T = NULL;
	create(T);
	//
	cout<<"�������к������������ݹ�ʵ�ֵģ�"<<endl;
	pre_traverse(T); cout<<endl;
	inorder_traverse(T);  cout<<endl;
	suf_traverse(T);  cout<<endl;
	//
	cout<<"�������к������������ǵݹ�ʵ�ֵģ�"<<endl;
	pre_traverse_stack(T);      cout<<endl;
	inorder_traverse_stack(T);  cout<<endl;
	suf_traverse_stack(T);      cout<<endl;
	//
	cout<<"���ǲ�������Ľ��"<<endl;
	sequence_traverse(T);   cout<<endl; 
	//
	cout<<"�ڵ���Ϊ"<<get_size(T)<<endl;
	cout<<"���ĸ߶�"<<get_height(T)<<endl;
	//
	cout<<"������Ԫ�صĸ���n�Լ��������м�����Ӧ���������У�ע��û���ظ�Ԫ�أ����ַ���ʽ���룩"<<endl;
	int n;
	char pre[1000];
	char in[1000];
	cin>>n;
	for(int i=1; i<=n; i++) cin>>pre[i];
	for(int i=1; i<=n; i++) cin>>in[i];
	Btree P = NULL;
	int rt = 1;
	get_tree(P,pre,in,rt,1,n);
	cout<<"����������ĺ���������"<<endl;
	suf_traverse(P);
	return 0;
}
