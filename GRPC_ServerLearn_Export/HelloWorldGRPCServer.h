#pragma once


#ifdef GRPCSERVERLEARNEXPORT_EXPORTS
#define GRPCSERVERLEARNEXPORT_API __declspec(dllexport)
#else
#define GRPCSERVERLEARNEXPORT_API __declspec(dllimport)
#endif


extern "C" GRPCSERVERLEARNEXPORT_API void helloworld_start();

extern "C" GRPCSERVERLEARNEXPORT_API void helloworld_stop();