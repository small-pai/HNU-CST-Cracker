/**
 * hdu1237, �������ʽ�ķ����Ӽ��˳����ţ�ʵ������
 * SLR1���죬�Լ�LR�����������﷨��
 */
#include <bits/stdc++.h>
using namespace std;

/// ԭʼ���ݣ���1��Ϊ��ʼ����
const string VN_STR = " ETF";
const vector<string> RULES_STR = {
	"",
	"E=E+T", "E=E-T", "E=T",
	"T=T*F", "T=T/F", "T=F",
	"F=(E)", "F=i"
};

typedef vector<int> vi;

using value_t = double;

/// �ķ����ŵ�����
struct symbol_t{
	int type;  // ���Ǳ��
    value_t value; // ���ԣ������о���ֵ
};

using vsym = vector<symbol_t>;

/// �����ķ��ļ��㺯��
const vector<function<void(symbol_t&, const vsym&)> > AttribFun = {
    nullptr, 
	[](symbol_t&left, const vsym&right){left.value = right[0].value + right[2].value;},
	[](symbol_t&left, const vsym&right){left.value = right[0].value - right[2].value;},
	[](symbol_t&left, const vsym&right){left.value = right[0].value;},
	[](symbol_t&left, const vsym&right){left.value = right[0].value * right[2].value;},
	[](symbol_t&left, const vsym&right){left.value = right[0].value / right[2].value;},
	[](symbol_t&left, const vsym&right){left.value = right[0].value;},
	[](symbol_t&left, const vsym&right){left.value = right[1].value;},
	[](symbol_t&left, const vsym&right){left.value = right[0].value;}
};

const int EPS = -1; // ��
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

#ifdef _OUTDE_
	/// �൱�ڵ������
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
	}
#endif
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
#ifdef _OUTDE_
    /// ���
	printf("\n===== First Set =====\n");
	for(int vn: VN){		
		vn ^= VN_MSK;
		printf("{%c, %d}: ", VN_STR[vn], vn);
		for(int ch: First[vn]){
			if(-1 == ch) printf("{EPS, -1}");
            else printf("{%c, %d} ", VT_STR[ch], ch);
		}
		printf("\n");
	}	
#endif
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
		if(!rule.empty() && (rule.back() & VN_MSK)){
			si & ans = Follow[rule.back() ^ VN_MSK];
			for(int ch: Follow[left]){
				flag = (ans.insert(ch)).second || flag;
			}
		}		
	}
	if(flag) goto LFOLLOW;
#ifdef _OUTDE_
	printf("\n===== Follow Set =====\n");
	for(int vn: VN){		
		vn ^= VN_MSK;
		printf("{%c, %d}: ", VN_STR[vn], vn);
		for(int ch: Follow[vn]){
            printf("{%c, %d} ", VT_STR[ch], ch);
		}
		printf("\n");
	}	
#endif	
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
#ifdef _OUTDE_
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
	}
#endif
}

string Input;
vector<symbol_t> Tokens;

/// �ʷ�����
bool lex(){
    Tokens.clear();
    for(int i=0,n=Input.length();i<n;++i){
		if(isdigit(Input[i])){
			int v = 0;
			while(i<n && isdigit(Input[i])){
				v = v * 10 + (Input[i] - '0');
				++i;
			}
			Tokens.push_back({V2Idx['i'], (value_t)v});	
			--i;		
		}else if('+' == Input[i] || '*' == Input[i]){            
			Tokens.push_back({V2Idx[Input[i]]});
		}else if('-' == Input[i] || '/' == Input[i]){
			Tokens.push_back({V2Idx[Input[i]]});
		}else if('(' == Input[i] || ')' == Input[i]){
            Tokens.push_back({V2Idx[Input[i]]});
		}else if(' ' == Input[i]){
 
		}else{
			return false;
		}	
	}
    return true;
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
symbol_t LastSymbol;

bool parse(){
    ///����һ��#��
    Tokens.push_back({0, 0});
    /// ׼������ջ������ջ��״̬ջ���ֱ���״̬0��#
    vector<symbol_t> symbolStack(1, {0, 0});
    vector<int> statusStack(1, 0);
    int cur = 0;
    while(1){
        /// ״̬ջ��
        int a = statusStack.back();
        int b = Tokens[cur].type;
        int c = LR[a][b];
        if(c & SHIFT){
            int sn = c ^ SHIFT;
            statusStack.push_back(sn);            
            symbolStack.push_back(Tokens[cur++]);  
        }else if(c & REDUC){
            int sn = c ^ REDUC;
            int sz = Rules[sn].size();
			/// ����Լʱ����Ҫʹ�������ķ��ļ��㹫ʽ
			auto f = AttribFun[sn];
            /// ����һ���·���
			symbol_t left = {RulesLeft[sn], 0};		
			/// Ӧ�ù�ʽ���м���
			f(left, vsym(symbolStack.end()-sz, symbolStack.end()));				
			/// ��ջ
            symbolStack.erase(symbolStack.end()-sz, symbolStack.end());
            statusStack.erase(statusStack.end()-sz, statusStack.end());
			/// ��ջ
            symbolStack.push_back(left);
            statusStack.push_back(GO[statusStack.back()][RulesLeft[sn]^VN_MSK]);
        }else if(c & ACCPT){
			/// ��ȫ�ֱ���������
			LastSymbol = symbolStack[1];
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

int main(){
	digitalGrammar();
	calcFirst();
	calcFollow();
	calcLR();
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    while(getline(cin, Input)){
        if("0" == Input) break;
        assert(proc());
		printf("%.2lf\n", LastSymbol.value);
    }
	return 0;
}
