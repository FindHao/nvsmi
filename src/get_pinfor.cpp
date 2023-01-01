#include "get_pinfor.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;
void get_pinfor(GPUProcess &gpuprocess)
{
    int pid = gpuprocess.pid;
    ifstream cmdline_file("/proc/" + std::to_string(pid) + "/cmdline");
    // Read the entire file into a string
    stringstream buffer;
    buffer << cmdline_file.rdbuf();
    gpuprocess.cmdline = buffer.str();
}

string get_arch_name(nvmlDeviceArchitecture_t product_arch)
{
    string product_arch_str;
    switch (product_arch)
    {
    case NVML_DEVICE_ARCH_KEPLER:
        product_arch_str = "Kepler";
        break;
    case NVML_DEVICE_ARCH_MAXWELL:
        product_arch_str = "Maxwell";
        break;
    case NVML_DEVICE_ARCH_PASCAL:
        product_arch_str = "Pascal";
        break;
    case NVML_DEVICE_ARCH_VOLTA:
        product_arch_str = "Volta";
        break;
    case NVML_DEVICE_ARCH_TURING:
        product_arch_str = "Turing";
        break;
    case NVML_DEVICE_ARCH_AMPERE:
        product_arch_str = "Ampere";
        break;
#ifdef NVML_DEVICE_ARCH_ADA
    case NVML_DEVICE_ARCH_ADA:
        product_arch_str = "Ada";
        break;
#endif
#ifdef NVML_DEVICE_ARCH_HOPPER
    case NVML_DEVICE_ARCH_HOPPER:
        product_arch_str = "Hopper";
        break;
#endif
    default:
        product_arch_str = "Unknown";
        break;
    }
    return product_arch_str;
}

string brandTypeToString(nvmlBrandType_enum brandType)
{
    switch (brandType)
    {
    case NVML_BRAND_UNKNOWN:
        return "Unknown";
    case NVML_BRAND_QUADRO:
        return "Quadro";
    case NVML_BRAND_TESLA:
        return "Tesla";
    case NVML_BRAND_NVS:
        return "NVS";
    case NVML_BRAND_GRID:
        return "GRID";
    case NVML_BRAND_GEFORCE:
        return "GeForce";
    case NVML_BRAND_TITAN:
        return "Titan";
    case NVML_BRAND_NVIDIA_VAPPS:
        return "Virtual Applications";
    case NVML_BRAND_NVIDIA_VPC:
        return "Virtual PC";
    case NVML_BRAND_NVIDIA_VCS:
        return "Virtual Compute Server";
    case NVML_BRAND_NVIDIA_VWS:
        return "RTX Virtual Workstation";
    case NVML_BRAND_NVIDIA_CLOUD_GAMING:
        return "Cloud Gaming";
    case NVML_BRAND_QUADRO_RTX:
        return "Quadro RTX";
    case NVML_BRAND_NVIDIA_RTX:
        return "RTX";
    case NVML_BRAND_NVIDIA:
        return "NVIDIA";
    case NVML_BRAND_GEFORCE_RTX:
        return "GeForce RTX";
    case NVML_BRAND_TITAN_RTX:
        return "Titan RTX";
    default:
        return "Invalid brand type";
    }
}