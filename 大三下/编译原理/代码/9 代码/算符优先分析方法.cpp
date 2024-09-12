/**
 * 算符优先分析方法处理算术表达式
 * 支持加减乘除和乘方运算，乘方运算使用**符号
*/
#include <bits/stdc++.h>
using namespace std;

int const ER = 0;
int const LT = 1;
int const GT = 2;
int const EQ = 4;
int const AC = 8;

int const JING = 0;
int const PLUS = 1;
int const MINUS = 2;
int const MULTI = 3;
int const DIVID = 4;
int const POWER = 5;
int const LEFT = 6;
int const RIGHT = 7;
int const OPERAND = 8;

const string CH4OUT[] = {
    "#", "+", "-", "*", "/", "**", "(", ")", "i"
};

int const TABLE[][9] = {
    ///# +  -  *  / **  (  )  i
/*#*/{AC,LT,LT,LT,LT,LT,LT,ER,LT},
/*+*/{GT,GT,GT,LT,LT,LT,LT,GT,LT},
/*-*/{GT,GT,GT,LT,LT,LT,LT,GT,LT},
/***/{GT,GT,GT,GT,GT,LT,LT,GT,LT},
/*/*/{GT,GT,GT,GT,GT,LT,LT,GT,LT},
/*P*/{GT,GT,GT,GT,GT,LT,LT,GT,LT},
/*(*/{ER,LT,LT,LT,LT,LT,LT,EQ,LT},
/*)*/{GT,GT,GT,GT,GT,GT,ER,GT,ER},
/*i*/{GT,GT,GT,GT,GT,GT,ER,GT,ER}
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

/// 词法分析，结果保存在全局数组Tokens里面
/// 保证输入没有空格
bool lex(){
    Tokens.clear();
    int k = 0, n = Input.length();
    while(k < n){
        char ch = Input[k];
        if(isdigit(ch)){
            int t = 0;
            while(k<n && isdigit(Input[k])){
                t = t * 10 + (Input[k]-'0');
                ++k;
            }
            Tokens.push_back({OPERAND, t});
        }else if('+' == ch){
            Tokens.push_back({PLUS});
            ++k;
        }else if('-' == ch){
            Tokens.push_back({MINUS});
            ++k;
        }else if('*' == ch){            
            if(k+1 < n && '*' == Input[k+1]){
                Tokens.push_back({POWER});
                k += 2;
            }else{
                Tokens.push_back({MULTI});
                ++k;
            }
        }else if('/' == ch){
            Tokens.push_back({DIVID});
            ++k;
        }else if('(' == ch){
            Tokens.push_back({LEFT});
            ++k;
        }else if(')' == ch){
            Tokens.push_back({RIGHT});
            ++k;
        }else if(' ' == ch){ // 滤空格，虽然不必要
            ++k;
        }else{
            return false;
        }
    }
    /// 最后还要塞入一个#
    Tokens.push_back(TJING);
    return true;
}

/// 算符优先分析方法
/// 分析的结果输出在Output中
bool parse(){
    /// 初始化,准备一个栈
    vector<token_t> st;
    st.push_back(TJING);
    int cur = 0;
    Output.clear();

    while(1){
        int a = st.back().type;
        int b = Tokens[cur].type;
        int now = TABLE[a][b];
        if(now & (LT | EQ)){ // 入栈
            st.push_back(Tokens[cur++]);
        }else if(now & GT){ // 出栈，除了右括号，每次只出栈一个
            if(RIGHT != a){
                Output.push_back(st.back());
                st.pop_back();
            }else{
                st.pop_back(); st.pop_back();
            }
        }else if(now & AC){
            break;
        }else{
            return false;
        }
    }
    return true;   
}

/// 计算后缀表达式
pair<bool, int> calc(){
    vector<int> vec;
    for(const token_t&t: Output){
        if(t.type != OPERAND){ // 就是运算符
            if(vec.size() < 2) return {false, 0};
            int b = vec.back(); vec.pop_back();
            int a = vec.back(); vec.pop_back();
            if(PLUS == t.type){
                vec.push_back(a + b);
            }else if(MINUS == t.type){
                vec.push_back(a - b);                
            }else if(MULTI == t.type){
                vec.push_back(a * b);
            }else if(DIVID == t.type){
                vec.push_back(a / b);
            }else if(POWER == t.type){
                int t = 1;
                for(int i=0;i<b;++i) t*=a;
                vec.push_back(t);
            }else{
                return {false, 0};
            }
        }else{
            vec.push_back(t.value);
        }
    }
    if(1 == vec.size()) return {true, vec[0]};
    return {false, 0};
}

pair<bool, int> proc(){
    /// 首先做词法分析
    bool b = lex();
    if(!b){
        cerr<<"lex error."<<endl;
        return {false, 0};
    }
    b = parse();
    if(!b){
        cerr<<"parse error."<<endl;
        return {false, 0};
    }
    return calc();
}

void output(){
    for(const token_t&t: Output){
        cout<<CH4OUT[t.type];
    }
    cout<<endl;
}



int main(){
    freopen("1.txt", "r", stdin);
    while(cin>>Input){
        auto b = proc();
        if(b.first){
            cout<<"Yes"<<endl;
            output();
            cout<<"result = "<<b.second<<endl;
        }
    }    
    return 0;
}