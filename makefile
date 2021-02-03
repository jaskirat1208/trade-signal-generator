all:
	mkdir -p ./bin
	g++ src/main.cpp -o ./bin/signal_generator

generate_data:
	mkdir -p ./data
	python3 market_data_generator.py --file_path ./data/input.txt

clean: 
	rm -rf bin
	rm -rf data