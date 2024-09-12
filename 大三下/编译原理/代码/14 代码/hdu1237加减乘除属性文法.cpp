/**
 * hdu1237, 算术表达式文法，加减乘除括号，实数运算
 * SLR1构造，以及LR分析，构造语法树
 */
#include <bits/stdc++.h>
using namespace std;

/// 原始数据，第1个为开始符号
const string VN_STR = " ETF";
const vector<string> RULES_STR = {
	"",
	"E=E+T", "E=E-T", "E=T",
	"T=T*F", "T=T/F", "T=F",
	"F=(E)", "F=i"
};

typedef vector<int> vi;

using value_t = double;

/// 文法符号的类型
struct symbol_t{
	int type;  // 就是编号
    value_t value; // 属性，本例中就是值
};

using vsym = vector<symbol_t>;

/// 属性文法的计算函数
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

const int EPS = -1; // 空
const int VN_MSK = 0x100;
string VT_STR = "#";
int V2Idx[256];

/// 保存VN和VT的编号
vi VN, VT(1, 0); 
/// 数字化的规则，Rules[i]就是第i条规则
vi RulesLeft;
vector<vi> Rules;
/// 按vn存取的规则的编号, VnRules[i][j]表示非终结符i的第j条规则的序号
vector<vi> VnRules(VN_STR.size()+1);

/// 数字化Grammar，即把字符串转为整数
/// 其中Vt按1、2、3排序，#编号为0
/// Vn中0x101开始往后编号
void digitalGrammar(){
	/// 先确定VN的编号
	for(int i=1;i<VN_STR.length();++i) VN.push_back(V2Idx[VN_STR[i]] = i | VN_MSK);
	/// 再确定Vt的编号并且把规则变为整数序列
	Rules.push_back(vi()); // 第0条规则不用
	RulesLeft.push_back(0);
	for(int i=1;i<RULES_STR.size();++i){
		const string & str = RULES_STR[i]; // 第i条规则
		vi ans; // 数字化的第i条规则
        for(char ch: str.substr(2)){
			if(0 == V2Idx[ch]){ // 肯定是尚未编号的终结符
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
	/// 相当于调试输出
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
/// 计算First集合与Follow集合
void calcFirst(){
	First.assign(VN.size()+1, si());
    bool flag;
LFIRST: // 计算First集合
    flag = false;
	for(int vn: VN){
		vn ^= VN_MSK;
		si & s = First[vn];
		for(int i: VnRules[vn]){
			const vi & rule = Rules[i];
			/// 如果是空规则
			if(rule.empty()){
				flag = (s.insert(-1)).second || flag;
				continue;
			}
            /// 依次取规则的符号
			bool isBreak = false;
			for(int v: rule){
				if(0 == (v & VN_MSK)){ // 终结符
                    flag = (s.insert(v)).second || flag;
					isBreak = true;
					break;
				}
				/// 到此说明是非终结符
				/// 说明First集合还没有计算过
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
			/// 如果不是break出来的，说明整体可以为空
			if(!isBreak) flag = (s.insert(-1)).second || flag;
		}
	}
	if(flag) goto LFIRST;
#ifdef _OUTDE_
    /// 输出
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

/// 计算符号串的First集合，符号串内容在[s, e)之间
si calcFirst(vi::const_iterator s, vi::const_iterator e){
    si ans;
    while(s != e){
		int v = *s++;
		if(0 == (v & VN_MSK)){ // 非终结符
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
	/// 对每一条规则
	for(int i=1,n=Rules.size();i<n;++i){
		int left = RulesLeft[i] ^ VN_MSK;
		const vi & rule = Rules[i];
		/// 对规则右边的每一个符号
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
			/// 还要将Follow左边加进来
			if(hasEmpty)for(int ch: Follow[left]){
				flag = (ans.insert(ch)).second || flag;
			}
		}
		/// 对于右边的最后一个符号，直接把Follow左边加进去
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

/// 项目的类型
struct item_t{
    int idx; // 规则的编号
	int pos; // 点的位置，一共有n+1种可能的位置
	bool operator < (const item_t & b)const{
		if(idx != b.idx) return idx < b.idx;
		return pos < b.pos;
	}
};

typedef set<item_t> ItemSetTy;

int const SHIFT = 0x100;
int const REDUC = 0x200;
int const ACCPT = 0x400;

/// 拆成两张表
vector<vi> LR, GO;
vector<ItemSetTy> Items;
map<ItemSetTy, int> Items2Indx;

/// 根据item扩展项目集规范族
ItemSetTy extend(const item_t & item){
    ItemSetTy ans; ans.insert(item); // item本身首先加进去
	queue<item_t> q; q.push(item);
	while(!q.empty()){
        auto h = q.front(); q.pop();
		/// 取出rule
		const vi & rule = Rules[h.idx];
		/// 如果点的位置在最后或者是vt，都不用处理
		if(h.pos == rule.size() || 0 == (rule[h.pos] & VN_MSK)) continue;
		/// 表明是非终结符，需要把相关项目全部加入
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

/// 计算LR分析表，结果保存在全局变量中
void calcLR(){
	/// 写一个小函数表示填表
	auto assign = [](int&a, int b){
		if(a) return false;
        return a = b, true;
	};
	/// 首先加一个第0条规则
	Rules[0].push_back(VN_MSK|1);
	/// 初始化第0个项目集规范族
	Items.push_back(extend({0, 0}));
	Items2Indx.insert({Items[0], 0});
	/// 第0行
	LR.push_back(vi(VT.size(), 0));
	GO.push_back(vi(VN.size()+1, 0));	
	/// 开始造表
    for(int i=0;i<Items.size();++i){
		vi & row = LR[i];
		vi & go = GO[i];
		/// 取出第i个项目集规范族
		const ItemSetTy & items = Items[i];
		map<int, vector<ItemSetTy::const_iterator> > m;
		/// 将每个项目按照点旁的符号进行分类
		for(auto it=items.begin(),et=items.end();it!=et;++it){
			const auto & item = *it;
			/// 说明是归约项目，直接处理
			if(item.pos == Rules[item.idx].size()){
                if(0 == item.idx){ // 说明是ACC
                    if(!assign(row[0], ACCPT)){
                        throw runtime_error("row[0] = " + int2string(row[0]));
                    }
				}else{
					/// Follow集合的每一个填上reduce
					const si & f = Follow[RulesLeft[item.idx]^VN_MSK];
					for(int col: f){
						if(!assign(row[col], REDUC | item.idx)){
                            throw runtime_error("row["+int2string(col)+"] = "+int2string(row[col]));
                        }
					}
				}
			}else{ // 记录
                m[Rules[item.idx][item.pos]].push_back(it);
			}
		}
		/// 移动项目，相同的项目经过相同的符号移动到相同的项目
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
			/// 说明这是新项目集，加编号，LR和GOTO表也要加行
			if(Items2Indx.end() == it){
                it = Items2Indx.insert(it, {nts, Items.size()});
				Items.push_back(nts);		
                LR.push_back(vi(VT.size(), 0));
                GO.push_back(vi(VN.size()+1, 0));		
			}
			/// 写移进和goto项，这里不能再使用引用
            /// 因为前更改了数据结构，引用会失效
			if(symbol & VN_MSK){ // 写goto表
                GO[i][symbol^VN_MSK] = it->second;
			}else{ // 写移进
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

/// 词法分析
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

/// 语法树的节点类型
struct node_t{
    int idx; // 符号的编号
    char ch; // 符号本身，用于输出
    node_t *parent; // 指向父节点
    vector<node_t*> children; // 指向子节点
    node_t(int a):idx(a), parent(nullptr){if(idx&VN_MSK)ch=VN_STR[idx^VN_MSK];else ch=VT_STR[idx];}
};

void link(node_t *father, node_t *son){
    father->children.insert(father->children.begin(), son);
    son->parent = father;
}

/// 输出语法树
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
    ///最后加一个#号
    Tokens.push_back({0, 0});
    /// 准备两个栈，符号栈和状态栈，分别是状态0和#
    vector<symbol_t> symbolStack(1, {0, 0});
    vector<int> statusStack(1, 0);
    int cur = 0;
    while(1){
        /// 状态栈顶
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
			/// 当归约时，需要使用属性文法的计算公式
			auto f = AttribFun[sn];
            /// 创建一个新符号
			symbol_t left = {RulesLeft[sn], 0};		
			/// 应用公式进行计算
			f(left, vsym(symbolStack.end()-sz, symbolStack.end()));				
			/// 出栈
            symbolStack.erase(symbolStack.end()-sz, symbolStack.end());
            statusStack.erase(statusStack.end()-sz, statusStack.end());
			/// 进栈
            symbolStack.push_back(left);
            statusStack.push_back(GO[statusStack.back()][RulesLeft[sn]^VN_MSK]);
        }else if(c & ACCPT){
			/// 用全局变量带出答案
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
