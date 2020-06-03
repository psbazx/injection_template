# dll_injection  
## 导入表注入(过于基础)  
对pe结构略微了解即可知道原理
就和新增节一样，新增一个导入表  
把待注入dll写入即可  
## 远程线程注入(remote_thread.c)  
流程:  
1.获取进程句柄  
2.VirtualAllocEx后WriteProcessMemory，把dll名称写入目标文件  
3.CreateRemoteThread 线程函数为LoadLibraryW，参数为 VirtualAllocEx返回值，即dll名称地址  
