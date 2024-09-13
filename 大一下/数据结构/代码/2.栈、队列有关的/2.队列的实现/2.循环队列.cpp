#include<iostream>
#define maxn_capacity 100000 
using namespace std;
/**************************************************************************************************
	1.���ѭ����������ͨ�����ڴ�������һ���ģ���Ҫ���ڴﵽmaxn_capacity��ʱ��ص�0��ʼ����ѭ������ 
	2.ʵ���ϵ�ѭ����������ȡģ������Ϊmaxn_capacity��ѭ�����п�����[0,maxn_capacity-1]λ�ô������ݣ� 
	3.������Ӧ�����벻ѭ���Ķ��еĲ��
	4.ע������������ 
	5.����֮����ᷢ����νѭ�����У��������ڳ����ܷ���ʹ���Ѿ�������Ԫ�صĿռ䣬������ǰ�����ͨ����һ����tailһֱ�� tail++ headҲһֱ��head++ 
***************************************************************************************************/
struct loop_queue{
	int data[maxn_capacity]; //maxn_capacity 100000
	int head,tail;
};
void ini(loop_queue& q){ //��ʼ�� ��head = tail = 0 
	q.head = q.tail = 0;
	return ;
}
bool empty(loop_queue& q){
	return q.head == q.tail;
}
bool full(loop_queue& q){
	/*
		ÿһ���������������Ԫ�ص�λ��Ӧ����q.tail��������Ԫ��֮��
		tailӦ�ñ�Ϊ (q.tail+1)%maxn_capacity�������ʱtail��1��ȡģ֮������head��ȣ�˵����ʱ�����Ѿ����ˣ������������Ԫ����
		�����൱���˷�һ���ռ����ж��Ƿ��ʱ�����Ѿ�����
		���� ѭ�����е�maxn_capacityΪ5
 		��ʱhead = 0��tail = 4�����Ҫ�����������Ԫ�أ������tail��4��λ���ϣ�������֮��tail = (4+1)%5 = 0����ʱtail == head��
		����4��λ�ñ�����û�з���Ԫ�صģ�����������Ϊ��ʱѭ�����л������ˣ���Ϊ4��λ�÷���Ԫ��֮��tail�͵���head�ˣ�����������Ϊ��ʱ����
		����ѭ�������м���Ԫ��
		��������Ŀ����Ҫ��Ҫ���ж���Ϊ�գ�tail == head�����ж���Ϊ���������ֿ�����Ȼ�����޷���ѭ���������жϵ����ǿջ����� 
		!!!�����������£�����Ϊmaxn_capacity��ѭ������ʵ����ֻ�ܴ�����maxn_capacity-1 �����ݣ���Ϊ��һ���ռ䲻�ᱻʹ�� 
	*/
	return (q.tail+1)%maxn_capacity == q.head; 
}
bool push(loop_queue& q,int val){
	if(!full(q)) {
		q.data[q.tail] = val;
		q.tail = (q.tail+1)%maxn_capacity;
	}
	else return false; //��ʱ�����Ѿ����ˣ��޷��ٷ���Ԫ��
	 
	return true;
}
bool top(loop_queue& q,int& ret){
	if(!empty(q)) ret = q.data[q.head];
	else return false; //��ʱ����Ϊ�գ�������û����Ԫ��
	 
	return true;
}
bool pop(loop_queue& q){
	if(!empty(q)){
		q.head = (q.head+1)%maxn_capacity; //ʼ��Ҫע�⣬��ʱ������ѭ�������ģ�����һ��Ҫ�ǵ�ȡģ 
	}
	else return false; //����Ϊ�գ�������û��Ԫ�ؿ��Ե��� 
	
	return true;
}
int main(){
	loop_queue q;
	ini(q);
	
	//����һЩԪ������
	cout<<"������Ԫ�صĸ���n���Լ���n��Ԫ��"<<endl;
	int n,val;
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>val;
		push(q,val);
	}
	//������ЩԪ�� 
	cout<<"������ЩԪ��"<<endl;
	int r;
	while(!empty(q)){
		top(q,r);
		pop(q);
		cout<<r<<" ";
	}
	cout<<endl;
	return 0;
}
