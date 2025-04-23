# Philosopher Simulation

## Overview

This is a simulation of the classic "Dining Philosophers" problem, which illustrates the challenges of resource sharing and synchronization in concurrent programming.
This simulation makes use of `pthreads` to create multiple threads representing philosophers, each of whom needs to acquire two forks (resources) to eat, while only having one.
To achieve this, the simulation uses a mutex lock to ensure that only one philosopher can access a fork at a time.

## Requirements

- C compiler (here Clang is used)
- the `pthreads` library
- `make` (optional, for building the project)
- `mold` (optional, for faster linking)
- `valgrind` (optional, for memory leak detection)

## Compilation

To compile the project, you can use the provided `Makefile`. Simply run:

```bash
make
```

This will create an executable named `philo`.

To compile the 'bonus' version of the project, which includes the `philo_bonus` executable, run:

```bash
make bonus
```

This will create an additional executable named `philo_bonus`.

To compile the project with `mold` for faster linking, simply install `mold`, and the
Makefile will automatically use it for linking. You can check if `mold` is installed by running:

```bash
mold --version
```

If `mold` is not installed, the Makefile will fall back to the default linker,
which is usually `ld`. You can install `mold` using your package manager. For example, on Ubuntu, you can run:

```bash
sudo apt install mold
```

## Usage

To run the simulation, use the following command:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

In which:

- `number_of_philosophers`: The number of philosophers (and forks) in the simulation.
- `time_to_die`: The time in milliseconds that a philosopher can go without eating before they die.
- `time_to_eat`: The time in milliseconds that a philosopher takes to eat.
- `time_to_sleep`: The time in milliseconds that a philosopher takes to sleep.
- `number_of_times_each_philosopher_must_eat`: `OPTIONAL`: The number of times each philosopher must eat before the simulation ends. If not provided, the simulation will run indefinitely until a philosopher dies.

### Examples

```bash
./philo 5 800 200 200
```

This will create a simulation with 5 philosophers, where each philosopher can go 800 milliseconds without eating before they die, and takes 200 milliseconds to eat and sleep.

```bash
./philo 5 800 200 200 7
```

This will create a simulation with 5 philosophers, where each philosopher can go 800 milliseconds without eating before they die, and takes 200 milliseconds to eat and sleep. Each philosopher must eat 7 times before the simulation ends.

```bash
./philo_bonus 5 800 200 200
```

This will create a simulation with 5 philosophers, where each philosopher can go 800 milliseconds without eating before they die, and takes 200 milliseconds to eat and sleep. Each philosopher must eat 7 times before the simulation ends.

```bash
./philo_bonus 5 800 200 200 7
```

This will create a simulation with 5 philosophers, where each philosopher can go 800 milliseconds without eating before they die, and takes 200 milliseconds to eat and sleep. Each philosopher must eat 7 times before the simulation ends.

## Memory Leak Detection

To check for memory leaks, you can use `valgrind`. Run the simulation with `valgrind` like this:

```bash
valgrind --leak-check=full ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

This will run the simulation under `valgrind` and check for memory leaks. If there are any memory leaks, `valgrind` will report them in the output.

## Licence

This project uses both the MIT and Apache 2.0 licences,
you may choose which one you prefer based on your needs.

## Licence Information

This project is dual-licensed under both MIT and Apache 2.0 licence. Choose the one that better suits your needs.

### MIT Licence

**Description:** A permissive licence with very few restrictions.

✅ **Permissions:**

- Commercial use
- Modification
- Distribution
- Private use

📋 **Conditions:**

- Licence and copyright notice must be included

⚠️ **Limitations:**

- No liability
- No warranty

### Apache Licence 2.0

**Description:** A permissive licence similar to MIT but with additional protections.

✅ **Permissions:**

- Commercial use
- Modification
- Distribution
- Patent use
- Private use

📋 **Conditions:**

- Licence and copyright notice must be included
- Changes must be documented

⚠️ **Limitations:**

- Trademark use not granted
- No liability
- No warranty

