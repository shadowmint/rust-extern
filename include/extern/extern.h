// Fake c headers for exported symbols

#ifdef _WIN64
  #define __EXT __declspec(dllexport)
#elif _WIN32
  #define __EXT __declspec(dllexport)
#else
  #define __EXT extern
#endif

__EXT int rs_trigger(int val);
__EXT void rs_register(void *cb);
