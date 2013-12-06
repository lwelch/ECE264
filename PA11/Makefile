GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = answer11.o pa11.o
HDRS = pa11.h
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

pa11: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f pa10 $(OBJS) outputs/*

test: | test01 test02 test03 test04 test05 test06 test07 test08 test09 test10 

environment:
	@cd $(CURDIR)
	@mkdir -p outputs

test01: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput1 ./pa10 sort 321

test02: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput2 ./pa10 shapes 1 > outputs/output2
	@$ diff -w expected/shapes-1 outputs/output2

test03: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 2 > outputs/output3
	@$ diff -w expected/shapes-2 outputs/output3

test04: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 3 > outputs/output3
	@$ diff -w expected/shapes-3 outputs/output3

test05: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 4 > outputs/output3
	@$ diff -w expected/shapes-4 outputs/output3

test06: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 5 > outputs/output3
	@$ diff -w expected/shapes-5 outputs/output3

test07: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 6 > outputs/output3
	@$ diff -w expected/shapes-6 outputs/output3

test08: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 7 > outputs/output3
	@$ diff -w expected/shapes-7 outputs/output3

test09: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 8 > outputs/output3
	@$ diff -w expected/shapes-8 outputs/output3

test10: pa10 | environment
	@$(VALGRIND) --log-file=outputs/intmemoutput3 ./pa10 shapes 9 > outputs/output3
	@$ diff -w expected/shapes-9 outputs/output3
