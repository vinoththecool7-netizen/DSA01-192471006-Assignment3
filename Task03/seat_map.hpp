#ifndef SEAT_MAP_HPP
#define SEAT_MAP_HPP
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
class Event {
 std::string name_;int rows_,seats_;char** map_;std::size_t booked_=0;
 void check(int r,int s)const{if(r<0||r>=rows_||s<0||s>=seats_)throw std::out_of_range("seat index");}
public:
 inline static int live=0;
 Event(std::string name,int rows,int seats):name_{std::move(name)},rows_{rows},seats_{seats},map_{nullptr}{
  if(rows<0||seats<0||(rows>0&&seats==0))throw std::invalid_argument("invalid dimensions");
  if(static_cast<unsigned long long>(rows)>std::numeric_limits<std::size_t>::max()/(static_cast<std::size_t>(seats)+sizeof(char*)))throw std::overflow_error("map size overflow");
  if(rows){map_=new char*[static_cast<std::size_t>(rows)]{};
   try{for(int r=0;r<rows;++r)map_[r]=new char[static_cast<std::size_t>(seats)]{};}
   catch(...){for(int r=0;r<rows;++r)delete[] map_[r];delete[] map_;throw;}
  }
  ++live;std::cout<<"construct "<<name_<<" rows="<<rows_<<" seats="<<seats_<<'\n';
 }
 Event(const Event&)=delete;Event& operator=(const Event&)=delete;
 ~Event(){if(map_){for(int r=0;r<rows_;++r)delete[] map_[r];delete[] map_;}--live;std::cout<<"destroy "<<name_<<" booked="<<booked_<<'\n';}
 bool book(int r,int s){check(r,s);if(map_[r][s])return false;map_[r][s]=1;++booked_;return true;}
 bool cancel(int r,int s){check(r,s);if(!map_[r][s])return false;map_[r][s]=0;--booked_;return true;}
 std::size_t requestedBytes()const{return static_cast<std::size_t>(rows_)*(static_cast<std::size_t>(seats_)+sizeof(char*));}
 std::size_t allocations()const{return rows_?static_cast<std::size_t>(rows_)+1:0;}
};
#endif
