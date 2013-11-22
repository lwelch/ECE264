GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS = 
SOURCES	= answer06.c pa05.c

.DEFAULT_GOAL := build

build: pa06

test: test1 test2 test3 test4 test5 test6

test1: pa06
	@./pa06 images/01-unnormalized-smile.ee264  outputs/output01
	@diff outputs/output01 expected/01-smile.ppm
	@echo ""
	@echo "test 1 case okay"
	@valgrind --leak-check=full --verbose --log-file=valgrind/valgrindlog1 ./pa06 images/01-unnormalized-smile.ee264 valgrind/valout1
	@echo "Valgrind Okay!"
	@echo ""

test2: pa06
	@./pa06 images/02-unnormalized-cat-chess.ee264  outputs/output02
	@diff outputs/output02 expected/02-cat-chess.ppm
	@echo ""
	@echo "test 2 case okay"
	@valgrind --leak-check=full --verbose --log-file=valgrind/valgrindlog1 ./pa06 images/02-unnormalized-cat-chess.ee264  valgrind/valout2
	@echo "Valgrind Okay!"
	@echo ""

test3: pa06
	@./pa06 images/03-unnormalized-hawkes-bay-NZ.ee264  outputs/output03
	@diff outputs/output03 expected/03-hawkes-bay-NZ.ppm
	@echo ""
	@echo "test 3 case okay"
	@valgrind --leak-check=full --verbose --log-file=valgrind/valgrindlog1 ./pa06 images/03-unnormalized-hawkes-bay-NZ.ee264  valgrind/valout3
	@echo "Valgrind Okay!"
	@echo ""

test4: pa06
	@./pa06 images/04-unnormalized-nelsonmandela.ee264  outputs/output04
	@diff outputs/output04 expected/04-nelsonmandela.ppm
	@echo ""
	@echo "test 4 case okay"
	@valgrind --leak-check=full --verbose --log-file=valgrind/valgrindlog1 ./pa06 images/04-unnormalized-nelsonmandela.ee264 valgrind/valout
	@echo "Valgrind Okay!"
	@echo ""

test5: pa06
	@./pa06 images/05-unnormalized-sagan-stamp.ee264  outputs/output05
	@diff outputs/output05 expected/05-sagan-stamp.ppm
	@echo ""
	@echo "test 5 case okay"
	@valgrind --leak-check=full --verbose --log-file=valgrind/valgrindlog1 ./pa06 images/05-unnormalized-sagan-stamp.ee264 valgrind/valout
	@echo "Valgrind Okay!"
	@echo ""

test6: pa06
	@./pa06 images/corrupt-testcases/bad-comment-len.ee264  outputs/output06
	@echo ""
	@echo "test case okay"
	@echo ""
	@diff outputs/output01 expected/01-smile.ppm
	@valgrind --leak-check=full --verbose --log-file=valgrind/valgrindlog1 ./pa06 images/corrupt-testcases/bad-comment-len.ee26 valgrind/valout6


environment:
	@cd $(CURDIR)
	@mkdir -p outputs
	@mkdir -p obj

pa06: answer06.o pa06.o | environment
	$(GCC) $(CFLAGS) pa06.o answer06.o -o pa06

pa06.o: pa06.c pa06.h | environment
	$(GCC)$(CFLAGS) -c pa06.c

answer06.o: answer06.c pa06.h | environment
	$(GCC) $(CFLAGS) -c answer06.c

clean:
	@cd $(CURDIR)
	rm -rf pa06 obj outputs
