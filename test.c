#include <stdio.h>

void rs_register(void(* value)(int));
void rs_trigger(int value);

void callback(int value) {
  printf("C-callback invoked with value: %d\n", value);
}

int main(int argc, char *argv[]) {
  rs_trigger(0);
  rs_trigger(1);
  rs_register(&callback);
  rs_trigger(0);
  rs_trigger(1);
}
