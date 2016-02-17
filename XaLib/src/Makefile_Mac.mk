##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

#
## MAC
## TESTED: 10.10.3
## TESTED: 10.10.4
## TESTED: 10.10.5

CPP      = g++
OBJDIR   = ../objects/
RM       = rm -f
CUR_DIR  = $(shell pwd)
BIN      = $(CUR_DIR)/../bin/XaLib.so

LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl 
CPPINCS  = -I../include -I/usr/include -I/opt/local/include -I/usr/include/libxml2 -I/usr/local/mysql/include
LDFLAGS  = -dynamiclib -install_name
CPPFLAGS = $(CPPINCS) -fPIC -std=gnu++14 -O3 -Wall