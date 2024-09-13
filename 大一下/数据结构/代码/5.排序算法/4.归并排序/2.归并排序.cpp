#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
// �鲢���� �ǵݹ�ʵ��
// ��С�������� 
void merge(int R[],int tem[],int s,int m,int e){ // ��R����[s,m]�����[m+1,e]����ϲ�,(��ʱ[s,m],[m+1,e]�Ѿ���������) 
	int pa = s;
	int pb = m+1;
	int index = s;
	// �����鲢������ 
	while(pa <= m && pb <= e){
		if(R[pa] <= R[pb]) tem[index++] = R[pa++];
		else tem[index++] = R[pb++];
	}
	while(pa <= m) tem[index++] = R[pa++];
	while(pb <= e) tem[index++] = R[pb++];
	// copy
	for(int i=s; i<=e; i++) R[i] = tem[i];
	return ;
}
int main(){
	int n; // ����Ĵ�С
	int R[maxn];
	int tem[maxn]; //�鲢����ر�����ʱ����,������ʦ���� R1����
	// ��������
	cin>>n;
	for(int i=1; i<=n; i++) cin>>R[i];
	// forѭ���ϲ�����
	for(int len = 1; len<n; len <<= 1){ //len�������ɶ��ڵ�ǰ����R ÿlen �������Ѿ�������,����������ϲ�[1,1+len-1]��[1+len,len*2] 
		for(int i = 1; i+len<=n; i+=len*2){
			merge(R,tem,i,i+len-1,min(i+len*2-1,n)); // ��ϸ�����һ�仰,�����׹鲢����ǵݹ�ʵ�־������״���� 
		}
	}
	// �����ǿ����鲢����Ľ����ô��
	for(int i=1; i<=n; i++) cout<<R[i]<<" ";
	cout<<endl; 
	return 0; 
}
