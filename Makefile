CFLAGS=-std=c++11 -g
LDFLAGS=-g
CXX=g++


all: main test.bin

test.bin: test.src mkbin
	@echo -e '\e[33mBUILDING \e[96m$@\e[m \e[33mFROM \e[94m$<\e[m'
	@./mkbin
	@echo -e -n "\e[m"

main: main.o instable.o emucore.o | utypes.hpp
	@echo -e '\e[33mLINKING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(LDFLAGS) $^ -o $@
	@echo -e -n "\e[m"

main.o: main.cpp
	@echo -e '\e[33mCOMPILING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo -e -n "\e[m"

instable.o: InsTable.cpp InsTable.hpp
	@echo -e '\e[33mCOMPILING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo -e -n "\e[m"

emucore.o: EmuCore.cpp EmuCore.hpp
	@echo -e '\e[33mCOMPILING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo -e -n "\e[m"

clean:
	rm -f *.o *~ test.bin

clobber: clean
	rm -f main
