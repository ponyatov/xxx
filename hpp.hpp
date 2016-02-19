#ifndef _H_XXX
#define _H_XXX

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string tag,val;
	Sym(string,string); Sym(string);
	vector<Sym*> nest; void push(Sym*);
	string dump(int depth=0); string pad(int);
	virtual string tagval(); string tagstr();
	Sym* lookup(string); void reg(string,Sym*);	// env lookup/register
	virtual Sym* eval(); void nesteval();
	virtual Sym* eq(Sym*);
	virtual Sym* at(Sym*);
};

extern map<string,Sym*> env;
extern void env_init();

extern void W(Sym*);
extern void W(string);

struct Str: Sym { Str(string); string tagval(); Sym*eval(); };

struct List: Sym { List(); Sym*eval(); };

struct Op: Sym { Op(string); Sym*eval(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_XXX
