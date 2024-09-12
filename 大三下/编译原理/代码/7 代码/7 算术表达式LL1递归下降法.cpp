/**
 * �������ʽLL1�ķ����ݹ��½���
*/
#include <bits/stdc++.h>
using namespace std;

/// �﷨����
vector<string> Rules[256];

const string VN = "ETFZY";
inline bool isVN(char ch){return 'E'==ch||'T'==ch||'F'==ch||'Z'==ch||'Y'==ch;}
inline bool isVT(char ch){return !isVN(ch);}

int const UNKWN = 0;
int const EMPTY = 1;
int const NOEMP = 2;
int IsEps[256] = {UNKWN};

/// First����
set<char> First[256];

/// Follow����
set<char> Follow[256];

/// ѡ�񼯺�, Select[A][0]��ʾA�ĵ�0������Ľ��
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

/// �����ս����Ϊ���࣬һ���ܹ������գ�һ�಻��
/// ���������ȫ������IsEps��
void calcEpsilon(){
	bool flag = false;
EPS_L:
    flag = false;
	/// forÿһ��vn��ÿһ������
	for(char vn: VN){
		if(UNKWN != IsEps[vn]) continue;
		bool feikong = true;
		for(const string&rule: Rules[vn]){
			/// ����ұߵ�ÿһ�����Ŷ��ǿյģ����vnҲ�ǿյ�
			/// ����ұ���һ�����Ų��ǿյģ���ù���Կ�û��Ӱ��
			/// ���vn�����й��򶼶Կ�û��Ӱ�죬��vn�Ƿǿյ�
			/// ����ұ��в�֪���ķ��ţ����vn��ʱҲ��֪��
			if(rule.empty()){ // ֱ�ӾͿ����п�
				IsEps[vn] = EMPTY; 
				flag = true; // ��ʾ�������µĽ��
				feikong = false; // ��ʾ�϶����Ƿǿ���
				continue;
			}
			bool t = true;
			for(char ch: rule){
				/// ��ʾ���п�û�а���
				if(isVT(ch) || NOEMP == IsEps[ch]){
					t = false; break;
				}
				/// ���п�û�а�������ͬ��Ҳ���ܿ϶��Ƿǿ�
				if(UNKWN == IsEps[ch]){
					t = feikong = false; break;
				}
			}
			/// ˵��rule��������ɶ������Ƶ�����
			if(t) IsEps[vn] = EMPTY, flag = true, feikong = false;
		}		
		if(feikong) IsEps[vn] = NOEMP, flag = true;	
	}
	if(flag) goto EPS_L;
   
	/// ����൱�ڵ������
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

/// �������з��ս����First����
/// ���������ȫ��������First��
void calcFirst(){
    bool flag = false;
FIRST_L:
    flag = false;
	/// ���Ȱ��������Ƶ����յķ��ս������Ͽ�
	for(char vn: VN)if(EMPTY == IsEps[vn]){
		flag = (First[vn].insert('\0')).second || flag;
	}
    /// forÿһ��vn��ÿһ������
	for(char vn: VN)for(const string&rule: Rules[vn]){
		if(rule.empty()) continue; // �չ����Ѿ�û����
        /// A=BCD... ��ÿһ�����򣬰��ұ߷��ŵ�first�ǿռ���first(A)
		/// ����ұ�ĳ�����ŵ�firstΪ�գ����ǻ�û����		
		for(char ch: rule){
			if(isVT(ch)){ // ֱ����Ӽ��ɣ�������ĸ�Ͳ����ٿ�����
                flag = (First[vn].insert(ch)).second || flag;
				break; 
			}
			/// ��ʱch����VN����ch��First���϶��ӽ�ȥ
            for(auto t: First[ch]){
				if('\0' == t) continue;
				flag = (First[vn].insert(t)).second || flag;
			}
			/// �����VN�Ƿǿյģ��������ĸ�Ͳ��ÿ�����
			if(NOEMP == IsEps[ch]) break;
		}
	}
	if(flag) goto FIRST_L;
	
	/// ����൱�ڵ������
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

/// ����ָ�����Ŵ���First����
/// ������Ŵ�Ϊ ABC...
/// ��FirstA�����AΪ�գ�����FirstB,���BΪ�ջ���FirstC...
set<char> calcFirst(const string &s){
    set<char> ans;
	bool bb = false;
    for(char ch: s){
		if(isVT(ch)){ // �ս��ֱ�����
			ans.insert(ch); bb = true;
			break;
		}
		/// ch��VN������Ҫ����First����
		bool b = false;
	    for(char t: First[ch]){
            if('\0' == t){
				b = true;
			}else{
				ans.insert(t);
			}
		}	
		if(!b) {bb = true; break;} // �������յĻ��Ͳ�������
	}
	/// bbΪ��˵����break�����ģ�˵�����岻Ϊ��
	if(!bb){ans.insert('\0');}
	return ans;
}

/// ����ÿһ�����ս����Follow����
/// ���������ȫ������Follow��
void calcFollow(){
    bool flag = false;
Follow_L:
    flag = false;
    /// ���Ȱ�#����Follow(E)
	Follow['E'].insert('#');
	/// forÿһ��vn��ÿһ������
	for(char vn: VN)for(const string&rule: Rules[vn]){
        /// ��������ұߵ�ÿһ�����ս��
		for(int i=0,n=rule.length();i<n;++i){
			if(isVT(rule[i])) continue; // �����VT���Ͳ�����
			set<char> tmp = calcFirst(rule.substr(i+1));
			/// tmp�����зǿռ���Follow(vn)
			bool bb = false;
			for(char t: tmp){
				if('\0' == t){
					bb = true;
				}else{
					flag = (Follow[rule[i]].insert(t)).second || flag;
				}
			}
			/// ˵������Ϊ�գ�����Ҫ��Follow(vn)����
			if(bb)for(char t: Follow[vn]){
				flag = (Follow[rule[i]].insert(t)).second || flag;
			}
		}
	}
	if(flag) goto Follow_L;

	/// ����൱�ڵ������
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

/// ����ѡ�񼯺ϣ���Թ������
/// ���������Select��
void calcSelect(){
    for(char vn: VN)for(int i=0;i<Rules[vn].size();++i){
		/// rule��vn�ĵ�i������
        const string &rule = Rules[vn][i];
		set<char> ans;
	    set<char> first = calcFirst(rule);
		bool bb = false;
		for(char ch: first){
			if('\0' == ch) bb = true;
			else ans.insert(ch);
		}
		/// ����пջ���Ҫ��Follow�ӽ�ȥ
		if(bb)for(char ch: Follow[vn]){
			ans.insert(ch);
		}
		Select[vn].push_back(std::move(ans));
	}

	/// �൱�ڵ������
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

/// ���ù���origin[idx]�ķ��ս���滻��
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
    Input += '#'; // Ҫ��һ���������
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
    init(); // ����
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

