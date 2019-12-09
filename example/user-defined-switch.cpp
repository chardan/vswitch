/* 
vswitch: switch on type comparisons 

This example shows how to work with user-defined comparitors.
*/

#include <string>
#include <iostream>

#include "vswitch.hpp"

// The easiest way is probably to just define an appropriate equality operator:
struct record
{
 std::string name;
 int great_justice;

 bool operator==(const record& rhs) const { return name == rhs.name and great_justice == rhs.great_justice; }
};

int main(int argc, char *argv[])
try
{
 if(3 != argc)
  {
    std::cout << "Usage: " << argv[0] << " <name> <val>\n";
    return 0;
  }

 record r = { argv[1], std::stoi(argv[2]) };

 auto s = vswitch::vswitch_t<std::string, record>(r)
	.result("matched record",    { "wombat", 42 })
	.result("I've got that one", { "marmot", 7 })
	.nodefault();

 std::cout << "Yep-- " << s << ".\n";
}
catch(...)
{
 std::cout << "Nope!\n";
}
