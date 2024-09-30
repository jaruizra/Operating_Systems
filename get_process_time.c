#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

// my suscall number number assigned to get_process_runtime
#define SYS_get_process_runtime 549

// Main
int main (int argc, char *argv[]) {

    // the running_time
    long runtime_ms = -1;

    // Get the process PID
    pid_t pid = getpid();
    
    // Sleep process
    sleep(20);
        
    // Call the system call
    runtime_ms = syscall(SYS_get_process_runtime, pid);

    // print the call
    if (runtime_ms < 0) {
        printf("System call failed \n");
        return 1;
    } 
    else {
        // Print the PID and the runtime in milliseconds
        printf("Process ID: %d\n", pid);
        printf("Process runtime: %ld ms. \n", runtime_ms);
        return 0;
    }

}
