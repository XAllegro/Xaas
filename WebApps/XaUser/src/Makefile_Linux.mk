##  Makefile
##  Project: XAAS
##  Alessandro Mariotti
##  alex@xallegro.com
CPP      = g++
OBJDIR   = ../objects/
RM       = rm -f
BIN      = ../../../web/$(BIN_NAME)
LIBS     = -lxml2 -lxslt -lexslt -lssl -lcrypto -L/usr/local/mysql/lib -lmysqlclient -lcurl

XALLEGRO_DIR = ../../..
XALIB_DIR = $(XALLEGRO_DIR)/XaLib
XALIB=/XAllegro/Xaas/XaLib/bin/XaLib.so

APP_NAME=XaUser
APP_DIR=$(XALLEGRO_DIR)\WebApps\$(APP_NAME)    

CPPINCS  = -I../include -I/usr/include -I/usr/include/libxml2 -I/usr/include/mysql -I$(XALLEGRO_DIR)/XaLib/include
CPPFLAGS = $(CPPINCS)  -std=c++0x -O3 -Wall