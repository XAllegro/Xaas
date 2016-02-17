##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)

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

OBJ=$(OBJDIR)XaLibBase.o $(OBJDIR)XaLibAction.o $(OBJDIR)XaLibModel.o $(OBJDIR)XaLibHttp.o $(OBJDIR)XaLibToken.o \
    $(OBJDIR)XaLibDb.o $(OBJDIR)XaLibSql.o $(OBJDIR)XaLibConfig.o $(OBJDIR)XaLibXsl.o $(OBJDIR)XaLibCrypto.o \
    $(OBJDIR)XaLibDom.o $(OBJDIR)XaLibChar.o $(OBJDIR)XaLibCurl.o $(OBJDIR)XaLibError.o \
    $(OBJDIR)XaLibLog.o \
    $(OBJDIR)XaLibTime.o $(OBJDIR)XaLibWs.o $(OBJDIR)XaLibGui.o $(OBJDIR)XaLibController.o $(OBJDIR)XaLibControllerBackEnd.o $(OBJDIR)XaLibControllerFrontEnd.o\
    $(OBJDIR)XaUserLogin.o $(OBJDIR)XaUserLoginUi.o $(OBJDIR)XaLanguage.o \
    $(OBJDIR)XaLibRbUart.o

#MACROS
.PHONY: all all-before all-after clean print-variables
all:print-variables $(BIN) #all-after

clean:
	${RM} $(OBJ) print-variables $(BIN)
all-before:
	${RM} $(OBJ)
all-after:
	$(OBJ)

print-variables:
	@echo "I am compiling on : " $(UNAME_P) $(UNAME_S) $(OS)

#LINK
ifeq ($(findstring CYGWIN_NT,$(UNAME_S)),CYGWIN_NT)
    $(BIN): $(OBJ)
	ar r $(BIN) $(OBJ)
	ranlib $(BIN) $(LDFLAGS)
endif

#ifeq ($(findstring MINGW32_NT,$(UNAME_S)),MINGW32_NT)
#    $(BIN): $(OBJ)
#	ar r $(BIN) $(OBJ)
#	ranlib $(BIN) $(LDFLAGS)
#endif

#ifeq ($(findstring MSYS_NT,$(UNAME_S)),MSYS_NT)
#    $(BIN): $(OBJ)
#	ar r $(BIN) $(OBJ)
#	ranlib $(BIN) $(LDFLAGS)
#endif

ifeq ($(UNAME_S),Linux)
    $(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(LIBS) $(LDFLAGS)
endif

ifeq ($(UNAME_S),Darwin)
    $(BIN): $(OBJ)
	$(CPP) $(OBJ) -v -o $(BIN) $(LIBS) $(LDFLAGS) $(BIN)
endif

#COMPILE
$(OBJDIR)XaLibController.o: XaLibController.cpp 
	$(CPP) -c XaLibController.cpp -o $(OBJDIR)XaLibController.o $(CPPFLAGS)
$(OBJDIR)XaLibControllerBackEnd.o: XaLibControllerBackEnd.cpp 
	$(CPP) -c XaLibControllerBackEnd.cpp -o $(OBJDIR)XaLibControllerBackEnd.o $(CPPFLAGS)
$(OBJDIR)XaLibControllerFrontEnd.o: XaLibControllerFrontEnd.cpp 
	$(CPP) -c XaLibControllerFrontEnd.cpp -o $(OBJDIR)XaLibControllerFrontEnd.o $(CPPFLAGS)
$(OBJDIR)XaLibBase.o: XaLibBase.cpp 
	$(CPP) -c XaLibBase.cpp -o $(OBJDIR)XaLibBase.o $(CPPFLAGS)
$(OBJDIR)XaLibAction.o: XaLibAction.cpp 
	$(CPP) -c XaLibAction.cpp -o $(OBJDIR)XaLibAction.o $(CPPFLAGS)
$(OBJDIR)XaLibModel.o: XaLibModel.cpp 
	$(CPP) -c XaLibModel.cpp -o $(OBJDIR)XaLibModel.o $(CPPFLAGS)
$(OBJDIR)XaLibHttp.o: XaLibHttp.cpp 
	$(CPP) -c XaLibHttp.cpp -o $(OBJDIR)XaLibHttp.o $(CPPFLAGS)
$(OBJDIR)XaLibToken.o: XaLibToken.cpp 
	$(CPP) -c XaLibToken.cpp -o $(OBJDIR)XaLibToken.o $(CPPFLAGS)
$(OBJDIR)XaLibDb.o: XaLibDb.cpp
	$(CPP) -c XaLibDb.cpp -o $(OBJDIR)XaLibDb.o $(CPPFLAGS)
$(OBJDIR)XaLibSql.o: XaLibSql.cpp
	$(CPP) -c XaLibSql.cpp -o $(OBJDIR)XaLibSql.o $(CPPFLAGS)
$(OBJDIR)XaLibConfig.o: XaLibConfig.cpp 
	$(CPP) -c XaLibConfig.cpp -o $(OBJDIR)XaLibConfig.o $(CPPFLAGS)
$(OBJDIR)XaLibXsl.o: XaLibXsl.cpp 
	$(CPP) -c XaLibXsl.cpp -o $(OBJDIR)XaLibXsl.o $(CPPFLAGS)
$(OBJDIR)XaLibCrypto.o: XaLibCrypto.cpp 
	$(CPP) -c XaLibCrypto.cpp -o $(OBJDIR)XaLibCrypto.o $(CPPFLAGS) -w
$(OBJDIR)XaLibDom.o: XaLibDom.cpp 
	$(CPP) -c XaLibDom.cpp -o $(OBJDIR)XaLibDom.o $(CPPFLAGS)
$(OBJDIR)XaLibChar.o: XaLibChar.cpp
	$(CPP) -c XaLibChar.cpp -o $(OBJDIR)XaLibChar.o $(CPPFLAGS)
$(OBJDIR)XaLibCurl.o: XaLibCurl.cpp 
	$(CPP) -c XaLibCurl.cpp -o $(OBJDIR)XaLibCurl.o $(CPPFLAGS)
$(OBJDIR)XaLibError.o: XaLibError.cpp 
	$(CPP) -c XaLibError.cpp -o $(OBJDIR)XaLibError.o $(CPPFLAGS)
$(OBJDIR)XaLibSocket.o: XaLibSocket.cpp 
	$(CPP) -c XaLibSocket.cpp -o $(OBJDIR)XaLibSocket.o $(CPPFLAGS)
$(OBJDIR)XaLibWebSocket.o: XaLibWebSocket.cpp 
	$(CPP) -c XaLibWebSocket.cpp -o $(OBJDIR)XaLibWebSocket.o $(CPPFLAGS)
$(OBJDIR)XaLibLog.o: XaLibLog.cpp 
	$(CPP) -c XaLibLog.cpp -o $(OBJDIR)XaLibLog.o $(CPPFLAGS)
$(OBJDIR)XaLibTime.o: XaLibTime.cpp 
	$(CPP) -c XaLibTime.cpp -o $(OBJDIR)XaLibTime.o $(CPPFLAGS)
$(OBJDIR)XaLibWs.o: XaLibWs.cpp 
	$(CPP) -c XaLibWs.cpp -o $(OBJDIR)XaLibWs.o $(CPPFLAGS)
$(OBJDIR)XaLibGui.o: XaLibGui.cpp 
	$(CPP) -c XaLibGui.cpp -o $(OBJDIR)XaLibGui.o $(CPPFLAGS)
$(OBJDIR)XaUserLogin.o: XaUserLogin.cpp 
	$(CPP) -c XaUserLogin.cpp -o $(OBJDIR)XaUserLogin.o $(CPPFLAGS)
$(OBJDIR)XaUserLoginUi.o: XaUserLoginUi.cpp 
	$(CPP) -c XaUserLoginUi.cpp -o $(OBJDIR)XaUserLoginUi.o $(CPPFLAGS)


#$(OBJDIR)XaUserProfile.o: XaUserProfile.cpp 
#	$(CPP) -c XaUserProfile.cpp -o $(OBJDIR)XaUserProfile.o $(CPPFLAGS)
#$(OBJDIR)XaAddress.o: XaAddress.cpp 
#	$(CPP) -c XaAddress.cpp -o $(OBJDIR)XaAddress.o $(CPPFLAGS)
#$(OBJDIR)XaLabel.o: XaLabel.cpp 
#	$(CPP) -c XaLabel.cpp -o $(OBJDIR)XaLabel.o $(CPPFLAGS)
$(OBJDIR)XaLanguage.o: XaLanguage.cpp 
	$(CPP) -c XaLanguage.cpp -o $(OBJDIR)XaLanguage.o $(CPPFLAGS)

#$(OBJDIR)XaCurrency.o: XaCurrency.cpp 
#	$(CPP) -c XaCurrency.cpp -o $(OBJDIR)XaCurrency.o $(CPPFLAGS)
#$(OBJDIR)XaDomain.o: XaDomain.cpp 
#	$(CPP) -c XaDomain.cpp -o $(OBJDIR)XaDomain.o $(CPPFLAGS)
$(OBJDIR)XaLibMail.o: XaLibMail.cpp 
	$(CPP) -c XaLibMail.cpp -o $(OBJDIR)XaLibMail.o $(CPPFLAGS)
$(OBJDIR)XaLibRbUart.o: XaLibRbUart.cpp 
	$(CPP) -c XaLibRbUart.cpp -o $(OBJDIR)XaLibRbUart.o $(CPPFLAGS)
$(OBJDIR)XaLibRbGpIo.o: XaLibRbGpIo.cpp 
	$(CPP) -c XaLibRbGpIo.cpp -o $(OBJDIR)XaLibRbGpIo.o $(CPPFLAGS)