# Philosophers
*This project was created as part of the 42 curriculum by [your name].*

## Description

Philosophers is an implementation of the classic **Dining Philosophers Problem**,
originally formulated by Dijkstra. N philosophers sit at a circular table and alternate
between thinking, picking up forks, eating, and sleeping. The challenge is to ensure
that no philosopher starves, while avoiding deadlocks and data races at all times.

The program spawns one POSIX thread (`pthread`) per philosopher, plus an independent
monitor thread. Forks and all shared simulation state are protected by mutexes to
prevent race conditions.

## Instructions

### Compilation

```bash
make
```

### Usage

```bash
./philo <num_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [must_eat]
```

All time values are in **milliseconds**. The `must_eat` argument is optional:
if provided, the simulation stops once every philosopher has eaten that many times.

### Examples

| Command | Expected result |
|---|---|
| `./philo 1 800 200 200` | The philosopher dies (~800 ms) |
| `./philo 5 800 200 200` | No one dies, runs indefinitely |
| `./philo 4 410 200 200` | No one dies (10 ms margin) |
| `./philo 5 800 200 200 7` | Stops after every philosopher eats 7 times |
| `./philo 4 310 200 100` | A philosopher dies (~310 ms) |

### Quick Validation Rule

- `time_to_eat + time_to_sleep < time_to_die` → no philosopher should die
- `time_to_eat + time_to_sleep >= time_to_die` → a philosopher will die

## Resources

### References

- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — LLNL HPC](https://hpc-tutorials.llnl.gov/posix/)
- [`pthread_mutex_lock` — Linux man pages](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [Philosophers 42 Guide — The Dining Philosophers Problem] (https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
- [42-cursus.gitbook.io - Philosophers] (https://42-cursus.gitbook.io/guide/3-rank-03/philosophers)
- [fran byte | 42 - Introducción al Proyecto Philosophers] (https://42-fran-byte-f94097.gitlab.io/docs/philosophers/philosophers-approach-es/#/)

### AI Usage

**Tool used:** Perplexity AI, as a pedagogical assistant.

| Area | Tasks where AI was used |
|---|---|
| Problem understanding | Explanation of the dining philosophers problem, difference between deadlock and data race, need for mutexes |
| Logical design | Thread structure (N philosophers + monitor + main), `philosopher()` flow, monitor logic |
| Debugging | Bug in `check_death` (timestamp comparison and `last_meal` update), `meals_eaten` overshoot, Norminette errors |
| Testing | Design of a test suite for correct death timing, no-deadlock cases, and `must_eat` termination |
| Key functions | Understanding of `ft_usleep`, `get_time`, and mutex patterns protecting `stop`, `last_meal`, and `meals_eaten` |

AI did not write any project code. Its use was strictly explanatory and for logical
guidance to understand the concepts involved.