
%{
    #include <bits/stdc++.h>
    #include <stdio.h>
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(const char *s) { printf("Error:  %s\n", s); }
    int nums;
%}

%union{
    char *string; 
    int token;
}

%token <token> TYPE_INT TYPE_STRING TYPE_BOOL TYPE_BYTES
%token <token> TEQUAL
%token <token> NEWLINE OP
%token <string> NAME INT
%token ERRORTOKEN

%%

program : 
    | program  stmts NEWLINE{ /* 语义动作 */std::cout<<"\n"<<std::endl; }
    
    ;

stmts : stmt {std::cout<< "语句s\n";}
	  | stmts OP stmt {std::cout<< "语句ss\n";}
	  ;

stmt : var {std::cout<<"语句\n";}
	 
     ;


var: var_type_stmt
    | var_stmt
    ;

var_type_stmt:
    TYPE_INT NAME {std::cout<<$1<<" "<<$2<<std::endl;nums++;}
    | error { /*yyerror("Syntax error"); */}
    ;

var_stmt:
    TYPE_INT NAME TEQUAL INT { /* 语义动作 */std::cout<<$1<<" "<<$2<<" "<<$4<<std::endl;  nums++;}
    
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
