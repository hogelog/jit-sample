#include <stdio.h>
#include <xbyak/xbyak.h>

typedef int (*JIT_FUNCTION)();

JIT_FUNCTION jit_compile(Xbyak::CodeGenerator &gen, const char *source) {
  int ch;

  gen.mov(gen.eax, 0);

  while ((ch = *source++) != '\0') {
    switch (ch) {
      case '+':
        gen.inc(gen.eax);
        break;
      case '-':
        gen.dec(gen.eax);
        break;
    }
  }

  gen.ret();

  return (JIT_FUNCTION) gen.getCode();
}

int main() {
  Xbyak::CodeGenerator gen(20000);
  const JIT_FUNCTION codes = jit_compile(gen, "++++++++---++");
  printf("result: %d\n", codes());
  return 0;
}
