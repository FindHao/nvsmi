#include "nvsmi.h"
#include <iostream>
#include <nvml.h>
#include "gui.h"
#include "get_pinfor.h"
#include <memory>

using std::make_unique;

GPUInforPtrVector *gpuinfors;
#ifndef NVML_ERROR_CHECK
#define NVML_ERROR_CHECK(call)                                                   \
    {                                                                            \
        auto status = static_cast<nvmlReturn_t>(call);                           \
        if (status != NVML_SUCCESS)                                              \
        {                                                                        \
            fprintf(stderr,                                                      \
                    "ERROR: CUDA NVML call \"%s\" in line %d of file %s failed " \
                    "with "                                                      \
                    "%s (%d).\n",                                                \
                    #call,                                                       \
                    __LINE__,                                                    \
                    __FILE__,                                                    \
                    nvmlErrorString(status),                                     \
                    status);                                                     \
            nvmlShutdown();                                                      \
            exit(1);                                                             \
        }                                                                        \
    }
#endif // NVML_ERROR_CHECK


int main(void)
{
    NVML_ERROR_CHECK(nvmlInit());
    // Get the number of GPU devices
    unsigned int device_count;
    NVML_ERROR_CHECK(nvmlDeviceGetCount(&device_count));
    gpuinfors = new GPUInforPtrVector();
    // Iterate through each GPU device
    for (unsigned int i = 0; i < device_count; i++)
    {
        // Get the handle for the GPU device
        nvmlDevice_t device;
        NVML_ERROR_CHECK(nvmlDeviceGetHandleByIndex(i, &device));
        // Get the name of the GPU
        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        NVML_ERROR_CHECK(nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE));
        printf("GPU %d: %s\n", i, name);
        // Get the list of graphics processes running on the GPU
        nvmlProcessInfo_t infos[64];
        unsigned int info_count;
        NVML_ERROR_CHECK(nvmlDeviceGetGraphicsRunningProcesses(device, &info_count, infos));
        // Get the UUID of the GPU
        char uuid[NVML_DEVICE_UUID_BUFFER_SIZE];
        NVML_ERROR_CHECK(nvmlDeviceGetUUID(device, uuid, NVML_DEVICE_UUID_BUFFER_SIZE));
        GPUInfor *gpuinfor = new GPUInfor(i, string(uuid));
        // get driver version
        char driver_version[NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE];
        NVML_ERROR_CHECK(nvmlSystemGetDriverVersion(driver_version, NVML_SYSTEM_DRIVER_VERSION_BUFFER_SIZE));
        gpuinfor->driver_version = string(driver_version);
        // get product name
        char product_name[NVML_DEVICE_NAME_BUFFER_SIZE];
        nvmlDeviceGetName(device, product_name, NVML_DEVICE_NAME_BUFFER_SIZE);
        gpuinfor->product_name = string(product_name);
        // get product brand
        nvmlBrandType_t product_brand;
        NVML_ERROR_CHECK(nvmlDeviceGetBrand(device, &product_brand));
        gpuinfor->product_brand = brandTypeToString(product_brand);
        // get product arch
        nvmlDeviceArchitecture_t product_arch;
        NVML_ERROR_CHECK(nvmlDeviceGetArchitecture(device, &product_arch));
        gpuinfor->product_arch = get_arch_name(product_arch);
        // get fan speed
        unsigned int fan_speed;
        NVML_ERROR_CHECK(nvmlDeviceGetFanSpeed(device, &fan_speed));
        gpuinfor->fan_speed = fan_speed;
        // get temperature
        unsigned int temperature;
        NVML_ERROR_CHECK(nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature));
        gpuinfor->temperature = temperature;
        // get power usage
        unsigned int power_usage;
        NVML_ERROR_CHECK(nvmlDeviceGetPowerUsage(device, &power_usage));
        gpuinfor->power_usage = power_usage / 1000;
        // get power limit
        unsigned int power_limit;
        NVML_ERROR_CHECK(nvmlDeviceGetPowerManagementLimit(device, &power_limit));
        gpuinfor->power_limit = power_limit / 1000;
        // get power management mode
        nvmlEnableState_t power_management_mode;
        NVML_ERROR_CHECK(nvmlDeviceGetPowerManagementMode(device, &power_management_mode));
        // get memory usage
        nvmlMemory_v2_t memory;
        nvmlDeviceGetMemoryInfo_v2(device, &memory);
        gpuinfor->memory_total = memory.total /  1024 / 1024;
        gpuinfor->memory_used = memory.used / 1024 / 1024;
        // get utilization
        nvmlUtilization_t utilization;
        NVML_ERROR_CHECK(nvmlDeviceGetUtilizationRates(device, &utilization));
        gpuinfor->utilization.gpu = utilization.gpu;
        gpuinfor->utilization.memory = utilization.memory;
        // get SM version
        NVML_ERROR_CHECK(nvmlDeviceGetCudaComputeCapability(device, &gpuinfor->sm_version.major, &gpuinfor->sm_version.minor));
        for (unsigned int i = 0; i < info_count; i++)
        {
            // change usedGPUmemory to MB
            infos[i].usedGpuMemory = infos[i].usedGpuMemory / 1024 / 1024;
            GPUProcess *gpuprocess = new GPUProcess(infos[i].pid, 'G', infos[i].usedGpuMemory, string(uuid));
            get_pinfor(*gpuprocess);
            // gpuinfors[i].gpu_processes.push_back(gpuprocess);
            gpuinfor->gpu_processes.push_back(gpuprocess);
        }
        gpuinfors->push_back(gpuinfor);
    }
    print_like_nvidia_smi(*gpuinfors);
    // Clean up NVML library
    nvmlShutdown();
    return 0;
}
