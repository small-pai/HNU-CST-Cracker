#include <bits/stdc++.h>
using namespace std;

int const STATE_SIZE = 8;
int const START_STATE = 1;
int const ERROR_STATE = 0;
int const ALPHA_SIZE = 5;

inline int tr(char ch){
    if('0' <= ch && ch <= '9') return 0;
    if('.' == ch) return 1;
    if('e' == ch || 'E' == ch) return 2;
    if('+' == ch || '-' == ch) return 3;
    return 4;
}

int DFA[STATE_SIZE][ALPHA_SIZE] = {
//    d  .  e  +    
     {0, 0, 0, 0, 0},
/*1*/{2, 4, 0},
/*2*/{2, 3, 5, 0},
/*3*/{3, 0, 5, 0},
/*4*/{3, 0},
/*5*/{7, 0, 0, 6, 0},
/*6*/{7, 0},
/*7*/{7, 0}
};

int run(const string& s){
    int state = START_STATE;
    for(char ch: s){
        state = DFA[state][tr(ch)];
        if(ERROR_STATE == state) break;
    }
    return state;
}

int main(){
    string a[] = {
        "123452", ".124", "111.", "2.451",
        "1E3", "12.5e-3",
        "1E3.1255", "1.2345.1245",
        "abcd"
    };
    for(string &s: a){
        int ans = run(s);
        if(2 == ans){
            cout<<"Int: "<<s<<endl;
        }else if(3 == ans){
            cout<<"Fix: "<<s<<endl;
        }else if(7 == ans){
            cout<<"Exp: "<<s<<endl;
        }else{
            cout<<"Err: "<<s<<endl;
        }
    }
}