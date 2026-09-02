all: main
	g++ main.cpp -o main

test:
	rm test
	g++ test.cpp -o test
	./test

clean:
	rm main
	rm test