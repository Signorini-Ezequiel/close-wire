TARGETS := main.o net/unix/driver.c

%.o: %.c
	cc -O2 -c $^ -o $@

main: $(TARGETS)
	cc $(TARGETS) -o main
