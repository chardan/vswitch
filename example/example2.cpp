/* tswitch: switch on type comparisons */

#include <string>
#include <iostream>

#include "vswitch.hpp"

using std::cout;
using std::tuple;
using std::string;

enum struct department = { creative, engineering, hr };

using employee = tuple<string, string, department>;

void 

int main(int argc, char *argv[])
{
 if(2 != argc)
  {
    cout << "Usage: " << argv[0] << " red|crimson|vermillion|blue|azure|cerulian|yellow\n";
    return 0;
  }

 colors color = vswitch<colors, string>(argv[1])
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
