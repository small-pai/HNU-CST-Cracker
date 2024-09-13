#include<bits/stdc++.h>
using namespace std;
typedef struct node{
	int data;
	node *l,*r;
} Bnode,* Btree; // �ڵ�,Btree��ָ��Bnode��ָ��
bool find(Bnode* T,int x,Bnode** f,Bnode** c){
	Bnode* q = NULL; //q��¼p�ڵ�ĸ��� 
	Bnode* p = T; // ��ǰ�ȽϵĽڵ�p 
	if(!T){ //���� 
		*f = q;
		*c = p;
		return false;
	}
	else { //��ʼѰ��x 
		while(p){
			if(p->data == x) { //p�ڵ��ֵ����x���ҵ��ˣ� 
				*f = q;
				*c = p;// c = &child
				return true;
			}
			else { // p��ָ��Ľڵ㲻�ǵ����в��ҵĽڵ� 
				q = p;
				// �ж�����������ӻ����Ҷ��� 
				if(x < p->data) p = p->l; 
				else p = p->r;
			}
		}
	}
	//�����ﻹû�ҵ�˵�������������û��x
	*f = q;
	*c = p;
	return false;
}
// ���� T�в���x�������ǵ�Tָ����ܱ����ģ����Դ���T�ĵ�ַ����&T��
void insert(Bnode** pT,int x){ 
	Bnode* fa = NULL;
	Bnode* child = NULL;
	bool flag = find(*pT,x,&fa,&child);
	if(!flag){ //û�ҵ������Խ��в���insert 
		// ��ΪҪ����ڵ��ˣ������Ȱ�����ڵ��������
		Bnode* p = new Bnode;
		p->data = x;
		p->l = NULL;
		p->r = NULL;
		// ��������ȷ��λ��
		if(fa == NULL){ //fa�͵��ڿգ�����˵�������ڿ������棬�����ǰѸ��ڵ�ĳ�p������ 
			*pT = p;
		}
		else { //���ǿ�����������Ҫ��p�ڵ����fa�ڵ����ȷλ�ã�������ӻ����Ҷ���
			if(x < fa->data) fa->l = p;
			else fa->r = p; 
		}
	}
	return ;
}
void remove(Bnode** pT,int x){ //��T���������ɾȥֵΪx�Ľڵ�
	Bnode* fa = NULL;
	Bnode* child = NULL;
	bool flag = find(*pT,x,&fa,&child);
	if(flag){ //����ҵ���x����ô���ǲŽ���ɾ��
		if(fa == NULL){ // ����ҵ��ˣ������ҵ��Ľڵ㣨child����û�и��ף�fa == NULL��˵��ʲô���ǲ���˵��Ҫɾ���Ľڵ�child���Ǹ��ڵ� 
			if(child->l == NULL && child->r == NULL){ // child���Ҷ��Ӷ�û�� 
				*pT = NULL;
			}
			else if(child->l != NULL && child->r == NULL){ // ��֧ 
				*pT = child->l;
			}
			else if(child->l == NULL && child->r != NULL){ // ��֧ 
				*pT = child->r; 
			}
			else if(child->l != NULL && child->r != NULL){ // ˫֧ 
				*pT = child->l; //����֧����ȥ 
				Bnode* p = child->l; //��p���ҵ���֧�����ұߵĶ˵�
				while(p->r) p = p->r;
				p->r = child->r; // Ȼ����֧������֧�����ұ� 
			}
		}
		else if(fa != NULL){ //Ҫɾ���Ľڵ㲻�Ǹ��ڵ� 
			if(child->data < fa->data){ // ˵��child��fa������� 
				if(child->l == NULL && child->r == NULL){ // child���Ҷ��Ӷ�û�� 
						fa->l = NULL;
					}
				else if(child->l != NULL && child->r == NULL){ // ��֧ 
						fa->l = child->l;
					}
				else if(child->l == NULL && child->r != NULL){ // ��֧ 
						fa->l = child->r; 
					}
				else if(child->l != NULL && child->r != NULL){ // ˫֧ 
					fa->l = child->l; //����֧����ȥ 
					Bnode* p = child->l; //��p���ҵ���֧�����ұߵĶ˵�
					while(p->r) p = p->r;
					p->r = child->r; // Ȼ����֧������֧�����ұ� 
				}
			}
			else { // ˵��child��fa���Ҷ��� 
				if(child->l == NULL && child->r == NULL){ // child���Ҷ��Ӷ�û�� 
						fa->r = NULL;
					}
				else if(child->l != NULL && child->r == NULL){ // ��֧ 
						fa->r = child->l;
					}
				else if(child->l == NULL && child->r != NULL){ // ��֧ 
						fa->r = child->r; 
					}
				else if(child->l != NULL && child->r != NULL){ // ˫֧ 
					fa->r = child->l; //����֧����ȥ 
					Bnode* p = child->l; //��p���ҵ���֧�����ұߵĶ˵�
					while(p->r) p = p->r;
					p->r = child->r; // Ȼ����֧������֧�����ұ� 
				}
			}
		}
		//ע������Ժ�delete child
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
	puts("����Ԫ�صĸ���n���Լ���n��Ԫ��");
	int n;
	cin>>n;
	// ����n������
	int v;
	for(int i=0; i<n; i++){
		cin>>v;
		insert(&T,v); 
	}
	puts("������������Ľ��"); 
	inorder_traver(T);cout<<endl;
	
	int re;
	puts("������Ҫ�����Ԫ�ص�ֵ");
	cin>>re;
	insert(&T,re);
	puts("�������Ԫ��ֵ֮��Ľ��");
	inorder_traver(T);cout<<endl;
	
	puts("������Ҫɾ����Ԫ�ص�Ԫ��ֵ");
	cin>>re;
	remove(&T,re);
	puts("����֮��Ľ��");
	inorder_traver(T);cout<<endl;
	
	return 0;
}
