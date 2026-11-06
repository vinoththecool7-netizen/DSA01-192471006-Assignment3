#include "seat_map.hpp"
int main(){Event* event=new Event{"intentionally leaked",10,20};event->book(0,0);std::cout<<"live events at exit="<<Event::live<<" (delete deliberately omitted)\n";}
