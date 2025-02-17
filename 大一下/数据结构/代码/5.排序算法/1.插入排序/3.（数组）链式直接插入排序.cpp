#include<iostream>
#define maxn 1000
using namespace std;
/*********************************************************************************************************************************************
	1.这个是链式的直接插入排序，实际上是对数组的直接插入排序的优化
	2.对数组直接插入排序的优化是不用每一次插入都进行多次赋值，而是当形成L数组后每一个点最多只进行一次赋值，而L数组就相当与一条另外一种意义上的链表
	3.这个优化主要是在于当待排序的节点的大小很大时，这个赋值操作的速度便会慢下来（因为当节点很大的时候，一次节点的赋值就对相当多的变量进行了赋值），所以
	我们利用L数组实现类似链表的链式排序，实际上是对下标进行了排序 
	4.这个根据L数组复原的过程就是老师上课讲的搬家 
***********************************************************************************************************************************************/
int main(){
	int R[maxn];
	int L[maxn];
	int n;
//	先输入数据
	puts("请输入元素的个数n，以及这n个元素");
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	
	//将链建立起来
	for(int i=0; i<n; i++) L[i] = i+1; //形成这样逻辑上的链 0->1->2->3->4->.....->n->-1 
	L[n] = -1; //最后一个点的下一个L[n] = -1 
	// 对着一条链排序，实际上何链表的直接插入排序是一样的
	int p = L[0];
	L[0] = -1;
	int t;
	int next;
	while(p != -1){
		next = L[p];
		t = 0;
		while(L[t] != -1 && R[L[t]] < R[p]) t = L[t];
		L[p] = L[t];
		L[t] = p;
		p = next;
	}
	//现在L数组里面就储存了排好序的元素的先后关系，如果新开一个数组，我们可以很简单的解决这一个问题，但是如果不允许新开数组的话，我们只能用老师讲的搬家
	/***************************************************
		//这是新开数组的方法，我觉得应该很好理解了吧，但是我们需要浪费一倍的空间，所以在某些情况下并不是很可取，所以才有了后面所谓的“搬家” 
		int temp[maxn];
		int index = 1;
		p = L[0];
		while(p != -1){
			temp[index++] = R[p];
			p = L[p];
		}
		for(int i=1; i<=n; i++) R[i] = temp[i];
		for(int i=1; i<=n; i++) cout<<R[i]<<" ";
		cout<<endl;
	//****************************************************/
	
	/******************************************************************
		这个就是老师讲了很久的搬家，想法确实很精妙的，应该好好理解理解！！！ 
	*********************************************************************/
	int i = 1;
	p = L[0];
	while(p != -1){
		if(p == i){
			i++;
			p = L[p];
		}
		else if(p > i){
			// 交换 swap 写成函数好看一点
			int m = R[i];
			R[i] = R[p];
			R[p] = m;
			//交换所带来的的赋值 
			int next = L[p]; 	//因为L[p]后面被赋值为l[i]所以要提前记录一下，不然找不到p后面是谁了 
			L[p] = L[i]; 		//带着i后面的这一天链 
			L[i] = p;			//i被搬动到了p号位置 
			//往后面走 
			i++;
			p = next;
		}
		else {
			while(p < i) p = L[p]; //找到p正确的位置 
		}
	}
	//输出一下结果
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl;
	
	return 0;
}
