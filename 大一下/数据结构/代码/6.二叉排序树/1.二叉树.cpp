#include<bits/stdc++.h>
using namespace std;
typedef struct node{
	int data;
	node *l,*r;
} Bnode,* Btree; // 节点,Btree是指向Bnode的指针
bool find(Bnode* T,int x,Bnode** f,Bnode** c){
	Bnode* q = NULL; //q记录p节点的父亲 
	Bnode* p = T; // 当前比较的节点p 
	if(!T){ //空树 
		*f = q;
		*c = p;
		return false;
	}
	else { //开始寻找x 
		while(p){
			if(p->data == x) { //p节点的值就是x，找到了！ 
				*f = q;
				*c = p;// c = &child
				return true;
			}
			else { // p所指向的节点不是的所有查找的节点 
				q = p;
				// 判断是走向左儿子还是右儿子 
				if(x < p->data) p = p->l; 
				else p = p->r;
			}
		}
	}
	//到这里还没找到说明在这颗树里面没有x
	*f = q;
	*c = p;
	return false;
}
// 向树 T中插入x，但考虑到T指针可能被更改，所以传入T的地址即（&T）
void insert(Bnode** pT,int x){ 
	Bnode* fa = NULL;
	Bnode* child = NULL;
	bool flag = find(*pT,x,&fa,&child);
	if(!flag){ //没找到，所以进行插入insert 
		// 因为要插入节点了，我们先把这个节点申请出来
		Bnode* p = new Bnode;
		p->data = x;
		p->l = NULL;
		p->r = NULL;
		// 插入在正确的位置
		if(fa == NULL){ //fa就等于空，所以说明插入在空树里面，那我们把根节点改成p就行了 
			*pT = p;
		}
		else { //不是空树，那我们要将p节点接在fa节点的正确位置，是左儿子还是右儿子
			if(x < fa->data) fa->l = p;
			else fa->r = p; 
		}
	}
	return ;
}
void remove(Bnode** pT,int x){ //在T这个树里面删去值为x的节点
	Bnode* fa = NULL;
	Bnode* child = NULL;
	bool flag = find(*pT,x,&fa,&child);
	if(flag){ //如果找到了x，那么我们才进行删除
		if(fa == NULL){ // 如果找到了，并且找到的节点（child）并没有父亲（fa == NULL）说明什么，是不是说明要删除的节点child就是根节点 
			if(child->l == NULL && child->r == NULL){ // child左右儿子都没有 
				*pT = NULL;
			}
			else if(child->l != NULL && child->r == NULL){ // 左支 
				*pT = child->l;
			}
			else if(child->l == NULL && child->r != NULL){ // 右支 
				*pT = child->r; 
			}
			else if(child->l != NULL && child->r != NULL){ // 双支 
				*pT = child->l; //将左支挂上去 
				Bnode* p = child->l; //用p来找到左支的最右边的端点
				while(p->r) p = p->r;
				p->r = child->r; // 然后将右支挂在左支的最右边 
			}
		}
		else if(fa != NULL){ //要删除的节点不是根节点 
			if(child->data < fa->data){ // 说明child是fa的左儿子 
				if(child->l == NULL && child->r == NULL){ // child左右儿子都没有 
						fa->l = NULL;
					}
				else if(child->l != NULL && child->r == NULL){ // 左支 
						fa->l = child->l;
					}
				else if(child->l == NULL && child->r != NULL){ // 右支 
						fa->l = child->r; 
					}
				else if(child->l != NULL && child->r != NULL){ // 双支 
					fa->l = child->l; //将左支挂上去 
					Bnode* p = child->l; //用p来找到左支的最右边的端点
					while(p->r) p = p->r;
					p->r = child->r; // 然后将右支挂在左支的最右边 
				}
			}
			else { // 说明child是fa的右儿子 
				if(child->l == NULL && child->r == NULL){ // child左右儿子都没有 
						fa->r = NULL;
					}
				else if(child->l != NULL && child->r == NULL){ // 左支 
						fa->r = child->l;
					}
				else if(child->l == NULL && child->r != NULL){ // 右支 
						fa->r = child->r; 
					}
				else if(child->l != NULL && child->r != NULL){ // 双支 
					fa->r = child->l; //将左支挂上去 
					Bnode* p = child->l; //用p来找到左支的最右边的端点
					while(p->r) p = p->r;
					p->r = child->r; // 然后将右支挂在左支的最右边 
				}
			}
		}
		//注意结束以后delete child
		delete child;
	} 
	return ;
}
void inorder_traver(Bnode* p){
	if(p == NULL) return ;
	inorder_traver(p->l);
	cout<<p->data<<" ";
	inorder_traver(p->r);
	return ;
}
int main(){
	Bnode* T = NULL;
	puts("输入元素的个数n，以及这n个元素");
	int n;
	cin>>n;
	// 输入n个数据
	int v;
	for(int i=0; i<n; i++){
		cin>>v;
		insert(&T,v); 
	}
	puts("这是中序遍历的结果"); 
	inorder_traver(T);cout<<endl;
	
	int re;
	puts("请输入要插入的元素的值");
	cin>>re;
	insert(&T,re);
	puts("插入这个元素值之后的结果");
	inorder_traver(T);cout<<endl;
	
	puts("请输入要删除的元素的元素值");
	cin>>re;
	remove(&T,re);
	puts("插入之后的结果");
	inorder_traver(T);cout<<endl;
	
	return 0;
}
