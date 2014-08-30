# Resumable Prime Finder for up to 64 bit numbers.
resumable-prime-finder: resumable-prime-finder.c
	gcc resumable-prime-finder.c -o resumable-prime-finder

# LargeUInt rules.
large-u-int-test: large-u-int.o large-u-int-test.o
	gcc large-u-int.o large-u-int-test.o -o large-u-int-test

large-u-int-test.o: large-u-int-test.c large-u-int.h
	gcc -c large-u-int-test.c

# Resumable Prime Finder supporting large unsigned integers.
large-u-int-resumable-prime-finder: large-u-int-resumable-prime-finder.o large-u-int.o
	gcc large-u-int-resumable-prime-finder.o large-u-int.o -o large-u-int-resumable-prime-finder

large-u-int-resumable-prime-finder.o: large-u-int-resumable-prime-finder.c large-u-int.h
	gcc -c large-u-int-resumable-prime-finder.c

large-u-int.o: large-u-int.c large-u-int.h
	gcc -c large-u-int.c

clean:
	rm *.o large-u-int-test resumable-prime-finder large-u-int-resumable-prime-finder
