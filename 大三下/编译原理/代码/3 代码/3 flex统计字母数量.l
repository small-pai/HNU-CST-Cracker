/* 定义部分 */
%{
int count = 0;
%}

/* 规则部分, yytext是flex内置的一个全局变量，就是刚刚识别出的字符串 */
%%
[A-Za-z] {printf("%s, a letter\n", yytext); ++count;}
.        {printf("%s, not a letter\n", yytext);}
\n       {return 0;}
%%

/* 代码部分 */
int yywrap(){}
int main(){
    freopen("3eg2.txt", "r", stdin);
    yylex();
    printf("\n\nThere are %d letters in the input.\n", count);
    return 0;
}

