#ifndef CHECK_HPP
#define CHECK_HPP
#include <iostream>
#include <stdexcept>
#include <string>
struct Checks {
 int good=0,bad=0;
 void expect(const std::string& name,bool ok) { (ok?good:bad)++; std::cout<<name<<", "<<(ok?"PASS":"FAIL")<<'\n'; }
 template<class E,class F> void rejects(const std::string& name,F fn) {bool ok=false;try{fn();}catch(const E&){ok=true;}expect(name,ok);}
 int finish()const{std::cout<<"Checks: "<<good<<" passed, "<<bad<<" failed\n";return bad?1:0;}
};
#endif
