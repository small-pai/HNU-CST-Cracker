#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
struct edge{
	int u;
	int v;
	int w;
};
bool cmp(const edge& a,const edge& b){
	return a.w < b.w;
}
int get_ancester(int* F,int node){
	int t = node;
	while(F[t] != -1){
		t = F[t];
	}
	return t; 
}
int main(){
	edge e[1000];
	puts("������ߵ�����n���Լ���n���ߵ���Ϣ");
	int n;
	cin>>n;
	int u,v,w;
	//��ͼ 
	for(int i = 1; i<=n; i++){
		cin>>u>>v>>w;
		e[i].u = u;
		e[i].v = v;
		e[i].w = w;
	}
	//���ߵ�Ȩ�ش�С�������� ע�⿼�Ե�ʱ����ܲ�������STL���sort�����Կ����Լ�д���򣬻���ÿһ��forһ�����б��ҳ���̵ı� 
	sort(e+1,e+1+n,cmp);
	//
	for(int i=1; i<=n; i++){
		cout<<"i = "<<i<<"u : "<<e[i].u<<" v : "<< e[i].v << "w : "<< e[i].w<<endl; 
	}
	// define F ,ini
	int F[2000];
	for(int i=0; i<2000; i++) F[i] = -1;
	int sum = 0;
	// mist ���� 
	edge mist[1000];
	int index = 0;
	// 
	for(int i=1; i<=n; i++){
		edge now = e[i];
		int u = now.u;
		int v = now.v;
		int w = now.w;
		int ancester_u = get_ancester(F,u);
		int ancester_v = get_ancester(F,v);
		if(ancester_u == ancester_v) continue;
		else {
			F[ancester_u] = ancester_v;
			sum += w;
			mist[index] = now;
			index++;
//			mist[index++] = now;
		}
	}
	//out
	cout<<"MIST ��Ȩֵ��Ϊ"<<sum<<endl;
	cout<<"���⼸�����������Եõ���С������"<<endl;
	for(int i=0; i<index; i++){
		cout<<"u = "<<mist[i].u<<"v = "<<mist[i].v <<"w = "<<mist[i].w<<endl; 
	}
	return 0;
}

