#include "../include/rpc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void PrintSerialized(const char* buffer) {

  printf("%d %f %f %f %f %f %f %d\n", *(Command*)buffer, *(float*)(buffer+32),*(float*)(buffer+64), *(float*)(buffer+96), *(float*)(buffer+128), *(float*)(buffer+164), *(float*)(buffer+192), *(int*)(buffer+224));

}

void Dispatcher(Call* call) { // Only going to be run on the MCU
  switch(call->function_enum) {
    case read_sensor:
      //TODO: extern void read_sensor()
      //
      // Assign its output to ret and then reserialize to the other end .
      break;

    case run_motor:   //currently just running it at a certain speed
      extern int run_motor_fn(float motor_id, float pwm_frequency);
      call->ret->err = run_motor_fn(call->args->arg1,call->args->arg2);
      break;

    case pid_to_position:
      // TODO: 
      break;

    case finger_pos:
      // TODO:
      break;


  }
}







int main() {
  // ON the nano 
  printf("This is on the nano\n");
  printf("-------------------\n");
  char* buffer = malloc(sizeof(char[BUF_SIZE]));
  Call* call = malloc(sizeof(Call));

  call->function_enum = run_motor;
  Args* args = malloc(sizeof(Args));
  Ret* ret = malloc(sizeof(Ret));
  args->arg1 = 1; 
  args->arg2 = 0.1;
  args->arg3 = 0;

  call->args = args;
  call->ret = ret;

  Serialize(call, buffer);
  printf("Serialized:\n");
  PrintSerialized(buffer);

  printf("Imagine I sent something to the MCU\n");
  printf("-------------------\n");

  printf("This is on the MCU\n");
  printf("-------------------\n");
  Call* call_mcu = malloc(sizeof(Call));
  char* buffer_mcu = malloc(sizeof(char[BUF_SIZE]));
  Args* args_mcu = malloc(sizeof(Args));
  Ret* ret_mcu = malloc(sizeof(Ret));

  call_mcu->args = args_mcu;
  call_mcu->ret = ret_mcu;

  printf("Imagine I just recieved something\n");
  memcpy(buffer_mcu, buffer, sizeof(char[BUF_SIZE]));
  fflush(stdout);

  Deserialize(buffer_mcu, call_mcu);

  Dispatcher(call_mcu);

  Serialize(call_mcu, buffer_mcu);

  //This is a test

  printf("Now I'm sending this to Nano:\n");
  // PrintSerialized(buffer_mcu);
  memcpy(buffer, buffer_mcu, sizeof(char[BUF_SIZE]));

  free(ret_mcu);
  free(args_mcu);
  free(call_mcu);
  free(buffer_mcu);



  printf("This is on the Nano\n");
  printf("-------------------\n");


  Deserialize(buffer, call);
  printf("%d\n", call->ret->err);


  free(ret);
  free(args);
  free(call);
  free(buffer);


}
