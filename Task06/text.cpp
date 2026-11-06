#include "text.hpp"
#include "check.hpp"
#include <chrono>
#include <string>
Text onCopy(Text a,const Text& b){a+=b;return a;}
int main(){Checks test;Text a{"A"},b{"B"},c{"C"};Text::copies=0;Text result=a+b+c;std::cout<<"a+b+c="<<result<<" observed_copies="<<Text::copies<<'\n';test.expect("concatenation",result==Text{"ABC"});
 Text::copies=0;Text alternative=onCopy(a,b);std::cout<<"plus on a by-value copy="<<alternative<<" observed_copies="<<Text::copies<<'\n';
 Text copy=a;copy+=b;test.expect("deep independent copy",a==Text{"A"}&&copy==Text{"AB"});Text assigned;assigned=a;Text& alias=assigned;assigned=alias;test.expect("self assignment",assigned==a);
 Text empty;test.expect("empty concatenation",empty+a==a&&a+empty==a);test.expect("not equal",a!=b);std::string longInput(100000,'x');Text longText{longInput.c_str()};test.expect("long message",(longText+a).size()==100001);test.rejects<std::invalid_argument>("null rejected",[]{Text bad{nullptr};});
 // Volatile indirect calls prevent the optimiser replacing constant joins by a folded result.
 Text (* volatile joinText)(const Text&,const Text&)=[](const Text& x,const Text& y){return x+y;};
 std::string (* volatile joinString)(const std::string&,const std::string&)=[](const std::string& x,const std::string& y){return x+y;};
 const int count=100000;Text left{"Hello"},right{"World"};std::string sl="Hello",sr="World";std::size_t x=0,y=0;
 auto start=std::chrono::steady_clock::now();for(int i=0;i<count;++i){Text joined=joinText(left,right);x+=joined.size();}auto middle=std::chrono::steady_clock::now();
 for(int i=0;i<count;++i){std::string joined=joinString(sl,sr);y+=joined.size();}auto end=std::chrono::steady_clock::now();
 std::cout<<"independent_concatenations="<<count<<" Text_ns="<<std::chrono::duration_cast<std::chrono::nanoseconds>(middle-start).count()<<" std_string_ns="<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-middle).count()<<" checksum="<<x<<'\n';
 test.expect("benchmark checksums",x==y&&x==1000000);return test.finish();}
