# philosophers 

The **philosophers** project at [42](https://42wolfsburg.de) is a classic introduction to **multithreading** and **synchronization** in C.  
It explores the **Dining Philosophers Problem**, a concurrency problem proposed by Edsger Dijkstra, where philosophers alternately **eat**, **think**, and **sleep** while sharing limited resources (forks).  

The challenge is to prevent **race conditions**, **deadlocks**, and **starvation**, ensuring that all philosophers can coexist peacefully.  

---

## Project Description

- A number of philosophers sit around a table with a fork between each pair.  
- To eat, a philosopher must take **two forks**.  
- They alternate between:
  - **Thinking** 
  - **Eating** 
  - **Sleeping**
- The program must ensure:
  - Philosophers don’t die from starvation.  
  - No deadlocks occur.  
  - Synchronization is properly handled using **threads** and **mutexes**.  

---

### 1. Compilation
```bash
make
```
### 2. Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### 3. Arguments

number_of_philosophers — Total philosophers (and forks).

time_to_die (ms) — Time before a philosopher dies if they don’t start eating.

time_to_eat (ms) — Time a philosopher spends eating.

time_to_sleep (ms) — Time a philosopher spends sleeping.

(optional) number_of_times_each_philosopher_must_eat — Program stops when all philosophers eat this many times.

Classic run
```bash

./philo 5 800 200 200
```

5 philosophers
800ms before death without eating
200ms to eat
200ms to sleep

With mandatory eating count

```bash
./philo 4 410 200 200 7
```

4 philosophers
Must each eat 7 times before program ends
