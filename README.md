# yakpro-vm-start
YAK Pro - VirtualBox Bridged Mode Nic Select and VM Start

If you are using VirtualBox with bridged mode network interface on a laptop computer,
you have to manually change the network interface each time you are switching
from RJ45/Wired to Wifi/Wireless

This little program will do the job automatically!  
if Wired interface is available, it chooses it othewise the Wireless one is chosen.  
Then the virtual machine is automatically launched!

This source code is for Windows Hosts, but can be easily adapted for Linux Hosts.

I have generated the program using Visual Studio Community 2015  
Specific options I have used:
 - no precompiled headers.
 - /D_CRT_SECURE_NO_WARNINGS 
 
### Warning: ###
If you want to use directly the exe and you do not have Visual Studio 2015 installed on your machine,
you will have to download and install "Visual C++ Redistributable for Visual Studio 2015"  
**vc_redist.x86.exe** from Microsoft Web Site!
https://www.microsoft.com/download/details.aspx?id=48145


### Usage: ###
 1. Set your working directory to the directory where VboxManage.exe is located.  
Usually "C:\Program Files\Oracle\VirtualBox"
 2. Use the following syntax to launch your VM:  
yakpro-vm-start "The Virtual Machine Name"

A convenient way is to create on your Desktop a shortcut to yakpro-vm-start.exe  
Set the start location to  "C:\Program Files\Oracle\VirtualBox" or wherever you installed VirtualBox.  
and set your VM Name (surrounded by double-quotes if it contains spaces) as an argument after yakpro-vm-start.exe  


### How the job is done? ###
VBoxManage.exe is call 3 times...  
  1. to list all available network interfaces.  
    **VBoxManage.exe list bridgedifs**  
  2. to select the good nic within the VM.  
    **VBoxManage.exe modifyvm "VM Name" --bridgeadapter1 "nic name"**  
  3. to launch the VM.  
    **VBoxManage.exe startvm "VM Name"**  

