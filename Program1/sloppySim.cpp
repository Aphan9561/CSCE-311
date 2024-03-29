/* Programming Assignment 1 - SloppySim
 * Written by Anna Phan
 *
 * Main Function of program:
 *  - To simulate a sloppy counter which is multi-threading with a global
 *    local counter, where each thread preforms CPU-Bound or I/O-Bound.
 *
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <pthread.h>
#include <random>

using namespace std;

// Global variables and defaults for them
mutex global_mutex;
int nThreads = 2;
int sloppiness = 10;
int workTime = 10;
int workIterations = 100;
bool cpuBound = false;
bool doLogging = false;
int globalCounter = 0;

struct ThreadData {
    int localCounter;
    ThreadData(): localCounter(0){}
};

// Function to simulate work
void simulateWork() {
  //random number generator
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distrib(workTime/2, workTime+workTime/2);
  int rand = distrib(gen);

  if (cpuBound) {
    // CPU-bound
    long increments = workTime * 1000000;
    for (long j = 0; j < increments; j++)
      ;
  } else {
    // Simulate I/O-bound work
    this_thread::sleep_for(chrono::milliseconds(rand));
  }
}

// Function to execute in each thread
void* threadFunction(void* arg) {
  ThreadData* data = static_cast<ThreadData*>(arg);

  for (int i = 1; i <= workIterations; i++) {
    //CPU Bound
    simulateWork();

    // Increment local counter
    data->localCounter++;

    // Check to update the global counter
    if (data->localCounter >= sloppiness) {
      lock_guard<mutex> lock(global_mutex);
      globalCounter += data->localCounter; 
      data->localCounter = 0; //emptying the bucket
    }
  }

  pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
  // Check for skipping
  if(argc != 7){
    cout << "skipping means that you can some arguments from left to right but once you skip one you must skip all the rest" << endl;
  } 

  // Parse command line arguments
  if (argc > 1) nThreads = stoi(argv[1]);
  if (argc > 2) sloppiness = stoi(argv[2]);
  if (argc > 3) workTime = stoi(argv[3]);
  if (argc > 4) workIterations = stoi(argv[4]);
  if (argc > 5) cpuBound = (string(argv[5]) == "true");
  if (argc > 6) doLogging = (string(argv[6]) == "true");

  cout << "Calculating the time cost of 1B increments\n" << endl;

  // start timer
  auto start = chrono::high_resolution_clock::now();

  // Create threads
  pthread_t threads[nThreads];
  ThreadData threadData[nThreads];

  for (int i = 0; i < nThreads; i++) {
    // threadIds[i] = i;
    int result = pthread_create(&threads[i], NULL, threadFunction,  &threadData[i]);
    if (result) {
      cerr << "Error creating thread " << i << endl;
      exit(-1);
    }
  }

  if(doLogging){
    cout << "Logging every " << workTime * workIterations / 10 <<" ms"<< endl;
    for(int i = 1; i <= workIterations; i += workIterations /10){
      this_thread::sleep_for(chrono::milliseconds(workTime * workIterations / 10));
      cout << "Global Ct = " << globalCounter << " Locals [";
        for (int j = 0; j < nThreads; ++j) {
          cout << threadData[j].localCounter;
          if (j < nThreads - 1)
            cout << ",";
        }
        cout << "]" << endl;
    }
  }

  // Join pthreads
  for (int i = 0; i < nThreads; i++) {
    pthread_join(threads[i], NULL);
  }

  // End timer and calculate time
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

  // Printing current settings
  cout << "\nIt took " << duration / 1e6 << " s to do 1B increments" << endl; 
  cout << "So it should take " << (1e9 / duration)*1000 << " increments for ~1ms of operations" << endl; 
  cout << "with simulation parameters:" << endl;
  cout << "\t#threads = " << nThreads << endl;
  cout << "\tsloppiness = " << sloppiness << endl;
  cout << "\twork time = " << workTime << endl;
  cout << "\twork iterations = " << workIterations << endl;
  cout << "\tCPU bound = " << (cpuBound ? 1 : 0) << endl;
  cout << "\tDo logging = " << (doLogging ? 1 : 0) << endl;

  // Display final global counter
  cout << "Final Global Counter: " << globalCounter << endl;

  return 0;
}
