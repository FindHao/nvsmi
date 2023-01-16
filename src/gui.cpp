#include "gui.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::to_string;
void print_like_nvidia_smi(GPUInforPtrVector &gpuinfors)
{
     const int TABLE_WIDTH = 100;
     const int COLUMN_1_WIDTH = 5;
     const int COLUMN_2_WIDTH = 10;
     const int COLUMN_3_WIDTH = TABLE_WIDTH - 2 - COLUMN_1_WIDTH * 2 - COLUMN_2_WIDTH * 2;
     string line(TABLE_WIDTH - 2, '-');
     string line_double(TABLE_WIDTH - 2, '=');
     line_double = '+' + line_double + '+';
     line = '+' + line + '+';

     const int COLUMN_4_WIDTH = 40;
     const int COLUMN_5_WIDTH = 20;
     cout << line << endl;
     int major_version = gpuinfors[0]->cuda_version / 1000;
     int minor_version = gpuinfors[0]->cuda_version % 1000;
     string cuda_version = to_string(major_version) + "." + to_string(minor_version);
     cout << "|" << setw(COLUMN_5_WIDTH) << left << "Driver Version: "
          << setw(COLUMN_5_WIDTH) << left << gpuinfors[0]->driver_version
          << setw(COLUMN_5_WIDTH) << left << "CUDA Version: "
          << setw(TABLE_WIDTH - COLUMN_5_WIDTH * 3 - 2) << left << cuda_version
          << "|" << endl;
          
     cout << line << endl;
     cout << "|" << setw(COLUMN_1_WIDTH) << left << "GPU"
          << setw(COLUMN_4_WIDTH) << left << "Name"
          << setw(TABLE_WIDTH - COLUMN_1_WIDTH - COLUMN_4_WIDTH - 2) << left << " "
          << "|" << endl;
     cout << "|" << setw(COLUMN_1_WIDTH) << left << "Fan"
          << setw(COLUMN_1_WIDTH) << left << "Temp"
          << setw(COLUMN_5_WIDTH) << left << "Power:Usage/Cap"
          << setw(COLUMN_5_WIDTH) << left << "Memory-Usage"
          << setw(COLUMN_2_WIDTH) << left << "GPU-Util"
          << setw(COLUMN_2_WIDTH) << left << "SM"
          << setw(TABLE_WIDTH - COLUMN_1_WIDTH * 2 - COLUMN_5_WIDTH * 2 - COLUMN_2_WIDTH * 2 - 2) << left << " "
          << "|" << endl;

     cout << line_double << endl;
     for (int i = 0; i < gpuinfors.size(); i++)
     {
          auto gpuinfor = gpuinfors[i];
          cout << "|" << setw(COLUMN_1_WIDTH) << left << to_string(i)
               << setw(COLUMN_4_WIDTH) << left << gpuinfor->product_name
               << setw(TABLE_WIDTH - COLUMN_1_WIDTH - COLUMN_4_WIDTH - 2) << left << " "
               << "|" << endl;
          string fan_speed = gpuinfor->fan_speed == 10000 ? "N/A" : to_string(gpuinfor->fan_speed) + "%";
          cout << "|" << setw(COLUMN_1_WIDTH) << left << fan_speed
               << setw(COLUMN_1_WIDTH) << left << to_string(gpuinfor->temperature) + "C"
               << setw(COLUMN_5_WIDTH) << left << to_string(gpuinfor->power_usage) + "W/" + to_string(gpuinfor->power_limit) + "W"
               << setw(COLUMN_5_WIDTH) << left << to_string(gpuinfor->memory_used) + "MiB/" + to_string(gpuinfor->memory_total) + "MiB"
               << setw(COLUMN_2_WIDTH) << left << to_string(gpuinfor->utilization.gpu) + "%"
               << setw(TABLE_WIDTH - COLUMN_1_WIDTH * 2 - COLUMN_5_WIDTH * 2 - COLUMN_2_WIDTH - 2) << left << to_string(gpuinfors[0]->sm_version.major) + "." + to_string(gpuinfors[0]->sm_version.minor)
               << "|" << endl;
     }

     cout << line << endl <<endl;
     cout << line << endl;
     cout << "|" << setw(TABLE_WIDTH - 2) << left << "Processes:"
          << "|" << endl;
     cout << "|" << setw(COLUMN_1_WIDTH) << left << "GPU"
          //  << setw(COLUMN_1_WIDTH) << left << "GI"
          //  << setw(COLUMN_1_WIDTH) << left << "CI"
          << setw(COLUMN_2_WIDTH) << left << "PID"
          << setw(COLUMN_1_WIDTH) << left << "Type"
          << setw(COLUMN_3_WIDTH) << left << "Process name"
          << setw(COLUMN_2_WIDTH) << left << "GPU Memory"
          << "|" << endl;
     cout << "|" << setw(COLUMN_1_WIDTH) << left << " "
          //  << setw(COLUMN_1_WIDTH) << left << "ID"
          //  << setw(COLUMN_1_WIDTH) << left << "ID"
          << setw(COLUMN_1_WIDTH + COLUMN_2_WIDTH + COLUMN_3_WIDTH) << left << " "
          << setw(COLUMN_2_WIDTH) << left << "Usage"
          << "|" << endl;
     cout << line_double << endl;

     // iterate through each GPU device
     for (int i = 0; i < gpuinfors.size(); i++)
     {
          auto gpuinfor = gpuinfors[i];
          for (auto gpuprocess : gpuinfor->gpu_processes)
          {
               string cmdline = gpuprocess->cmdline;
               size_t pos = 0;
               while ((pos = cmdline.find('\0', pos)) != string::npos)
               {
                    cmdline.erase(pos, 1);
               }
               if (cmdline.length() > COLUMN_3_WIDTH)
                    cmdline = cmdline.substr(0, COLUMN_3_WIDTH);
               else
                    cmdline += string(COLUMN_3_WIDTH - cmdline.length(), ' ');
               cout << "|" << setw(COLUMN_1_WIDTH) << left << i
                    // << setw(COLUMN_1_WIDTH) << left << " "
                    // << setw(COLUMN_1_WIDTH) << left << " "
                    << setw(COLUMN_2_WIDTH) << left << gpuprocess->pid
                    << setw(COLUMN_1_WIDTH) << left << gpuprocess->type
                    << setw(COLUMN_3_WIDTH) << left << cmdline
                    << setw(COLUMN_2_WIDTH) << right << (to_string(gpuprocess->used_memory) + "MB")
                    << "|" << endl;
          }
     }
     cout << line << endl;
}