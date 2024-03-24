
%{
    #include <bits/stdc++.h>
    #include <stdio.h>
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(const char *s) { printf("Error:  %s\n", s);exit(1); }
%}

%union{
    char *string; 
    int token;
}

%token <token> TYPE_INT TYPE_STRING TYPE_BOOL TYPE_BYTES
%token <token> TEQUAL
%token <string> NAME INT
%token ERRORTOKEN

%%

program : 
    |program expr { /* 语义动作 */std::cout<<"$1<<$2<<$3<<$4"<<std::endl; }
    
    ;

expr:
      TYPE_INT NAME TEQUAL INT { /* 语义动作 */std::cout<<$1<<$2<<$3<<$4<<std::endl; }
    
    | error { yyerror("Syntax error"); }
    ;

%%


int main() {
    std::cout<<"Hi,there!\n";
    addMapping("文本型",TYPE_STRING);
    addMapping("整数型",TYPE_INT);
    addMapping("布尔型",TYPE_BOOL);
    addMapping("字节型",TYPE_BYTES);


    yyparse();

    
    return 0;
}
