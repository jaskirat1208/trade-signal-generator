# Stock Trade signal generator

Given the stock price information at various intervals, groups it into bars of fixed length, say 1 minute, and generates buy/sell signals based on fast and slow SMA crossovers. 

Usage: 

- Compile the program:

```bash
./build.sh
```

- Run

```bash
cd build/strategy/test
./strategy_test
```

## Overview

The program consists mainly of three different parts:

- Event Loop: Main engine which keeps the program running
- Platform: A publisher subscriber based architecture. Currently reads the feed information from a file and publishes a feed event. Contains APIs to add subscribers to the feed event.
- Strategy: 


### Event loop

- Main engine. Keeps the platofrm running. Contains APIs for  onStart, onStop, onTerminate, onUpdate.

### Platform

- A publisher subscriber based architecture.
- Currently reads the feed information from a file and publishes a feed event after a successful read.
- Contains APIs to add subscribers to feed event.
- Terminates the engine once the entire feed is read.

### Strategy

- A simple trading strategy.
- Groups the interval into bars and computes rolling moving average(slow and fast).
- Buys and sells orders on crossover.
