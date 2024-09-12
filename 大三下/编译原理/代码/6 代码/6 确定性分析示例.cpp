/**
 * 确定性分析示例
*/
#include <bits/stdc++.h>
using namespace std;

/// 语法规则
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
/// 判断中间推导出的句型是否与最终的句子有冲突
bool isCrash(const string &juxing, const string &juzi){
	/// 首先快速的根据长度判断是否冲突
	if(juxing.length() > juzi.length()) return true;
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
	if(-1 == t) return true;
    char ch = cur[t];
	for(const auto &rule: Rules[ch]){
		/// 检查rule的第一个字母和目标当前character
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
