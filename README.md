# SystemCall
Implementing a custom system call  named get_process_runtime that returns the elapsed execution time of the calling process in milliseconds.

## Context
I have created a custom system called according to the assigment guidelines.

In my case the get_process_runtime was hard to create because I have never program a system call. 

## My Implementation

In case of a simple User Space program my implementation would check the /proc/PID file and get the data related to a process given the PID of the process. In this case because the assigment is to make a system_call I tried to look for ways that make sense to a system call to retrieve a process information.

I manage to find a structure called "task_struct" where all data related to a process is stored. From that structure there is a value called "start_time" in where the time when the process was created is stored.

Then I get the current time of execution with the function " ktime_get_real_ts64()" so that I get the current time in ns.

Then I move the process_time to ns, compare the two and change them to ms and return the value to the system_call caller.

## In detail
### Defining the function


### Finding the process PID and struct


### Get the process 