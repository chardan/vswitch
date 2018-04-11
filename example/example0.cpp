/* tswitch: switch on type comparisons */

#include <string>
#include <iostream>

#include "vswitch.hpp"

int main(int argc, char *argv[])
{
 using std::cout;
 using std::string;

 using namespace vswitch;

 if(2 != argc)
  {
    cout << "Usage: " << argv[0] << " red|crimson|vermillion|blue|azure|cerulian|yellow\n";
    return 0;
  }

 // The general form is to say "value switch" and then to match. The result of
 // a match is given first, followed by the match conditions. This is the inverse
 // of traditional "switch syntax in order to allow variadic matching in a natural
 // way, hence the relabling of "case" as "result":

 try
  {
	auto color = vswitch_t<string, const char *>(argv[1])
	   .result("red", 
	   	"red", "crimson", "vermillion")
	   .result("blue", 
	   	"blue", "azure", "cerulian")
	   .result("yellow", 
	   	"yellow", "canary", "ochre", "gold")
	   .nodefault();
	
	cout << color << '\n';
  }
 catch(std::range_error& e)
  {
	cout << "no match for \"" << argv[1] << "\".\n";
  }
}
