#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }
int main() { return yyparse(); }

Sym::Sym(string V) { val=V; }

string Sym::tagval() { return "<"+val+">"; }
string Sym::tagstr() { return "<'"+val+"'>"; }
string Sym::dump() { return tagval(); }
void W(Sym*o) { cout<<o->dump(); }

Str::Str(string V):Sym(V) {}
string Str::tagval() { return tagstr(); }

