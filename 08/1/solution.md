#1
##2. 
I chose to try out OMP_PROC_BIND with "master" "close" "spread". Because they can determine where to map the threads.

##3.
The "master" setting thread performed best because all the threads are reading and writing the same variable. 
So they can perhabs use the same cache.