#include "prescription.hpp"
#include "check.hpp"
#include <chrono>
int byValue(Prescription p){return p.size();}
int byReference(const Prescription& p){return p.size();}
int main(){
 Checks t;Prescription p{2};p.set(0,"A");p.set(1,"B");Prescription q=p;q.set(1,"C");
 t.expect("copy independent",p.get(1)=="B"&&q.get(1)=="C");Prescription r{1};r=p;p.set(0,"D");
 t.expect("assignment independent",r.get(0)=="A");Prescription& alias=p;p=alias;t.expect("self assignment",p.get(0)=="D");
 Prescription::copies=0;t.expect("value parameter data",byValue(p)==2);std::cout<<"by value copies="<<Prescription::copies<<'\n';t.expect("one copy by value",Prescription::copies==1);
 Prescription::copies=0;t.expect("reference parameter data",byReference(p)==2);std::cout<<"const reference copies="<<Prescription::copies<<'\n';t.expect("zero copies by reference",Prescription::copies==0);
 t.rejects<std::invalid_argument>("negative count",[]{Prescription bad{-1};});
 t.rejects<std::out_of_range>("negative index",[&]{p.get(-1);});Prescription zero{0};t.expect("empty prescription",zero.size()==0);
 for(int n:{10,1000,100000}){Prescription original{n};for(int i=0;i<n;++i)original.set(i,"Medicine "+std::to_string(i));
  auto start=std::chrono::steady_clock::now();std::size_t checksum=0;
  for(int k=0;k<5;++k){Prescription copy{original};checksum+=copy.get(n-1).size();}
  auto ns=std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()-start).count();
  std::cout<<"copy medicines="<<n<<" repetitions=5 total_ns="<<ns<<" checksum="<<checksum<<'\n';
 }
 return t.finish();
}
