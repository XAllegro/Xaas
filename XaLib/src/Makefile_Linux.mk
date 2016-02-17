##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

CPP      = g++
OBJDIR   = ../objects/
RM       = rm -f
CUR_DIR  = $(shell pwd)
BIN      = ../bin/XaLib.so

LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -lmysqlclient -lcurl 
CPPINCS  = -I../include -I/usr/include -I/usr/include/libxml2 -I/usr/include/mysql -I$(CUR_DIR)/../../XaLib/include
LDFLAGS  = -shared
CPPFLAGS = $(CPPINCS) -fPIC -std=gnu++14 -O3 -Wall