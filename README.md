# trade-signal-generator
Given the stock price information at various intervals, groups it into bars of fixed length, say 1 minute, and generates buy/sell signals based on fast and slow SMA. 

Usage: 

- Generate stock price data: 
```bash
make generate_data
```
- Compile the program:
```bash
make
```
- Execute the program
```bash
./bin/signal_generator <market_data_file> <output_file>
```

### Overview:
The program consists mainly of two different parts:
- A data parser that reads the data from input file and converts it into several segments of length 1 minute
- A signal generator that computes the fast and slow simple moving averages and outputs a buy/sell signal on crossover. The signal generated depends on the direction of the crossover.

### Implementation details
Everything could have done in one step, however, due to the given problem statement, the number of bars was not very high and could easily fit into memory. So, in order to have a better code quality, I split the process into two different components as described in the overview.

#### Data Parser:
- Reads the file line by line, parses the timestamp and stock price from the file given as a `Time` object as described in utils.h. Initialize starting Timestamp to (-1, -1, -1)
- At every readline, get the current timestamp and price. If current timestamp and starting timestamp belong to the same interval, update the closing prices, high and low prices.
- If the current and starting timestamp are in different intervals, add the previous interval data to the result.
- If they do not belong to same interval, create a new interval and update the starting point of the interval. Update open price = current price.
- Finally, once you are done reading the file, close the file, add the last interval data to the result and output the result vector.

#### Signal generator:
- Iterate over the interval data to compute the rolling moving average. 
- Keep a track of the fast and slow moving sums, and later divide by the size to get the correct Moving average
- When crossover happens, i.e, just when fast moving average crosses the slow moving average, it will generate a buy signal, indicating that the stock prices are likely to appreciate in the near future, and vice versa.
- If the fast moving average stoops below the slow moving average, it will generate a sell signal, indicating that the stock prices are likely to depreciate, so, sell the stocks in order to avoid the potential loss, or maybe do a short selling to hope for a profit.
