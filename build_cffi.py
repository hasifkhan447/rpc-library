from cffi import FFI 
ffibuilder = FFI()

ffibuilder.cdef("""
    typedef enum Command {
      read_sensor, 
      run_motor, 
      pid_to_position, 
      finger_pos, 
    } Command;


    typedef struct Args {
      float arg1;
      float arg2;
      float arg3;
    } Args;

    typedef struct Ret { 
      float arg1;
      float arg2;
      float arg3;
      int err;
    } Ret;

    typedef struct Call { 
      Command function_enum;
      Args* args;
      Ret* ret;
    } Call;

    void Serialize(const Call* call, char* buffer); 
    void Deserialize(const char* buffer, Call* call); 
    void Dispatcher(Call* call); 

    void PrintSerialized(const char* buffer);
""")

ffibuilder.set_source("pyrpc",

                      """
                      #include "include/rpc.h"
                      """,

                      sources=['src/rpc.c'])

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
