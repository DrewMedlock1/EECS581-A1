all: main
	g++ main.cpp -o main

test:
	g++ test.cpp -o test
	./test

clean:
	rm main