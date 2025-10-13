GENERATES = range
TRASH = *.o *~ o.*

all: range

range: range.c
		cc -O0 -g $< -o $@

clean:
		rm -rf $(GENERATES)
		rm -f $(TRASH)

test: range
		echo "Test 1"
		gdb -q -nx -batch -x script1.gdb range | grep '@@@' | cmp correct_answer1.txt 
		echo "Test 2"
		gdb -q -nx -batch -x script2.gdb range | grep '@@@' | cmp correct_answer2.txt 
