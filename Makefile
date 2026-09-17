# All: main was written by me
all: main
	g++ main.cpp -o main

# Test is mixed between me and Google Gemini 3.8 from prompts 2 & 3
.PHONY: test
test:
	rm -f test # Adding a rm with a -f will always remove the file first
	g++ -DTESTING main.cpp test.cpp -o test # The -DTESTING flag will pass along the info that testing is defined, for preprocessor guards
	./test

# Clean is mixed between me and Google Gemini 3.8, as it helped me realized to add the .PHONY and -f flag in prompt 4.
.PHONY: clean
clean:
	rm -f main
	rm -f test