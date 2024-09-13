#include<iostream>
using namespace std;
/*************************************************************************
	1.二叉树的建立
	2.二叉树的三种遍历的递归实现以及非递归实现 以及层序遍历 
	3.一些简单的应用，如求节点数，求树高,等等还有很多，反正大部分都是递归的过程 
	4.根据先序，中序构建二叉树
	5.用单链表将二叉树的叶子节点链起来（这个我就不写了，实际上就是找到叶子节点，之后的就是链表操作了） 
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
//三种遍历顺序 递归实现 
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
//三种遍历顺序 非递归（用栈实现）
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
	Status s[1000]; //因为后续遍历需要将左右儿子都输出之后在输出自己，所以必须要有一个量可以表明这一点
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
//层序遍历
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
//求节点数（其他求树高这些我也不写了，代码差不多，包括什么求最值这些）
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
// 根据先序以及中序构建二叉树
int find(char in[],int l,int r,char x){ //在序列in[l.....r]中找到x的位置并返回这个位置 
	int ret;
	for(int i=l; i<=r; i++){
		if(in[i] == x){
			ret = i;
			break;
		}
	}
	return ret;
}
void get_tree(Btree& T,char pre[],char in[],int& rt,int l,int r){ //建立起以pre[rt]为根，中序序列为[l,r]的树
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
	cout<<"这是先中后序遍历结果（递归实现的）"<<endl;
	pre_traverse(T); cout<<endl;
	inorder_traverse(T);  cout<<endl;
	suf_traverse(T);  cout<<endl;
	//
	cout<<"这是先中后序遍历结果（非递归实现的）"<<endl;
	pre_traverse_stack(T);      cout<<endl;
	inorder_traverse_stack(T);  cout<<endl;
	suf_traverse_stack(T);      cout<<endl;
	//
	cout<<"这是层序遍历的结果"<<endl;
	sequence_traverse(T);   cout<<endl; 
	//
	cout<<"节点数为"<<get_size(T)<<endl;
	cout<<"树的高度"<<get_height(T)<<endl;
	//
	cout<<"请输入元素的个数n以及先序序列及其相应的中序序列（注意没有重复元素，以字符形式输入）"<<endl;
	int n;
	char pre[1000];
	char in[1000];
	cin>>n;
	for(int i=1; i<=n; i++) cin>>pre[i];
	for(int i=1; i<=n; i++) cin>>in[i];
	Btree P = NULL;
	int rt = 1;
	get_tree(P,pre,in,rt,1,n);
	cout<<"这个二叉树的后续序列是"<<endl;
	suf_traverse(P);
	return 0;
}
