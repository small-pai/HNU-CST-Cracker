/**
 * 力扣224，支持加减括号，支持负数
 * 力扣227，支持加减乘除和括号
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    enum{ER, LT, GT, EQ=4, AC=8};
    enum{JING, PLUS, MINUS, MULTI, DIVID, NEG, LEFT, RIGHT, OPERAND};    
    vector<vector<int> > TABLE;

    struct token_t{
        int type;
        int value;
        token_t(int a=0,int b=0):type(a),value(b){}
    };

    token_t TJING;    

    string Input;
    vector<token_t> Tokens;
    vector<token_t> Output;

public:
    int calculate(string s) {
        Input = s; TJING = {JING};
        init();
        lex();
        parse();
        return calc();
    }

    void init(){    
        static int const a[][9] = {
            ///# +  -  *  /   P  (  )  i
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

        for(int i=0;i<9;++i) TABLE.emplace_back(a[i], a[i]+9);     
    }

    void lex(){
        Tokens.clear();
        int k = 0, n = Input.length();
        bool needNumber = true;
        while(1){
            while(k < n && ' ' == Input[k]) ++k;
            if(k == n) break;

            if(needNumber){
                if('(' == Input[k]){
                    Tokens.push_back({LEFT});
                    needNumber = true;
                    ++k;
                }else if('-' == Input[k]){
                    Tokens.push_back({NEG});
                    needNumber = true;
                    ++k;
                }else{
                    int v = 0;
                    while(isdigit(Input[k])){
                        v = v * 10 + (Input[k] - '0');
                        ++k;
                    }
                    needNumber = false;
                    Tokens.push_back({OPERAND, v});
                }
            }else{
                switch(Input[k]){
                    case '+': Tokens.push_back({PLUS});needNumber = true;break;
                    case '-':Tokens.push_back({MINUS});needNumber = true;break;
                    case ')':Tokens.push_back({RIGHT});needNumber = false;break;
                    case '*':Tokens.push_back({MULTI});needNumber = true;break;
                    case '/':Tokens.push_back({DIVID});needNumber = true;break;
                    default:exit(*(int*)0);
                }                
                ++k;
            }
        }
        /// 最后还要塞入一个#
        Tokens.push_back(TJING);
        return;
    }

    void parse(){
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
                return;
            }
        }
        return; 
    }

    int calc(){
        vector<int> vec;
        for(const token_t&t: Output){
            if(t.type == NEG){
                vec.back() = -vec.back();
            }else if(t.type != OPERAND){ // 就是运算符
                if(vec.size() < 2) exit(*(int*)0);
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
                }else if(NEG == t.type){
                    int t = 1;
                    for(int i=0;i<b;++i) t*=a;
                    vec.push_back(t);
                }else{
                    exit(*(int*)0);
                }
            }else{
                vec.push_back(t.value);
            }
        }
        if(1 != vec.size()) exit(*(int*)0);
        return vec[0];
    }
};

int main(){
    freopen("1.txt", "r", stdin);
    Solution s;
    string input;
    while(cin>>input) cout<<s.calculate(input)<<endl;  
    return 0;
}