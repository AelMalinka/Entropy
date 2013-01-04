libEntropy.so = 
ENTROPY_OBJS = 
ENTROPY_H_SRCS = Exception.hh
ENTROPY_H = $(foreach i,$(ENTROPY_H_SRCS),build/Entropy/$(i))
ENTROPY_CXXFLAGS = -fPIC
ENTROPY_LDFLAGS = -shared

TARGETS = $(ENTROPY_H)
TESTS = Exception

TEST_FLAGS = -Ibuild
TEST_LDFLAGS = -pthread -lgtest -lgtest_main #-lEntropy

libEntropy.so: build/libEntropy.so
	cp -f build/libEntropy.so $@

build/libEntropy.so: $(ENTROPY_OBJS)
	$(CC) $(ENTROPY_LDFLAGS) -o $@ $(ENTROPY_OBJS)

$(ENTROPY_OBJS): build/src/%.o: src/%.cc
	mkdir -p build/src
	$(CXX) $(ENTROPY_CXXFLAGS) -c -o $@ $<

$(ENTROPY_H): build/Entropy/%.hh: src/%.hh
	d=$$(echo $@) ; mkdir -p $${d%/*}
	cp -f $< $@
