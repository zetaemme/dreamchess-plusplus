# DreamChess++
Porting of the original [dreamchess](https://github.com/dreamchess/dreamchess) project in Modern C++ (C++17).

## Author
Mattia Zorzan - VR464472

## Build and Controls
Use `cmake` >= 3.16 to build the project, simply launch
```bash
mkdir build
cmake -S . -B build
cd build
```
at this point you should have created 2 `make` targets:
* `install`: Creates a `bin` directory in the `dc++_main` root with the executable
* `doc`: Creates a `doc` directory containing the HTML documentation

Run them with
```bash
make install
make doc
```

## DISCLAIMER
This project is born as my final for the **Modern C++ Programming** class that I attended at University of Verona - CS Dep.
