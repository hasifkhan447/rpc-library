#include "../include/rpc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
  printf("Serialized: %s\n", buffer);

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

  printf("Now I'm sending this to Nano: %s\n", buffer_mcu);
  memcpy(buffer, buffer_mcu, sizeof(char[BUF_SIZE]));

  // free(ret_mcu);
  // free(args_mcu);
  // free(call_mcu);
  // free(buffer_mcu);



  printf("This is on the Nano\n");
  printf("-------------------\n");


  Deserialize(buffer, call);
  printf("%d\n", call->ret->err);

  free(ret);
  free(args);
  free(call);
  free(buffer);

  free(ret_mcu);
  free(args_mcu);
  free(call_mcu);
  free(buffer_mcu);


}
