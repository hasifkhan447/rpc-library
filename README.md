This is a library that's going to be used on either end. It will be compiled seperately for zephyr, and linked there. And seperately compiled for the jetson nano. 


The idea is to have different types of messages which can be serialized and deserialized. 

The RPC stuff in zephyr will live in its own thread that serializes and deserializes.
