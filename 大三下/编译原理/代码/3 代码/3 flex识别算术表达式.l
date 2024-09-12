/* 定义部分 */
%{
#include <string.h>
#define PLUS   1
#define MINUS  2
#define MULTI  3
#define DIVID  4
#define LEFTP  5
#define RIGHTP 6
#define VALUE  7
#define VRBLE  8
int const LIMIT = 99;
char const TYPES[][22] = {
    "", "PLUS", "MINUS", "MULTI", "DIVID", "LEFTP", "RIGHTP",
    "VALUE", "VRBLE"
};
int count = 0;
struct token_t{
    int type;
    int value;
    char name[99+1];
}Tokens[99];
%}

/* 规则部分, yytext是flex内置的一个全局变量，就是刚刚识别出的字符串 */
%%
\n       {;/*do nothing*/}
\+     {Tokens[count++].type = PLUS;}
[-]    {Tokens[count++].type = MINUS;}
[*]    {Tokens[count++].type = MULTI;}
[/]    {Tokens[count++].type = DIVID;}
[(]    {Tokens[count++].type = LEFTP;}
[)]    {Tokens[count++].type = RIGHTP;}
[0-9]+  {Tokens[count].type = VALUE; Tokens[count++].value = atoi(yytext);}
[_a-z][_a-z0-9]* {Tokens[count].type = VRBLE; memcpy(Tokens[count++].name, yytext, strlen(yytext)+1);}
%%

/* 代码部分 */
int yywrap(){}
int main(){
    freopen("1.txt", "r", stdin);
    yylex();
    printf("There are %d words.\n", count);
    for(int i=0;i<count;++i){
        printf("type = %d,  the name of type is %s\n", Tokens[i].type, TYPES[Tokens[i].type]);
    }
    return 0;
}

