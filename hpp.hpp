#ifndef _H_XXX
#define _H_XXX

#include <iostream>
#include <cstdlib>
using namespace std;

struct Sym {
	string val;
	Sym(string);
	string dump(); virtual string tagval(); string tagstr();
};

extern void W(Sym*);
extern void W(string);

struct Str: Sym { Str(string); string tagval(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_XXX
