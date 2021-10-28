# DreamChess++
Porting of the original [dreamchess](https://github.com/dreamchess/dreamchess) project in Modern C++ (C++17).

## Author
Mattia Zorzan - VR464472

## Build and Controls
### Build
Use `cmake` >= 3.16 to build the project, simply launch
```bash
mkdir build
cmake -S . -B build
cd build
```

at this point you should have created 3 `make` targets:
* `install`: Creates a `bin` directory in the `dreamchess++` root with the executable
* `doc`: Creates a `doc` directory containing the HTML documentation
* `build_and_test`: Builds the `dc++_test` and run all the tests for the project

Run them with
```bash
make install
make doc
make build_and_test
```
### Controls
When the executable is launched a chaess board will be printed asking for an input. You can do a move inputing a string with the following format: <*rank*><*file*>-<*rank*><*file*><br>
If the move is a *promotion move* you can use the following syntax to specify the the promotion piece <*rank*><*file*>-<*rank*><*file*>=<*piece_fen*>. If no piece is specified it will be promoted to a Queen.<br>
You can export the whole game history (so far if the game is still in progress) using the *export_hisotry* command instead of a move. 

## DISCLAIMER
This project is born as my final for the **Modern C++ Programming** class that I attended at University of Verona - CS Dep.
