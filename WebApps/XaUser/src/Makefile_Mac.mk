##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com

CPP      = g++
OBJDIR   = ../objects/
RM       = rm -f
BIN      = ../../../web/$(BIN_NAME)
LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl

XALLEGRO_DIR = /XAllegro/Xaas
XALIB=$(XALLEGRO_DIR)/XaLib/bin/XaLib.so

CPPINCS  = -I../include -I/usr/include -I/opt/local/include -I/usr/include/libxml2 -I/usr/local/mysql/include -I$(XALLEGRO_DIR)/XaLib/include
CPPFLAGS = $(CPPINCS)  -std=c++14 -O3 -Wall