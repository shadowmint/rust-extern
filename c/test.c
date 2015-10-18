#include <stdio.h>

#ifdef _WIN64
  #define __EXT __declspec(dllexport)
#elif _WIN32
  #define __EXT __declspec(dllexport)
#else
  #define __EXT extern
#endif

static void (*callback)(int value) = NULL;

__EXT const char *rs_str(void) {
  return "Hello World";
}

__EXT int rs_trigger(int val) {
  printf("Trigger called\n");
  if (val == 1) {
    printf("Invoking callback\n");
    if (callback != NULL) {
      (*callback)(100);
    }
    else {
      printf("No callback bound\n");
    }
  }
  else {
    printf("Nope\n");
  }
  return val + 100;
}

__EXT void rs_register(void *cb) {
  printf("Register called\n");
  callback = cb;
}
