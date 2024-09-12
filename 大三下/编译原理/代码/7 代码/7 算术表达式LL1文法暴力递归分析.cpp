/**
 * �������ʽLL1�ķ��ı����ݹ��������
*/
#include <bits/stdc++.h>
using namespace std;

/// �﷨����
vector<string> Rules[256];
inline bool isVN(char ch){return 'E'==ch||'T'==ch||'F'==ch||'Z'==ch||'Y'==ch;}

string Input;
vector<string> Ans;

int find(const string & s){
	for(int i=0;i<s.length();++i){
		if(isVN(s[i])){
			return i;
		}
	}
	return -1;
}
/// �ж��м��Ƶ����ľ����Ƿ������յľ����г�ͻ
bool isCrash(const string &juxing, const string &juzi){
	/// ���ȿ��ٵĸ��ݳ����ж��Ƿ��ͻ
	if(juxing.length() > 2*juzi.length()) return true;
    for(int i=0;i<juxing.length()&&i<juzi.length();++i){
		if(isVN(juxing[i])) return false;
		if(juxing[i] != juzi[i]) return true;
	}
	return false;
}
/// ���ù���origin[idx]�ķ��ս���滻��
string replace(const string &origin, const string &rule, int idx){
    string ans;
	ans.append(origin.substr(0, idx));
	ans.append(rule);
	ans.append(origin.substr(idx+1));
	return ans;  
}
bool dfs(){
	/// ȡ����ǰ�Ƶ����ķ��Ŵ�
	/// ����ʹ�����ã���Ϊ�ڵݹ�����иı���Ans��״̬
	const string cur = Ans.back();
	/// �ҳ�����ߵķ��ս��
    int t = find(cur);
	if(-1 == t) {
		return Input == cur;
	}
    char ch = cur[t];
	for(const auto &rule: Rules[ch]){
		string s = replace(cur, rule, t);
		if(isCrash(s, Input)) continue;
		Ans.emplace_back(s);
		bool b = dfs();
		if(b) return true;
		Ans.pop_back();
	}
	return false;
}
bool proc(){
    Ans.clear();
	Ans.push_back("E");
	bool b = dfs();
	return b;
}
void output(){
	cout<<Ans.front()<<endl;
	for(int i=1;i<Ans.size();++i){
		cout<<" -> "<<Ans[i]<<endl;
	}
	cout<<endl;
}

void initRules(){
    Rules['E'].push_back("TZ");
	Rules['Z'].push_back("+TZ");
    Rules['Z'].push_back("");
	Rules['T'].push_back("FY");
	Rules['Y'].push_back("*FY");
	Rules['Y'].push_back("");
	Rules['F'].push_back("(E)");
	Rules['F'].push_back("i");
}
int main() {
    freopen("1.txt", "r", stdin);
    initRules();
    while(cin>>Input){
		clock_t s = clock();
		bool b = proc();
		clock_t e = clock();
		if(b){
			cout<<("Yes")<<endl;
			output();
		}else{
			cout<<("No")<<endl;
		}
		cout<<"time: "<<e-s<<endl;
	}
    return 0;
}