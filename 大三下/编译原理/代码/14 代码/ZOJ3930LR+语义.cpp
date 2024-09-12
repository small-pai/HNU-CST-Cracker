//LR·½·¨

#include <cstdio>
#include <string>
#include <cctype>
#include <cstring>
#include <vector>
#include <stack>
#include <sstream>
#include <cstring>
using namespace std;

int str2int(string const&s){
    stringstream ss(s);
    int x;
    ss >> x;
    return x;
}

struct Token{
    int attr;
    string value;
    Token(int a=0,string const&b=""):attr(a),value(b){}
};

int const JING = 0;
int const PLUS = 1;
int const SUBTRACT = 2;
const int MULTI = 3;
const int DIVID = 4;
const int LEFT = 5;
const int RIGHT = 6;
const int VT_d = 7;
const int VT_I = 8;
const int VN_E = 9;
const int VN_T = 10;
const int VN_F = 11;
const int VN_D = 12;

const int ACC = 0x400;
const int SHIFT = 0x100;
const int REDUCE = 0x200;
const int ERR = 0;

int const s1 = SHIFT | 1;
int const s2 = SHIFT | 2;
int const s3 = SHIFT | 3;
int const s4 = SHIFT | 4;
int const s5 = SHIFT | 5;
int const s6 = SHIFT | 6;
int const s7 = SHIFT | 7;
int const s8 = SHIFT | 8;
int const s9 = SHIFT | 9;
int const s10 = SHIFT | 10;
int const s11 = SHIFT | 11;
int const s12 = SHIFT | 12;
int const s13 = SHIFT | 13;
int const s14 = SHIFT | 14;
int const s15 = SHIFT | 15;
int const s16 = SHIFT | 16;
int const s17 = SHIFT | 17;
int const s18 = SHIFT | 18;
int const s19 = SHIFT | 19;
int const s20 = SHIFT | 20;

int const r1 = REDUCE | 1;
int const r2 = REDUCE | 2;
int const r3 = REDUCE | 3;
int const r4 = REDUCE | 4;
int const r5 = REDUCE | 5;
int const r6 = REDUCE | 6;
int const r7 = REDUCE | 7;
int const r8 = REDUCE | 8;
int const r9 = REDUCE | 9;
int const r10 = REDUCE | 10;
int const r11 = REDUCE | 11;

int const LR[21][13] = {
//       #   +   -   *   /   (   )   d   I    E T F D
/*0*/   {ERR,ERR,ERR,ERR,ERR,s4, ERR,s7, s5,1,2,3,6},
/*1*/   {ACC,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
/*2*/   {r3, s8, s9, ERR,ERR,ERR,r3, ERR,ERR},
/*3*/   {r6, r6, r6, s10,s11,ERR,r6, ERR,ERR},
/*4*/   {ERR,ERR,ERR,ERR,ERR,s4, ERR,s7, s5,12,2,3,6},
/*5*/   {r8, r8, r8, r8, r8, ERR,r8, s13,ERR},
/*6*/   {r9, r9, r9, r9, r9, ERR,r9, ERR,ERR},
/*7*/   {ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,s14},
/*8*/   {ERR,ERR,ERR,ERR,ERR,s4, ERR,s7, s5,15,2,3,6},
/*9*/   {ERR,ERR,ERR,ERR,ERR,s4, ERR,s7, s5,16,2,3,6},
/*10*/  {ERR,ERR,ERR,ERR,ERR,s4, ERR,s7, s5,0 ,17,3,6},
/*11*/  {ERR,ERR,ERR,ERR,ERR,s4, ERR,s7, s5,0 ,18,3,6},
/*12*/  {ERR,ERR,ERR,ERR,ERR,ERR,s19,ERR,ERR},
/*13*/  {ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,s20},
/*14*/  {r10,r10,r10,r10,r10,ERR,r10,ERR,ERR},
/*15*/  {r1, ERR,ERR,ERR,ERR,ERR,r1, ERR,ERR},
/*16*/  {r2, ERR,ERR,ERR,ERR,ERR,r2, ERR,ERR},
/*17*/  {r4, r4, r4, ERR,ERR,ERR,r4, ERR,ERR},
/*18*/  {r5, r5, r5, ERR,ERR,ERR,r5, ERR,ERR},
/*19*/  {r7, r7, r7, r7, r7, ERR,r7, ERR,ERR},
/*20*/  {r11,r11,r11,r11,r11,ERR,r11,ERR,ERR},
};

int const _RULES[12][4] = {
    	{ERR,VN_E,JING},
/*1*/  	{VN_E,VN_T,PLUS,VN_E},
/*2*/  	{VN_E,VN_T,SUBTRACT,VN_E},
/*3*/  	{VN_E,VN_T},
/*4*/  	{VN_T,VN_F,MULTI,VN_T},
/*5*/  	{VN_T,VN_F,DIVID,VN_T},
/*6*/  	{VN_T,VN_F},
/*7*/  	{VN_F,LEFT,VN_E,RIGHT},
/*8*/  	{VN_F,VT_I},
/*9*/  	{VN_F,VN_D},
/*10*/ 	{VN_D,VT_d,VT_I},
/*11*/ 	{VN_D,VT_I,VT_d,VT_I}
};

typedef vector<int> vi_t;
const vi_t RULES[12] = {
    	vi_t(_RULES[0],_RULES[0]+3),
/*1*/  	vi_t(_RULES[1],_RULES[1]+4),
/*2*/  	vi_t(_RULES[2],_RULES[2]+4),
/*3*/  	vi_t(_RULES[3],_RULES[3]+2),
/*4*/  	vi_t(_RULES[4],_RULES[4]+4),
/*5*/  	vi_t(_RULES[5],_RULES[5]+4),
/*6*/  	vi_t(_RULES[6],_RULES[6]+2),
/*7*/  	vi_t(_RULES[7],_RULES[7]+4),
/*8*/  	vi_t(_RULES[8],_RULES[8]+2),
/*9*/  	vi_t(_RULES[9],_RULES[9]+2),
/*10*/ 	vi_t(_RULES[10],_RULES[10]+3),
/*11*/ 	vi_t(_RULES[11],_RULES[11]+4)
};


char Input[2005];

int main(){
    int kase;
    scanf("%d",&kase);
    fgets(Input, 2200, stdin);
    while(kase--){
        fgets(Input, 2200, stdin);
        Input[strlen(Input) - 1] = '\0';
        void proc();
        proc();
    }
    return 0;
}
Token Tokens[2005];
int CntOfTokens;

void getTokens(){
    CntOfTokens = 0;
    int n = strlen(Input);
    int k = 0;
    while ( k < n ){
        if ( isdigit(Input[k]) ){
            int t = 0;
            while( isdigit(Input[k+t]) ){
                ++t;
            }
            Tokens[CntOfTokens].attr = VT_I;
            Tokens[CntOfTokens++].value.assign(Input+k,Input+k+t);
            k += t;
        }else if ( '+' == Input[k] ){
            Tokens[CntOfTokens].attr = PLUS;
            Tokens[CntOfTokens++].value = " + ";
            ++k;
        }else if ( '-' == Input[k] ){
            Tokens[CntOfTokens].attr = SUBTRACT;
            Tokens[CntOfTokens++].value = " - ";
            ++k;
        }else if ( '*' == Input[k] ){
            Tokens[CntOfTokens].attr = MULTI;
            Tokens[CntOfTokens++].value = " * ";
            ++k;
        }else if ( '/' == Input[k] ){
            Tokens[CntOfTokens].attr = DIVID;
            Tokens[CntOfTokens++].value = " / ";
            ++k;
        }else if ( '(' == Input[k] ){
            Tokens[CntOfTokens].attr = LEFT;
            Tokens[CntOfTokens++].value = "(";
            ++k;
        }else if ( ')' == Input[k] ){
            Tokens[CntOfTokens].attr = RIGHT;
            Tokens[CntOfTokens++].value = ")";
            ++k;
        }else if ( 'd' == Input[k] ){
            Tokens[CntOfTokens].attr = VT_d;
            Tokens[CntOfTokens++].value = "d";
            ++k;
        }else{
            ++k;
        }
    }
    Tokens[CntOfTokens].attr = JING;
    Tokens[CntOfTokens++].value = "#";
}

void parse(){
    stack<Token> symbol_stack;
    symbol_stack.push(Token(JING,"#"));

    stack<int> status_stack;
    status_stack.push(0);

    int index = 0;
    while(1){
        int a = status_stack.top();
        int b = Tokens[index].attr;

        if ( SHIFT & LR[a][b] ){
            int status = LR[a][b] ^ SHIFT;
            status_stack.push(status);
            symbol_stack.push(Tokens[index++]);

        }else if ( REDUCE & LR[a][b] ){
            int sn = LR[a][b] ^ REDUCE;
            string value;

            if ( 1 == sn || 2 == sn || 4 == sn || 5 == sn || 7 == sn ){//E::=T+E | T-E T::=F*T|F/T F::=(E)
    			value = symbol_stack.top().value;
    			symbol_stack.pop();
    			status_stack.pop();

    			value = symbol_stack.top().value + value;
    			symbol_stack.pop();
    			status_stack.pop();

    			value = symbol_stack.top().value + value;
    			symbol_stack.pop();
    			status_stack.pop();

            }else if ( 3 == sn || 6 == sn || 8 == sn || 9 == sn ){//E::=T T::=F  F::=I F::=D
    			value = symbol_stack.top().value;
    			symbol_stack.pop();
    			status_stack.pop();

    		}else if ( 10 == sn ){//D::=dI
    			value = symbol_stack.top().value;
    			value = "[d" + value + "]";
   				status_stack.pop();status_stack.pop();
   				symbol_stack.pop();symbol_stack.pop();
   			}else if ( 11 == sn ){//D::=IdI
   			    string t = "[d"+symbol_stack.top().value+"]";
   				value += "(";
   				value += t;

   				status_stack.pop();status_stack.pop();
   				symbol_stack.pop();symbol_stack.pop();

   				int cnt = str2int(symbol_stack.top().value);
   				for(int i=0;i<cnt-1;++i){
   					value += " + ";
   					value += t;
   				}

                if ( 1 == cnt ) value = value.substr(1);
   				else value += ")";

   				status_stack.pop();
   				symbol_stack.pop();
   			}

    		symbol_stack.push(Token(RULES[sn][0], value/*TODO*/));

    		int status = LR[status_stack.top()][RULES[sn][0]];
    		status_stack.push(status);

        }else if ( ACC == LR[a][b] ){
            string str = symbol_stack.top().value + " = [Result]";
            printf("%s\n",str.c_str());
            break;
        }else{
            while(1);
        }
    }
}

void proc(){
    getTokens();
    parse();
}
