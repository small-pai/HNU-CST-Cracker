#include <bits/stdc++.h>
using namespace std;

int const STATE_SIZE = 17;
int const START_STATE = 1;
int const ERROR_STATE = 0;
int const ALPHA_SIZE = 3;

inline int tr(char ch){
    if('0' <= ch && ch <= '9') return 0;
    if('.' == ch) return 1;
    return 2;
}

int DFA[STATE_SIZE][ALPHA_SIZE] = {
//    d  .      
/*0*/ 0, 0, 0, //Error state
/*1*/ 2, 0, 0,
      3, 5, 0,
      4, 5, 0,
      0, 5, 0,
/*5*/ 6, 0, 0,
      7, 9, 0,
      8, 9, 0,
      0, 9, 0,
/*9*/ 10,0, 0,
      11,13,0,
      12,13,0,
      0, 13,0,
/*13*/14,0, 0,
      15,0, 0,//final state 
      16,0, 0,//final state 
      0, 0, 0 //final state                
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
    freopen("1.txt", "r", stdin);
    string s;
    while(cin>>s){
        int ans = run(s);
        if(14 == ans || 15 == ans || 16 == ans){
            cout<<"Yes: "<<s<<endl;
        }else{
            cout<<"Err: "<<s<<endl;
        }
    }
}