GENERATES = prog README prog-a prog-so liboutput* outfile*
TRASH = *.o *~ o.*

all: README prog prog-a prog-so

prog: const.o fun.o prog.o

README: prog
	./$< 2> $@

%.o:    %.c
	cc -fPIC -c $< -o $@

fun.o: outlib.h

prog-so: prog.o liboutput.so
	cc -o $@ $^ -L. -loutput

liboutput.so: const.o fun.o
	cc -shared $^ -o $@

prog-a: prog.o liboutput_static.a
	cc -L. $^ -o $@

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

clean:
	rm -rf $(GENERATES)
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

test: prog prog-a prog-so
	./prog > outfile11 2>&1
	./prog test1 > outfile12 2>&1
	./prog test1 test3> outfile13 2>&1
	./prog-a > outfile21 2>&1
	./prog-a test1 > outfile22 2>&1
	./prog-a test1 test3> outfile23 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > outfile31 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so test1 > outfile32 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so test1 test3> outfile33 2>&1
	cmp outfile11 outfile21
	cmp outfile12 outfile22
	cmp outfile13 outfile23
	cmp outfile11 outfile31
	cmp outfile12 outfile32
	cmp outfile13 outfile33
