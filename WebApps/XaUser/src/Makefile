##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

BIN_NAME=XaUser.cgi

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

#User OBJ
OBJ=$(OBJDIR)Controller.o $(OBJDIR)XaUserRole.o \
    $(OBJDIR)XaOu.o $(OBJDIR)XaOuType.o $(OBJDIR)XaUser.o \
    $(OBJDIR)XaUserAddressGeo.o $(OBJDIR)XaUserAddressGeoType.o \
    $(OBJDIR)XaUserAddressMail.o $(OBJDIR)XaUserAddressMailType.o \
    $(OBJDIR)XaUserAddressPhone.o $(OBJDIR)XaUserAddressPhoneCode.o $(OBJDIR)XaUserAddressPhoneType.o

#MACROS
.PHONY: all all-before all-after clean print-varialbes
all:print-varialbes $(BIN) all-after

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
$(OBJDIR)XaUserRole.o: XaUserRole.cpp
	$(CPP) -c XaUserRole.cpp -o $(OBJDIR)XaUserRole.o $(CPPFLAGS)
$(OBJDIR)XaOuType.o: XaOuType.cpp
	$(CPP) -c XaOuType.cpp -o $(OBJDIR)XaOuType.o $(CPPFLAGS)
$(OBJDIR)XaOu.o: XaOu.cpp
	$(CPP) -c XaOu.cpp -o $(OBJDIR)XaOu.o $(CPPFLAGS)
$(OBJDIR)XaUser.o: XaUser.cpp
	$(CPP) -c XaUser.cpp -o $(OBJDIR)XaUser.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressGeo.o: XaUserAddressGeo.cpp
	$(CPP) -c XaUserAddressGeo.cpp -o $(OBJDIR)XaUserAddressGeo.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressGeoType.o: XaUserAddressGeoType.cpp
	$(CPP) -c XaUserAddressGeoType.cpp -o $(OBJDIR)XaUserAddressGeoType.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressMail.o: XaUserAddressMail.cpp
	$(CPP) -c XaUserAddressMail.cpp -o $(OBJDIR)XaUserAddressMail.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressMailType.o: XaUserAddressMailType.cpp
	$(CPP) -c XaUserAddressMailType.cpp -o $(OBJDIR)XaUserAddressMailType.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressPhone.o: XaUserAddressPhone.cpp
	$(CPP) -c XaUserAddressPhone.cpp -o $(OBJDIR)XaUserAddressPhone.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressPhoneCode.o: XaUserAddressPhoneCode.cpp
	$(CPP) -c XaUserAddressPhoneCode.cpp -o $(OBJDIR)XaUserAddressPhoneCode.o $(CPPFLAGS)
$(OBJDIR)XaUserAddressPhoneType.o: XaUserAddressPhoneType.cpp
	$(CPP) -c XaUserAddressPhoneType.cpp -o $(OBJDIR)XaUserAddressPhoneType.o $(CPPFLAGS)