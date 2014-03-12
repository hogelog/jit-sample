#include <stdlib.h>
#include <malloc.h>
#include <sys/mman.h>

void* jit_compile(char *source) {
  char *codes = valloc(20000);
  size_t code_len = 0;
  int ch;
 
  // mov $0, %eax
  codes[code_len++] = 0xB8; 
  codes[code_len++] = 0x00; 
  codes[code_len++] = 0x00; 
  codes[code_len++] = 0x00; 
  codes[code_len++] = 0x00; 

  while ((ch = *source++) != EOF) {
    switch (ch) {
      case '+':
        codes[code_len++] = 0x40; // inc %eax
        break;
      case '-':
        codes[code_len++] = 0x48; // dec %eax
        break;
    }
  }

  codes[code_len++] = 0xC3; // ret

  mprotect(codes, code_len, PROT_EXEC);
  return codes;
}

int main(int argc, char *argv[]) {
  int (*codes)() = jit_compile("++++++++---++");
  printf("result: %d\n", codes());

  return 0;
}
