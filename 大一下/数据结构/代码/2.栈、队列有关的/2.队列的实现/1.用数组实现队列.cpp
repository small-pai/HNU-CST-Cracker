#include<iostream>
#define maxn_capacity 100000 
using namespace std;
/*******************************************************************************************************
	1.���к�ջ��������ǣ��������Ƚ��ȳ��� 
	2.ʵ�ֵ�ʱ����һ�����������С��head��tail�Ϳ����� 
	3.ͬ����һ��������ʵ����ʹ�õ�ʱ���ðѶ��з�װ����������Щ��Ӧ�����ĺ�������һ�д���Ϳ��Խ����
	4.����Ҳֻ�ÿ���ʵ�־ͺã��������Ӧ�õ�ʱ�򣬱������Թ��������
	�������Щ�����Ƕ�ֻ�ö���һ�����飬һ��headһ��tail�Ϳ��Խ���ˣ��� 
	
*********************************************************************************************************/
struct queue{
	int data[maxn_capacity];  //maxn_capacity����������������Ĵ�����������������ʹ�õ��Ǻ궨�壬��Ϊ���Ϊ100000 
	int head,tail;           //headָ��ǰ���еĵ�һ��Ԫ�أ�tailָ���һ���������ݵ�λ�ã��� [head,tail) �ķ�Χ�ڱ�ʾ��ǰ�����е�Ԫ�� 
};
void ini(queue& q){//���еĳ�ʼ�� 
	q.head = q.tail = 0;
	return ;
}
bool empty(queue& q){ // �����Ƿ����qΪ�� 
	return q.head == q.tail;
}
bool push(queue& q,int v){ //�Ӷ�β���룬���װ�����ˣ��ͷ���false 
	if(q.tail < maxn_capacity) q.data[q.tail++] = v;
	else return false;
	
	return true;
}
bool front(queue& q,int& ret){ //ret�д�������Ԫ�أ��������Ϊ�գ���head == tail���򷵻�false 
	if(!empty(q)) ret = q.data[q.head];
	else return false;
	
	return true;
}
bool pop(queue& q){ //��������Ԫ�أ��������Ϊ�գ��򵯳�ʧ�ܣ�����false 
	if(!empty(q)) q.head++;
	else return false;
	
	return true;
}
int main(){
	queue q;
	ini(q);
	
	//����һЩԪ��
	cout<<"������Ԫ�ص�����n���Լ���n��Ԫ��"<<endl;
	int n,val;
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>val;
		push(q,val);
	}
	cout<<"�������е�Ԫ��ȫ������"<<endl;
	int r;
	while(!empty(q)){
		front(q,r);
		pop(q);
		cout<<r<<" ";
	}
	cout<<endl;
	return 0;
} 
