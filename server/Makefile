TARGETS := main.o net/unix/driver.o
.PHONY: clean

%.o: %.c
	cc -O2 -c $^ -o $@

main: $(TARGETS)
	cc $(TARGETS) -o main.elf

clean:
	@rm main.elf 2> /dev/null
	@find . -name '*.o' -delete
