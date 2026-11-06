#include "money.hpp"
#include "check.hpp"
#include <sstream>
int main(){Checks t;
 auto carry=Money{0,75}+Money{0,50};std::cout<<"carry: "<<carry<<'\n';t.expect("75+50 paise=125",carry.paise()==125);
 const auto negative=Money{0,25}-Money{1};std::cout<<"negative refund: "<<negative<<'\n';t.expect("negative refund allowed",negative.paise()==-75);
 Money bill{120,75};Money& same=(bill+=Money{79,25});std::cout<<"bill: "<<bill<<'\n';t.expect("compound reference",&same==&bill&&bill==Money{200});t.expect("comparison",Money{1}<Money{2});
 for(const auto& text:{"0.75","-1.25","12.3","+0.05","92233720368547758.07","-92233720368547758.08"}){
  std::istringstream in{text};Money value;in>>value;t.expect(std::string{"valid input "}+text,!in.fail());std::cout<<text<<" => "<<value<<'\n';}
 for(const auto& text:{"letters","1.234","1e2","1x","-","1.","92233720368547758.08","-92233720368547758.09"}){
  std::istringstream in{text};Money value{7};in>>value;t.expect(std::string{"invalid unchanged "}+text,in.fail()&&value==Money{7});}
 const auto max=Money::fromPaise(std::numeric_limits<long long>::max()),min=Money::fromPaise(std::numeric_limits<long long>::min());
 t.rejects<std::overflow_error>("addition overflow",[&]{(void)(max+Money::fromPaise(1));});
 t.rejects<std::overflow_error>("subtraction overflow",[&]{(void)(min-Money::fromPaise(1));});
 t.rejects<std::overflow_error>("constructor overflow",[]{Money bad{std::numeric_limits<long long>::max()};});
 Money exact;double floating=0;for(int i=0;i<1000000;++i){exact+=Money{0,10};floating+=0.1;}
 std::cout<<std::setprecision(17)<<"one million additions: integer_paise="<<exact.paise()<<" double_rupees="<<floating<<" error_rupees="<<floating-100000.0<<'\n';
 t.expect("million exact",exact.paise()==10000000);return t.finish();}
