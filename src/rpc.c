#include "../include/rpc.h"
#include <stdlib.h>
#include <string.h>


//TODO: Is there any way I can make generating this Serialize easier? So I don't have to make the Args and Ret together? Is there any macro I can make?






void Serialize(Call call, char* buffer) { // called on one side
  memcpy(buffer, &call.function_enum, sizeof(Command));

  memcpy(buffer+32, (char*)call.args.arg1, sizeof(float));
  memcpy(buffer+64, (char*)call.args.arg2, sizeof(float));
  memcpy(buffer+96, (char*)call.args.arg3, sizeof(float));


  memcpy(buffer+128, (char*)call.ret.arg1, sizeof(float));
  memcpy(buffer+160, (char*)call.ret.arg2, sizeof(float));
  memcpy(buffer+192, (char*)call.ret.arg3, sizeof(float));

  memcpy(buffer+224, (char*)call.ret.err, sizeof(float));
}; //This needs to be serialized, then sent, and then freed

Call Deserialize(char* buffer) { // called on another side
  char* call = malloc(sizeof(Call));

};


void Dispatcher(Call call) {


  // free(call);
}
