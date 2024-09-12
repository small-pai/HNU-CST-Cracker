/// 只有加乘，没有括号，可以用更简单的方法实现
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 20;
#else
int const SIZE = 2E6+10;
#endif

char A[SIZE];
vector<int> V;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    fgets(A, SIZE, stdin);
	char const * p = A;
	int prev = 0;
	while(1){
		if(isdigit(*p)){
			int v = 0;
			while(isdigit(*p)){
				v = v * 10 + (*p++ - '0');
			}
			V.push_back(v%10000);
		}else if('+' == *p){
			++p;
		}else if('*' == *p){
            assert(V.size() >= 1);
			++p;
			assert(isdigit(*p));
			
			int v = 0;
			while(isdigit(*p)){
				v = v * 10 + (*p++ - '0');
			}
			V.back() = V.back() * (v % 10000) % 10000;
		}else if('\n' == *p || '\0' == *p){
			break;
		}else{
			throw runtime_error("wrong");
		}
	}
	int ans = 0;
	for(int v: V) ans = (ans + v) % 10000;
	cout<<ans<<endl; 
	return 0;
}