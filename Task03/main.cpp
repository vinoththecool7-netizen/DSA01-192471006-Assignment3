#include "seat_map.hpp"
#include "check.hpp"
int main(){Checks t;
 {Event stack{"stack",2,3};t.expect("book",stack.book(0,1));t.expect("duplicate booking",!stack.book(0,1));
  {Event block{"block",1,2};Event* heap=new Event{"heap",1,1};t.expect("heap booking",heap->book(0,0));delete heap;}
  t.expect("cancel",stack.cancel(0,1));t.expect("empty cancellation",!stack.cancel(0,1));
  t.rejects<std::out_of_range>("invalid seat",[&]{stack.book(-1,0);});}
 t.expect("all scoped events destroyed",Event::live==0);
 for(auto dimensions:{std::pair<int,int>{10,20},{100,200},{1000,2000}}){Event map{"measurement",dimensions.first,dimensions.second};
  std::cout<<"requested_bytes="<<map.requestedBytes()<<" allocations="<<map.allocations()<<'\n';
  t.expect("payload formula",map.requestedBytes()==static_cast<std::size_t>(dimensions.first)*static_cast<std::size_t>(dimensions.second)+static_cast<std::size_t>(dimensions.first)*sizeof(char*));}
 {Event empty{"zero",0,0};t.expect("zero row no allocations",empty.allocations()==0&&empty.requestedBytes()==0);t.rejects<std::out_of_range>("empty booking",[&]{empty.book(0,0);});}
 t.rejects<std::invalid_argument>("negative rows",[]{Event bad{"bad",-1,2};});
 return t.finish();}
