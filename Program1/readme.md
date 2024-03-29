# Programming Assignment - SloppySim

This programming assignment is meant to be simulating a sloppy counter.

## Compiling in Terminal

To compile in the termainal without makeFile would be:

```bash
g++ -Wall --std=c++17 sloppySim.cpp -o sloppySim -pthread
```

## Compiling and Runnning Through MakeFile

There are four functions in the makeFile. Every function has the line above to compile. The four functions are all different.

1. Testing without any arguments
```bash
make sloppySim
```

2. Testing code with small number of threads
```bash
make smallEx
```

3. Testing code with large number of threads
```bash
make largeEx
```

4. Testing CPU bound with small number of threads
```bash
make cpuBoundEx
```

## Command Line Arguments

./sloppySim [nThreads] [sloppiness] [workTime] [workIterations] [cpuBound] [doLogging]

nThreads: Number of threads use. Default: 2. 
sloppiness: How many events to do before updating global counter. Default: 10.
workTime: Duration of each task in milliseconds. Default: 10.
WorkIterations: Number of iterations pre thread. Default: 100.
cpuBound: CPU-intensive or not. Default: false.
doLogging: Logging or not. Default: false. 

## Cleaning

To clean, use makeFile function clean.
```bash
make clean
```

## Testing

Example testing can be found in the testing.txt that run the makeFile. 


