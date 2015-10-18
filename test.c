#include <stdio.h>

#ifdef _WIN64
  #define __EXT __stdcall
#elif _WIN32
  #define __EXT __stdcall
#else
  #define __EXT extern
#endif

__EXT void rs_register(void(* value)(int));
__EXT int rs_trigger(int value);
__EXT const char* rs_str(void);

void callback(int value) {
  printf("C-callback invoked with value: %d\n", value);
}

int main(int argc, char *argv[]) {
  printf("%s\n", (char *) rs_str());
  rs_trigger(0);
  rs_trigger(1);
  rs_register(&callback);
  rs_trigger(0);
  int rtn_val = rs_trigger(1);
  printf("Read return: %d\n", rtn_val);
}
