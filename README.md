# dll_injection  
环境:win10 vs2019  
test.dll仅用于测试dll注入是否成功,主要功能就是弹个messagebox  
## 导入表注入(过于基础)  
对pe结构略微了解即可知道原理
就和新增节一样，新增一个导入表  
把待注入dll写入即可  
## 远程线程注入(remote_thread.c)  
流程:  
1.获取进程句柄  
2.VirtualAllocEx后WriteProcessMemory，把dll名称写入目标文件  
3.CreateRemoteThread 线程函数为LoadLibraryW，参数为 VirtualAllocEx返回值，即dll名称地址  
## 注册表注入(win10 AppInit_Dlls被限制，代码模板就不写了//摸)  
只要dll绝对路径位于注册表windows就会让加载了USER32.dll的进程自动加载该进程//dll注册表项记得改为1  

//to do
