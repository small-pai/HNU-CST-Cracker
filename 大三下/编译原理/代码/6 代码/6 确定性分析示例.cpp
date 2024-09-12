/**
 * ȷ���Է���ʾ��
*/
#include <bits/stdc++.h>
using namespace std;

/// �﷨����
vector<string> Rules[256];
inline bool isVN(char ch){return 'S'==ch||'A'==ch||'B'==ch;}

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
	if(juxing.length() > juzi.length()) return true;
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
	if(-1 == t) return true;
    char ch = cur[t];
	for(const auto &rule: Rules[ch]){
		/// ���rule�ĵ�һ����ĸ��Ŀ�굱ǰcharacter
		char r1 = rule[0];
		char target = Input[t];
		if(r1 != target) continue;
		string s = replace(cur, rule, t);
		Ans.emplace_back(s);
		bool b = dfs();
		if(b) return true;
		Ans.pop_back();
	}
	return false;
}
bool proc(){
    Ans.clear();
	Ans.push_back("S");
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
    Rules['S'].push_back("pA");
	Rules['S'].push_back("qB");
    Rules['A'].push_back("cAd");
	Rules['A'].push_back("a");
	Rules['B'].push_back("dB");
	Rules['B'].push_back("b");
}
int main() {
    freopen("1.txt", "r", stdin);
    initRules();
    while(cin>>Input){
		bool b = proc();
		if(b){
			cout<<("Yes")<<endl;
			output();
		}else{
			cout<<("No")<<endl;
		}
	}
    return 0;
}
