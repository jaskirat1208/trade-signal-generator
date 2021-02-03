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