ifdef CLANG
CC 			= clang++
else
CC			= g++
endif

CFLAGS		= -c -g -pedantic -Wall -Wpointer-arith -Wcast-qual \
			  -std=c++11
LD			= g++
LDFLAGS 	= 
AR			= ar
ARFLAGS		= rcs
RM			= rm
CP			= cp
ECHO		= echo -e
SHELL		= /bin/sh
CTAGS		= ctags

LIBS 				= -lSDL2

OBJDIR				= obj
DEPS				= 
EXECUTABLE 			= gameoflife
PROG_SOURCES 		= $(wildcard src/*.cpp)
PROG_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(PROG_SOURCES:.cpp=.o)))

TEST				= test
TEST_SOURCES 		= $(filter-out src/chess.cpp,$(wildcard src/*.cpp)) $(wildcard testsrc/*.cpp)
TEST_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(TEST_SOURCES:.cpp=.o)))

default: $(EXECUTABLE)

all: $(EXECUTABLE) $(TEST)

$(EXECUTABLE): $(PROG_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

check: $(TEST)
	./$(TEST)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(TEST): $(TEST_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) -lcppunit $(LIBS) -o $@ $(TEST_OBJECTS)

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: testsrc/%.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $<

#$(PROG_OBJECTS): $(OBJDIR)
#
#$(OBJDIR):
#	mkdir $(OBJDIR)

clean:
	$(RM) -f $(EXECUTABLE) $(TEST) $(PROG_OBJECTS) $(TEST_OBJECTS)
