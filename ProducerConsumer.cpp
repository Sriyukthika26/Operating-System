#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <semaphore>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;

// Counting semaphores
counting_semaphore<BUFFER_SIZE> empty(BUFFER_SIZE); // Initially all slots are empty
counting_semaphore<BUFFER_SIZE> full(0);            // Initially no slots are full

// Mutex for critical section
mutex mtx;

void producer(int id) {
    for (int i = 0; i < 7; ++i) {
        // Simulate producing an item
        this_thread::sleep_for(chrono::milliseconds(100 * (rand() % 5 + 1)));
        int item = rand() % 100;
        
        empty.acquire(); // Wait for empty slot
        mtx.lock();
        
        buffer.push(item);
        cout << "Producer " << id << " produced item: " << item 
             << " (Buffer size: " << buffer.size() << ")\n";
        
        mtx.unlock();
        full.release(); // Signal that a slot is full
    }
}

void consumer(int id) {
    for (int i = 0; i < 7; ++i) {
        // Simulate consuming an item
        this_thread::sleep_for(chrono::milliseconds(100 * (rand() % 5 + 1)));
        
        full.acquire(); // Wait for full slot
        mtx.lock();
        
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item: " << item 
             << " (Buffer size: " << buffer.size() << ")\n";
        
        mtx.unlock();
        empty.release(); // Signal that a slot is empty
    }
}

void test_producer_consumer() {
    cout << "\nProducer-Consumer Problem Simulation\n";
    cout << "-----------------------------------\n";
    
    thread producers[2];
    thread consumers[2];
    
    for (int i = 0; i < 2; ++i) {
        producers[i] = thread(producer, i + 1);
        consumers[i] = thread(consumer, i + 1);
    }
    
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        consumers[i].join();
    }
}

int main() {
    cout << "Classic Synchronization Problems using Semaphores\n";
    cout << "================================================\n";
    
    test_producer_consumer();
    
    return 0;
}
// This code demonstrates the Producer-Consumer problem using semaphores and mutexes in C++.