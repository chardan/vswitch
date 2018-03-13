/* tswitch: switch on type comparisons */

#include <string>
#include <iostream>

#include "vswitch.hpp"

using std::cout;
using std::string;

enum class colors { red, blue, yellow, unknown };

int main(int argc, char *argv[])
{
 if(2 != argc)
  return 0;

 colors color = vswitch<colors, string>(argv[1])
	.caseof(colors::red, "red", "crimson", "vermillion")
	.caseof(colors::blue, "blue", "azure", "cerulian")
	.caseof(colors::yellow, "yellow")
	.defaultas(colors::unknown);

 switch(color)
 { 
	default:					cout << "unknown\n"; break;
	case colors::red:			cout << "red\n"; break;
	case colors::blue:			cout << "blue\n"; break;
	case colors::yellow:		cout << "yellow\n"; break;
 }
}
