# DEVS Engine — min-heap event scheduler

![Languages](https://img.shields.io/github/languages/top/Exclusioning/DEVS-Engine-w-min-heap) ![License](https://img.shields.io/github/license/Exclusioning/DEVS-Engine-w-min-heap)

A small C++ Discrete Event System Specification (DEVS) engine that demonstrates an event-driven scheduler using a min-heap priority queue. It models a network of atomic "Action" components (for example, OreMining, Forge, and Crafting) and runs simulations driven by events.

## Why this project is useful

- Minimal, easy-to-read implementation of core DEVS concepts, including atomic models and discrete-event scheduling.
- Compact min-heap implementation for event ordering, making it a useful teaching and reference example.
- Suitable as a starting point for simulation work, academic projects, or experiments with event-driven systems in C++.

## Project structure

```text
Action.h         Atomic action model with process timing and state transitions
Action.cpp       Empty implementation file
AtomicModel.h    Abstract DEVS atomic-model interface
Event.h          Event structure with time, model, type, and quantity
EventType.h      INTERNAL / EXTERNAL / CONFLUENT event types
Heap.h           Generic min-heap implementation used as the event queue
Network.h/.cpp   Network model that connects actions and injects inputs
Scheduler.h/.cpp Scheduler loop and time management using the heap
TimeMoment.h     Time representation and ordering logic
main.cpp         Demo CLI application for the BlackSmith Network
README.md        Project overview and quickstart instructions
```

## What this project does

This repository implements a basic DEVS-style simulation engine in C++:

- Atomic models are represented by `Action` objects, derived from `AtomicModel`.
- Events are scheduled and ordered in time using a min-heap (`Heap.h`).
- The `Scheduler` executes the simulation up to a requested time and produces outputs such as completed actions in the demo.

## Quickstart

### Prerequisites

- A C++ compiler with C++17 support (for example, `g++` or `clang++)
- Standard build tools available on the system

### Build

From the project root, compile the project with:

```bash
g++ -std=c++17 *.cpp -o devs_engine
```

### Run

```bash
./devs_engine
```

The program prompts for input in this form:

```text
Enter <Time>, <Quantity of Ore/Wood>
-1 -1 to quit.
```

Example:

```text
10 5
```

This runs the simulation for time 10 and injects a quantity of 5 into the network.

## How it works

- External input enters the network and is passed to the scheduler.
- The scheduler stores future events in a min-heap keyed by time.
- The next event is always extracted in chronological order.
- `Action` instances react according to the DEVS lifecycle:
  - `deltaInt()` for internal events
  - `deltaExt()` for external events
  - `deltaCon()` for simultaneous internal/external events
- `timeAdvance()` determines when the model should fire next.

## Key code notes

- `AtomicModel.h` defines the required DEVS interface:
  - `lambda()`
  - `deltaInt()`
  - `deltaExt(int input, double elapsedTime)`
  - `deltaCon(int input)`
  - `timeAdvance()`
- `Action.h` implements the behavior for a single processing step with state such as `partsProcessing` and `timeRemaining`.
- `Heap.h` implements the generic priority queue used for ordered event handling.
- `main.cpp` provides the BlackSmith demo and shows the simulation loop in use.

## Example behavior

The example application creates actions such as:

- OreMining
- Forge
- Cutting Wood
- Crafting
- Market
- Shop Storage

It then simulates a production flow and reports how many finished items were produced and the cumulative profit.

## Where to get help

- Review the source files in the repository for implementation details:
  - `main.cpp`
  - `Scheduler.h` and `Scheduler.cpp`
  - `Network.h` and `Network.cpp`
  - `Heap.h`
  - `Action.h`
- Open an issue in this repository for bug reports, questions, or feature requests.

## Contributing

Contributions are welcome. Please keep changes focused and well-scoped.

Typical workflow:

1. Fork the repository.
2. Create a feature branch.
3. Make a narrow, well-tested change.
4. Open a pull request with a clear description of the fix or enhancement.

## Maintainers

This project is maintained by the repository owner, `Exclusioning`.

## License

See the `LICENSE` file in the repository for licensing details.
