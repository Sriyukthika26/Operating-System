#include <iostream>
#include <unistd.h>   // for fork(), getpid(), getppid(), sleep()
#include <sys/wait.h> // for wait()
#include <cstdlib>    // for exit()

using namespace std;

int main() {
    cout << "Parent process started. PID: " << getpid() << endl;

    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        cerr << "Fork failed!" << endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        cout << "Child process created. PID: " << getpid()
             << ", Parent PID: " << getppid() << endl;

        sleep(2); // Simulate some work

        cout << "Child process exiting." << endl;
        exit(0);
    } else {
        // Parent process
        cout << "Parent waiting for child to terminate..." << endl;
        wait(NULL); // Wait for the child process
        cout << "Child process terminated. Parent resuming." << endl;
    }

    return 0;
}