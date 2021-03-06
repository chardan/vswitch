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

 enum struct colors { red, blue, yellow, unknown };

 colors color = vswitch_t<colors, string>(argv[1])
    .result(colors::red, "red", "crimson", "vermillion")
    .result(colors::blue, "blue", "azure", "cerulian")
    .result(colors::yellow, "yellow", "gold")
    .defaultas(colors::unknown);

 switch(color)
 { 
    default:                    cout << "unknown\n"; break;
    case colors::red:           cout << "red\n"; break;
    case colors::blue:          cout << "blue\n"; break;
    case colors::yellow:        cout << "yellow\n"; break;
 }
}
