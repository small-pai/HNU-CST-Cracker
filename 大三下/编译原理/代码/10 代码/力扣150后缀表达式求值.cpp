class Solution {
    template<typename T> 
    T s2v(const string &s){
        stringstream ss(s);
        T x; ss>>x;
        return x;
    }
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> st;
        for(const string & s: tokens){
            if(isdigit(s[0]) || (('+' == s[0] || '-' == s[0]) && s.length() > 1)){
                st.push_back(s2v<int>(s));
            }else{
                int b = st.back(); st.pop_back();
                int a = st.back(); st.pop_back();
                if('+' == s[0]) st.push_back(a+b);
                else if('-' == s[0]) st.push_back(a-b);
                else if('/' == s[0]) st.push_back(a/b);
                else if('*' == s[0]) st.push_back(a*b);
                else throw runtime_error("wrong");
            }
        }
        return st[0];
    }
};