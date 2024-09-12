/**
 * POJ 2106 布尔表达式计算
 * 支持 非与或，括号
*/
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int const ER = 0;
int const LT = 1;
int const GT = 2;
int const EQ = 4;
int const AC = 8;

int const JING = 0;
int const NOT = 1;
int const AND = 2;
int const OR = 3;
int const LEFT = 4;
int const RIGHT = 5;
int const OPERAND = 6;

int const TABLE[][7] = {
    ///# !  &  |   (  )  i
/*#*/{AC,LT,LT,LT,LT,ER,LT},
/*!*/{GT,LT,GT,GT,LT,GT,LT},
/*&*/{GT,LT,GT,GT,LT,GT,LT},
/*|*/{GT,LT,LT,GT,LT,GT,LT},
/*(*/{ER,LT,LT,LT,LT,EQ,LT},
/*)*/{GT,GT,GT,GT,ER,GT,ER},
/*i*/{GT,GT,GT,GT,ER,GT,ER}
};

struct token_t{
    int type;
    int value;
    token_t(int a=0,int b=0):type(a),value(b){}
};

const token_t TJING(JING);


string Input;
vector<token_t> Tokens;
vector<token_t> Output;

void lex(){
    Tokens.clear();
    int k = 0, n = Input.length();
    while(1){
        while(k < n && ' ' == Input[k]) ++k;
        if(k == n) break;

        switch(Input[k]){
            case 'V':Tokens.push_back(token_t(OPERAND, 1));break;
            case 'F':Tokens.push_back(token_t(OPERAND, 0));break;
            case '!':Tokens.push_back(token_t(NOT));break;
            case '&':Tokens.push_back(token_t(AND));break;
            case '|':Tokens.push_back(token_t(OR));break;
            case '(':Tokens.push_back(token_t(LEFT));break;
            case ')':Tokens.push_back(token_t(RIGHT));break;
            default: exit(*(int*)0);
        }
        ++k;
    }
    Tokens.push_back(TJING);
    return;
}

void parse(){
    Output.clear();
    int cur = 0;

    vector<token_t> st;
    st.push_back(TJING);
    
    while(1){
        int a = st.back().type;
        int b = Tokens[cur].type;
        int now = TABLE[a][b];

        if(now & (LT | EQ)){
            st.push_back(Tokens[cur++]);
        }else if(now & GT){
            if(st.back().type != RIGHT){
                Output.push_back(st.back());
                st.pop_back();
            }else{
                st.pop_back(); st.pop_back();
            }
        }else if(now & AC){
            break;
        }else{
            exit(*(int*)0);
        }
    }
    return;
}

int calc(){
    vector<int> vec;
    for(int i=0,n=Output.size();i<n;++i){
        const token_t & t = Output[i];
        switch(t.type){
            case OPERAND:vec.push_back(t.value);break;
            case NOT:{
                vec.back() = ! vec.back();break;
            }
            case AND:{
                int a = vec.back(); vec.pop_back();
                int b = vec.back(); vec.pop_back();
                vec.push_back(a&&b);break;
            }
            case OR:{
                int a = vec.back(); vec.pop_back();
                int b = vec.back(); vec.pop_back();
                vec.push_back(a||b);break;
            }
            default: exit(*(int*)0);
        }
    }
    assert(1 == vec.size());
    return vec[0];
}

int proc(){
    lex();
    parse();
    return calc();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    char ans[] = "FV";
    for(int kase=1;getline(cin, Input);++kase){
        printf("Expression %d: %c\n", kase, ans[proc()]);
    }
    return 0;
}