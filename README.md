# Screen Event Capturer
This project records the computer screen and waits for an event to occur, once the event occurs the program will then save a video file with footage of the event occuring.

To prevent an indefinately long video, the user selects a duration for the video. Two streams are repeatedly ran in parallel for the durtion of the video.

The two streams are 50% overlapping where one stream's first half is recording along with the other streams second half and vice versa.

When the event occurs the program checks which stream is in the center half and saves that file while discarding all other files.

<img src="screen.gif"/>

## Build Instructions

Install cmake and git

```
sudo apt install cmake git
```

clone repo and change directories into the repo
```
git clone https://github.com/Abdob/Screen-Event-Capturer
cd Screen-Event-Capturer
```
Install Gstreamer using the script provided

```
sudo ./install_gstreamer.sh
```

create a build directory, cd into it and build using cmake

```
mkdir build
cd build
cmake ..
make
```

## Run Instructions
Run the program

``` 
./screen_recording_app
```

Enter a duration in seconds as prompted and allow the recording to happen.

When ready to stop, open a separate terminal induce an event by creating an event file on the same directory where the program is ran

```
cd Screen-Event-Capturer/build
touch event
```

## File and Class Structures
The two classes used are ```VideoRecorder``` and ```RecordManager```. In total there are five C++ files:
```
VideoRecorder.cpp
VideoRecorder.hpp
RecordManager.cpp
RecordManager.hpp
main.cpp
``` 

The main file initializes gstreamer and instantiates a ```RecordManager``` object and initializes to start the recording with Video```1```.

The ```RecordManager``` class is responsible for getting the duration from the user, launching two recording threads in parrallell and synchronizing between the threads. The ```RecordManager``` class instantiates a ```VideoRecorder``` object each time a Video is started, twice per video duration and tells the ```VideoRecorder``` when to start and stop recording and if it needs to save the file.

The ```VideoRecorder``` class sets a gstreamer pipeline to capture images from the screen and record them into a video file. It is responsible for creating and deleting or saving the video files.




## Rubric Points

### A README with instructions is included with the project
- [x] This README is included with the project and has instructions for building/running the project. Additional libraries are needed to run the project, these are indicated with CMAKE installation instructions. This README is a markdown file.

### The README indicates which project is chosen.
- [x] The README describes the project you have built.The README also indicates the file and class structure, along with the expected behavior or output of the program.

### The README includes information about each rubric point addressed.
- [x] The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.

### The submission must compile and run.
- [x] The project code compiles and runs without errors. It uses cmake and make, as provided.


### The project demonstrates an understanding of C++ functions and control structures.

- [x] A variety of control structures are used in the project. The project code is clearly organized into functions.

### The project reads data from a file and process the data, or the program writes data to a file. 

 - [x] The project reads data from an external file or writes data to a file as part of the necessary operation of the program. The filename is shown in ```VideoRecorder.cpp``` line 33 and is being written to under-the-hood when the starting the pipeline in ```VideoRecorder.cpp``` line 52. If the file is not saved it is deleted as shown in ```VideoRecorder.cpp``` line 45.

### The project accepts user input and processes the input.

 - [x] The project accepts input from a user as part of the necessary operation of the program. The duration is taken from the user at ```RecordManager.cpp``` line 13.

 ### The project uses Object Oriented Programming techniques.

 - [x] The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.

### Classes use appropriate access specifiers for class members.

 - [x] All class data members are explicitly specified as public, protected, or private.

### Class constructors utilize member initialization lists.

 - [x] All class members that are set to argument values are initialized through member initialization lists. ```RecordManager.cpp``` line 3 shows the video number being initialized with a member initializing list set in ```main.cpp``` line 9.

### Classes abstract implementation details from their interfaces.

 - [x] All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.

### Classes encapsulate behavior.

 - [x] Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions. On ```VideoRecorder.cpp``` line 73 and 74, the ```saveFile``` member is set through the ```setSaveFile()``` member function.

### Classes follow an appropriate inheritance hierarchy.

 - [ ] Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified.

### Overloaded functions allow the same function to operate on different parameters.

 - [ ] One function is overloaded with different signatures for the same function name.

### Derived class functions override virtual base class functions.

 - [ ] One member function in an inherited class overrides a virtual base class member function.

### Templates generalize functions in the project.

 - [ ] One function is declared with a template that allows it to accept a generic parameter.

### The project makes use of references in function declarations.

- [ ] At least two variables are defined as references, or two functions use pass-by-reference in the project code.

### The project uses destructors appropriately.

- [x] At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor. The destructor in ```VideoRecorder.cpp``` line 37 performs cleaning acts include removing the file if needed.

### The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.

- [x] The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction. ```RecordManager.cpp``` line 42 uses a unique pointer to store a ```VideoRecorder``` object. If the scope is left on line 50 it is cleaned properly, otherwise the scope is transferred in line 55 and later left in line 82. 

### The project follows the Rule of 5.

- [ ] For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.

### The project uses move semantics to move data, instead of copying it, where possible.

- [] For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object.

### The project uses smart pointers instead of raw pointers.

- [x] The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers. ```RecordManager.cpp``` line 36.

### The project uses multithreading.

- [x] The project uses multiple threads in the execution. ```RecordManager.cpp``` line 93 and 94 launch two threads.

### A promise and future is used in the project.

- [ ] A promise and future is used to pass data from a worker thread to a parent thread in the project code.


### A mutex or lock is used in the project.

- [x] A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code. ```RecordManger.cpp``` line 39 and 63 use mutex and lock.

### A condition variable is used in the project.

- [x] A std::condition_variable is used in the project code to synchronize thread execution. ```RecordManager.cpp``` line 40 and 64 use condition variable.

