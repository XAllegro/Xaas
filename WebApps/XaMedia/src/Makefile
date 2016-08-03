##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

BIN_NAME=XaMedia.cgi

##WINDOWS CYGWIN
ifeq ($(filter CYGWIN_NT-%.%,$(UNAME_S)),)
    include Makefile_Win.mk
endif

## LINUX
ifeq ($(UNAME_S),Linux)
   include Makefile_Linux.mk
endif

##DARWIN
ifeq ($(UNAME_S),Darwin)
    include Makefile_Mac.mk
endif

#Media OBJ
OBJ=$(OBJDIR)Controller.o \
    $(OBJDIR)XaMedia.o $(OBJDIR)XaMediaData.o

#MACROS
.PHONY: all all-before all-after clean print-varialbes
all:print-varialbes $(BIN) #all-after

clean:
	${RM} $(OBJ) print-varialbes $(BIN)
all-before:
	${RM} $(OBJ)
all-after:
	${RM} $(OBJ)

print-varialbes:
	@echo "I am compiling on : " $(UNAME_P) $(UNAME_S) $(OS) $(PROCESSOR_ARCHITECTURE) $(CASE)

#LINK
    $(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(XALIB) $(LIBS)

#COMPILE
$(OBJDIR)Controller.o: Controller.cpp
	$(CPP) -c Controller.cpp -o $(OBJDIR)Controller.o $(CPPFLAGS)
$(OBJDIR)XaMedia.o: XaMedia.cpp
	$(CPP) -c XaMedia.cpp -o $(OBJDIR)XaMedia.o $(CPPFLAGS)
$(OBJDIR)XaMediaData.o: XaMediaData.cpp
	$(CPP) -c XaMediaData.cpp -o $(OBJDIR)XaMediaData.o $(CPPFLAGS)
