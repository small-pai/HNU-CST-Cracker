#include<cstdio>
#include<iostream>
using namespace std;

/************************************************************************
	ע����� 
	1.ע������ǲ�����ͷ�ڵ�ĵ�����ע����б�ͷ�ڵ�ĵ�����Ա�!!!
	���߶Աȣ���Ӧ�ÿ�����������ͷ�ڵ㣨��ʵ������Ľڵ㣩�ĺô��� 
	
	2.Ϊ�˽�ʡʱ�䣬��ʲô����������ĺ����ҾͲ�����д�ˣ���ʵ����Щ����Ҳ��һ�仰 List L = NULL��
	3.���������Ĭ�ϵ��±��Ǵ�1��ʼ���� 1��Ԫ�ؾ��ǵ�һ��Ԫ�أ�����ϰ�ߴ�0��ʼ����0�ǵ�һ��Ԫ�صĻ���������Ӧ�ĸ��ļ���
	 
**************************************************************************/

typedef struct Node{ //����Ľڵ�Ķ��� 
	int data;
	Node* next;
}Node,*List;
/*************************************************************************************
	1.�ⲿ�������������в���Ԫ�صĲ���
	ʵ������һ��insert��������Խ����
	���ǿ��ܵ�ʱ��ῼʲô����дͷ���룬β���룬�����ҾͰ����������������ó���дһ��
	��Ҫ���ף���νͷ���룬β���룬���ʾ���insert������ pos ��ֵ
	3.ע��Ϊʲô�������L�����������ͣ�   ����˵��c���ԵĻ�Ҫ��List*���ͣ�ע��List*����ʵ����Node**���ͣ� �� �� 
	�����һ�����������˲�����ͷ�ڵ�ĵ�����ȴ���ͷ�ڵ���Ƿȱ�Ķ�����������ͷ�ڵ�ĵ�������ʲô����qwq��
	 
*********************************************************************************************/
void head_insert(List& L, int val){
	//������������ڵ���������� 
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	
	//���ýڵ����ͷ�� 
	t->next = L;
	L = t; // �����õ�ԭ�򣨻���c���ԣ���List*��ԭ�� ע�⣡���� 
	return ;
}
void tail_insert(List& L,int val){
	//������������ڵ����������
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	
	//���ڵ����β��
	// ���ҵ�β��������
	Node* p = L; //ʹ��ָ��p��Ѱ��
	while(p && p->next){
		p = p->next;
	} 
	//ѭ��������ʱ�����Ǿ��ҵ���β�������β�;���p����������Ҫ���ڵ����pָ��ڵ�ĺ���
	// ����ע������ѭ���л�д��һ�� p && p->next���ж�p�Ƿ�Ϊ�յ������������Ϊ�˷�ֹ����L����һ����������L == NULL����ô��ʱ��β����ʵ���Ͼ��Ǹ�ֵ
	if(p) p->next = t; //p��Ϊ�գ�˵��p��β�ڵ㣬��ô���ǽ��ڵ���뵽p�ĺ��� 
	else L = t; //pΪ�գ�˵��L������ǿյģ�����β���뵽L�������У�ʵ���Ͼ��� L = t;
	 
	
	return ;
}
bool Linsert(List& L,int pos,int val){ //��ֵval���뵽����L��posλ���ϼ�����Ľڵ��Ϊ����L�ĵ�pos���ڵ㣬��posλ�ò��Ϸ��򷵻�false�������ʧ�ܣ�ͬʱ�����κβ���
	//����������Ƚ��ڵ��������
	Node* t = new Node;
	t->data = val;
	t->next = NULL;
	//�����ǲ���Ҫ���뵽ͷ������pos = 1
	if(pos == 1) {
		t->next = L;
		L = t;
	} 
	else {
		//�ҵ�Ҫ�����λ�ã�ʵ������posλ��ǰ����Ǹ��ڵ� 
		Node*p = L; //��p���ҵ�λ�� 
		for(int i=1; i<pos-1 && p; i++){
			p = p->next;
		}
		if(p){ //�ڵ������p��p->next֮�� 
			t->next = p->next;
			p->next = t;
		}
		else { //pΪ�գ�˵��Ҫ�����λ�ò��Ϸ� 
			return false;
		}
	}
	return true;
}

//Lsize() 
int Lsize(List L){ //��������L��Ԫ�صĴ�С 
	int cnt = 0;
	Node* p = L;
	while(p){
		cnt++;
		p = p->next;
	}
	return cnt;
}

//reverse()
void reverse(List& L){
	Node* pre = NULL;
	Node* now = L;
	Node* next;
	
	while(now){
		next = now->next;
		now->next = pre;
		pre = now;
		now = next;
	}
	L = pre;
	return ;
}

void disp(List L){ //��ӡ���� 
	Node* p = L;
	while(p){
		cout<<p->data<<" ";
		p = p->next;
	}
	return ;
}
/**************************************************************************************************************
	�⼸����������insert����ǰ���Ѿ�ʵ���ˣ�ɾ��ĺ���������˼·��insert��������࣬�����Լ�ʵ�������֣�
	�⼸����������ֵ�����ζ������Լ���ƣ���Ҫ������������
	 
	bool remove(List L,int pos,int* del) ɾ������L��posλ���ϵĽڵ㣬����ɾ���Ľڵ��ֵͨ��ָ��del�������������Ƿ�ɾ���ɹ�
	Node* at(List L,int pos) ���� ָ������L��posλ���Ͻڵ��ָ�룬û��posλ���ϵĽڵ�ͷ��ؿ� 
	bool modify(List L,int pos,int new_val) �������posλ���ϵĽڵ��ֵ��Ϊnew_val���޸ĳɹ��ͷ���true�����򷵻�false 
***************************************************************************************************************/
Node* Lat(List L,int pos){
	Node* p = L;
	for(int i=1; p&&i<pos; i++) p = p->next;
	return p;
}
bool Lremove(List& L,int pos,int* del){ //ע��Ϊʲô������ 
	//�����ǲ���ɾ����ͷ�ڵ�
	if(pos == 1){
		if(L == NULL) return false;//������ǿսڵ㣬ɾ��ʧ��
		else {
			Node* t = L;
			L = L->next;
			*del = t->data;//��ɾ���Ľڵ��ֵ������
			delete t;//ɾ���ڵ� 
		}
	}
	else {
		Node* p = L;//�ҵ�Ҫɾ���Ľڵ��ǰ��һ���ڵ㣨����ǰ���ڵ㣩 
		for(int i=1; p&&i<pos-1; i++) p = p->next;
		if(p && p->next){
			Node* t = p->next;
			p->next = t->next;
			*del = t->data;
			delete t;
		}
		else return false;//p����p->next����һ��Ϊ�գ��������޷�ɾ������ɾ��ʧ�� 
	}
	return true;
}
bool Lmodify(List L,int pos,int new_val){
	Node* p = L;
	for(int i=1; p&&i<pos; i++) p = p->next;
	if(p) p->data = new_val;
	else return false;//pΪ�գ�˵����ǰ�����и�����û��pos���λ���ϵĽڵ㣬�����޸�ʧ�ܣ�����false
	 
	return true;
}
int main(){
	//����һ��������������
	List L = NULL; // L������ʹList��ʵ���Ͼ���Node*����
	
	//������������������������һЩ����
	int n,val;
	puts("������Ԫ�صĸ���n���Լ���n��Ԫ��");
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>val;
		head_insert(L,val); //ͷ����
							//β���� ����� tail_insert(L,val)
							//������insert(L,1,val) 
	}
	// ���ǿ������һ��������Ԫ�صĸ��� �� Lsize() ����
	// ������������һֱ��ͷ��������ȥ�����ʱ���������Ӧ����ʲô���ӣ��ǲ��ǻ������Ĳ�һ�� 
	cout<<"����L��Ԫ�صĸ���Ϊ"<<Lsize(L)<<endl;
	cout<<"��ʱ���� : ";
	disp(L); 
	cout<<endl;
	
	// ��������L��ת reverse()���������ܻῼ��Ҳ���ܲ��ᣬ������
	reverse(L);
	cout<<"����ת֮�� : ";
	disp(L);
	cout<<endl;
	
	// �ټ���ʹ�õ����� 
	// Lat
	Node* p = Lat(L,2);
	if(p) cout<<"at 2 "<<p->data<<endl;
	//Lremove
	int dele;
	bool f = Lremove(L,2,&dele);
	if(f) cout<<dele<<" is removed"<<endl;
	else cout<<"fail to remove"<<endl;
	disp(L); cout<<endl;
	//Lmodify
	int new_val = 100;
	f = Lmodify(L,2,new_val);
	if(f){
		Node* t = Lat(L,2);
		if(t) cout<<"�ڵ�2 "<<"has been modified to "<<t->data<<endl;
	}
	else cout<<"fail to modify"<<endl;
	disp(L); cout<<endl;
	return 0;
}
