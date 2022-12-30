# nvsmi

A wider nvidia-smi.

An exmaple of nvidia-smi output is as follows:

```
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 525.60.13    Driver Version: 525.60.13    CUDA Version: 12.0     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  NVIDIA GeForce ...  On   | 00000000:09:00.0  On |                  N/A |
| 30%   45C    P0    25W /  75W |   1780MiB /  4096MiB |      9%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A      2618      G   /usr/lib/xorg/Xorg                714MiB |
|    0   N/A  N/A      2809      G   /usr/bin/gnome-shell              234MiB |
|    0   N/A  N/A      3846      G   /usr/lib/insync/insync              1MiB |
|    0   N/A  N/A     21388      G   ...6\extracted\WeChatApp.exe        3MiB |
|    0   N/A  N/A     23797      G   ...veSuggestionsOnlyOnDemand      460MiB |
|    0   N/A  N/A     31976      G   ...isable-features=ReadLater       86MiB |
|    0   N/A  N/A     32760      G   ...RendererForSitePerProcess      209MiB |
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
|Driver Version:                                                                                   |
+--------------------------------------------------------------------------------------------------+
|GPU  Name                                                                                         |
|Fan  Temp Power:Usage/Cap     Memory-Usage        |GPU-Util  |
+==================================================================================================+
|0    NVIDIA GeForce GTX 1650                                                                      |
|31%  45C  25W/75W             2085MiB/4096MiB     |8%        
+--------------------------------------------------------------------------------------------------+

|Processes:                                                                                        |
|GPU  PID       Type Process name                                                        GPU Memory|
|                                                                                        Usage     |
+==================================================================================================+
|0    2618      G    /usr/lib/xorg/Xorgvt2-displayfd3-auth/run/user/1000/gdm/Xauthority-n     714MB|
|0    2809      G    /usr/bin/gnome-shell                                                     226MB|
|0    3846      G    /usr/lib/insync/insyncstart                                                1MB|
|0    21388     G    C:\users\findhao\Application Data\Tencent\WeChat\XPlugin\Plugins\XWe       3MB|
|0    23797     G    /usr/lib/slack/slack --type=gpu-process --enable-logging --enable-cr     460MB|
|0    31976     G    /opt/google/chrome/chrome --type=gpu-process --crashpad-handler-pid=      61MB|
|0    32760     G    /usr/share/code/code --type=gpu-process --enable-crashpad --enable-c     322MB|
+--------------------------------------------------------------------------------------------------+
```