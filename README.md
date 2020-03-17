# console.log

I hate typing `std::cout << blah << " " << blah << std::endl;` especially after I got used to the browser Javascript `console.log(blah,blah)` so I made this.

And it's got a **colorized output** (when stderr is outputing to console) and more! Setting log level is also supported.

## Integration

You only need to include the file `consolelog.hpp` and start using `console.log` in your project!

Note that you should use C++11 or above.

## Usage

```c++
console.log(...);
console.info(...);
console.warn(...);
console.error(...);

console.time("label"); // label name can be omitted
console.timeLog("label");
console.timeEnd("label");

console.count("label"); // label name can be omitted
console.countReset("label");
```

See `example_advanced.cpp` for more usage.

