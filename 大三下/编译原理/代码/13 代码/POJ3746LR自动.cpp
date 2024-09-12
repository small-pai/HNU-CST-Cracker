/// POJ不支持C++11，样例了就当过了
#include <bits/stdc++.h>
using namespace std;

/// 原始数据，第1个为开始符号
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

	/// 相当于调试输出
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

    /// 输出
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

/// 辅助函数，根据词性得到相应的终结符
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

/// 读入数据并且创建字典
void readAndDic(){
    cin>>N>>M;
    for(int i=0;i<N;++i){
        string word, type;
        cin>>word>>type;
        /// 全部改成小写字母
        for(int j=0;j<word.length();++j)if(isupper(word[j]))word[j]=tolower(word[j]);
        Dic[word] = f(type);
    }
}

string Input;
vector<int> Tokens;

/// 词法分析，将输入的字符串扫描成符号串，略过介词词组和标点符号
/// 结果保存在全局数组token中
bool lex(){
    /// 初始化
    Tokens.clear();
    string word;
    stringstream ss(Input);
    int pidx = -1, cnt = 0;
    while(ss>>word){
        /// 删可能的标点符号
        if(!isalpha(*--word.end())) word.erase(--word.end());
        /// 全部小写
        for(int j=0;j<word.length();++j)if(isupper(word[j]))word[j]=tolower(word[j]);
        int tmp = Dic[word];
        assert(tmp != 0);
        /// 记录介词的位置
        if(tmp == JIE) pidx = Tokens.size(), ++cnt;
        Tokens.push_back(tmp);        
    }
    /// 没有介词就直接返回
    if(0 == cnt) return true;
    /// 介词超过1个，返回false，题目说最多只允许1个
    if(cnt > 1) return false;
    /// 删去介词词组，介词词组的格式为 介代 或者 介+名词词组
    /// 名词词组指冠名或者冠形名
    /// 首先看是否为介代
    if(pidx + 1 < Tokens.size() && V2Idx['d'] == Tokens[pidx+1]){
        Tokens.erase(Tokens.begin()+pidx, Tokens.begin()+pidx+2);
        return true;
    }
    /// 看是否为介加名词词组，首先要找到介词后面的第一个名词
    int midx = pidx + 1;
    while(midx < Tokens.size() && V2Idx['m'] != Tokens[midx]) ++midx;
    if(Tokens.size() == midx) return false; // 说明介词后面没有名词
    /// 必须是介冠名或者介冠形名的格式
    if(midx - pidx > 3) return false; // 相隔太远
    if(midx - pidx == 1) return false; // 隔得太近
    if(midx - pidx == 2 && V2Idx['g'] == Tokens[pidx+1]){
        Tokens.erase(Tokens.begin()+pidx, Tokens.begin()+midx+1);
        return true; // 说明是介冠名的格式
    }
    if(midx - pidx == 3 && V2Idx['g'] == Tokens[pidx+1] && V2Idx['x'] == Tokens[pidx+2]){
        Tokens.erase(Tokens.begin()+pidx, Tokens.begin()+midx+1);
        return true; // 说明是介冠形名的格式
    }
    return false; // 说明啥都不是
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
vector<vi> Ans;

bool parse(){
	Tokens.push_back(0);
    /// 造语法树，弄一个节点栈
    vector<node_t*> nodeStack;
    /// 为输出做准备
    Ans.assign(1, Tokens);
    /// 准备两个栈，符号栈和状态栈，分别是状态0和#
    vector<int> symbolStack(1, 0);
    vector<int> statusStack(1, 0);
    int cur = 0;
    while(1){
        /// 状态栈顶
        int a = statusStack.back();
        int b = Tokens[cur];
        int c = LR[a][b];
        if(c & SHIFT){
            int sn = c ^ SHIFT;
            statusStack.push_back(sn);            
            symbolStack.push_back(Tokens[cur++]);  
            /// 移进的时候就新造一个节点
            nodeStack.push_back(new node_t(Tokens[cur-1]));          
        }else if(c & REDUC){
            int sn = c ^ REDUC;
            int sz = Rules[sn].size();
            symbolStack.erase(symbolStack.end()-sz, symbolStack.end());
            statusStack.erase(statusStack.end()-sz, statusStack.end());
            symbolStack.push_back(RulesLeft[sn]);
            statusStack.push_back(GO[statusStack.back()][RulesLeft[sn]^VN_MSK]);
            /// 符号栈和队列中的内容就是当前句型
            Ans.push_back(symbolStack);
            Ans.back().insert(Ans.back().end(), Tokens.begin()+cur, Tokens.end());
            /// 节点栈栈顶的sz个节点，有共同的父节点，首先创建一个父节点
            node_t * father = new node_t(RulesLeft[sn]);
            for(int i=0;i<sz;++i){ // 然后连接
                link(father, nodeStack.back());
                nodeStack.pop_back();
            }
            nodeStack.push_back(father);
        }else if(c & ACCPT){
            /// 此时节点栈里应该只有一个节点，为语法树的根
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

/// 将编码转换为符号再输出
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
    /// 首先读入数据并且创建字典
    readAndDic();
    getline(cin, Input);
    /// 对输入的每一个符号串，进行判断
    for(int i=1;i<=M;++i){
        /// 首先读取一行
        getline(cin, Input);
        /// 然后做分析
        cout<<(proc()?"YES":"NO")<<endl;
    }
	return 0;
}
