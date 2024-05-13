##3.

Static Scheduling:
Static scheduling divides the iterations of the loop evenly among the threads before execution.
Each thread is assigned to a block of iterations at the beginning and works on it until completion.
Execution times are slightly higher compared to the other scheduling methods, due to potential load imbalance, where some threads finish their work earlier and are waiting for others to finish.

Dynamic Scheduling:
Dynamic scheduling assigns chunks of iterations to threads dynamically at runtime.
Each thread requests a new chunk of work when it finishes its current chunk.
Dynamic scheduling can potentially lead to better load balancing compared to static scheduling, especially when the workload per iteration varies.

Guided Scheduling:
Guided scheduling is similar to dynamic scheduling but starts with larger chunk sizes and gradually reduces them.
It aims to reduce overhead by initially assigning larger chunks and then reducing them to improve load balancing.

All three scheduling methods show improved performance as the number of threads increases.
Dynamic scheduling shows the worst results compared to static and guided scheduling. Which might be due a bad choice of the chunk size.
Static and guided scheduling show similar performance, with guided scheduling potentially having a slight edge in certain scenarios due to its adaptive nature.


##4.
Runtime: The scheduling type and the chunk size is taken from
OMP_SCHEDULE environment variable. I set the environment variable to "dynamic".
When not defining the environment variable, the default scheduling is dynamic, 1. It performed worst in my case.

Auto:
Schedule is left up to the runtime system to choose. Which performed best in my case.