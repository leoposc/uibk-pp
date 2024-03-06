### Group 3: Göthert Philipp Robert, Schmid Leopold Julius, Seling Tobias	

# Assignment 1

## Exercise 1

**Submit jobs:** 

    qsub [ -q std.q ] [options] job_script job_script_arguments …]

**Check Status:**

    qstat [options]

        - u $USER (print all jobs of $USER)
        - j job-id 
        - f (print all jobs and queses)
        - help

**Cancel job:**

    scancel <job-id>    



**Submission script**

    #!/bin/bash

    # Execute job in the partition "lva" unless you have special requirements.
    #SBATCH --partition=lva
    # Name your job to be able to identify it later
    #SBATCH --job-name test
    # Redirect output stream to this file
    #SBATCH --output=output.log
    #SBATCH --ntasks=96
    # Maximum number of tasks (=processes) to start per node
    #SBATCH --ntasks-per-node=12
    # Enforce exclusive node allocation, do not share with other jobs
    #SBATCH --exclusive

    /bin/hostname


**5 most important parameters**

`--job-name=name` is useful to keep track of the submitted jobs. This is especially helpful when submitting diffrent jobs simultaneously.

`--output=filename_pattern` setting this parameter can prevent creating many unwanted artifacts.

`--ntasks=ntasks` Request CPU resources for a total number of ntasks tasks.
Without further options (see below) the tasks are placed on free resources on any node (nodes are "filled up").
For MPI jobs, tasks correspond to MPI ranks.
Slurm will set the environment variable $SLURM_NTASKS to the number ntasks that you requested.

`--time=time`


