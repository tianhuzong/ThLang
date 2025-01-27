
%{
    #include <bits/stdc++.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <cstdio>
    #include <string>
    #include "node.h"
    #include "codegen.h"
    extern int yylineno;
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(thlang::NModule &root_program, thlang::CodeGenContext& context, const char *s) { printf("Error:  %s,lineno: %d\n", s, yylineno);exit(1); }
    int nums;
    
    
%}

%union{
    std::string *string;
    std::string *str; 
    int token;
    thlang::Node *node;
    thlang::NBlock *block;
    thlang::ExprAst *stmt;
    thlang::Type *type;
    std::string *values;
}


%token <token> TOKEN_INT TOKEN_FLOAT  /*int float string*/
%token <token> TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV /*+ - * / */
%token <token> LPAREN RPAREN /*( ) */ LBRACKET RBRACKET /*[ ] */ LBRACE RBRACE /*{ } */
%token <token> TOKEN_RETURN /*return*/ TOKEN_IF /*if*/ TOKEN_ELSE /*else*/ TOKEN_WHILE /*while*/ TOKEN_FOR /*for*/ TOKEN_EXTERN
%token <token> TOKEN_EQUAL TOKEN_CEQ TOKEN_NEL TOKEN_NLT TOKEN_NLE TOKEN_NGT TOKEN_NGE /*= ==!= < <= > >= */
%token <token> TOKEN_XOR TOKEN_MOD TOKEN_SHL TOKEN_SHR /*^ % << >> */
%token <token> TOKEN_AND TOKEN_OR TOKEN_NOT /*&& || !*/
%token <token> TOKEN_COMMA /*, */ TOKEN_SEMICOLON /*; */ TOKEN_DOT /*. */ TOKEN_NEWLINE /*\n*/
%token <string> TOKEN_ID NUM TOKEN_STRING/*identifier*/

/*
%type <block> program block stmts
%type <exprvec>  call_args 
%type <varvec> func_decl_args
%type <expr>  expr assign
%type <stmt>  stmt if_stmt while_stmt for_stmt var_decl func_decl 
%type <tkid>  tkid
%type <token> op
*/
%type<node> program  
%type<node> stmt if_stmt while_stmt for_stmt var_decl func_decl 
%type<node> expr assign tkid
%type<block> block stmts
%type<str> op

%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MUL TOKEN_DIV TOKEN_MOD
%parse-param {thlang::NModule &root_program}
%parse-param {thlang::CodeGenContext &context}
%define parse.error verbose
%start program
%%

program : stmts {
    root_program  = thlang::NModule();
    root_program.block = std::unique_ptr<thlang::Node>($1);
} ;

block : LBRACE stmts RBRACE { $$ = $2; }
    | LBRACE RBRACE { $$ = new thlang::NBlock(); }

stmts : stmts stmt { $1->stmts->push_back(std::unique_ptr<thlang::Node>($2)); $$ = $1; }
    | stmts TOKEN_SEMICOLON { $$ = $1; }
    | stmts TOKEN_SEMICOLON stmt { $1->stmts->push_back(std::unique_ptr<thlang::Node>($3)); $$ = $1; }
    | stmt { auto ast = new thlang::NBlock(); ast->stmts->push_back(std::unique_ptr<thlang::Node>($1)); $$ = ast; }



stmt : if_stmt {$$ = $1;}
    | while_stmt {$$ = $1;}
    | for_stmt {$$ = $1;}
    | var_decl {$$ = $1;}
    | func_decl {$$ = $1;}
    | TOKEN_RETURN expr { $$ = new thlang::ReturnStmtAst(std::unique_ptr<thlang::Node>($2)); }
    | expr { $$ = new thlang::ExprStmtAst(std::move(std::unique_ptr<thlang::Node>($1))); }
    
expr : NUM {
    $$ = new thlang::IntAst(std::atol($1->c_str()));
    delete $1;
    }
    | TOKEN_STRING { $$ = new thlang::StringAst(*$1); delete $1; } //TODO
    | assign { $$ = $1; }
    | tkid { $$ = $1; }
    | LPAREN expr RPAREN {$$ = $2; }
    | expr op expr { $$ = new thlang::BinOpAst(*$2, std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); delete $2; }
    | expr TOKEN_MOD expr { $$ = new thlang::BinOpAst("%", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_MUL expr { $$ = new thlang::BinOpAst("*", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_DIV expr { $$ = new thlang::BinOpAst("/", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_PLUS expr { $$ = new thlang::BinOpAst("+", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_MINUS expr { $$ = new thlang::BinOpAst("-", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    //| tkid LPAREN call_args RPAREN { $$ = new thlang::CallExprAst(std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::ExprList>($3)); }    

op :  TOKEN_EQUAL  { $$ = new std::string("="); }
    | TOKEN_CEQ    { $$ = new std::string("=="); }
    | TOKEN_NEL    { $$ = new std::string("!="); }
    | TOKEN_NLT    { $$ = new std::string("<"); }
    | TOKEN_NLE    { $$ = new std::string("<="); }
    | TOKEN_NGT    { $$ = new std::string(">"); }
    | TOKEN_NGE    { $$ = new std::string(">="); }
    | TOKEN_XOR    { $$ = new std::string("^"); }
    | TOKEN_SHL    { $$ = new std::string("<<"); }
    | TOKEN_SHR    { $$ = new std::string(">>"); }
    | TOKEN_AND    { $$ = new std::string("&&"); }
    | TOKEN_OR     { $$ = new std::string("||"); }

assign : tkid TOKEN_EQUAL expr {auto expr = std::unique_ptr<thlang::Node>($3); $$ = new thlang::AssignAst(std::unique_ptr<thlang::Node>($1), std::move(std::unique_ptr<thlang::Node>($3))); }

for_stmt : TOKEN_FOR LPAREN expr TOKEN_SEMICOLON expr TOKEN_SEMICOLON expr RPAREN block { $$ = new thlang::ForStmtAst(std::unique_ptr<thlang::Node>($3), std::unique_ptr<thlang::Node>($5), std::unique_ptr<thlang::Node>($7), std::unique_ptr<thlang::Node>($9)); }

while_stmt : TOKEN_WHILE LPAREN expr RPAREN block  { $$ = new thlang::WhileStmtAst(std::unique_ptr<thlang::Node>($3), std::unique_ptr<thlang::Node>($5)); }

if_stmt : TOKEN_IF LPAREN expr RPAREN block {$$ = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>($3), std::unique_ptr<thlang::Node>($5)); }
    | TOKEN_IF LPAREN expr RPAREN block TOKEN_ELSE block {$$ = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>($3), std::unique_ptr<thlang::Node>($5), std::unique_ptr<thlang::Node>($7)); }
    | TOKEN_IF LPAREN expr RPAREN block TOKEN_ELSE if_stmt { 
		auto blk = new thlang::NBlock(); 
		blk->stmts->push_back(std::unique_ptr<thlang::Node>($7)); 
		$$ = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>($3), std::unique_ptr<thlang::Node>($5), std::unique_ptr<thlang::Node>(blk)); 
	}

var_decl : TOKEN_INT tkid {auto type = context.typeSystem.get_type("整数型");  $$ = new thlang::VarStmtAst(type, std::unique_ptr<thlang::Node>($2)); std::cout << "第一个:---" << &type << "---\n"; }
    | TOKEN_INT tkid TOKEN_EQUAL  expr {auto type = context.typeSystem.get_type("整数型"); $$ = new thlang::VarStmtAst(type, std::unique_ptr<thlang::Node>($2), std::unique_ptr<thlang::Node>($4)); std::cout << "第二个:---" << &type << "---" << type.get_type_name() << "---\n";}

func_decl : TOKEN_INT tkid LPAREN  RPAREN block { $$ = new thlang::FunctionStmtAst(context.typeSystem.get_type("整数型"), std::unique_ptr<thlang::Node>($2), std::make_unique<thlang::VarList>(), std::unique_ptr<thlang::Node>($5)); }

tkid : TOKEN_ID { $$ = new thlang::NameAst(*$1); delete $1; }



%%

