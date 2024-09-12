/// POJ��֧��C++11�������˾͵�����
#include <bits/stdc++.h>
using namespace std;

/// ԭʼ���ݣ���1��Ϊ��ʼ����
const string VN_STR = " SZW";
const vector<string> RULES_STR = {
	"",
	"S=ZW", "W=i",
	"W=tZ", "W=v",
	"W=vZ", "W=fi",
	"W=ftZ", "W=fv", "W=fvZ",
	"Z=d", "Z=gm", "Z=gxm"
};

typedef vector<int> vi;

const int VN_MSK = 0x100;
string VT_STR = "#";
int V2Idx[256];

/// ����VN��VT�ı��
vi VN, VT(1, 0); 
/// ���ֻ��Ĺ���Rules[i]���ǵ�i������
vi RulesLeft;
vector<vi> Rules;
/// ��vn��ȡ�Ĺ���ı��, VnRules[i][j]��ʾ���ս��i�ĵ�j����������
vector<vi> VnRules(VN_STR.size()+1);

/// ���ֻ�Grammar�������ַ���תΪ����
/// ����Vt��1��2��3����#���Ϊ0
/// Vn��0x101��ʼ������
void digitalGrammar(){
	/// ��ȷ��VN�ı��
	for(int i=1;i<VN_STR.length();++i) VN.push_back(V2Idx[VN_STR[i]] = i | VN_MSK);
	/// ��ȷ��Vt�ı�Ų��Ұѹ����Ϊ��������
	Rules.push_back(vi()); // ��0��������
	RulesLeft.push_back(0);
	for(int i=1;i<RULES_STR.size();++i){
		const string & str = RULES_STR[i]; // ��i������
		vi ans; // ���ֻ��ĵ�i������
        for(char ch: str.substr(2)){
			if(0 == V2Idx[ch]){ // �϶�����δ��ŵ��ս��
                VT.push_back(V2Idx[ch] = VT_STR.length());
				VT_STR += ch;
			}
			ans.push_back(V2Idx[ch]); 
		}
		Rules.push_back(ans);
		RulesLeft.push_back(V2Idx[str[0]]);		

		int vn = V2Idx[str[0]] ^ VN_MSK;
		VnRules[vn].push_back(i);

	}

	/// �൱�ڵ������
	/*
	printf("VN to code:\n");
	for(int i: VN){
		printf("{%c, %d} ", VN_STR[i^VN_MSK], i^VN_MSK);
	}
	printf("\n\nVT to code:\n");
	for(int i: VT){
		printf("{%c, %d} ", VT_STR[i], i);
	}
	printf("\n\nRules:\n");
	for(int vn: VN){
		for(const auto & ridx: VnRules[vn^VN_MSK]){
            printf("%-6d", ridx);
			printf("%d =", vn);
			for(int v: Rules[ridx]) printf(" %d", v);
			printf("\n");
			printf("%6c%s\n", ' ', RULES_STR[ridx].c_str());
		}
		
	}//*/
}

typedef set<int> si;
vector<si> First;
vector<si> Follow;
/// ����First������Follow����
void calcFirst(){
	First.assign(VN.size()+1, si());
    bool flag;
LFIRST: // ����First����
    flag = false;
	for(int vn: VN){
		vn ^= VN_MSK;
		si & s = First[vn];
		for(int i: VnRules[vn]){
			const vi & rule = Rules[i];
			/// ����ǿչ���
			if(rule.empty()){
				flag = (s.insert(-1)).second || flag;
				continue;
			}
            /// ����ȡ����ķ���
			bool isBreak = false;
			for(int v: rule){
				if(0 == (v & VN_MSK)){ // �ս��
                    flag = (s.insert(v)).second || flag;
					isBreak = true;
					break;
				}
				/// ����˵���Ƿ��ս��
				/// ˵��First���ϻ�û�м����
				if(First[v^VN_MSK].empty()){
					isBreak = true;
					break;
				}

				bool hasEmpty = false;
				for(int ch: First[v^VN_MSK]){
					if(ch != -1) flag = (s.insert(ch)).second || flag;
					else hasEmpty = true;
				}
				if(!hasEmpty) {isBreak=true;break;}
			}
			/// �������break�����ģ�˵���������Ϊ��
			if(!isBreak) flag = (s.insert(-1)).second || flag;
		}
	}
	if(flag) goto LFIRST;

    /// ���
	/*
	printf("\n===== First Set =====\n");
	for(int vn: VN){		
		vn ^= VN_MSK;
		printf("{%c, %d}: ", VN_STR[vn], vn);
		for(int ch: First[vn]){
            printf("{%c, %d} ", VT_STR[ch], ch);
		}
		printf("\n");
	}//*/
}

/// ������Ŵ���First���ϣ����Ŵ�������[s, e)֮��
si calcFirst(vi::const_iterator s, vi::const_iterator e){
    si ans;
    while(s != e){
		int v = *s++;
		if(0 == (v & VN_MSK)){ // ���ս��
            ans.insert(v);
			break;
		}
		bool hasEmpty = false;
		for(int ch: First[v^VN_MSK]){
			if(-1 != ch) ans.insert(ch);
			else hasEmpty = true;
		}
		if(!hasEmpty) break;
	}
	return ans;
}

void calcFollow(){
	Follow.assign(VN.size()+1, si());
	Follow[1].insert(0);
	bool flag;
LFOLLOW:
    flag = false;
	/// ��ÿһ������
	for(int i=1,n=Rules.size();i<n;++i){
		int left = RulesLeft[i] ^ VN_MSK;
		const vi & rule = Rules[i];
		/// �Թ����ұߵ�ÿһ������
		for(auto it=rule.begin(),et=rule.end();it!=et;++it){
			int v = *it;
			if(0 == (v & VN_MSK)) continue;

			si & ans = Follow[v ^ VN_MSK];
			si tmp = calcFirst(it+1, et);
			bool hasEmpty = false;
			for(int ch: tmp){
				if(-1 != ch) flag = (ans.insert(ch)).second || flag;
				else hasEmpty = true;
			}
			/// ��Ҫ��Follow��߼ӽ���
			if(hasEmpty)for(int ch: Follow[left]){
				flag = (ans.insert(ch)).second || flag;
			}
		}
		/// �����ұߵ����һ�����ţ�ֱ�Ӱ�Follow��߼ӽ�ȥ
		if(rule.back() & VN_MSK){
			si & ans = Follow[rule.back() ^ VN_MSK];
			for(int ch: Follow[left]){
				flag = (ans.insert(ch)).second || flag;
			}
		}		
	}
	if(flag) goto LFOLLOW;
    /*
	printf("\n===== Follow Set =====\n");
	for(int vn: VN){		
		vn ^= VN_MSK;
		printf("{%c, %d}: ", VN_STR[vn], vn);
		for(int ch: Follow[vn]){
            printf("{%c, %d} ", VT_STR[ch], ch);
		}
		printf("\n");
	}//*/		
}

/// ��Ŀ������
struct item_t{
    int idx; // ����ı��
	int pos; // ���λ�ã�һ����n+1�ֿ��ܵ�λ��
	bool operator < (const item_t & b)const{
		if(idx != b.idx) return idx < b.idx;
		return pos < b.pos;
	}
};

typedef set<item_t> ItemSetTy;

int const SHIFT = 0x100;
int const REDUC = 0x200;
int const ACCPT = 0x400;

/// ������ű�
vector<vi> LR, GO;
vector<ItemSetTy> Items;
map<ItemSetTy, int> Items2Indx;

/// ����item��չ��Ŀ���淶��
ItemSetTy extend(const item_t & item){
    ItemSetTy ans; ans.insert(item); // item�������ȼӽ�ȥ
	queue<item_t> q; q.push(item);
	while(!q.empty()){
        auto h = q.front(); q.pop();
		/// ȡ��rule
		const vi & rule = Rules[h.idx];
		/// ������λ������������vt�������ô���
		if(h.pos == rule.size() || 0 == (rule[h.pos] & VN_MSK)) continue;
		/// �����Ƿ��ս������Ҫ�������Ŀȫ������
		int vn = rule[h.pos] ^ VN_MSK;
		for(int i: VnRules[vn]){
            item_t nt = {i, 0};
			if(0 == ans.count(nt)){
				ans.insert(nt);
				q.push(nt);
			}
		}
	}
	return ans;
}

string int2string(int n){
	stringstream ss;
	ss<<n;
	return ss.str();
}

/// ����LR���������������ȫ�ֱ�����
void calcLR(){
	/// дһ��С������ʾ���
	auto assign = [](int&a, int b){
		if(a) return false;
        return a = b, true;
	};
	/// ���ȼ�һ����0������
	Rules[0].push_back(VN_MSK|1);
	/// ��ʼ����0����Ŀ���淶��
	Items.push_back(extend({0, 0}));
	Items2Indx.insert({Items[0], 0});
	/// ��0��
	LR.push_back(vi(VT.size(), 0));
	GO.push_back(vi(VN.size()+1, 0));	
	/// ��ʼ���
    for(int i=0;i<Items.size();++i){
		vi & row = LR[i];
		vi & go = GO[i];
		/// ȡ����i����Ŀ���淶��
		const ItemSetTy & items = Items[i];
		map<int, vector<ItemSetTy::const_iterator> > m;
		/// ��ÿ����Ŀ���յ��Եķ��Ž��з���
		for(auto it=items.begin(),et=items.end();it!=et;++it){
			const auto & item = *it;
			/// ˵���ǹ�Լ��Ŀ��ֱ�Ӵ���
			if(item.pos == Rules[item.idx].size()){
                if(0 == item.idx){ // ˵����ACC
                    if(!assign(row[0], ACCPT)){
                        throw runtime_error("row[0] = " + int2string(row[0]));
                    }
				}else{
					/// Follow���ϵ�ÿһ������reduce
					const si & f = Follow[RulesLeft[item.idx]^VN_MSK];
					for(int col: f){
						if(!assign(row[col], REDUC | item.idx)){
                            throw runtime_error("row["+int2string(col)+"] = "+int2string(row[col]));
                        }
					}
				}
			}else{ // ��¼
                m[Rules[item.idx][item.pos]].push_back(it);
			}
		}
		/// �ƶ���Ŀ����ͬ����Ŀ������ͬ�ķ����ƶ�����ͬ����Ŀ
		for(const auto & p: m){
			int symbol = p.first;
			ItemSetTy nts;
			for(auto it: p.second){
				item_t item = *it;
				++item.pos;
				auto tmp = extend(item);
                for(auto t: tmp) nts.insert(t);
			}
			auto it = Items2Indx.find(nts);
			/// ˵����������Ŀ�����ӱ�ţ�LR��GOTO��ҲҪ����
			if(Items2Indx.end() == it){
                it = Items2Indx.insert(it, {nts, Items.size()});
				Items.push_back(nts);		
                LR.push_back(vi(VT.size(), 0));
                GO.push_back(vi(VN.size()+1, 0));		
			}
			/// д�ƽ���goto����ﲻ����ʹ������
            /// ��Ϊǰ���������ݽṹ�����û�ʧЧ
			if(symbol & VN_MSK){ // дgoto��
                GO[i][symbol^VN_MSK] = it->second;
			}else{ // д�ƽ�
			    if(!assign(LR[i][symbol], SHIFT | it->second)){
					throw runtime_error("LR["+int2string(i)+"]["+int2string(symbol)+"] = "+int2string(LR[i][symbol]));
				}
			}			
		}
	}

    /*
	printf("\n\n===== LR TABLE =====\n%-6c", ' ');
	for(int vt: VT){
		printf("%-7c", VT_STR[vt]);
	}
	for(int vn: VN){
        printf("%-7c", VN_STR[vn^VN_MSK]);
	}
	printf("\n");
	for(int i=0;i<LR.size();++i){
		const vi & row = LR[i];
		const vi & go = GO[i];
        printf("%-6d", i);
		for(int a: row){
			if(0 == a){
				printf("%-7c", ' ');
			}else if(a & ACCPT){
				printf("%-6s", "acc");
			}else if(a & SHIFT){
                printf("%c%-6d", 's', a^SHIFT);
			}else if(a & REDUC){
				printf("%c%-6d", 'r', a^REDUC);
			}else{
				throw runtime_error("XX");
			}
		}
		for(int a: go){
			if(a){
				printf("%-7d", a);
			}
		}
		printf("\n");
	}//*/
}

int const JIE = -1;
int N, M;
map<string, int> Dic;

/// �������������ݴ��Եõ���Ӧ���ս��
inline int f(const string&s){
    if('p' == s[0]){
        if('o' == s[2]) return V2Idx['d'];
        if('e' == s[2]) return JIE;
        throw runtime_error("XX");
    }else if('n' == s[0]){
        return V2Idx['m'];
    }else if('a' == s[0]){
        if('j' == s[2]) return V2Idx['x'];
        if('v' == s[2]) return V2Idx['f'];
        if('r' == s[1]) return V2Idx['g'];
        throw runtime_error("YYY");
    }else if('v' == s[0]){
        if(1 == s.length() || (2 == s.length() && '.' == s[1])) return V2Idx['v'];
        if('i' == s[1]) return V2Idx['i'];
        if('t' == s[1]) return V2Idx['t'];
        throw runtime_error("ZZZ");
    }else{
        throw runtime_error("wrong word function.");
    }
}

/// �������ݲ��Ҵ����ֵ�
void readAndDic(){
    cin>>N>>M;
    for(int i=0;i<N;++i){
        string word, type;
        cin>>word>>type;
        /// ȫ���ĳ�Сд��ĸ
        for(int j=0;j<word.length();++j)if(isupper(word[j]))word[j]=tolower(word[j]);
        Dic[word] = f(type);
    }
}

string Input;
vector<int> Tokens;

/// �ʷ���������������ַ���ɨ��ɷ��Ŵ����Թ���ʴ���ͱ�����
/// ���������ȫ������token��
bool lex(){
    /// ��ʼ��
    Tokens.clear();
    string word;
    stringstream ss(Input);
    int pidx = -1, cnt = 0;
    while(ss>>word){
        /// ɾ���ܵı�����
        if(!isalpha(*--word.end())) word.erase(--word.end());
        /// ȫ��Сд
        for(int j=0;j<word.length();++j)if(isupper(word[j]))word[j]=tolower(word[j]);
        int tmp = Dic[word];
        assert(tmp != 0);
        /// ��¼��ʵ�λ��
        if(tmp == JIE) pidx = Tokens.size(), ++cnt;
        Tokens.push_back(tmp);        
    }
    /// û�н�ʾ�ֱ�ӷ���
    if(0 == cnt) return true;
    /// ��ʳ���1��������false����Ŀ˵���ֻ����1��
    if(cnt > 1) return false;
    /// ɾȥ��ʴ��飬��ʴ���ĸ�ʽΪ ��� ���� ��+���ʴ���
    /// ���ʴ���ָ�������߹�����
    /// ���ȿ��Ƿ�Ϊ���
    if(pidx + 1 < Tokens.size() && V2Idx['d'] == Tokens[pidx+1]){
        Tokens.erase(Tokens.begin()+pidx, Tokens.begin()+pidx+2);
        return true;
    }
    /// ���Ƿ�Ϊ������ʴ��飬����Ҫ�ҵ���ʺ���ĵ�һ������
    int midx = pidx + 1;
    while(midx < Tokens.size() && V2Idx['m'] != Tokens[midx]) ++midx;
    if(Tokens.size() == midx) return false; // ˵����ʺ���û������
    /// �����ǽ�������߽�������ĸ�ʽ
    if(midx - pidx > 3) return false; // ���̫Զ
    if(midx - pidx == 1) return false; // ����̫��
    if(midx - pidx == 2 && V2Idx['g'] == Tokens[pidx+1]){
        Tokens.erase(Tokens.begin()+pidx, Tokens.begin()+midx+1);
        return true; // ˵���ǽ�����ĸ�ʽ
    }
    if(midx - pidx == 3 && V2Idx['g'] == Tokens[pidx+1] && V2Idx['x'] == Tokens[pidx+2]){
        Tokens.erase(Tokens.begin()+pidx, Tokens.begin()+midx+1);
        return true; // ˵���ǽ�������ĸ�ʽ
    }
    return false; // ˵��ɶ������
}

/// �﷨���Ľڵ�����
struct node_t{
    int idx; // ���ŵı��
    char ch; // ���ű����������
    node_t *parent; // ָ�򸸽ڵ�
    vector<node_t*> children; // ָ���ӽڵ�
    node_t(int a):idx(a), parent(nullptr){if(idx&VN_MSK)ch=VN_STR[idx^VN_MSK];else ch=VT_STR[idx];}
};

void link(node_t *father, node_t *son){
    father->children.insert(father->children.begin(), son);
    son->parent = father;
}

/// ����﷨��
void outputTree(const node_t * root){
    queue<const node_t*> q;
    q.push(root);
    while(!q.empty()){
        auto h = q.front(); q.pop();
        printf("Node %c: ", h->ch);
        if(h->parent) printf("parent = %c", h->parent->ch);
        else printf("ROOT");
        printf(", sons = (");
        for(auto son: h->children){
            printf("%c, ", son->ch);
            q.push(son);
        }
        printf(")\n");
    }
}

node_t * Root;
vector<vi> Ans;

bool parse(){
	Tokens.push_back(0);
    /// ���﷨����Ūһ���ڵ�ջ
    vector<node_t*> nodeStack;
    /// Ϊ�����׼��
    Ans.assign(1, Tokens);
    /// ׼������ջ������ջ��״̬ջ���ֱ���״̬0��#
    vector<int> symbolStack(1, 0);
    vector<int> statusStack(1, 0);
    int cur = 0;
    while(1){
        /// ״̬ջ��
        int a = statusStack.back();
        int b = Tokens[cur];
        int c = LR[a][b];
        if(c & SHIFT){
            int sn = c ^ SHIFT;
            statusStack.push_back(sn);            
            symbolStack.push_back(Tokens[cur++]);  
            /// �ƽ���ʱ�������һ���ڵ�
            nodeStack.push_back(new node_t(Tokens[cur-1]));          
        }else if(c & REDUC){
            int sn = c ^ REDUC;
            int sz = Rules[sn].size();
            symbolStack.erase(symbolStack.end()-sz, symbolStack.end());
            statusStack.erase(statusStack.end()-sz, statusStack.end());
            symbolStack.push_back(RulesLeft[sn]);
            statusStack.push_back(GO[statusStack.back()][RulesLeft[sn]^VN_MSK]);
            /// ����ջ�Ͷ����е����ݾ��ǵ�ǰ����
            Ans.push_back(symbolStack);
            Ans.back().insert(Ans.back().end(), Tokens.begin()+cur, Tokens.end());
            /// �ڵ�ջջ����sz���ڵ㣬�й�ͬ�ĸ��ڵ㣬���ȴ���һ�����ڵ�
            node_t * father = new node_t(RulesLeft[sn]);
            for(int i=0;i<sz;++i){ // Ȼ������
                link(father, nodeStack.back());
                nodeStack.pop_back();
            }
            nodeStack.push_back(father);
        }else if(c & ACCPT){
            /// ��ʱ�ڵ�ջ��Ӧ��ֻ��һ���ڵ㣬Ϊ�﷨���ĸ�
            assert(1 == nodeStack.size());
            Root = nodeStack.front();
            return true;
        }else{
            return false;
        }
    }
}

bool proc(){
    if(!lex()) return false;
    if(!parse()) return false;
    return true;
}

/// ������ת��Ϊ���������
void output(){
    for(const vi &v: Ans){
        for(int i: v){
            if(i & VN_MSK){
                printf("%c", VN_STR[i^VN_MSK]);
            }else if(i){
                printf("%c", VT_STR[i]);
            }
        }
        printf("\n --> ");
    }
    printf("\n");
}

int main(){
	digitalGrammar();
	calcFirst();
	calcFollow();
	calcLR();
#ifndef ONLINE_JUDGE	
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    /// ���ȶ������ݲ��Ҵ����ֵ�
    readAndDic();
    getline(cin, Input);
    /// �������ÿһ�����Ŵ��������ж�
    for(int i=1;i<=M;++i){
        /// ���ȶ�ȡһ��
        getline(cin, Input);
        /// Ȼ��������
        cout<<(proc()?"YES":"NO")<<endl;
    }
	return 0;
}
