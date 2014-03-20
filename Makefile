CFLAGS= -m32 -Wall
CXXFLAGS= -Ixbyak -m32 -Wall -W -O2 -fno-operator-names
TARGETS=manual-jit xbyak-jit

all: $(TARGETS)

clean:
	rm $(TARGETS)
