%.out: %.o
	gcc -no-pie -o $@ $<

%.o: %.asm
	nasm -f elf64 $<

%.asm: %.c
	../bin/scc $<

%.o: %.c

clean:
	-rm -f *.o *.out *~
