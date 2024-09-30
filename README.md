# SystemCall
Implementing a custom system call  named get_process_runtime that returns the elapsed execution time of the calling process in milliseconds.


## Context
I have created a custom system call according to the assignment guidelines.

In my case, get_process_runtime was hard to create because I have never programmed a system call before. 


## My Implementation
In the case of a simple User Space program, my implementation would check the /proc/PID file and get the data related to a process, given the PID. However, because the assignment required making a system call, I needed to look for approaches that made sense in the context of kernel-space programming to retrieve process information.

I managed to find a structure called task_struct where all the data related to a process is stored. From that structure, there is a field called start_time which records when the process was created.

Next, I get the current time using the function ktime_get_real_ts64() to retrieve the current system time in nanoseconds. I then compare the process start time with the current time, calculate the elapsed time in milliseconds, and return the result to the system call caller.


## In detail

### Defining the system call
I use the SYSCALL_DEFINE1 macro to define the get_process_runtime function. This macro is designed for system calls that take one argument, in this case, the PID of the process for which we want to calculate the runtime. The argument is of type pid_t, representing the process ID.

### Get the Current system Time
I handle the current time retrieval at the beginning of the function to minimize any added delay caused by the syscall's execution. I define a variable of type timespec64 to store the current system time. Using the function ktime_get_real_ts64, I retrieve the time and convert it to nanoseconds with timespec64_to_ns. This provides me with a precise measure of the current time in the system.

### Finding the process PID and struct
To get the necessary process information, I use the function pid_task(find_vpid(pid), PIDTYPE_PID) to locate the process in the kernel using its PID. The function returns a pointer to the task_struct, which holds all the information about the process. If the PID doesn't match any active process, I handle this by checking if the task_struct pointer is NULL and returning an error code (-ESRCH), which indicates that the process could not be found.

### Get the process start time
Once I have the task_struct for the given process, I retrieve its start time by accessing the start_time field, which is recorded in nanoseconds from system boot. This time is stored as a 64-bit unsigned integer (u64).

### Calculate the process elapsed Time
With the current time and process start time both in nanoseconds, I subtract the process's start time from the current time to determine how long the process has been running. I convert the resulting value from nanoseconds to milliseconds by dividing the result by 1,000,000.

### Return the time
Finally, I return the calculated elapsed time in milliseconds to the caller of the system call. This value represents how long the process has been running since it was created.




# User Program
The user-space program is designed to test the get_process_runtime system call. It retrieves the process ID and uses the custom system call to print the elapsed time since the process started, in milliseconds.


## My Implementation
In this user program, the syscall() function is used to invoke the get_process_runtime system call, passing the current process's PID. The program sleeps for 20 seconds to simulate the passage of time before calling the system call, and then it retrieves the runtime in milliseconds.

The program outputs the PID and the elapsed runtime, which is useful for validating that the system call works correctly.


## In Detail
### Defining the System Call Number
I defined the system call number using #define SYS_get_process_runtime 549, where 549 corresponds to the number assigned to my custom system call in the kernel's syscall table. This allows the program to correctly identify and call the get_process_runtime system call.

### Getting the Process ID
The first task is to get the current process's PID using the getpid() function. This PID is passed to the system call as an argument, allowing the system call to retrieve the runtime of the calling process.

### Simulating Process Execution Time
To simulate a running process, I added a sleep(20) call, which causes the process to pause for 20 seconds. This helps demonstrate that the system call is accurately tracking the elapsed runtime of the process since it started.

### Calling the System Call
The main functionality of the user program lies in calling the syscall() function with the defined system call number and the process's PID. The syscall() function invokes the kernel system call, passing the PID and receiving the process runtime in milliseconds.
