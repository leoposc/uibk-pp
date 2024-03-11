echo "Run benchmarks"

for i in {1..8}
do
    export OMP_NUM_THREADS=$i
    echo "Running algorithm on $OMP_NUM_THREADS thread(s)."
    gcc -o slow slow.c -fopenmp -std=gnu11 -Wall -Werror -Wextra -ffast-math
    gcc -o medium medium.c -fopenmp -std=gnu11 -Wall -Werror -Wextra -ffast-math
    gcc -o fast fast.c -fopenmp -std=gnu11 -Wall -Werror -Wextra -ffast-math

    ./slow
    ./medium
    ./fast

done
    