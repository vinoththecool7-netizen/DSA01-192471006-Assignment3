#include "playback.hpp"
#include <chrono>
#include <iostream>
volatile unsigned long long observable=0;
int main(){constexpr unsigned long long n=10000000;Time prefix,postfix;unsigned long long first=0,second=0;using C=std::chrono::steady_clock;
 auto begin=C::now();for(unsigned long long i=0;i<n;++i){auto value=(++prefix).seconds();first+=value;observable=value;}auto middle=C::now();
 for(unsigned long long i=0;i<n;++i){auto value=(postfix++).seconds();second+=value;observable=value;}auto end=C::now();
 std::cout<<"increments="<<n<<" prefix_ns="<<std::chrono::duration_cast<std::chrono::nanoseconds>(middle-begin).count()<<" postfix_ns="<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-middle).count()<<" prefix_checksum="<<first<<" postfix_checksum="<<second<<'\n';
 if(first!=n*(n+1)/2||second!=n*(n-1)/2||prefix.seconds()!=n||postfix.seconds()!=n)return 1;
 Playlist checked{{"Track","Track","Track","Track"}};std::vector<std::string> unchecked{"Track","Track","Track","Track"};unsigned long long x=0,y=0;
 begin=C::now();for(unsigned long long i=0;i<n;++i){auto value=checked[static_cast<long long>(i&3)].size();x+=value;observable=value;}middle=C::now();
 for(unsigned long long i=0;i<n;++i){auto value=unchecked[static_cast<std::size_t>(i&3)].size();y+=value;observable=value;}end=C::now();
 std::cout<<"accesses="<<n<<" checked_ns="<<std::chrono::duration_cast<std::chrono::nanoseconds>(middle-begin).count()<<" unchecked_ns="<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-middle).count()<<" checksum="<<x<<'\n';return x==y&&x==5*n?0:1;
}
