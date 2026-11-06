#include "check.hpp"
#include <vector>
#include <string>
struct Prescription {std::vector<std::string> medicines;};
int main(){Checks t;Prescription p{{"A","B"}};Prescription q=p;q.medicines[0]="C";t.expect("Rule of Zero independent copy",p.medicines[0]=="A");return t.finish();}
