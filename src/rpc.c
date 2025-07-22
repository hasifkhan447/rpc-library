#include "../include/rpc.h"
#include <string.h>


//TODO: Is there any way I can make generating this Serialize easier? So I don't have to make the Args and Ret together? Is there any macro I can make?






void Serialize(const Call call, char* buffer) { // called on one side
  memcpy(buffer, &call.function_enum, sizeof(Command));

  memcpy(buffer+32, (char*)call.args.arg1, sizeof(float));
  memcpy(buffer+64, (char*)call.args.arg2, sizeof(float));
  memcpy(buffer+96, (char*)call.args.arg3, sizeof(float));


  memcpy(buffer+128, (char*)call.ret.arg1, sizeof(float));
  memcpy(buffer+160, (char*)call.ret.arg2, sizeof(float));
  memcpy(buffer+192, (char*)call.ret.arg3, sizeof(float));

  memcpy(buffer+224, (char*)call.ret.err, sizeof(float));
}; //This needs to be serialized, then sent, and then freed

void Deserialize(const char* buffer, Call *call) { // called on another side

  memcpy((void*)call->args.arg1, buffer+32, sizeof(float));
  memcpy((void*)call->args.arg2, buffer+64, sizeof(float));
  memcpy((void*)call->args.arg3, buffer+96, sizeof(float));

  memcpy((void*)call->ret.arg1, buffer+128, sizeof(float));
  memcpy((void*)call->ret.arg2, buffer+160, sizeof(float));
  memcpy((void*)call->ret.arg3, buffer+192, sizeof(float));

  memcpy((void*)call->ret.err, buffer+224, sizeof(float));
};


void Dispatcher(Call* call) {
  int err;
  switch(call.function_enum) {
    case read_sensor:
      //TODO: extern void read_sensor()
      //
      // Assign its output to ret and then reserialize to the other end .
      break;

    case run_motor:   //currently just running it at a certain speed
      extern int run_motor_fn(int motor_id, int pwm_frequency);
      int err_code; 
      err_code = run_motor_fn(*(int*)call.args.arg1, *(int*)call.args.arg2);
      break;

    case pid_to_position:
      // TODO: 
      break;

    case finger_pos:
      // TODO:
      break;
  }

  call->ret.err = (void*)err;
  // free(call);
}
