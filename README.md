# vswitch
Function-like value switch.

...easily create switch-like constructs with your choice of type.

```c++
enum struct colors { red, blue, yellow, unknown };

 colors color = vswitch<colors, string>(argv[1])
    .result(colors::red, "red", "crimson", "vermillion")
    .result(colors::blue, "blue", "azure", "cerulian")
    .result(colors::yellow, "yellow")
    .defaultas(colors::unknown);

 switch(color) { ... }
```

...the result of the switch is (a copy of) the selected value, so you can say:

```c++
 colors color = vswitch<string, string(argv[1])
	.result("red", "red", "crimson", "scarlet")
    .nodefault();

 cout << "matched: " << color << '\n';
```

Using nodefault() will cause the library to throw a std::range_error if no value
has matched, or return the result of the match (in this case, "red").

