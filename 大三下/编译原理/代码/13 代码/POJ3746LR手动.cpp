//基于语法的形式规则，LR算法
#include <cstdio>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

//Just as its name
int const SIZE_OF_TRIE = 500000;//TODO
//The count of all valid letters
int const ALPHA_SIZE = 26;//TODO
//The map from letters to ints
int L2I[256];
//To initialize L2I array, don't forget calling it!!!
void initL2I(){//不区分大小写
    for(int i=0;i<26;++i) L2I[i+'a'] = L2I[i+'A'] = i;
}
//The transition matrix of DFA
int Trie[SIZE_OF_TRIE][ALPHA_SIZE];
int Flag[SIZE_OF_TRIE];
int SCnt;

int StartState;
int ErrorState;

//to new a state
inline int _newState(){
    fill(Trie[SCnt],Trie[SCnt]+ALPHA_SIZE,0);
    Flag[SCnt] = 0;
    return SCnt++;
}

//run DFA by a string
int _run(char const word[]){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        state = Trie[state][sn];
        if ( ErrorState == state ) return ErrorState;
    }
    return state;
}

//to insert a string into Trie
void insert(char const word[],int idx=1){
    int state = StartState;
    for(char const*p=word;*p;++p){
        int sn = L2I[(int)*p];
        if ( 0 == Trie[state][sn] ) Trie[state][sn] = _newState();
        state = Trie[state][sn];
    }
    Flag[state] = idx;
}

//to find whether a given string exists in Trie
int find(char const word[]){
    return Flag[_run(word)];
}

void initTrie(){
    SCnt = 0;
    ErrorState = _newState();
    StartState = _newState();
}

int const SHIFT = 0x100;
int const REDUCE = 0x200;
int const ACCEPT = 0x400;

inline int _shift(int n){return SHIFT|n;}
inline int _reduce(int n){return REDUCE|n;}

int const ERR = 0;
int const ACC = ACCEPT;
int const S01 = _shift(1);
int const S02 = _shift(2);
int const S03 = _shift(3);
int const S04 = _shift(4);
int const S05 = _shift(5);
int const S06 = _shift(6);
int const S07 = _shift(7);
int const S08 = _shift(8);
int const S09 = _shift(9);
int const S10 = _shift(10);
int const S11 = _shift(11);
int const S12 = _shift(12);
int const S13 = _shift(13);
int const S14 = _shift(14);
int const S15 = _shift(15);
int const S16 = _shift(16);
int const S17 = _shift(17);
int const S18 = _shift(18);

int const R01 = _reduce(1);
int const R02 = _reduce(2);
int const R03 = _reduce(3);
int const R04 = _reduce(4);
int const R05 = _reduce(5);
int const R06 = _reduce(6);
int const R07 = _reduce(7);
int const R08 = _reduce(8);
int const R09 = _reduce(9);
int const R10 = _reduce(10);
int const R11 = _reduce(11);

int const JING = 0;
int const NOUN = 1;//名
int const VI = 2;//不及物动词
int const VT = 3;//及物动词
int const ADJ = 4;//形容词
int const PRON = 5;//代词
int const ADV = 6;//副词
int const ART = 7;//冠词
int const VERB = 8;//动词
int const PREP = 9;//介词
int const Vn_S = 9;//S
int const Vn_Z = 10;//主语或者宾语

//一共有11条语法规则
int const RULES[12][10] = {
/*0*/{0},
/*1*/{Vn_S,Vn_Z,VI},
/*2*/{Vn_S,Vn_Z,ADV,VI},
/*3*/{Vn_S,Vn_Z,VT,Vn_Z},
/*4*/{Vn_S,Vn_Z,ADV,VT,Vn_Z},
/*5*/{Vn_Z,PRON},
/*6*/{Vn_Z,ART,NOUN},
/*7*/{Vn_Z,ART,ADJ,NOUN},
/*8*/{Vn_S,Vn_Z,VERB},
/*9*/{Vn_S,Vn_Z,ADV,VERB},
/*10*/{Vn_S,Vn_Z,VERB,Vn_Z},
/*11*/{Vn_S,Vn_Z,ADV,VERB,Vn_Z}
};
int const RL[12] = {0,2,3,3,4,1,2,3,2,3,3,4};

int const TABLE[][11] = {
//    #   名  不  及  形  代  副  冠  动  S Z
/*0*/{ERR,ERR,ERR,ERR,ERR,S03,ERR,S04,ERR,1,2},
/*1*/{ACC},
/*2*/{ERR,ERR,S05,S06,ERR,ERR,S07,ERR,S15},
/*3*/{R05,ERR,R05,R05,ERR,ERR,R05,ERR,R05},
/*4*/{ERR,S08,ERR,ERR,S09},
/*5*/{R01},
/*6*/{ERR,ERR,ERR,ERR,ERR,S03,ERR,S04,ERR,0,10},
/*7*/{ERR,ERR,S11,S12,ERR,ERR,ERR,ERR,S15},
/*8*/{R06,ERR,R06,R06,ERR,ERR,R06,ERR,R06},
/*9*/{ERR,S13},
/*10*/{R03},
/*11*/{R02},
/*12*/{ERR,ERR,ERR,ERR,ERR,S03,ERR,S04,ERR,0,14},
/*13*/{R07,ERR,R07,R07,ERR,ERR,R07,ERR,R07},
/*14*/{R04},
/*15*/{R08,ERR,ERR,ERR,ERR,S03,ERR,S04,ERR,0,17},
/*16*/{R09,ERR,ERR,ERR,ERR,S03,ERR,S04,ERR,0,18},
/*17*/{R10},
/*18*/{R11}
};

inline int _g(char const a[]){
    switch( a[0] ){
        case 'n':return NOUN;
        case 'v':if ( '.' == a[1] )return VERB;
            if ( 'i' == a[1] ) return VI;
            return VT;
        case 'a': if ( 'r' == a[1] ) return ART;
            if ( 'j' == a[2] ) return ADJ;
            return ADV;
        case 'p': if ( 'o' == a[2] ) return PRON;
            return PREP;
    }
}

int N,M;
char A[1000],B[1000];
void read(){
    scanf("%d%d",&N,&M);

    initTrie();
    //不区分大小写
    for(int i=0;i<N;++i){
        scanf("%s%s",A,B);
        insert(A,_g(B));
    }
    return;
}

typedef vector<int>::iterator vit;
//判断介词
bool doPrep(vector<int>& tokens){
    vit pit;
    int cnt = 0;
    for(vit it=tokens.begin();it!=tokens.end();++it){
        if ( PREP == *it ) ++cnt,pit = it;
    }

    if ( cnt > 1 ) return false;
    if ( 0 == cnt ) return true;
    //介词后面必须接代词，或者冠名，或者冠形名
    vit tt = pit + 1;
    //如果是介词，OK
    if ( PRON == *tt ){
        tokens.erase(pit,tt+1);
        return true;
    }
    //如果不是冠词，NO
    if ( ART != *tt ) return false;

    ++tt;

    if ( NOUN == *tt ){
        tokens.erase(pit,tt+1);
        return true;
    }

    if ( ADJ != *tt ) return false;

    ++tt;
    if ( NOUN == *tt ) {
        tokens.erase(pit,tt+1);
        return true;
    }

    return false;
}

bool parse(vector<int>&tokens){
    tokens.push_back(JING);
    vector<int> status;//状态栈
    vector<int> symbol;//符号栈

    status.push_back(0);
    symbol.push_back(JING);
    vit it = tokens.begin();

    while(1){
        int a = status.back();
        int b = *it;

        if ( TABLE[a][b] & SHIFT ){
            int sn = TABLE[a][b] ^ SHIFT;
            symbol.push_back(*it++);
            status.push_back(sn);
        }else if ( TABLE[a][b] & REDUCE ){
            int sn = TABLE[a][b] ^ REDUCE;
            symbol.erase(symbol.end()-RL[sn],symbol.end());
            status.erase(status.end()-RL[sn],status.end());
            symbol.push_back(RULES[sn][0]);
            status.push_back(TABLE[status.back()][RULES[sn][0]]);
        }else if ( TABLE[a][b] == ACC ){
            return true;
        }else{
            return false;
        }
    }
}

bool proc(){
    //首先做词法
    vector<int> tokens;
    stringstream ss(A);
    string s;
    while( ss >> s ){
        char ch = *--s.end();
        if ( !isalpha(ch) ) s.erase(s.end()-1);

        tokens.push_back(find(s.c_str()));
    }

    //判断介词，并将介词删除
    if ( !doPrep(tokens) ) return false;

    //对没有介词的token做语法分析
    return parse(tokens);
}

int main(){
    //freopen("1.txt","r",stdin);
    initL2I();

    read();

    fgets(A,200000,stdin);
    for(int i=0;i<M;++i){
        fgets(A,200000,stdin);
        printf(proc()?"YES\n":"NO\n");
    }
    return 0;
}
