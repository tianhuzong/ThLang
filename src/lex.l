%{
    #include <iostream>
    #include <string>
    #include <thlang/node.h>
    #include "parser.hpp"
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)
    int yyparse();

%}

%option noyywrap
%option noinput
%option yylineno
%option unicode


%%


\n                                              { /*return TOKEN(TOKEN_NEWLINE);*/}
";"                                             { return TOKEN(TOKEN_SEMICOLON);}
","                                             { return TOKEN(TOKEN_COMMA);}
"("                                             { return TOKEN(LPAREN);}
")"                                             { return TOKEN(RPAREN);}
"]"                                             { return TOKEN(RBRACKET);}
"["                                             { return TOKEN(LBRACKET);}
"{"                                             { return TOKEN(LBRACE);}
"}"                                             { return TOKEN(RBRACE);}
"+"                                             { return TOKEN(TOKEN_PLUS); }
"-"                                             { return TOKEN(TOKEN_MINUS); }
"*"                                             { return TOKEN(TOKEN_MUL); }
"/"                                             { return TOKEN(TOKEN_DIV); }
"=="                                            { return TOKEN(TOKEN_CEQ); }
"="                                             { return TOKEN(TOKEN_EQUAL); }
"!="                                            { return TOKEN(TOKEN_NLT); }
"<"                                             { return TOKEN(TOKEN_NLT); }
"<="                                            { return TOKEN(TOKEN_NLE); }
">"                                             { return TOKEN(TOKEN_NGT); }
">="                                            { return TOKEN(TOKEN_NGE); }
"^"                                             { return TOKEN(TOKEN_XOR); }
"%"                                             { return TOKEN(TOKEN_MOD); }
"<<"                                            { return TOKEN(TOKEN_SHL); }
">>"                                            { return TOKEN(TOKEN_SHR); }
("&&"|"且")                                     { return TOKEN(TOKEN_AND); }
("||"|"或")                                     { return TOKEN(TOKEN_OR); }
"如果"                                          { return TOKEN(TOKEN_IF); }
"否则"                                          { return TOKEN(TOKEN_ELSE); }
"."                                             { return TOKEN(TOKEN_DOT); }
"!"                                             { return TOKEN(TOKEN_NOT); }
(\"[^"\n]*\"|\'[^"\n]*\')                       { SAVE_TOKEN; return TOKEN_STRING; }
(([-+]?\d+\.\d{0,})|(\d+\.?\d{0,}[eE][+-]?\d+)) { SAVE_TOKEN; return TOKEN_FLOAT; }
[-+]?[0-9]+                                     { SAVE_TOKEN; return NUM; }
"整数型"                                         { SAVE_TOKEN;return TOKEN_INT; }
"返回"                                           { return TOKEN(TOKEN_RETURN); }
[\p{L}_][\p{L}\p{N}_]*                          { SAVE_TOKEN;return TOKEN_ID; }
.              { /* 忽略其他字符 cout<<"line"<<yylineno<<" type:ERRORTOKEN,value:"<<yytext<<"\n"; */}

%%

