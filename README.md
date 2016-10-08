# yakpro-vm-start
YAK Pro - VirtualBox Bridged Mode Nic Select and VM Start

If you are using VirtualBox with bridged mode network interface on a laptop computer,
you have to manually change the network interface each time you are switching
from RJ45/Wired to Wifi/Wireless

This little program will do the job automatically!
if Wired interface is available, it chooses it othewise the Wireless one is chosen.
Then the virtual machine is automatically launched!

This source code is for Windows Hosts, but can be easyly ported for Linux Hosts.

I have generated the program using Visual Studio Community 2015
Specific options I have used:
 - no precompiled headers.
 - /D_CRT_SECURE_NO_WARNINGS 
 
 
