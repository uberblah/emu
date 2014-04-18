BINS=main hex2bin bin2hex
CYGBINS=main.exe hex2bin.exe bin2hex.exe
OMAIN=main.o util.o core.o mem.o jump.o math.o bits.o sys.o debug.o bin.o
OHEX2BIN=hex2bin.o util.o bin.o
OBIN2HEX=bin2hex.o util.o bin.o 
CFLAGS=-O3
LDFLAGS=-O3

all: $(BINS)

main: $(OMAIN)
	@echo -e '\e[33mLINKING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(LDFLAGS) $^ -o $@
	@echo -e -n "\e[m"

hex2bin: $(OHEX2BIN)
	@echo -e '\e[33mLINKING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(LDFLAGS) $^ -o $@
	@echo -e -n "\e[m"

bin2hex: $(OBIN2HEX)
	@echo -e '\e[33mLINKING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(LDFLAGS) $^ -o $@
	@echo -e -n "\e[m"

%.o:%.cpp
	@echo -e '\e[33mCOMPILING \e[96m$@\e[m \e[33mFROM \e[94m$^\e[m'
	@$(CXX) $(CFLAGS) -c $< -o $@
	@echo -e -n "\e[m"

clean:
	@echo -e '\e[33mCLEANING...\e[m'
	@rm -f -v *.o *~ $(BINS) $(CYGBINS)

