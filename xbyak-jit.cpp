#include <stdio.h>
#include <xbyak/xbyak.h>

const void* jit_compile(Xbyak::CodeGenerator &gen, const char *source) {
  int ch;

  gen.mov(gen.eax, 0);

  while ((ch = *source++) != EOF) {
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

  return gen.getCode();
}

int main() {
  Xbyak::CodeGenerator gen(20000);
  int (*codes)() = (int (*)())jit_compile(gen, "++++++++---++");
  printf("result: %d\n", codes());
  return 0;
}
