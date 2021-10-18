# DreamChess++
Porting of the original [dreamchess](https://github.com/dreamchess/dreamchess) project in Modern C++ (C++17).

## Author
Mattia Zorzan - VR464472

## Build and Controls
### Build
Use `cmake` >= 3.16 to build the project, simply launch
```bash
mkdir build
cd build
cmake .. -B .
```
at this point you should have created 3 `make` targets:
* `install`: Creates a `bin` directory in the `dreamchess++` root with the executable
* `doc`: Creates a `doc` directory containing the HTML documentation
* `test`: Runs the tests for the project

Run them with
```bash
make install
make doc
make test
```
### Controls
When the executable is launched a chaess board will be printed asking for an input. You can do a move inputing a string with the following format: <*rank*><*file*>-<*rank*><*file*><br>
If the move is a *promotion move* you can use the following syntax to specify the the promotion piece <*rank*><*file*>-<*rank*><*file*>=<*piece_fen*>. If no piece is specified it will be promoted to a Queen.

## DISCLAIMER
This project is born as my final for the **Modern C++** class I attended at University of Verona - CS Dep.
