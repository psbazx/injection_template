# dll_injection  
## 远程线程注入(remote_thread.c)  
流程:  
1.获取进程句柄  
2.VirtualAllocEx后WriteProcessMemory，把dll名称写入目标文件  
3.CreateRemoteThread 线程函数为LoadLibraryW，参数为 VirtualAllocEx返回值，即dll名称地址  
