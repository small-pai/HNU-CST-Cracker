/// 计算前缀布尔表达式
/// 格式为  op (E, E, E, ...)
/// 非与或，格式必然正确
class Solution {
    using m_t = map<int, int>;
    m_t left2right;
    string input;
public:
    bool parseBoolExpr(string expression) {
        vector<int> st;
        int n=expression.length(); 
        for(int i=0;i<n;++i){
            if('(' == expression[i]){
                st.push_back(i);
            }else if(')' == expression[i]){
                left2right[st.back()] = i;
                st.pop_back();
            }
        }
        input = std::move(expression);
        return dfs(0, n-1);
    }

    bool dfs(int s, int e){
        if(s == e){
            if('t' == input[s]) return true;
            if('f' == input[s]) return false;
            throw runtime_error("XXX");
        }

        char op = input[s];
        vector<bool> vec;
        assert('(' == input[s+1] && ')' == input[e]);

        int k = s + 2;
        while(k < e){
            if('!' == input[k] || '|' == input[k] || '&' == input[k]){
                vec.push_back(dfs(k, left2right[k+1]));
                k = left2right[k+1] + 1;
            }else if(',' == input[k]){
                ++k;
            }else{
                vec.push_back(dfs(k, k));
                ++k;
            }
        }
        if('!' == op){
            assert(1 == vec.size());
            return !vec[0];
        }else if('&' == op){
            bool ans = true;
            for(bool b: vec) ans = ans && b;
            return ans;
        }else{
            bool ans = false;
            for(bool b: vec) ans = ans || b;
            return ans;
        }
    }
};