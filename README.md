This is a library that's going to be used on either end. It will be compiled seperately for zephyr, and linked there. And seperately compiled for the jetson nano. 


The idea is to have different types of messages which can be serialized and deserialized. 

The RPC stuff in zephyr will live in its own thread that serializes and deserializes.


It'd work like this 

Nano:
Serialize(ENCODER_MACRO(function_enum), &buffer)
send(buffer)

(wait for response)


MCU:
recv(buffer)
Deserialize(buffer, call)
Dispatcher(call)
(append output to call)
Serialize(call, buffer)

Nano: 
Recieved response 
Deserialize(buffer, call)

Now do my stuff




