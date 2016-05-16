test: main analyze.py
	./main > results.txt
	python analyze.py

main: main.o sincos.o

sincos.o: sincos.c
