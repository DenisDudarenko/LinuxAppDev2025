GENERATES = esub
TRASH = *.o *~ o.* *.txt

all: esub

esub: esub.c
	cc -O0 -g $< -o $@

clean:
	rm -rf $(GENERATES)
	rm -f $(TRASH)

reference:
	echo 'Learn regular expressions!' | sed -E 's/(regular) (express)ion(s?)/to \2 emotion\3 \1ly/' > reference.txt

test: esub reference
	echo "Test 1"
	./esub '(regular) (express)ion(s?)' 'to \2 emotion\3 \1ly' 'Learn regular expressions!' | cmp reference.txt
	echo "Test passed"
