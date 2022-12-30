#include "infor.h"

GPUInfor::GPUInfor()
{
}

GPUInfor::GPUInfor(int id, string UUID){
    this->id = id;
    this->UUID = UUID;
}

GPUInfor::~GPUInfor()
{
}

GPUProcess::GPUProcess()
{
}

GPUProcess::~GPUProcess()
{
}

GPUProcess::GPUProcess(int pid)
{
    this->pid = pid;
}

GPUProcess::GPUProcess(int pid, char type, int used_memory, string GPU_UUID)
{
    this->pid = pid;
    this->type = type;
    this->used_memory = used_memory;
    this->GPU_UUID = GPU_UUID;
}
