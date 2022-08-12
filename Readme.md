## Sublime Text simple setup for contest writing
It contains:
1. Build System.
2. Simple stress test, which usually compare output of fast program (aka `smart`) with output of slow program (aka `stupid`), using `gen` to generate tests.
3. Stress test with checker, where you can configure comparing of the `smart` and `stupid` answers with help of the `checker`.
4. Some simple library to generate base random objects (e.g. numbers, pairs, arrays, strings, some type of graphs).
5. Algo library.

## Usage
To run simple stress test, select `Stress` option in buildSystem. Also, you need to put your code for `stupid` to [stupid.cpp](src/stupid.cpp), code for `gen` to [gen.cpp](src/gen.cpp).  
To run stress test with checker, select `cStress` option in BuildSystem. Also, you need to put your code for `checker` to [checker.cpp](src/checker.cpp).