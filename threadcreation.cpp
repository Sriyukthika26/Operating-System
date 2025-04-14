// thread_creation.cpp
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void threadFunction(int id) {
    cout << "Thread " << id << " started.\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Thread " << id << " finished.\n";
}

int main() {
    thread t1(threadFunction, 1);  // Create a thread

    t1.join(); // Wait for thread to finish
    cout << "Main function ends after thread termination.\n";

    return 0;
}