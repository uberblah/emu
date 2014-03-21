
OBJECTS=main.o util.o core.o mem.o jump.o math.o bits.o sys.o debug.o bin.o
CFLAGS=-g
LDFLAGS=-g

main: $(OBJECTS)
	@echo -e '\e[33mLINKING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(LDFLAGS) $^ -o $@
	@echo -e -n "\e[m"

%.o:%.cpp
	@echo -e '\e[33mCOMPILING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo -e -n "\e[m"

clean:
	@echo -e '\e[33mCLEANING...\e[m'
	@rm -f -v $(OBJECTS) *~

clobber: clean
	@echo -e '\e[33mCLOBBERING...\e[m'
	@rm -f -v main

