#include "playback.hpp"
#include "check.hpp"
int main(){Checks test;Time t{5};Time a=t++;Time b=++t;test.expect("postfix a=5",a.seconds()==5);test.expect("prefix b=7 t=7",b.seconds()==7&&t.seconds()==7);
 Time minute{59};++minute;test.expect("minute rollover",minute.seconds()==60);std::cout<<"minute "<<minute<<'\n';
 Time hour{3599};++hour;test.expect("hour rollover",hour.seconds()==3600);std::cout<<"hour "<<hour<<'\n';
 test.expect("comparisons",a<b&&b==t);Playlist songs{{"One","Two"}};songs[0]="Revised";const Playlist& readonly=songs;
 test.expect("const and mutable indexing",readonly[0]=="Revised");test.rejects<std::out_of_range>("negative index",[&]{songs[-1];});test.rejects<std::out_of_range>("index equals size",[&]{songs[static_cast<long long>(songs.size())];});
 for(int i=0;i<3;++i){std::cout<<"play "<<readonly[i%2]<<" position "<<t<<'\n';++t;}
 Time max{std::numeric_limits<unsigned long long>::max()};test.rejects<std::overflow_error>("timer overflow",[&]{++max;});return test.finish();}
