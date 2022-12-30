#ifndef GET_PINFOR_H
#define GET_PINFOR_H

#include "infor.h"
#include <nvml.h>
void get_pinfor(GPUProcess &gpuprocess);
string get_arch_name(nvmlDeviceArchitecture_t product_arch);
string brandTypeToString(nvmlBrandType_enum brandType);
#endif