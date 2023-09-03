TARGETS := main.o net/unix/driver.o

%.o: %.c
	cc -O2 -c $^ -o $@

main: $(TARGETS)
	cc $(TARGETS) -o main.elf
