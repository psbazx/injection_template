# injection  
环境:win10 vs2019  
test.dll仅用于测试dll注入是否成功,主要功能就是弹个messagebox  
## 导入表注入(过于基础)  
对pe结构略微了解即可知道原理  
就和新增节一样，新增一个导入表  
把待注入dll写入即可  
## Dll Search Order Hijacking(存在开源工具)  
也叫dll劫持，顾名思义。  
主要是利用了windows加载dll的搜索顺序，这边提一点:为了快速加载还有安全，windows会在注册表下创建键值，系统会优先加载这些已知dll，所以攻击方式就能通过添加dll路径的键值或者利用加载顺序在加载正确dll前优先加载自己的dll  
比较好理解,没什么门栏,现成工具也多可以了解一下  
## 远程线程注入(remote_thread.c)  
经典注入方式  
流程:  
1.获取进程句柄  
2.VirtualAllocEx后WriteProcessMemory，把dll名称写入目标文件  
3.CreateRemoteThread 线程函数为LoadLibraryW，参数为 VirtualAllocEx返回值，即dll名称地址  
## 注册表注入(win10 AppInit_Dlls被限制，代码模板就不写了//摸)  
只要dll绝对路径位于注册表windows就会让加载了USER32.dll的进程自动加载该进程//dll注册表项记得改为1  
## Process Hollowing  
见pe_shell decode.c代码  
## code-inject  
实习时写的，组长提了需求需要把木马shellcode注入到explorer.exe中运行，其实挺简单但花费时间太多了，基本就是把之前外挂的检测进程和远程线程注入的代码整合下，有个坑就是Unicode多字节问题修复加上分配内存页时忘记加可执行属性。。。但是x86中没有任何问题可能和历史遗留问题有关？101012分页模式下没有可执行标志位，但是开PAE就有了啊，没有搞懂为啥，当时x86测试没什么问题  
//to do  
