
%{
    #include <bits/stdc++.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <cstdio>
    #include <string>
    #include "nn.h"
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(const char *s) { printf("Error:  %s\n", s); }
    int nums;
    
    
    
%}

%union{
    std::string *string; 
    int token;
    //char* types;
    Node *node;
    Type_ *types;
    std::string *values;
}


%token <token> TEQUAL
%token <token> NEWLINE OP
%token <string> NAME INT STRING FLOAT
%token ERRORTOKEN


%type <values> types 
%type <node> value
%%

program : 
    | program  stmts { /* 语义动作 */std::cout<<"\n"<<std::endl; }
    | program  stmts NEWLINE{ /* 语义动作 */std::cout<<"\n"<<std::endl; }
    ;

stmts : stmt {std::cout<< "语句_单独\n";}
	  | stmts OP stmt {std::cout<< "语句同行分号\n";}
      | stmts OP {std::cout<<"语句sss分号结尾\n";}
      | stmts NEWLINE stmt {std::cout<<"语句\n";}
	  ;

stmt : var {std::cout<<"语句 "<<"\n";}
	 
     ;


var: var_type_stmt
    | var_stmt 
    ;

var_type_stmt:
    types NAME {std::cout<<$1<<" "<<$2<<std::endl;nums++;}
    | error { /*yyerror("Syntax error"); */}
    ;

var_stmt:
    types NAME TEQUAL value { /* 语义动作 */std::cout<<*$1<<" "<<*$2<<" "<<$4<<std::endl;  nums++;}
    
    ;
types: NAME {$$ = $1;}
    ;

value: INT {$$ = new IntAst(atol($1->c_str()));delete $1;}
    | STRING {$$ = new StringAst($1->c_str());delete $1;}
    //| NAME {$$ = $1;}
    | FLOAT {$$ = new FloatAst(atof($1->c_str()));delete $1;}
    | error { /*yyerror("Syntax error"); */}
    ;
/*
value : INT {
    std::string tips = "your int is ";
    std::string result = tips + std::to_string($1);
    char* str = new char[result.length() + 1];
    strcpy(str, result.c_str());
    delete $1;
    $$ = str;
}
| NAME {
    std::string tips = "your NAME is ";
    std::string result = tips + $1;
    char* str = new char[result.length() + 1];
    strcpy(str, result.c_str());
    delete $1;
    $$ = str;
}
| STRING {
    std::string tips = "your STRING is ";
    std::string result = tips + $1;
    char* str = new char[result.length() + 1];
    strcpy(str, result.c_str());
    $$ = str;
}
;
*/
%%
