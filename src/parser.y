%{
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <cstdio>
    #include <string>
    #include <thlang/node.h>
    #include <thlang/codegen.h>
    extern int yylineno;
    int yylex();
    int findMapping(const char *type);
    void addMapping(const char *type, int token);
    void yyerror(thlang::NModule &root_program, thlang::CodeGenContext& context, const char *s) { 
        printf("Error: %s, lineno: %d\n", s, yylineno);
        exit(1); 
    }
    int nums;
%}

%union{
    std::string *string;
    std::string *str; 
    int token;
    thlang::Node *node;
    thlang::NBlock *block;
    thlang::ExprAst *expr;
    thlang::VarStmtAst *var_decl;
    thlang::Type *type;
    std::string *values;
    thlang::VarList* varvec;
    thlang::ExprList* exprvec;
    std::vector<thlang::Type*>* typevec;
}

%token <token> TOKEN_INT   /* int */
%token <token> TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV /* + - * / */
%token <token> LPAREN RPAREN /* ( ) */ LBRACKET RBRACKET /* [ ] */ LBRACE RBRACE /* { } */
%token <token> TOKEN_RETURN /* return */ TOKEN_IF /* if */ TOKEN_ELSE /* else */ TOKEN_WHILE /* while */ TOKEN_FOR /* for */ TOKEN_EXTERN
%token <token> TOKEN_EQUAL TOKEN_CEQ TOKEN_NEL TOKEN_NLT TOKEN_NLE TOKEN_NGT TOKEN_NGE /* = == != < <= > >= */
%token <token> TOKEN_XOR TOKEN_MOD TOKEN_SHL TOKEN_SHR /* ^ % << >> */
%token <token> TOKEN_AND TOKEN_OR TOKEN_NOT /* && || ! */
%token <token> TOKEN_COMMA /* , */ TOKEN_SEMICOLON /* ; */ TOKEN_DOT /* . */ TOKEN_NEWLINE /* \n */
%token <string> TOKEN_ID NUM STRING FLOAT /* identifier */

%type<node> program  
%type<node> stmt if_stmt while_stmt for_stmt var_decl func_decl 
%type<node> expr assign 
%type<block> block stmts
%type<str> op
%type<type> types type_id func_type
%type<expr> var_id
%type<varvec> func_args
%type<exprvec> call_args
%type<typevec> type_list

%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MUL TOKEN_DIV TOKEN_MOD
%right UMINUS
%right UPLUS
%right UFACT

%parse-param {thlang::NModule &root_program}
%parse-param {thlang::CodeGenContext &context}
%start program
%%

program : stmts {
    root_program = thlang::NModule();
    root_program.block = std::unique_ptr<thlang::Node>($1);
};

block : LBRACE stmts RBRACE { $$ = $2; }
     | LBRACE RBRACE { $$ = new thlang::NBlock(); };

stmts : stmts stmt { $1->stmts->push_back(std::unique_ptr<thlang::Node>($2)); $$ = $1; }
     | stmts TOKEN_SEMICOLON { $$ = $1; }
     | stmts TOKEN_SEMICOLON stmt { $1->stmts->push_back(std::unique_ptr<thlang::Node>($3)); $$ = $1; }
     | stmt { auto ast = new thlang::NBlock(); ast->stmts->push_back(std::unique_ptr<thlang::Node>($1)); $$ = ast; };

stmt : if_stmt { $$ = $1; }
     | while_stmt { $$ = $1; }
     | for_stmt { $$ = $1; }
     | var_decl { $$ = $1; }
     | func_decl { $$ = $1; }
     | TOKEN_RETURN  { $$ = new thlang::ReturnStmtAst(nullptr); }
     | TOKEN_RETURN expr { $$ = new thlang::ReturnStmtAst(std::unique_ptr<thlang::Node>($2)); }
     | expr { $$ = new thlang::ExprStmtAst(std::move(std::unique_ptr<thlang::Node>($1))); };

expr : NUM {
    $$ = new thlang::IntAst(std::atol($1->c_str()));
    delete $1;
    }
    | STRING { $$ = new thlang::StringAst(*$1); delete $1; }
    | FLOAT { $$ = new thlang::FloatAst(std::stod($1->c_str())); delete $1; }
    | assign { $$ = $1; }
    | var_id { $$ = $1; }
    | LPAREN expr RPAREN { $$ = $2; }
    | expr op expr { $$ = new thlang::BinOpAst(*$2, std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); delete $2; }
    | expr TOKEN_MOD expr { $$ = new thlang::BinOpAst("%", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_MUL expr { $$ = new thlang::BinOpAst("*", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_DIV expr { $$ = new thlang::BinOpAst("/", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_PLUS expr { $$ = new thlang::BinOpAst("+", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | expr TOKEN_MINUS expr { $$ = new thlang::BinOpAst("-", std::unique_ptr<thlang::Node>($1), std::unique_ptr<thlang::Node>($3)); }
    | TOKEN_MINUS expr %prec UMINUS { $$ = new thlang::UnOpAst("-", std::unique_ptr<thlang::Node>($2)); }
    | TOKEN_PLUS expr %prec UPLUS { $$ = new thlang::UnOpAst("+", std::unique_ptr<thlang::Node>($2)); }
    | TOKEN_NOT expr %prec UFACT { $$ = new thlang::UnOpAst("!", std::unique_ptr<thlang::Node>($2)); }
    | var_id LPAREN call_args RPAREN { $$ = new thlang::CallExprAst(std::unique_ptr<thlang::ExprAst>($1), std::unique_ptr<thlang::ExprList>($3)); };

op : TOKEN_EQUAL { $$ = new std::string("="); }
   | TOKEN_CEQ   { $$ = new std::string("=="); }
   | TOKEN_NEL   { $$ = new std::string("!="); }
   | TOKEN_NLT   { $$ = new std::string("<"); }
   | TOKEN_NLE   { $$ = new std::string("<="); }
   | TOKEN_NGT   { $$ = new std::string(">"); }
   | TOKEN_NGE   { $$ = new std::string(">="); }
   | TOKEN_XOR   { $$ = new std::string("^"); }
   | TOKEN_SHL   { $$ = new std::string("<<"); }
   | TOKEN_SHR   { $$ = new std::string(">>"); }
   | TOKEN_AND   { $$ = new std::string("&&"); }
   | TOKEN_OR    { $$ = new std::string("||"); };

assign : var_id TOKEN_EQUAL expr { 
    $$ = new thlang::AssignAst(std::unique_ptr<thlang::ExprAst>($1), 
                              std::move(std::unique_ptr<thlang::Node>($3))); 
};

for_stmt : TOKEN_FOR LPAREN expr TOKEN_SEMICOLON expr TOKEN_SEMICOLON expr RPAREN block { 
    $$ = new thlang::ForStmtAst(std::unique_ptr<thlang::Node>($3), 
                               std::unique_ptr<thlang::Node>($5), 
                               std::unique_ptr<thlang::Node>($7), 
                               std::unique_ptr<thlang::Node>($9)); 
};

while_stmt : TOKEN_WHILE LPAREN expr RPAREN block { 
    $$ = new thlang::WhileStmtAst(std::unique_ptr<thlang::Node>($3), 
                                 std::unique_ptr<thlang::Node>($5)); 
};

if_stmt : TOKEN_IF LPAREN expr RPAREN block { 
    $$ = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>($3), 
                              std::unique_ptr<thlang::Node>($5)); 
}
    | TOKEN_IF LPAREN expr RPAREN block TOKEN_ELSE block { 
        $$ = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>($3), 
                                  std::unique_ptr<thlang::Node>($5), 
                                  std::unique_ptr<thlang::Node>($7)); 
    }
    | TOKEN_IF LPAREN expr RPAREN block TOKEN_ELSE if_stmt { 
        auto blk = new thlang::NBlock(); 
        blk->stmts->push_back(std::unique_ptr<thlang::Node>($7)); 
        $$ = new thlang::IfStmtAst(std::unique_ptr<thlang::Node>($3), 
                                  std::unique_ptr<thlang::Node>($5), 
                                  std::unique_ptr<thlang::Node>(blk)); 
    };

var_decl : types var_id { 
    $$ = new thlang::VarStmtAst($1, std::unique_ptr<thlang::ExprAst>($2)); 
}
    | types var_id TOKEN_EQUAL expr {
        $$ = new thlang::VarStmtAst($1, 
                                   std::unique_ptr<thlang::Node>($2), 
                                   std::unique_ptr<thlang::Node>($4)); 
    };

func_args : /* 没有参数 */ { $$ = new thlang::VarList(); }
    | var_decl { $$ = new thlang::VarList(); $$->push_back(std::unique_ptr<thlang::VarStmtAst>($<var_decl>1)); }
    | func_args TOKEN_COMMA var_decl { $1->push_back(std::unique_ptr<thlang::VarStmtAst>($<var_decl>3)); }
    ;

func_decl : types var_id LPAREN func_args RPAREN block { 
    $$ = new thlang::FunctionStmtAst($1, 
                                    std::unique_ptr<thlang::ExprAst>($2), 
                                    std::unique_ptr<thlang::VarList>($4), 
                                    std::unique_ptr<thlang::Node>($6)); 
    };
    | TOKEN_EXTERN types var_id LPAREN func_args RPAREN {
        $$ = new thlang::FunctionStmtAst($2, 
                                    std::unique_ptr<thlang::ExprAst>($3), 
                                    std::unique_ptr<thlang::VarList>($5), 
                                    nullptr, true); 
    }

call_args : /* 无参数列表 */ { $$ = new thlang::ExprList(); }
    | expr { $$ = new thlang::ExprList(); $$->push_back(std::unique_ptr<thlang::ExprAst>($<expr>1)); }
    | call_args TOKEN_COMMA expr { $1->push_back(std::unique_ptr<thlang::ExprAst>($<expr>3)); }
    ;

types : TOKEN_INT { $$ = context.typeSystem.get_type("整数型"); }
    | type_id { $$ = $1; }
    | func_type { $$ = $1; }
    ;

func_type : LPAREN types RPAREN LPAREN RPAREN {  // 无参数情况
    $$ = new thlang::FunctionType($2, {}); 
}
| LPAREN types RPAREN LPAREN type_list RPAREN {  // 带参数列表
    $$ = new thlang::FunctionType($2, *$5);
    delete $5;
};

type_list : types {  // 单个类型
    $$ = new thlang::TypeList();
    $$->push_back($1);
}
| type_list TOKEN_COMMA types {  // 多个类型（逗号分隔）
    $1->push_back($3);
    $$ = $1;
};

type_id : TOKEN_ID { 
    thlang::Type* t = context.typeSystem.get_type(*$1) ;
    if (*$1 != "空类型" && t == context.typeSystem.get_type("空类型")) {
        LogError("未知的数据类型" +  *$1);
    }
    $$ = t;
    delete $1;
};

var_id : TOKEN_ID { 
    $$ = new thlang::NameAst(*$1);
    delete $1;
};

%%