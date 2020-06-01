# PriorityQueue
In this assignment you will be implementing a priority queue.

Project has following folder tree

.  
├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── PriorityQueue.cpp  
│   └── PriorityQueue.h  
└── tests  
    └── test_PriorityQueue.cpp  

CMakeLists.txt      : Ignore this file  
CMakeLists.txt.in   : Ignore this file  
README.md           : Readme file  
app\                : Application folder  
main.cpp            : Application main file for your personal tests. you can use this executable to debug your own classes.  
build\              : Build folder to build the project. your executables are gonna be here eventually.  
code\               : all your code should be in this folder.   
PriorityQueue.cpp        : PriorityQueue class source file  
PriorityQueue.h          : PriorityQueue class heather file  
tests\              : Tests folder  
test_PriorityQueue.cpp   : Tests implemented for you / your personal tests  

For your final submission you submitt PriorityQueue.cpp and PriorityQueue.h files. Any other changes in other folders will be ignored in grading process but feel free to change them if you want to test/debug something.

## Where to Start
Open a terminal window in Jupytherhub(recommended) or your personal linux/mac machine (no windows platforms). First pull the this repository by
```console
jovyan@jupyter-yourcuid:~$ git clone https://github.com/Colorado-CompSci-Ugrad/PriorityQueue.git
```
### If you want to use vscode environment
Then open the VScode app through JupyterHub and open PriorityQueue folder from vscode.

Now your environment is set up, change PriorityQueue.cpp and PriorityQueue.h files and eventually press CTRL+SHIFT+B to compile your code.

Open a terminal window in vscode and go into ''build'' folder and run tests by
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
debugger is also set up for you, go to debug tab on the left column and select ''Run Tests'' in drop-down menu and press the green play button to run the debugger. if you have any implementation in ''app/main.cpp'' you can also debug that code by first choosing ''Run App'' in drop-down menu and pressing green play button.

### If you want to use linux terminal for comilation
Make sure you have the dependecies installed (ckeck dependencies in this document)
go into your project folder, then build folder
```console
jovyan@jupyter-yourcuid:~$ cd PriorityQueue
jovyan@jupyter-yourcuid:~$ cd build
```
run cmake to create make file for your project
```console
jovyan@jupyter-yourcuid:~$ cmake ..
```
run make to compile your code
```console
jovyan@jupyter-yourcuid:~$ make
```
once done, you can run tests by 
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
app executable is also in this folder, you can run it by
```console
jovyan@jupyter-yourcuid:~$ ./run_app
```
you can debug in terminal using gdb

## Dependencies
you need ''gcc'' and ''cmake'' installed to be able to compile this code.

if you are using vscode environment in JupyterHub, you just need to make sure you have C/C++ extension installed.

## About This homework
This homework is all about implementing (fully) an abstract data
type. The ADT you're implementing is a priority queue, which has the
following operations:

- Insert element with some numeric priority
- Remove the highest priority element
- Peek at the highest priority element

### Implementation is your call

You'll implement this however you like. This causes some problems for
unit testing (see below).

The linked list assignment is a reasonable starting point. You'll have
to modify the node structure so it includes a priority value.

Another choice is to implement a heap. There's a lecture on this.

### How it is tested

Since our testing framework has no knowledge about how your
implementation is structured, it can only interact with your code via
the priority queue interface. This is defined in a struct `pq` in `PriorityQueue.h` .

As a result, it is not possible to test your functions independently.

Testing `Insert`, `Peek` and `Remove` all require `InitPriorityQueue`
to work. There are other dependencies. Take a look at the unit tests.

I recommend you implement your functions in this order:

1. `InitPriorityQueue`
2. `Peek`
3. `Insert`
4. `Remove`
