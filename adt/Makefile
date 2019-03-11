GTEST_DIR = /googletest

AR = ar
CXX = g++
CXXFLAGS += -g -Wall -Wextra -pthread -Og -std=c++11
CPPFLAGS += -I$(GTEST_DIR)/googletest/include

LDFLAGS += -L$(GTEST_DIR)/build/lib -L.
LDLIBS += -lgtest -lgtest_main -lpthread -lm -l$(LIB)

SRC = $(filter-out %_test.cc, $(wildcard *.cc))
OBJ = $(SRC:.cc=.o)

TEST_SRC = $(filter %_test.cc, $(wildcard *.cc))
TEST_OBJ = $(TEST_SRC:.cc=.o)

LIB = adt
LIBFILE = lib$(LIB).a

TARGETS = $(TEST_OBJ:.o=.out)

all: $(TARGETS)

$(LIBFILE): $(OBJ)
	$(AR) r $(LIBFILE) $(OBJ)

%.out: %.o $(LIBFILE)
	$(CXX) $(LDFLAGS) $(subst .out,.o,$@) $(LDLIBS) -o $@

%.a: %.o %.h

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ) $(TEST_OBJ) $(LIBFILE) $(TARGETS)

lint:
	@cpplint.py $(wildcard *.h) $(SRC)

.PHONY: all clean lint
