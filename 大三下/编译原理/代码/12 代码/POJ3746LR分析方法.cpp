/**
 * POJ3746，LR分析 
 */
#include <assert.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

/// 非终结符的数量
int const VNSIZE = 3;
int const VTSIZE = 9;

/// 定义终结符
int const VT_j = 0;
int const VT_m = 1; // 名词
int const VT_d = 2; // 动词
int const VT_x = 3; // 形容词
int const VT_i = 4; // 不及物动词
int const VT_t = 5; // 及物动词 
int const VT_v = 6; // 普通动词
int const VT_g = 7; // 冠词
int const VT_f = 8; // 副词
int const EPSI = 9; // 空
int const JIE = 10; // 介词


/// 非终结符的二进制位掩码
int const VN_MSK = 0x100;

/// 非终结符
int const VN_S = 1 | VN_MSK; // 句子
int const VN_W = 2 | VN_MSK; // 主语或者宾语
int const VN_Z = 3 | VN_MSK; // 谓语

/// 一共12条规则
const int RawRules[][7] = {
    {},
    {VN_S, VN_Z, VN_W},
    {VN_W, VT_i},
	{VN_W, VT_t, VN_Z},
	{VN_W, VT_v},
	{VN_W, VT_v, VN_Z},
	{VN_W, VT_f, VT_i},
	{VN_W, VT_f, VT_t, VN_Z},
	{VN_W, VT_f, VT_v},
	{VN_W, VT_f, VT_v, VN_Z},
	{VN_Z, VT_d},
	{VN_Z, VT_g, VT_m},
	{VN_Z, VT_g, VT_x, VT_m}
};
int const RuleLen[] = {
    0, 2, 1, 2, 1, 2, 2, 3, 2, 3, 1, 2, 3
};

int const SHIFT = 0x100;
int const REDUC = 0x200;
int const ACCPT = 0x400;
int const ACC = ACCPT;

#define r(x) (REDUC|(x))
#define s(x) (SHIFT|(x))

const int LR[][VTSIZE] = {
///  #      m     d     x   i      t     v      g    f
    {0,     0,    s(3), 0,  0,     0,    0,     s(4)},
    {ACC},
	{0,     0,    0,    0, s(6),  s(7),  s(8),  0, s(9)},
	{r(10), 0,    0,    0, r(10), r(10), r(10), 0, r(10)},
    {0,     s(10),0,    s(11)},
	{r(1)},
	{r(2)},
	{0,     0,    s(3), 0,  0,     0,     0,    s(4)},
	{r(4),  0,    s(3), 0,  0,     0,     0,    s(4)},
	{0,     0,    0,    0,  s(14), s(16), s(16)},
	{r(11), 0,    0,    0,  r(11), r(11), r(11)},
	{0,   s(17)},
	{r(3)},
	{r(5)},
	{r(6)},
	{0,     0,    s(3), 0,  0,     0,     0,    s(4)},
	{r(8),  0,    s(3), 0,  0,     0,     0,    s(4)},	
	{r(12), 0,    0,    0,  r(12), r(12), r(12)},	
	{r(7)},
	{r(9)}
};

const int GO[][VNSIZE+1] = {
	{0, 1, 0, 2},
	{0},
	{0, 0, 5},
	{0},
	{0},
	{0},
	{0},
	{0, 0, 0, 12},
	{0, 0, 0, 14},
	{0},
	{0},
	{0},
	{0},   
	{0},
	{0}, 
	{0, 0, 0, 18},
	{0, 0, 0, 19},
	{0},
	{0},
	{0}	
};

int N, M;
map<string, int> Dic;

/// 辅助函数，根据词性得到相应的终结符
inline int f(const string&s){
    if('p' == s[0]){
        if('o' == s[2]) return VT_d;
        if('e' == s[2]) return JIE;
        throw runtime_error("XX");
    }else if('n' == s[0]){
        return VT_m;
    }else if('a' == s[0]){
        if('j' == s[2]) return VT_x;
        if('v' == s[2]) return VT_f;
        if('r' == s[1]) return VT_g;
        throw runtime_error("YYY");
    }else if('v' == s[0]){
        if(1 == s.length() || (2 == s.length() && '.' == s[1])) return VT_v;
        if('i' == s[1]) return VT_i;
        if('t' == s[1]) return VT_t;
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
vector<int> Token;

/// 词法分析，将输入的字符串扫描成符号串，略过介词词组和标点符号
/// 结果保存在全局数组token中
bool lex(){
    /// 初始化
    Token.clear();
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
        if(tmp == JIE) pidx = Token.size(), ++cnt;
        Token.push_back(tmp);        
    }
    /// 没有介词就直接返回
    if(0 == cnt) return true;
    /// 介词超过1个，返回false，题目说最多只允许1个
    if(cnt > 1) return false;
    /// 删去介词词组，介词词组的格式为 介代 或者 介+名词词组
    /// 名词词组指冠名或者冠形名
    /// 首先看是否为介代
    if(pidx + 1 < Token.size() && VT_d == Token[pidx+1]){
        Token.erase(Token.begin()+pidx, Token.begin()+pidx+2);
        return true;
    }
    /// 看是否为介加名词词组，首先要找到介词后面的第一个名词
    int midx = pidx + 1;
    while(midx < Token.size() && VT_m != Token[midx]) ++midx;
    if(Token.size() == midx) return false; // 说明介词后面没有名词
    /// 必须是介冠名或者介冠形名的格式
    if(midx - pidx > 3) return false; // 相隔太远
    if(midx - pidx == 1) return false; // 隔得太近
    if(midx - pidx == 2 && VT_g == Token[pidx+1]){
        Token.erase(Token.begin()+pidx, Token.begin()+midx+1);
        return true; // 说明是介冠名的格式
    }
    if(midx - pidx == 3 && VT_g == Token[pidx+1] && VT_x == Token[pidx+2]){
        Token.erase(Token.begin()+pidx, Token.begin()+midx+1);
        return true; // 说明是介冠形名的格式
    }
    return false; // 说明啥都不是
}

typedef vector<int> vi;
/// 使用LR分析法分析单词序列
bool parse(){
	Token.push_back(VT_j);
    /// 准备两个栈，符号栈和状态栈，分别是状态0和#
    vector<int> symbolStack(1, VT_j);
    vector<int> statusStack(1, 0);
    int cur = 0;
    while(1){
        /// 状态栈顶
        int a = statusStack.back();
        int b = Token[cur];
        int c = LR[a][b];
        if(c & SHIFT){
            int sn = c ^ SHIFT;
            statusStack.push_back(sn);
            symbolStack.push_back(Token[cur++]);
        }else if(c & REDUC){
            int sn = c ^ REDUC;
            int sz = RuleLen[sn];
            symbolStack.erase(symbolStack.end()-sz, symbolStack.end());
            statusStack.erase(statusStack.end()-sz, statusStack.end());
            symbolStack.push_back(RawRules[sn][0]);
            statusStack.push_back(GO[statusStack.back()][RawRules[sn][0]^VN_MSK]);
        }else if(c & ACCPT){
            return true;
        }else{
            return false;
        }
    }
}

bool proc(){
    /// 首先做词法分析
    if(!lex()) return false;
    /// 然后做语法分析
    if(!parse()) return false;
    return true;
}

int main(){
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

