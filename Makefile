all:
	gcc utils.c -lm -o utils

clean:
	rm -f utils *.txt