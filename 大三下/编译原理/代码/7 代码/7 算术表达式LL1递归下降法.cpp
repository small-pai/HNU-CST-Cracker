/**
 * 算术表达式LL1文法，递归下降法
*/
#include <bits/stdc++.h>
using namespace std;

/// 语法规则
vector<string> Rules[256];

const string VN = "ETFZY";
inline bool isVN(char ch){return 'E'==ch||'T'==ch||'F'==ch||'Z'==ch||'Y'==ch;}
inline bool isVT(char ch){return !isVN(ch);}

int const UNKWN = 0;
int const EMPTY = 1;
int const NOEMP = 2;
int IsEps[256] = {UNKWN};

/// First集合
set<char> First[256];

/// Follow集合
set<char> Follow[256];

/// 选择集合, Select[A][0]表示A的第0条规则的结果
vector<set<char>> Select[256];

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

/// 将非终结符分为两类，一类能够导出空，一类不能
/// 结果保存在全局数组IsEps中
void calcEpsilon(){
	bool flag = false;
EPS_L:
    flag = false;
	/// for每一个vn的每一条规则
	for(char vn: VN){
		if(UNKWN != IsEps[vn]) continue;
		bool feikong = true;
		for(const string&rule: Rules[vn]){
			/// 如果右边的每一个符号都是空的，则该vn也是空的
			/// 如果右边有一个符号不是空的，则该规则对空没有影响
			/// 如果vn的所有规则都对空没有影响，则vn是非空的
			/// 如果右边有不知道的符号，则该vn暂时也不知道
			if(rule.empty()){ // 直接就可以判空
				IsEps[vn] = EMPTY; 
				flag = true; // 表示产生了新的结果
				feikong = false; // 表示肯定不是非空了
				continue;
			}
			bool t = true;
			for(char ch: rule){
				/// 表示对判空没有帮助
				if(isVT(ch) || NOEMP == IsEps[ch]){
					t = false; break;
				}
				/// 对判空没有帮助，但同样也不能肯定是非空
				if(UNKWN == IsEps[ch]){
					t = feikong = false; break;
				}
			}
			/// 说明rule的所有组成都可以推导出空
			if(t) IsEps[vn] = EMPTY, flag = true, feikong = false;
		}		
		if(feikong) IsEps[vn] = NOEMP, flag = true;	
	}
	if(flag) goto EPS_L;
   
	/// 最后相当于调试输出
	string a, b;
	for(char ch: VN){
		if(EMPTY == IsEps[ch]) a += ch;
		else if(NOEMP == IsEps[ch]) b += ch;
		else if(UNKWN == IsEps[ch]) throw runtime_error("unkown epsilon with " + string(1, ch));
		else throw runtime_error("unkown epsilon value.");
	}
	cout<<"Epsilon: "<<a<<endl;
	cout<<"NonEps: "<<b<<endl;
	cout<<endl;
}

/// 计算所有非终结符的First集合
/// 结果保存在全局数组中First中
void calcFirst(){
    bool flag = false;
FIRST_L:
    flag = false;
	/// 首先把所有能推导出空的非终结符添加上空
	for(char vn: VN)if(EMPTY == IsEps[vn]){
		flag = (First[vn].insert('\0')).second || flag;
	}
    /// for每一个vn的每一条规则
	for(char vn: VN)for(const string&rule: Rules[vn]){
		if(rule.empty()) continue; // 空规则已经没用了
        /// A=BCD... 对每一条规则，把右边符号的first非空加入first(A)
		/// 如果右边某个符号的first为空，就是还没计算		
		for(char ch: rule){
			if(isVT(ch)){ // 直接添加即可，后序字母就不用再考虑了
                flag = (First[vn].insert(ch)).second || flag;
				break; 
			}
			/// 此时ch就是VN，把ch的First集合都加进去
            for(auto t: First[ch]){
				if('\0' == t) continue;
				flag = (First[vn].insert(t)).second || flag;
			}
			/// 如果该VN是非空的，则后序字母就不用考虑了
			if(NOEMP == IsEps[ch]) break;
		}
	}
	if(flag) goto FIRST_L;
	
	/// 最后相当于调试输出
	cout<<"======First Set======"<<endl;
	for(char vn: VN){
        cout<<vn<<":";
		for(char ch: First[vn]){
            if('\0' == ch) cout<<" KONG";
			else cout<<" "<<ch;
		}
		cout<<endl;
	}
	cout<<endl;
}

/// 计算指定符号串的First集合
/// 假设符号串为 ABC...
/// 则FirstA，如果A为空，还有FirstB,如果B为空还有FirstC...
set<char> calcFirst(const string &s){
    set<char> ans;
	bool bb = false;
    for(char ch: s){
		if(isVT(ch)){ // 终结符直接添加
			ans.insert(ch); bb = true;
			break;
		}
		/// ch是VN，则需要加入First集合
		bool b = false;
	    for(char t: First[ch]){
            if('\0' == t){
				b = true;
			}else{
				ans.insert(t);
			}
		}	
		if(!b) {bb = true; break;} // 不包含空的话就不继续了
	}
	/// bb为真说明是break出来的，说明整体不为空
	if(!bb){ans.insert('\0');}
	return ans;
}

/// 计算每一个非终结符的Follow集合
/// 结果保存在全局数组Follow中
void calcFollow(){
    bool flag = false;
Follow_L:
    flag = false;
    /// 首先把#加入Follow(E)
	Follow['E'].insert('#');
	/// for每一个vn的每一条规则
	for(char vn: VN)for(const string&rule: Rules[vn]){
        /// 计算规则右边的每一个非终结符
		for(int i=0,n=rule.length();i<n;++i){
			if(isVT(rule[i])) continue; // 如果是VT，就不用算
			set<char> tmp = calcFirst(rule.substr(i+1));
			/// tmp的所有非空加入Follow(vn)
			bool bb = false;
			for(char t: tmp){
				if('\0' == t){
					bb = true;
				}else{
					flag = (Follow[rule[i]].insert(t)).second || flag;
				}
			}
			/// 说明后面为空，还需要将Follow(vn)加入
			if(bb)for(char t: Follow[vn]){
				flag = (Follow[rule[i]].insert(t)).second || flag;
			}
		}
	}
	if(flag) goto Follow_L;

	/// 最后相当于调试输出
	cout<<"======Follow Set======"<<endl;
	for(char vn: VN){
        cout<<vn<<":";
		for(char ch: Follow[vn]){
			cout<<" "<<ch;
		}
		cout<<endl;
	}
	cout<<endl;	
}

/// 计算选择集合，针对规则而言
/// 结果保存在Select中
void calcSelect(){
    for(char vn: VN)for(int i=0;i<Rules[vn].size();++i){
		/// rule是vn的第i条规则
        const string &rule = Rules[vn][i];
		set<char> ans;
	    set<char> first = calcFirst(rule);
		bool bb = false;
		for(char ch: first){
			if('\0' == ch) bb = true;
			else ans.insert(ch);
		}
		/// 如果有空还需要把Follow加进去
		if(bb)for(char ch: Follow[vn]){
			ans.insert(ch);
		}
		Select[vn].push_back(std::move(ans));
	}

	/// 相当于调试输出
	cout<<"======Select Set======"<<endl;
	for(char vn: VN){
        for(int i=0;i<Rules[vn].size();++i){
			cout<<"Select("<<vn<<" = ";
			cout<<(Rules[vn][i].empty()?"KONG":Rules[vn][i]);
			cout<<") = {";
			for(char ch: Select[vn][i]){
				cout<<ch<<", ";
			}
			cout<<"\b\b}"<<endl;
		}
	}
	cout<<endl;		
}

void init(){
    initRules();
    calcEpsilon();
	calcFirst();
	calcFollow();
	calcSelect();
}

string Input;
int CurIdx;
vector<string> Ans;

int find(const string & s){
	for(int i=0;i<s.length();++i){
		if(isVN(s[i])){
			return i;
		}
	}
	return -1;
}

/// 利用规则将origin[idx]的非终结符替换掉
string replace(const string &origin, const string &rule, int idx){
    string ans;
	ans.append(origin.substr(0, idx));
	ans.append(rule);
	ans.append(origin.substr(idx+1));
	return ans;  
}

bool dfsT();
bool dfsZ();
bool dfsF();
bool dfsY();
bool match(char);

/// E=TZ
bool dfsE(){
    if(Select['E'][0].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('E' == s[t]);
        string ss = replace(s, Rules['E'][0], t);
        Ans.push_back(ss);

        if(!dfsT()) return false;
        if(!dfsZ()) return false;
        return true;
    }
    return false;
}

/// T=FY
bool dfsT(){
    if(Select['T'][0].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('T' == s[t]);
        string ss = replace(s, Rules['T'][0], t);
        Ans.push_back(ss);

        if(!dfsF()) return false;
        if(!dfsY()) return false;
        return true;
    }
    return false;
}

/// Z = +TZ | kong
bool dfsZ(){
    if(Select['Z'][0].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('Z' == s[t]);
        string ss = replace(s, Rules['Z'][0], t);
        Ans.push_back(ss);

        if(!match('+')) return false;
        if(!dfsT()) return false;
        if(!dfsZ()) return false;
        return true;
    }
    if(Select['Z'][1].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('Z' == s[t]);
        string ss = replace(s, Rules['Z'][1], t);
        Ans.push_back(ss);

        return true;
    }
    return false;
}

/// F = (E) | i
bool dfsF(){
    if(Select['F'][0].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('F' == s[t]);
        string ss = replace(s, Rules['F'][0], t);
        Ans.push_back(ss);          

        if(!match('(')) return false;
        if(!dfsE()) return false;
        if(!match(')')) return false;
        return true;
    }
    if(Select['F'][1].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('F' == s[t]);
        string ss = replace(s, Rules['F'][1], t);
        Ans.push_back(ss);  

        if(!match('i')) return false;
        return true;         
    }
    return false;
}

/// Y = *FY | kong
bool dfsY(){
    if(Select['Y'][0].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('Y' == s[t]);
        string ss = replace(s, Rules['Y'][0], t);
        Ans.push_back(ss);          

        if(!match('*')) return false;
        if(!dfsF()) return false;
        if(!dfsY()) return false;
        return true;
    }
    if(Select['Y'][1].count(Input[CurIdx])){
        string s = Ans.back();
        int t = find(s);
        assert('Y' == s[t]);
        string ss = replace(s, Rules['Y'][1], t);
        Ans.push_back(ss); 

        return true;
    }
    return false;
}

bool match(char ch){
    if(Input[CurIdx] != ch) return false;
    ++CurIdx;
    return true;
}

bool proc(){
    Input += '#'; // 要加一个结束标记
    Ans.assign(1, "E");
    CurIdx = 0;
    bool b = dfsE();
    return b;
}

void output(){
	cout<<Ans.front()<<endl;
	for(int i=1;i<Ans.size();++i){
		cout<<" -> "<<Ans[i]<<endl;
	}
	cout<<endl;
}

int main(){
    freopen("1.txt", "r", stdin);
    init(); // 计算
    while(cin>>Input){
        bool b = proc();
        if(b){
            cout<<"Yes"<<endl;
            output();
        }else{
            cout<<"No"<<endl;
        }
    }
}

