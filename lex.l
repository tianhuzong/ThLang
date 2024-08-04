%{
    #include <iostream>
    #include <string>
    #include "nn.h"
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



\"[^"\n]*\"     { cout <<"line"<<yylineno<<"  type:STRING,value:"<<yytext<<"\n"; SAVE_TOKEN; return STRING; }
(([-+]?\d+\.\d{0,})|(\d+\.?\d{0,}[eE][+-]?\d+)) {
    cout << "line"<<yylineno<<"  type:FLOAT,value:"<<yytext<<"\n";
    SAVE_TOKEN;
    return FLOAT;
}
[-+]?[0-9]+         { cout<<"line"<<yylineno<<"  type:INT,value:"<<yytext<<"\n"; SAVE_TOKEN; return INT;}

[\p{L}_][\p{L}\p{N}_]* {cout << "line"<<yylineno<<"  type:NAME,value:"<<yytext<<"\n";SAVE_TOKEN;return NAME;}

=              { cout << "line"<<yylineno<<"  type:TOKEN,value:"<<TEQUAL<<"\n";return TOKEN(TEQUAL); }
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

