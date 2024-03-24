%{
#include <iostream>
#include <string>
#include "uthash.h"
#include "parser.hpp"

#define SAVE_TOKEN yylval.string = strdup(yytext)
#define TOKEN(t) (yylval.token = t)

using namespace std;
int yyparse();
int findMapping(const char *type);
void addMapping(const char *type, int token);

typedef struct {
    char type[20];
    int token;
    UT_hash_handle hh;
} TokenMap;

TokenMap *tokenMap = NULL; // 创建哈希表
%}

%option noyywrap
%option noinput
%option yylineno
%option unicode


%%



\"[^"\n]*\"     { cout <<"line"<<yylineno<<"  type:STRING,value:"<<yytext<<"\n"; }
[0-9]+         { 
    cout<<"line"<<yylineno<<"  type:INT,value:"<<yytext<<"\n";
    SAVE_TOKEN;
    return INT;}
[\p{L}_][\p{L}\p{N}_]* {
     cout << "line"<<yylineno<<"  type:NAME,value:"<<yytext<<"\n";
     SAVE_TOKEN;
     if (findMapping(yytext) != -1){
        return TOKEN(findMapping(yytext));
    }
     return NAME;
}

=              { cout << "line"<<yylineno<<"  type:TOKEN,value:"<<TEQUAL<<"\n";return TOKEN(TEQUAL); }
\n             { /*printf("line%d type:SPACE,value:\\n \n",yylineno); */}
.              { /* 忽略其他字符 cout<<"line"<<yylineno<<" type:ERRORTOKEN,value:"<<yytext<<"\n"; */}

%%

void addMapping(const char *type, int token) {
    TokenMap *mapping;
    mapping = (TokenMap *)malloc(sizeof(TokenMap));
    strcpy(mapping->type, type);
    mapping->token = token;
    HASH_ADD_STR(tokenMap, type, mapping);
}

/* 根据类型在哈希表中查找对应的 token */
int findMapping(const char *type) {
    TokenMap *mapping;
    HASH_FIND_STR(tokenMap, type, mapping);
    if (mapping) {
        return mapping->token;
    }
    return -1; // 找不到返回-1或其他错误值
}

int yywrap() {
    return 1;
}

