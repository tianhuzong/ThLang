
%{
    #include <bits/stdc++.h>
    #include <stdio.h>
    #include "nn.h"
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(const char *s) { printf("Error:  %s\n", s); }
    int nums;
    
%}

%union{
    char *string; 
    int token;
    //char* types;
    Node *node;
    Type *types;
    Value *values;
}

%token <token> TYPE_INT TYPE_STRING TYPE_BOOL TYPE_BYTES
%token <token> TEQUAL
%token <token> NEWLINE OP
%token <string> NAME INT
%token ERRORTOKEN

%type <node> t2
%type <token> types
%type <values> value
%%

program : 
    | program  stmts NEWLINE{ /* 语义动作 */std::cout<<"\n"<<std::endl; }
    
    ;

stmts : stmt {std::cout<< "语句s\n";}
	  | stmts OP stmt {std::cout<< "语句ss\n";}
      | stmts OP {std::cout<<"语句sss\n";}
	  ;

stmt : var {std::cout<<"语句\n";}
	 
     ;


var: var_type_stmt
    | var_stmt 
    ;

var_type_stmt:
    types NAME {std::cout<<$1<<" "<<$2<<std::endl;nums++;}
    | error { /*yyerror("Syntax error"); */}
    ;

var_stmt:
    types NAME TEQUAL value { /* 语义动作 */std::cout<<$1<<" "<<$2<<" "<<$4<<std::endl;  nums++;}
    
    ;
types: TYPE_INT {$$ = TYPE_INT;}
    | TYPE_BOOL {$$ = TYPE_BOOL;}
    | TYPE_BYTES {$$ = TYPE_BYTES;}
    | TYPE_STRING {$$ = TYPE_STRING;}
    ;

value : INT{$$ = new Value((char*)$1);delete $1;}
    | NAME {$$ = new Value((char*)$1);delete $1;}
    ;
%%

int main() {
    std::cout<<"Hi,there!\n";
    addMapping("文本型",TYPE_STRING);
    addMapping("整数型",TYPE_INT);
    addMapping("布尔型",TYPE_BOOL);
    addMapping("字节型",TYPE_BYTES);


    yyparse();
    std::cout << nums <<std::endl;
    
    return 0;
}
