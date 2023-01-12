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
| 32%   46C    P0    25W /  75W |   2239MiB /  4096MiB |      9%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A      2516      G   /usr/lib/xorg/Xorg                754MiB |
|    0   N/A  N/A      2697      G   /usr/bin/gnome-shell              253MiB |
|    0   N/A  N/A      4801      G   /usr/lib/insync/insync              1MiB |
|    0   N/A  N/A     55984      G   ...tracted\WeChatBrowser.exe        3MiB |
|    0   N/A  N/A     56666      G   ...6\extracted\WeChatApp.exe        3MiB |
|    0   N/A  N/A     56982      G   ...veSuggestionsOnlyOnDemand      293MiB |
|    0   N/A  N/A     57535      G   ...isable-features=ReadLater      693MiB |
|    0   N/A  N/A     62820      G   ...veSuggestionsOnlyOnDemand      165MiB |
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
|Driver Version:     525.60.13           CUDA Version:       12.0                                  |
+--------------------------------------------------------------------------------------------------+
|GPU  Name                                                                                         |
|Fan  Temp Power:Usage/Cap     Memory-Usage        GPU-Util  SM                                    |
+==================================================================================================+
|0    NVIDIA GeForce GTX 1650                                                                      |
|32%  46C  25W/75W             2247MiB/4096MiB     10%       7.5                                   |
+--------------------------------------------------------------------------------------------------+

+--------------------------------------------------------------------------------------------------+
|Processes:                                                                                        |
|GPU  PID       Type Process name                                                        GPU Memory|
|                                                                                        Usage     |
+==================================================================================================+
|0    2516      G    /usr/lib/xorg/Xorgvt2-displayfd3-auth/run/user/1000/gdm/Xauthority-n     754MB|
|0    2697      G    /usr/bin/gnome-shell                                                     253MB|
|0    4801      G    /usr/lib/insync/insyncstart                                                1MB|
|0    55984     G    C:\users\findhao\Application Data\Tencent\WeChat\XPlugin\Plugins\XWe       3MB|
|0    56666     G    C:\users\findhao\Application Data\Tencent\WeChat\XPlugin\Plugins\XWe       3MB|
|0    56982     G    /usr/lib/slack/slack --type=gpu-process --enable-logging --enable-cr     293MB|
|0    57535     G    /opt/google/chrome/chrome --type=gpu-process --crashpad-handler-pid=     688MB|
|0    62820     G    /usr/share/discord/Discord --type=gpu-process --enable-crashpad --cr     175MB|
+--------------------------------------------------------------------------------------------------+


```
