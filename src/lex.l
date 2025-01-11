%{
    #include <iostream>
    #include <string>
    #include "node.h"
    #include "parser.hpp"
    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)
    int yyparse();
    using namespace std;


%}

%option noyywrap
%option noinput
%option yylineno
%option unicode


%%



(\"[^"\n]*\"|\'[^"\n]*\')     { SAVE_TOKEN; return STRING; }
(([-+]?\d+\.\d{0,})|(\d+\.?\d{0,}[eE][+-]?\d+)) { SAVE_TOKEN; return FLOAT; }
[-+]?[0-9]+         { SAVE_TOKEN; return INT; }

[\p{L}_][\p{L}\p{N}_]* { SAVE_TOKEN;return NAME; }
=              { return TOKEN(TEQUAL); }
\n             { return TOKEN(NEWLINE);}
";"              {return TOKEN(SEMICOLON);}
","              {return TOKEN(COMMA);}
"("              {return TOKEN(LPAREN);}
")"              {return TOKEN(RPAREN);}
.              { /* 忽略其他字符 cout<<"line"<<yylineno<<" type:ERRORTOKEN,value:"<<yytext<<"\n"; */}

%%



int yywrap() {
    return 1;
}

