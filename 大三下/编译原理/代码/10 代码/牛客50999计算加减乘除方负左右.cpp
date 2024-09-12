/**
 *  支持加减乘除乘方运算，支持左右括号，支持负数
 *  此外还有多余的括号，应该只有多余的左括号 
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
int const LEFT = 5;
int const RIGHT = 6;
int const NEG = 7;
int const POWER = 8;
int const OPERAND = 9;

int const TABLE[][OPERAND+1] = {
///    #  +  -  *  /  (  )  N  ^  i
/*#*/{AC,LT,LT,LT,LT,LT,ER,LT,LT,LT},
/*+*/{GT,GT,GT,LT,LT,LT,GT,LT,LT,LT},
/*-*/{GT,GT,GT,LT,LT,LT,GT,LT,LT,LT},
/***/{GT,GT,GT,GT,GT,LT,GT,LT,LT,LT},
/*/*/{GT,GT,GT,GT,GT,LT,GT,LT,LT,LT},
/*(*/{ER,LT,LT,LT,LT,LT,EQ,LT,LT,LT},
/*)*/{GT,GT,GT,GT,GT,ER,GT,GT,GT,ER},
/*N*/{GT,GT,GT,GT,GT,LT,GT,LT,LT,LT},
/*^*/{GT,GT,GT,GT,GT,LT,GT,GT,LT,LT},
/*i*/{GT,GT,GT,GT,GT,ER,GT,GT,GT,ER}
};

struct _t{
	int type;
	int value;
};

string Input;
vector<_t> Tokens;

void lex(){
    Tokens.clear();
	int n = Input.length();
	int k = 0;
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
			}else if(isdigit(Input[k])){
				int v = 0;
				while(isdigit(Input[k])){
                    v = v * 10 + (Input[k++] - '0');
				}
				needNumber = false;
				Tokens.push_back({OPERAND, v});
			}else{
				throw runtime_error("???");
			}
		}else{
			switch(Input[k]){
				case '+':Tokens.push_back({PLUS});needNumber = true;break;
				case '-':Tokens.push_back({MINUS});needNumber = true;break;
				case ')':Tokens.push_back({RIGHT});needNumber = false;break;
				case '*':Tokens.push_back({MULTI});needNumber = true;break;
				case '/':Tokens.push_back({DIVID});needNumber = true;break;
				case '^':Tokens.push_back({POWER});needNumber = true;break;
				default:throw runtime_error("xxx");
			}                
			++k;			
		}
	}
	Tokens.push_back({JING});
	return;
}

string i2s(int x){
	stringstream ss;
	ss<<x;
	return ss.str();
}

vector<_t> Output;
void parse(){
    Output.clear();
	vector<_t> st(1, {JING});
	int cur = 0;

	while(1){
		int a = st.back().type;
		int b = Tokens[cur].type;
		int now = TABLE[a][b];
		if(now & (LT | EQ)){
            st.push_back(Tokens[cur++]);
		}else if(now & GT){
            if(RIGHT != a){
				Output.push_back(st.back());
				st.pop_back();
			}else{
				st.pop_back();
				st.pop_back();
			}
		}else if(now & AC){
			return;
		}else{
			// throw runtime_error("TABLE["+i2s(a)+"]["+i2s(b)+"] = "+i2s(now));
			st.pop_back();
		}
	}
}

int calc(){
	vector<int> st;
	for(const auto &t: Output){
		if(NEG == t.type){
			st.back() = -st.back();
		}else if(t.type == OPERAND){
            st.push_back(t.value);
		}else{
			int b = st.back();st.pop_back();
			int a = st.back();st.pop_back();
			if(PLUS == t.type){
                st.push_back(a+b);
			}else if(MINUS == t.type){
                st.push_back(a-b);
			}else if(MULTI == t.type){
                st.push_back(a*b);
			}else if(DIVID == t.type){
                st.push_back(a/b);
			}else if(POWER == t.type){
                int v = 1;
				for(int i=0;i<b;++i) v*=a;
				st.push_back(v);
			}else{
				throw runtime_error("WW");
			}
		}
	}
	assert(st.size() == 1);
	return st[0];
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
    getline(cin, Input);
	cout<<proc()<<endl;
	return 0;
}