MINGW = i686-w64-mingw32-
CXX = $(MINGW)g++
LD = $(MINGW)g++
AR = $(MINGW)ar
RC = $(MINGW)windres

CXXFLAGS = -g -O2 -Wall
CXXFLAGS += -mwindows
LDFLAGS = -g -O2 -Wall
LDFLAGS += -mwindows
LDFLAGS += -static

all: hwin-test.exe

hwin-test.exe: hwin/hwin.o
hwin-test.exe: hwin/hwin.hxx

hwin-test.exe: test.o test.res
	$(LD) $(LDFLAGS) -o $@ test.o test.res hwin/hwin.o

hwin/hwin.o: dummy
	$(MAKE) -C hwin

%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.res: %.rc
	$(RC) $< -O coff -o $@

dummy:

clean: dummy
	$(MAKE) -C hwin clean
	rm -f hwin-test.exe test.o

.PHONY: dummy
