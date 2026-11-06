#include "check.hpp"
#include <string>
#include <utility>
class Book {
 std::string title_,author_;
 int copies_;
public:
 Book():Book("","",0){}
 explicit Book(std::string title):Book(std::move(title),"Unknown",1){}
 Book(std::string title,std::string author,int copies):title_{std::move(title)},author_{std::move(author)},copies_{copies}{
  if(copies<0)throw std::invalid_argument("copies must be nonnegative");
 }
 int copies()const{return copies_;}
 void print()const{std::cout<<"Book{title='"<<title_<<"', author='"<<author_<<"', copies="<<copies_<<"}\n";}
};
int main(){
 Checks t;Book empty;Book donated{"Donated Atlas"};Book full{"C++ Primer","Lippman",3};
 empty.print();donated.print();full.print();Book array[2];
 t.expect("empty initialised",empty.copies()==0&&array[0].copies()==0&&array[1].copies()==0);
 t.expect("donation has one copy",donated.copies()==1);t.expect("full record",full.copies()==3);
 t.rejects<std::invalid_argument>("negative copies rejected",[]{Book bad{"x","y",-1};});
 return t.finish();
}
