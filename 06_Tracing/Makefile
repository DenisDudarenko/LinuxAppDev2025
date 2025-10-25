GENERATES = move libprotect.so *.so
TRASH = *.o *~ o.* *.txt *.err reference.txt 

.PHONY: all clean test

all: move libprotect.so

move: move.c
	cc -O0 -g $< -o $@

libprotect.so: save.c
	cc -shared $< -o $@

clean:
	rm -rf $(GENERATES)
	rm -rf $(TRASH)

test: move libprotect.so
	cal > reference.txt

	@echo "=== Start Test0: success ==="
	@cp reference.txt input.txt
	@./move input.txt output.txt 2>/dev/null ; res=$$? ; [ $$res -eq 0 ]
	@[ ! -f input.txt ]
	@cmp reference.txt output.txt
	@echo "Test0 Passed"

	@echo "=== Start Test1: incorrect args ==="
	@./move input.txt 2>/dev/null || res=$$? ; [ $$res -eq 1 ] ;
	@echo "Test1 Passed"

	@echo "=== Start Test2: open input fail ==="
	@cp reference.txt input.txt
	@strace -o /dev/null -e fault=openat -P input.txt ./move input.txt output.txt 2>/dev/null || res=$$? ; [ $$res -eq 2 ] ;
	@[ -f input.txt ]
	@echo "Test2 Passed"

	@echo "=== Start Test3: open output fail ==="
	@cp reference.txt input.txt 
	@strace -o /dev/null -e fault=openat -P output.txt ./move input.txt output.txt 2>/dev/null || res=$$? ; [ $$res -eq 3 ] ;
	@[ -f input.txt ]
	@echo "Test3 Passed"

	@echo "=== Start Test4: read fail ===" 
	@cp reference.txt input.txt 
	@strace -o /dev/null -e fault=read:error=EIO:when=1 -y -P input.txt ./move input.txt output.txt 2>/dev/null || res=$$? ; [ $$res -eq 5 ] ;
	@[ -f input.txt ]
	@echo "Test4 Passed"

	@echo "=== Start Test5: write fail ===" 
	@cp reference.txt input.txt 
	@strace -o /dev/null -e fault=write ./move input.txt output.txt 2>/dev/null || res=$$? ; [ $$res -eq 4 ] ;
	@[ -f input.txt ]
	@echo "Test5 Passed"

	@echo "=== Start Test6: fclose(in) fail ===" 
	@cp reference.txt input.txt 
	@strace -o /dev/null -e fault=close:when=3 ./move input.txt output.txt 2>/dev/null || res=$$? ; [ $$res -eq 6 ] 
	@[ -f input.txt ]
	@echo "Test6 Passed"
	
	@echo "=== Start Test7: fclose(out) fail ===" 
	@cp reference.txt input.txt 
	@strace -o /dev/null -e fault=close:error=EIO:when=4 ./move input.txt output.txt 2>/dev/null || res=$$? ; [ $$res -eq 7 ] 
	@[ -f input.txt ]
	@echo "Test7 Passed"

	@echo "=== Start Test8: unlink fail ===" 
	@cp reference.txt input.txt 
	@strace -o /dev/null -e fault=unlink:when=1 ./move input.txt output.txt 2>err.txt || res=$$? ; [ $$res -eq 8 ] 
	@[ -f input.txt ]
	@echo "Test8 Passed"
	
	@echo "=== Start Test9: LD_PRELOAD ==="
	@cp reference.txt input_PROTECT.txt
	@LD_PRELOAD=./libprotect.so ./move input_PROTECT.txt output.txt ; res=$$? ; [ $$res -eq 0 ]
	@[ -f input.txt ]
	@[ -f output.txt ]
	@echo "Test9 Passed"

	@echo "=== ALL TESTS PASSED ==="