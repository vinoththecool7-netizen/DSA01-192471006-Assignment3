#ifndef PLAYBACK_HPP
#define PLAYBACK_HPP
#include <iomanip>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
class Time {
 unsigned long long seconds_;
public:
 explicit Time(unsigned long long seconds=0):seconds_{seconds}{}
 unsigned long long seconds()const{return seconds_;}
 Time& operator++(){if(seconds_==std::numeric_limits<unsigned long long>::max())throw std::overflow_error("timer overflow");++seconds_;return *this;}
 Time operator++(int){Time old{*this};++*this;return old;}
 bool operator==(const Time& other)const{return seconds_==other.seconds_;}
 bool operator<(const Time& other)const{return seconds_<other.seconds_;}
 friend std::ostream& operator<<(std::ostream& out,const Time& t){
  const auto h=t.seconds_/3600,m=(t.seconds_/60)%60,s=t.seconds_%60;
  return out<<h<<':'<<(m<10?"0":"")<<m<<':'<<(s<10?"0":"")<<s;
 }
};
class Playlist {
 std::vector<std::string> tracks_;
 std::size_t checked(long long i)const{if(i<0||static_cast<unsigned long long>(i)>=tracks_.size())throw std::out_of_range("playlist index");return static_cast<std::size_t>(i);}
public:
 explicit Playlist(std::vector<std::string> tracks):tracks_{std::move(tracks)}{}
 std::size_t size()const{return tracks_.size();}
 std::string& operator[](long long i){return tracks_[checked(i)];}
 const std::string& operator[](long long i)const{return tracks_[checked(i)];}
};
#endif
