/**
 * POJ3746��LL1�ķ����ݹ��½���
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

/// ʹ�õݹ��½���������������
bool dfsS();
bool dfsW();
bool dfsZ();
bool dfsM();
bool dfsU();
bool dfsV();
bool match(int);
int Cur;
bool parse(){
    /// ������������һ��#
    Token.push_back(VT_j);
    Cur = 0;
    bool b = dfsS();
    return b && VT_j == Token[Cur];
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

bool match(int vt){
    if(vt == Token[Cur]) return ++Cur, true;
    return false;
}

bool dfsS(){
    int const & t = Token[Cur];
    if(VT_d == t || VT_g == t){
        if(!dfsZ()) return false;
        if(!dfsW()) return false;
        return true;
    }
    return false;
}

bool dfsW(){
    int const & t = Token[Cur];
    if(VT_i == t || VT_t == t || VT_v == t){
        if(!dfsU()) return false;
        return true;
    }
    if(VT_f == t){
        if(!match(VT_f)) return false;
        if(!dfsU()) return false;
        return true;
    }
    return false;
}

bool dfsZ(){
    int const & t = Token[Cur];
    if(VT_d == t){
        if(!match(VT_d)) return false;
        return true;
    }
    if(VT_g == t){
        if(!match(VT_g)) return false;
        if(!dfsM()) return false;
        return true;
    }
    return false;
}

bool dfsM(){
    int const & t = Token[Cur];
    if(VT_m == t){
        if(!match(VT_m)) return false;
        return true;
    }
    if(VT_x == t){
        if(!match(VT_x)) return false;
        if(!match(VT_m)) return false;
        return true;
    }
    return false;
}

bool dfsU(){
    int const & t = Token[Cur];
    if(VT_i == t){
        if(!match(VT_i)) return false;
        return true;
    }
    if(VT_t == t){
        if(!match(VT_t)) return false;
        if(!dfsZ()) return false;
        return true;
    }
    if(VT_v == t){
        if(!match(VT_v)) return false;
        if(!dfsV()) return false;
        return true;
    }
    return false;
}

bool dfsV(){
    int const & t = Token[Cur];
    if(VT_j == t){
        return true;
    }
    if(VT_d == t || VT_g == t){
        if(!dfsZ()) return false;
        return true;
    }
    return false;
}