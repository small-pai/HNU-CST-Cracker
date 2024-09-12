/**
 * POJ3746��LL1�ķ�
*/
#include <assert.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

/// ���ս��������
int const VNSIZE = 6;
int const VTSIZE = 9;

/// �����ս��
int const VT_j = 0;
int const VT_m = 1; // ����
int const VT_d = 2; // ����
int const VT_x = 3; // ���ݴ�
int const VT_i = 4; // �����ﶯ��
int const VT_t = 5; // ���ﶯ�� 
int const VT_v = 6; // ��ͨ����
int const VT_g = 7; // �ڴ�
int const VT_f = 8; // ����
int const EPSI = 9; // ��
int const JIE = 10; // ���


/// ���ս���Ķ�����λ����
int const VN = 0x100;

/// ���ս��
int const VN_S = 1 | VN; // ����
int const VN_W = 2 | VN; // ������߱���
int const VN_Z = 3 | VN; // ν��
int const VN_M = 4 | VN; // ������ν����߶����ṹ
int const VN_U = 5 | VN; // ���ʴ���
int const VN_V = 6 | VN; // ����


/// һ��12������
const int RawRules[][3] = {
    {},
    {VN_Z, VN_W}, // 1
    {VN_U},       // 2
    {VT_f, VN_U}, // 3
    {VT_d},       // 4
    {VT_g, VN_M}, // 5
    {VT_m},       // 6
    {VT_x, VT_m}, // 7
    {VT_i},       // 8
    {VT_t, VN_Z}, // 9
    {VT_v, VN_V}, // 10
    {},           // 11�� �չ��� 
    {VN_Z}        // 12
};
int const RuleLen[] = {
    0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 0, 1
};

const int TABLE[][VTSIZE] = {
    {},
    {0, 0, 1, 0, 0, 0, 0, 1},    // S
    {0, 0, 0, 0, 2, 2, 2, 0, 3}, // W
    {0, 0, 4, 0, 0, 0, 0, 5},    // Z
    {0, 6, 0, 7},                // M
    {0, 0, 0, 0, 8, 9,10, 0},    // U
    {11,0,12, 0, 0, 0, 0,12}     // V
};

int N, M;
map<string, int> Dic;

/// �������������ݴ��Եõ���Ӧ���ս��
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
vector<int> Token;

/// �ʷ���������������ַ���ɨ��ɷ��Ŵ����Թ���ʴ���ͱ�����
/// ���������ȫ������token��
bool lex(){
    /// ��ʼ��
    Token.clear();
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
        if(tmp == JIE) pidx = Token.size(), ++cnt;
        Token.push_back(tmp);        
    }
    /// û�н�ʾ�ֱ�ӷ���
    if(0 == cnt) return true;
    /// ��ʳ���1��������false����Ŀ˵���ֻ����1��
    if(cnt > 1) return false;
    /// ɾȥ��ʴ��飬��ʴ���ĸ�ʽΪ ��� ���� ��+���ʴ���
    /// ���ʴ���ָ�������߹�����
    /// ���ȿ��Ƿ�Ϊ���
    if(pidx + 1 < Token.size() && VT_d == Token[pidx+1]){
        Token.erase(Token.begin()+pidx, Token.begin()+pidx+2);
        return true;
    }
    /// ���Ƿ�Ϊ������ʴ��飬����Ҫ�ҵ���ʺ���ĵ�һ������
    int midx = pidx + 1;
    while(midx < Token.size() && VT_m != Token[midx]) ++midx;
    if(Token.size() == midx) return false; // ˵����ʺ���û������
    /// �����ǽ�������߽�������ĸ�ʽ
    if(midx - pidx > 3) return false; // ���̫Զ
    if(midx - pidx == 1) return false; // ����̫��
    if(midx - pidx == 2 && VT_g == Token[pidx+1]){
        Token.erase(Token.begin()+pidx, Token.begin()+midx+1);
        return true; // ˵���ǽ�����ĸ�ʽ
    }
    if(midx - pidx == 3 && VT_g == Token[pidx+1] && VT_x == Token[pidx+2]){
        Token.erase(Token.begin()+pidx, Token.begin()+midx+1);
        return true; // ˵���ǽ�������ĸ�ʽ
    }
    return false; // ˵��ɶ������
}

/// ʹ��Ԥ�������������������
bool parse(){
    /// ׼��һ��ջ��Ūһ��#��Ūһ����ʼ����
    vector<int> st(1, VT_j);
    st.push_back(VN_S);
    /// ������������һ��#
    Token.push_back(VT_j);
    int cur = 0;
    while(1){
        if(st.back() == Token[cur]){
            if(VT_j == Token[cur]) return true;
            st.pop_back(); ++cur;
        }else if(st.back() & VN){ // ˵���Ƿ��ս��
            int vn = st.back() ^ VN;
            int t = TABLE[vn][Token[cur]]; // ���
            if(0 == t) return false;
            /// ��t�����򣬷�����ջ
            st.pop_back();
            for(int i=RuleLen[t]-1;i>=0;--i){
                st.push_back(RawRules[t][i]);
            }
        }else{
            return false;
        } 
    }
    /// never here
    return false;
}

bool proc(){
    /// �������ʷ�����
    if(!lex()) return false;
    /// Ȼ�����﷨����
    if(!parse()) return false;
    return true;
}

int main(){
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

