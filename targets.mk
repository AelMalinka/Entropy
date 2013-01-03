libEntropy.so = 
ENTROPY_OBJS = 
ENTROPY_H_SRCS = Exception.hh
ENTROPY_H = $(foreach i,$(ENTROPY_H_SRCS),build/Entropy/$(i))
ENTROPY_CXXFLAGS = $(CXXFLAGS) -fPIC
ENTROPY_LDFLAGS = $(LDFLAGS) -shared

TARGETS = $(ENTROPY_H)
TESTS = Exception

TEST_FLAGS = $(CXXFLAGS) -Ibuild
TEST_LDFLAGS = $(LDFLAGS) -pthread -lgtest -lgtest_main -Lbuild #-lEntropy

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
