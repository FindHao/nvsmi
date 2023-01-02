# nvsmi

A wider nvidia-smi.

An exmaple of nvidia-smi output is as follows:

```
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 520.61.05    Driver Version: 520.61.05    CUDA Version: 11.8     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  NVIDIA RTX A5000    On   | 00000000:41:00.0 Off |                  Off |
| 30%   35C    P8    19W / 230W |     10MiB / 24564MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
|   1  NVIDIA RTX A5000    On   | 00000000:61:00.0  On |                  Off |
| 30%   31C    P8    22W / 230W |    909MiB / 24564MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A      3217      G   /usr/lib/xorg/Xorg                  4MiB |
|    0   N/A  N/A      3469      G   /usr/lib/xorg/Xorg                  4MiB |
|    1   N/A  N/A      3217      G   /usr/lib/xorg/Xorg                110MiB |
|    1   N/A  N/A      3469      G   /usr/lib/xorg/Xorg                450MiB |
|    1   N/A  N/A      3627      G   /usr/bin/gnome-shell               79MiB |
|    1   N/A  N/A     36809      G   ...veSuggestionsOnlyOnDemand       28MiB |
|    1   N/A  N/A    112385      G   ...b/thunderbird/thunderbird      224MiB |
+-----------------------------------------------------------------------------+

```
But the GPU name and process names are usually too long to be displayed in the terminal. So I wrote this tool to display the GPU name and process names in a wider way.

# Installation

```
mkdir build
cd build
cmake ..
make
```


## Usage

```
./build/nvsmi
```
The output is as follows:

```
+--------------------------------------------------------------------------------------------------+
|Driver Version:     520.61.05                                                                     |
+--------------------------------------------------------------------------------------------------+
|GPU  Name                                                                                         |
|Fan  Temp Power:Usage/Cap     Memory-Usage        GPU-Util  SM                                    |
+==================================================================================================+
|0    NVIDIA RTX A5000                                                                             |
|30%  36C  19W/230W            318MiB/24564MiB     0%        8.6                                   |
|1    NVIDIA RTX A5000                                                                             |
|30%  31C  23W/230W            1217MiB/24564MiB    0%        8.6                                   |
+--------------------------------------------------------------------------------------------------+

+--------------------------------------------------------------------------------------------------+
|Processes:                                                                                        |
|GPU  PID       Type Process name                                                        GPU Memory|
|                                                                                        Usage     |
+==================================================================================================+
|0    3217      G    /usr/lib/xorg/Xorgvt1-displayfd3-auth/run/user/125/gdm/Xauthority-ba       4MB|
|0    3469      G    /usr/lib/xorg/Xorgvt7-displayfd3-auth/run/user/322038/gdm/Xauthority       4MB|
|1    3217      G    /usr/lib/xorg/Xorgvt1-displayfd3-auth/run/user/125/gdm/Xauthority-ba     110MB|
|1    3469      G    /usr/lib/xorg/Xorgvt7-displayfd3-auth/run/user/322038/gdm/Xauthority     450MB|
|1    3627      G    /usr/bin/gnome-shell                                                      79MB|
|1    36809     G    /usr/lib/slack/slack --type=gpu-process --enable-logging --enable-cr      28MB|
|1    112385    G    /usr/lib/thunderbird/thunderbird                                         224MB|
+--------------------------------------------------------------------------------------------------+

```