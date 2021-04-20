######################################
#
# Top level Makefile for controlling
# sub-makefiles
#
######################################

.PHONY: clean tests messages ring all

all:
	@make messages
	@make ring
	@make tests
	@make clean

messages:
	@cd bin && make messages

ring:
	@cd bin && make ring

tests:
	@cd tests && make all

clean:
	rm -f src/*.o src/nodes/*.o src/paxos/*.o src/sys/*.o


