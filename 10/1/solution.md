### What is the main bottleneck of your parallel implementation and how can it be improved without changing the underlying algorithm?

The overhead when waiting for the other tasks to finish. This is why I use sequential execution, when n + m < 15.