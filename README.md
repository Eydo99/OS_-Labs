# OS Labs — Operating Systems Course

A collection of Operating Systems labs covering core OS concepts including process scheduling, inter-process communication, multithreading, synchronization, and distributed systems.

Each lab is an independent repository linked here as a Git submodule.

---

## Labs Overview

| Lab | Topic | Language | Key Concepts |
|-----|-------|----------|-------------|
| [Lab 1](#lab-1--simple-unix-shell) | Simple Unix Shell | C | `fork`, `execvp`, signals, environment variables |
| [Lab 2](#lab-2--multithreaded-matrix-multiplication) | Multithreaded Matrix Multiplication | C | `pthreads`, performance comparison |
| [Lab 3](#lab-3--caltrain-thread-synchronization) | Caltrain Thread Synchronization | C | Mutex, condition variables, deadlock avoidance |
| [Lab 4](#lab-4--custom-cpu-scheduler) | Custom CPU Scheduler | C | IPC, POSIX MQ, virtual time, FCFS/RR/HPF |
| [Project](#project--redlock-distributed-locking) | Redlock Distributed Locking | Python | Distributed systems, Redis, quorum consensus |

---

## Lab 1 — Simple Unix Shell

A custom Unix shell supporting built-in commands, external program execution, background processes, and environment variables.

**Key features:**
- Built-ins: `cd`, `echo`, `export`, `exit`
- Background execution with `&`
- Environment variable definition (`export KEY=VALUE`) and expansion (`$KEY`)
- `SIGCHLD` handler to reap zombie background processes

```bash
gcc -o shell simpleShell.c
./shell
```

---

## Lab 2 — Multithreaded Matrix Multiplication

Matrix multiplication implemented with three threading strategies and benchmarked using `gettimeofday()`.

**Strategies:**
- **Per Matrix** — 1 thread (baseline)
- **Per Row** — 1 thread per row
- **Per Element** — 1 thread per output element

```bash
gcc -o matMultp matMultp.c -lpthread
./matMultp a b c        # reads a.txt, b.txt → writes c_per_*.txt
```

---

## Lab 3 — Caltrain Thread Synchronization

Classic thread synchronization problem: passengers board a train only when seats are available, and the train waits until all boarding is complete.

**Key concepts:**
- POSIX mutex and condition variables
- Producer-consumer synchronization pattern
- Stress tested over 1000 runs

```bash
gcc -o caltrain caltrain_runner.c caltrain.c -lpthread
./caltrain
```

---

## Lab 4 — Custom CPU Scheduler

A deterministic OS process scheduler simulation using Virtual Time, POSIX Message Queues for IPC, and UNIX signals for process control.

**Algorithms implemented:**
- FCFS (First Come First Serve)
- Round Robin with configurable quantum
- HPF (Highest Priority First)

```bash
make
./runner.sh --all
```

**Results on sample input:**

| Algorithm | CPU Util | Avg TAT | Avg WT |
|-----------|---------|---------|--------|
| FCFS | 93.33% | 5.75 | 2.25 |
| RR (Q=3) | 93.33% | 6.25 | 2.75 |
| HPF | 93.33% | 6.00 | 2.50 |

---

## Project — Redlock Distributed Locking

A simulation of the Redlock distributed mutual exclusion algorithm across 5 independent Redis nodes running in Docker.

**Key concepts:**
- Distributed locking with quorum consensus (≥3/5 nodes)
- Atomic lock release via Lua scripting
- 5 concurrent client processes competing for a shared resource

```bash
docker-compose up -d
pip install -r requirements.txt
python3 redlock_simulation.py
```

---

## Cloning

To clone this repo with all submodules:

```bash
git clone --recurse-submodules <repo-url>
```

If you already cloned without submodules:
```bash
git submodule update --init --recursive
```

---

## Concepts Covered

- Process creation and management (`fork`, `exec`, `wait`)
- Inter-Process Communication (POSIX Message Queues, signals)
- Multithreading (`pthreads`, mutexes, condition variables)
- CPU Scheduling algorithms (FCFS, Round Robin, HPF)
- Virtual time simulation
- Distributed systems and consensus protocols
