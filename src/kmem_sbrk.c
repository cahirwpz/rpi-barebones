#include <klibc.h>
#include <kmem.h>

/* The end of the kernel's .bss section. Provided by the linker. */
extern uint8_t _bss_end[];
/* Limit for the end of kernel's bss. Provided by the linker. */
extern uint8_t _brk_limit[];

static struct {
  uint8_t *ptr;
  uint8_t *end;
} sbrk = {_bss_end, _brk_limit};

void *kmem_sbrk(size_t size) {
  uint8_t *ptr = sbrk.ptr;
  size = roundup(size, sizeof(uint64_t));
  assert(ptr + size <= sbrk.end);
  sbrk.ptr += size;
  bzero(ptr, size);
  return ptr;
}
