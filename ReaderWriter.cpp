#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <chrono>

using namespace std;

int shared_data = 0;
int readers_count = 0;

// Binary semaphores
binary_semaphore rw_mutex(1);   // Controls access to the shared data
binary_semaphore mutex(1);       // Protects readers_count

void reader(int id) {
    for (int i = 0; i < 5; ++i) {
        // Simulate reading preparation
        this_thread::sleep_for(chrono::milliseconds(100 * (rand() % 3 + 1)));
        
        mutex.acquire();
        readers_count++;
        if (readers_count == 1) {
            rw_mutex.acquire(); // First reader locks the writer out
        }
        mutex.release();
        
        // Reading section
        cout << "Reader " << id << " is reading data: " << shared_data << " (Readers: " << readers_count << ")\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        
        mutex.acquire();
        readers_count--;
        if (readers_count == 0) {
            rw_mutex.release(); // Last reader releases the lock
        }
        mutex.release();
    }
}

void writer(int id) {
    for (int i = 0; i < 5; ++i) {
        // Simulate writing preparation
        this_thread::sleep_for(chrono::milliseconds(100 * (rand() % 5 + 1)));
        rw_mutex.acquire();
        // Writing section
        shared_data++;
        cout << "Writer " << id << " is writing data: " << shared_data << "\n";
        this_thread::sleep_for(chrono::milliseconds(200));
        rw_mutex.release();
    }
}

void test_reader_writer() {
    cout << "\nReader-Writer Problem Simulation\n";
    cout << "--------------------------------\n";
    
    thread readers[3];
    thread writers[2];
    
    for (int i = 0; i < 3; ++i) {
        readers[i] = thread(reader, i + 1);
    }
    
    for (int i = 0; i < 2; ++i) {
        writers[i] = thread(writer, i + 1);
    }
    
    for (int i = 0; i < 3; ++i) {
        readers[i].join();
    }
    
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }
}

int main() {
    cout << "Classic Synchronization Problems using Semaphores\n";
    cout << "================================================\n";
    
    test_reader_writer();
    
    return 0;
}


