#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 3) {
		printf("usage xxx.exe pid xxx.dll\n");		//使用方法
		exit(0);
	}
	HANDLE p = NULL;
	HANDLE t = NULL;
	HMODULE module = NULL;
	LPVOID namebuffer = NULL;  
	DWORD size = (DWORD)(_tcslen(argv[2]) + 1) * sizeof(TCHAR);		//dll名称长度
	LPTHREAD_START_ROUTINE pThreadProc;
	DWORD pid = (DWORD)_tstol(argv[1]);
	if (!(p = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid))) {	//打开远程进程
		printf("open process failed\n");
		exit(0);
	}

	namebuffer = VirtualAllocEx(p, NULL, size, MEM_COMMIT, PAGE_READWRITE); //分配空间

	WriteProcessMemory(p, namebuffer, (LPVOID)argv[2], size, NULL);			//写入dll name

	module = GetModuleHandle(L"kernel32.dll");//获取模块句柄
	pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(module, "LoadLibraryW");	//获取函数地址，这边转化成线程函数

	t = CreateRemoteThread(p, NULL, 0, pThreadProc, namebuffer, 0, NULL);	//创建远程线程，开始注入
	printf("start!\n");
	WaitForSingleObject(t, INFINITE);//等待结束
	CloseHandle(t);
	CloseHandle(p);
	printf("yes!\n");
	return 0;
}