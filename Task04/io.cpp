#include "money.hpp"
#include <iostream>
#include <sstream>
int main(){std::string line;while(std::getline(std::cin,line)){std::istringstream in{line};Money value;if(in>>value){in>>std::ws;if(in.eof())std::cout<<value<<'\n';else std::cout<<"Invalid amount\n";}else std::cout<<"Invalid amount\n";}}
