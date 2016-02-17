##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

## WINDOWS CYGWIN
## TESTED WIN7 - WIN10
## ASSUMING XAAS INSTALLED UNDER C:/XAllegro

XALLEGRO_DIR = C:\XAllegro\Xaas

CYGWIN_LIB_DIR=C:\XAllegro\cygwin\usr\include

XALIB_DIR = $(XALLEGRO_DIR)\XaLib
XALIB=$(XALLEGRO_DIR)\XaLib\bin\XaLib.a

CPP      = g++
OBJDIR   = ..\objects\\
RM       = rm -f -r 
CUR_DIR  = $(cmd %cd%)

LIBS     = -L$(CYGWIN_LIB_DIR)\lib -L$(CYGWIN_LIB_DIR)\bin \
	    -lcurl.dll -lcrypto -lxml2.dll -lxslt.dll -lexslt.dll -lmysqlclient\

CPPINCS  = -I$(XALIB_DIR)\include -I$(XALLEGRO_DIR)\WebApps\XaUser\include \
	    -I$(CYGWIN_LIB_DIR) -I$(CYGWIN_LIB_DIR)\libxml2 -I$(CYGWIN_LIB_DIR)\mysql  

LDFLAGS  =
CPPFLAGS = $(CPPINCS) -std=c++14 -Wall

BIN      = $(XALLEGRO_DIR)\web\$(BIN_NAME)

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Windows