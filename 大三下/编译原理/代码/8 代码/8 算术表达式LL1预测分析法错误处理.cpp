/**
 * �������ʽLL1�ķ�Ԥ�������
 * ���ִ�����ʾ��
*/
#include <bits/stdc++.h>
using namespace std;

/// �﷨����
vector<string> Rules[256];

const string VN = "ETFZY";
const string VT = "()+*i#";
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


map<char, map<char, string> > PreDictiveParseTable;
pair<bool, string> queryPreDictiveParseTable(char vn, char vt){
    auto it = PreDictiveParseTable.find(vn);
    if(it == PreDictiveParseTable.end()) return {false, ""};
    auto jt = it->second.find(vt);
    if(jt == it->second.end()) return {false, ""};
    if("ER" != jt->second.substr(0, 2)){
        return {true, jt->second};
    }
    return {false, jt->second};
}

string ErrMsg;
map<string, string> ErrMsgs;
void calcErrs(){
    auto &m = PreDictiveParseTable;
    ErrMsgs[m['T']['#'] = "ER1"] = "missing a operand";
    ErrMsgs[m['E']['+'] = "ER1"] = "missing a operand";
    ErrMsgs[m['E']['*'] = "ER1"] = "missing a operand";
    ErrMsgs[m['Z']['i'] = "ER2"] = "missing a operator";
    ErrMsgs[m['Y']['i'] = "ER2"] = "missing a operator";
}

/// ����Ԥ�������������ȫ��������
void calcPredictiveParseTable(){
    /// forÿһ��vn��ÿһ�������ѡ�񼯺�
    for(char vn: VN)for(int i=0;i<Rules[vn].size();++i){
        /// ����
        const string &rule = Rules[vn][i];
        /// ѡ�񼯺�
        const set<char> &select = Select[vn][i];
        /// ���
        for(char vt: select){
            PreDictiveParseTable[vn][vt] = rule;
        }
    }

    /// �൱�ڵ������
    printf("======Predictive Parse Table======\n");
    printf("   ");
    for(char vt: VT) printf("%-6c", vt);
    printf("\n");
    for(char vn: VN){
        printf("%-3c", vn);
        for(char vt: VT){
            auto ans = queryPreDictiveParseTable(vn, vt);
            if(ans.first){
                printf("%-6s", ""==ans.second?"KONG":ans.second.c_str());
            }else{
                printf("      ");
            }
        }
        printf("\n");
    }
}

string Input;
vector<string> Ans;

void output(){
	cout<<Ans.front()<<endl;
	for(int i=1;i<Ans.size();++i){
		cout<<" -> "<<Ans[i]<<endl;
	}
	cout<<endl;
}

bool proc(){
    Input += "#";
    vector<char> st;
    st.push_back('#');
    st.push_back('E');
    Ans.assign(1, "E");
    string poped; // ���ڽ���pop����������
    int cur = 0;
    while(1){
        if(st.back() == Input[cur]){
            if('#' == Input[cur]){
                return true;
            }else{
                poped += st.back();
                st.pop_back(); 
                ++cur;
            }
        }else if(isVN(st.back())){
            auto ans = queryPreDictiveParseTable(st.back(), Input[cur]);
            if(!ans.first) {
                ErrMsg = ErrMsgs[ans.second];
                return false;
            }
            poped += st.back();
            st.pop_back();
            /// ������ջ
            st.insert(st.end(), ans.second.rbegin(), ans.second.rend());
            /// ��¼�Ƶ����̣�pop�����ݼ�ջ������ݾ��ǵ�ǰ����
            Ans.push_back(Input.substr(0, cur)+string(st.rbegin(), --st.rend()));
        }else{
            ErrMsg = "unknow error";
            return false;
        }
    }
    /// never here
    return false;
}

int main() {
    initRules();
    calcEpsilon();
	calcFirst();
	calcFollow();
	calcSelect();
    calcPredictiveParseTable();
    calcErrs();
    freopen("1.txt", "r", stdin);
    while(cin>>Input){
        bool b = proc();
        if(b){
            cout<<"Yes"<<endl;
            output();
        }else{
            cout<<"No: "<<ErrMsg<<endl;
        }
    }
    return 0;
}