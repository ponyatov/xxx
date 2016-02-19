#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("",V) {}
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::tagval() { return "<"+tag+":"+val+">"; }
string Sym::tagstr() { string S="<"+tag+":'";
	for (int i=0;i<val.size();i++)
		switch (val[i]) {
			case '\n': S+="\\n"; break;
			case '\t': S+="\\t"; break;
			default: S+=val[i]; }
	return S+"'>"; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) {
	string S = "\n"+pad(depth)+tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }
void W(Sym*o) { cout<<o->dump(); }
void W(string s) { cout<<s; }

Sym* Sym::lookup(string V) { auto it = env.find(V);
	if (it!=env.end()) return it->second;
	else return NULL; }
void Sym::reg(string V,Sym*o) { env[V]=o; }
void Sym::nesteval() {
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		(*it)=(*it)->eval(); }
Sym* Sym::eval() {
	Sym*E = lookup(val); if (E) return E; else reg(val,this);
	nesteval(); return this; }

Sym* Sym::eq(Sym*o) { Sym*R = new Sym("var",val); R->push(o); return R; }
Sym* Sym::at(Sym*o) { push(o); return this; }

Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }
Sym* Str::eval() { return this; }

List::List():Sym("","") {}
Sym* List::eval() { nesteval(); return this; }

Op::Op(string V):Sym("op",V) {}
Sym* Op::eval() {
	Sym::nesteval();
	if (val=="=") return nest[0]->eq(nest[1]);
	if (val=="@") return nest[0]->at(nest[1]);
	return this; }

map<string,Sym*> env;
void env_init() {}

