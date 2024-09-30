#include <linux/kernel.h>       // kernel functions
#include <linux/syscalls.h>     // for defining syscalls
#include <linux/sched.h>        // For process task structures
#include <linux/timekeeping.h>  // for time functions
#include <linux/errno.h>        // for error codes

// I define a system call that receives one argument -> the pid of the process
SYSCALL_DEFINE1(get_process_runtime, pid_t, pid) {

    // GET THE CURRENT SYSTEM TIME
    // variable for kernel time
    struct timespec64 current_time;
    // variable for time in ms
    u64 current_time_ns;
    // get time in nanoseconds
    ktime_get_real_ts64(&current_time);
    // get time in ns
    current_time_ns = timespec64_to_ns(&current_time);

    // FINDING THE PROCESS PID AND STRUCT
    // variable for process data_struct
    struct task_struct *task;
    // find the task given the pid
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    // Check if the task was found
    if (!task) {
        printk(KERN_ALERT "Process with PID %d not found.\n", pid);
        return -ESRCH;  // Return error if process doesn't exist
    }

    // GET THE PROCESS START TIME
    // variable for time in nanoseconds
    u64 task_start_ns;
    // get the time in nanoseconds
    task_start_ns = task->start_time;

    // CALCULATE THE PROCESS ELAPSED TIME
    // variable fot the elapsed time
    u64 elapsed_time_ms;
    elapsed_time_ms = (current_time_ns - task_start_ns) / 1000000;

    // TEST
    printk(KERN_INFO "Process with PID %d has been running for %llu ms.\n", pid, elapsed_time_ms);


    // RETURN THE ELAPSED TIME IN MS
    return elapsed_time_ms;

}
