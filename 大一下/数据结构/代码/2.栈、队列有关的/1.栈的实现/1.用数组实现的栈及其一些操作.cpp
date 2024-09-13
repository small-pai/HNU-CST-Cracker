#include<cstdio>
#include<iostream>
#define maxn_capacity 1000
using namespace std;
/**********************************************************
	1.这是栈的定义以及其一些基本操作
	2.因为这是专门给栈写的，所以有关操作的代码我都写成了函数，但实际上是不用写成函
	数的，平常使用栈的时候我们可以就一行代码把栈定义出来，包括其有关操作都可以一行代码实现！通常我们写代码就写成这种就够了，没必要进行一次封装！ 
	所以这个栈的代码看看怎么实现这几个操作就好了!!!!!!!!!在后面，你会明显的发现我们并没有使用这个自己封装好的栈！！！ 
	 
	3.对于栈的实现，我们可以使用数组实现（此时栈的大小就被固定了，或者说容量就被固定了），我们也可以使用链表的
	形式实现栈（称为链栈），此时栈的容量便不固定（或者说容量不固定），一个是静态的一个是动态的。但不管用哪种方法实现栈，
	栈本身的含义一直没有变，那就是后进先出的顺序，我们可以用这个来进行搜索（具体就是深度优先搜索，变的只是栈能储存数据的大小
	 
***********************************************************/
/*
	对于定义栈的函数就不写了，实际上就是定义一个数组，不管你是new（或者是malloc）出来的数组，还是在主函数里面定义的数组，反正就是一个数组 
	对于一个栈，一些基本操作就是 
	top()取出栈顶的元素
	pop()弹出栈顶的元素
	push()将元素放入栈 
	get_size()返回栈此时储存的数据的个数
	empty()返回此时栈是否为空
	full() 返回栈此时是否已经满了 
*/
struct Stack{
	//定义一个栈 s，假设这个栈储存的数据为int型的，那我们就定义一个int类型的数组即可，如果要存储其他类型的数据，定义成结构体数组即可 
	int data[maxn_capacity];//这个maxn_capacity是由你自己去定义这个栈的大小，这就是数组栈的局限，数组栈的最大大小在定义的时候就固定了
							//这个maxn_capacity可以使用宏定义，也可以定义成const int 类型的全局变量，两者都可以，此处我们让maxn_capacity为1000 
	int tail;			//对于栈，它还需要一个与之配套的tail下标（也可以理解成是这个数组的指针）,注意tail要初始化为0 
};
//这几个函数的设计由自己去构建 
bool top(Stack& s,int& ret){ //栈顶元素放在ret中返回回去 
	if(!s.tail) return false; // 栈此时为空，没有栈顶元素
	ret = s.data[s.tail-1];
	return true;
}
bool pop(Stack& s){
	if(!s.tail) return false;
	else s.tail--;
	return true;
}
bool full(Stack& s){
	return s.tail == maxn_capacity;
}
bool push(Stack& s,int val){
	if( full(s) ) return false;
	else s.data[s.tail++] = val;
	return true;
}
int get_size(Stack& s){
	return s.tail;
}
bool empty(Stack& s){
	return s.tail == 0;
}
int main(){
	Stack s; //定义一个栈s 
	//初始化 tail = 0
	s.tail = 0;
	
	//输入一些元素试试
	puts("输入元素的数量n，以及这n个元素");
	int n,val;
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>val;
		push(s,val);
	}
	puts("弹出这些元素并输出出来");
	int ret;
	while(!empty(s)){
		top(s,ret);
		pop(s);
		cout<<ret<<" ";
	}
	cout<<endl;
	
	return 0;
}
