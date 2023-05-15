# Multiprocessor Process Scheduler in C++

This project is a simulation of a process scheduler for a multiprocessor system. The program uses C++ to implement a process scheduler that can handle multiple processes running on multiple processors. The program also calculates various statistics related to the scheduling system to help improve its overall performance.

## Dependencies

This project requires the following dependencies to be installed:

- C++ Compiler (GCC or Clang)
- CMake

## Installation

To install the project, follow these steps:

1. Clone the repository: `git clone https://github.com/your-username/multiprocessor-process-scheduler.git`
2. Navigate to the project directory: `cd multiprocessor-process-scheduler`
3. Create a build directory: `mkdir build && cd build`
4. Run CMake to generate the build files: `cmake ..`
5. Build the project: `make`

## Usage

To use the program, specify in an input file the following:

```
```

- `<number_of_processors>`: The number of processors in the system.
- `<number_of_processes>`: The number of processes to be scheduled.
- `<Arrival Time>`: The arrival time for each process
- `<CT>`: The CPU time for each process
- `<N>`: The number of IO requests for each process

The program will simulate the operation of the process scheduler for the given parameters and output the following statistics:

- Average waiting time for each process
- Average turnaround time for each process
- CPU utilization
- CPU Load

## Contributing

Contributions to the project are welcome! If you find a bug or want to add a feature, please create an issue or submit a pull request.

