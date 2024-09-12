/**
 * 算术表达式LL1文法的暴力递归分析方法
*/
#include <bits/stdc++.h>
using namespace std;

/// 语法规则
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
/// 判断中间推导出的句型是否与最终的句子有冲突
bool isCrash(const string &juxing, const string &juzi){
	/// 首先快速的根据长度判断是否冲突
	if(juxing.length() > 2*juzi.length()) return true;
    for(int i=0;i<juxing.length()&&i<juzi.length();++i){
		if(isVN(juxing[i])) return false;
		if(juxing[i] != juzi[i]) return true;
	}
	return false;
}
/// 利用规则将origin[idx]的非终结符替换掉
string replace(const string &origin, const string &rule, int idx){
    string ans;
	ans.append(origin.substr(0, idx));
	ans.append(rule);
	ans.append(origin.substr(idx+1));
	return ans;  
}
bool dfs(){
	/// 取出当前推导出的符号串
	/// 不能使用引用，因为在递归过程中改变了Ans的状态
	const string cur = Ans.back();
	/// 找出最左边的非终结符
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