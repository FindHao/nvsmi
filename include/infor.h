#ifndef INFO_H
#define INFO_H

#include <vector>
#include <string>
#include <memory>
#include <nvml.h>
using std::string;
using std::vector;
using std::unique_ptr;

class GPUProcess
{
public:
    int pid;
    char type;
    string product_name;
    string cmdline;
    // MB
    int used_memory;
    string GPU_UUID;
    int giid;
    int ciid;
    GPUProcess();
    GPUProcess(int pid);
    GPUProcess(int pid, char type, int used_memory, string GPU_UUID);
    ~GPUProcess();
};

// typedef unique_ptr<GPUProcess> GPUProcessPtr;

struct SMVersion
{
    int major;
    int minor;
};


class GPUInfor
{
public:
    int id;
    string UUID;
    string product_name;
    string product_brand;
    string product_arch;
    string bus_id;
    string driver_version;
    int cuda_version;
    int memory_total;
    int memory_used;
    int temperature;
    int fan_speed;
    int power_usage;
    int power_limit;
    nvmlUtilization_t utilization;
    SMVersion sm_version;
    vector<GPUProcess *> gpu_processes;
    GPUInfor();
    GPUInfor(int id, string UUID);
    ~GPUInfor();
};

typedef vector<GPUInfor *> GPUInforPtrVector;
// typedef unique_ptr<GPUInfor> GPUInforPtr;

// typedef unique_ptr<vector<GPUInforPtr>> GPUInforPtrVector;
#endif