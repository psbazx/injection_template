# dll_injection  
## 远程线程注入  
流程:  
1.获取进程句柄  
2.VirtualAllocEx后WriteProcessMemory，向目标文件写入dll名称  
3.CreateRemoteThread 线程函数为LoadLibraryW，参数为 VirtualAllocEx返回值，即dll名称地址  
