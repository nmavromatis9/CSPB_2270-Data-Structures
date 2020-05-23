# LinkedList
In this assignment you will implement a Linked List Class

Project has following folder tree

.  
├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── LinkedList.cpp  
│   └── LinkedList.h  
└── tests  
    └── test_LinkedList.cpp  

CMakeLists.txt      : Ignore this file  
CMakeLists.txt.in   : Ignore this file  
README.md           : Readme file  
app\                : Application folder  
main.cpp            : Application main file for your personal tests. you can use this executable to debug your own classes.  
build\              : Build folder to build the project. your executables are gonna be here eventually.  
code\               : all your code should be in this folder.   
LinkedList.cpp      : LinkedList class source file  
LinkedList.h        : LinkedList class heather file  
tests\              : Tests folder  
test_LinkedList.cpp : Tests implemented for you / your personal tests  



For your final submission you submitt LinkedList.cpp and LinkedList.h files. Any other changes in other folders will be ignored in grading process but feel free to change them if you want to test/debug something.

## Where to Start
Open a terminal window in Jupytherhub(recommended) or your personal linux/mac machine (no windows platforms). First pull the this repository by
```console
jovyan@jupyter-yourcuid:~$ git clone https://github.com/Colorado-CompSci-Ugrad/LinkedList.git
```
### If you want to use vscode environment
Then open the VScode app through JupyterHub and open LinkedList folder from vscode.

Now your environment is set up, change LinkedList.cpp and LinkedList.h files and eventually press CTRL+SHIFT+B to compile your code.

Open a terminal window in vscode and go into ''build'' folder and run tests by
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
debugger is also set up for you, go to debug tab on the left column and select **Run Tests** in drop-down menu and press the green play button to run the debugger. if you have any implementation in **app/main.cpp** you can also debug that code by first choosing **Run App** in drop-down menu and pressing green play button.

### If you want to use linux terminal for comilation
Make sure you have the dependecies installed (ckeck dependencies in this document)
go into your project folder, then build folder
```console
jovyan@jupyter-yourcuid:~$ cd LinkedList
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
you need **gcc** and **cmake** installed to be able to compile this code.

if you are using vscode environment in JupyterHub, you just need to make sure you have C/C++ extension installed.

## About This homework

In this assignment you'll implement a linked list data
structure. We've covered the struct and associated operations in the
video lectures. Here's a summary:

* **LinkedList()** - LinkedList constructor, set top pointer to null when object is created.
* **~LinkedList()** - if not using smart pointers, make sure you remove heap memory here.
* **shared_ptr\<node> InitNode(int data)** - create a new node and return a shared pointer to it.
* **string Report()** - return a string representation of the list
* **void AppendData(int data)** - given data value, create a new node with that data and append to the end of list.
* **void Append(shared_ptr\<node> new_node)** - add given node to the end of the list.
* **void InsertData(int offset, int data)** - create a node with given data and insert to given offset position.
* **void Insert(int offset, shared_ptr\<node> new_node)** - insert given node into any spot in the list
* **void Remove(int offset)** - remove any index of list
* **int Size()** - return current number of nodes in the list.
* **bool Contains(int data)** - return true if the list contains a value
* **shared_ptr\<node> GetTop()** - Returns a shared_ptr for top of the list. (for testing purposes) (this is implemented for you)
* **void SetTop(shared_ptr\<node> top_ptr)** - Updates the Top pointer of the list to a new location given by top_ptr (for testing purposes) (this is implemented for you)

### Useful Tips
to create dynamic memory of an struct (for example "node") you can do
```cpp
shared_ptr<node> mynode(new node);
```

to re-assign a shared pointer to newly created memory do
```cpp
top_ptr_ = shared_ptr<node>(new node);
```

to assign a shared pointer to null
```cpp
top_ptr_ = shared_ptr<node>(NULL);
```

to check if shared_ptr is NULL or points to a valid address
```cpp
shared_ptr<node> a_pointer;
if(a_pointer){
    // this will run if a_pointer points to an address
} else {
    // this will run if a_pointer was NULL
}
```
