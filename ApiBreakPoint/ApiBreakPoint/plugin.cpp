#include "plugin.h"

#ifdef _UNICODE
#error "USE ASCII CODE PAGE"
#endif

using namespace Script::Module;
using namespace Script::Symbol;
using namespace Script::Debug;
using namespace Script::Register;

// make sure only one window exists
bool bIsMainWindowShow = false;


HWND hTabControl;
HWND hMain;
int CurTab = 0;

// checkbox handle
HWND hChecks[CHECK_COUNT];



/*
 * Add API Breakpoint here.
 * You can change display text language here if you want.
 * Dll name are not necessary so far cause we are using "bp" rather than SetBPX()
 * If the function name appears in multiple dlls, the behavior depends on the bp instruction
 */
#define CHINESE
#ifdef CHINESE
ApiGroup Groups[TAB_COUNT] =
{
	{
		"��������",
		{
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","GetModuleHandleA","����ģ��"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetModuleHandleExA",""),
			ApiBreakPointInfo("","GetModuleHandleExW",""),
			ApiBreakPointInfo("","CreateFileA","��������ļ�"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","ReadFile","���ļ�"),
			ApiBreakPointInfo("","WriteFile","д�ļ�"),
			ApiBreakPointInfo("","DeleteFileA","ɾ���ļ�"),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","CreateThread","�����߳�"),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","OpenProcess","�򿪽���"),
			ApiBreakPointInfo("","WriteProcessMemory","�����д�ڴ�"),
			ApiBreakPointInfo("","ReadProcessMemory","����̶��ڴ�"),
			ApiBreakPointInfo("","CreateMutexA","����������"),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","OpenMutexA","�򿪻�����"),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","CreateToolhelp32SnapShot","ö�ٽ���"),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","Module32First","ö��ģ��"),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Process32First","ö�ٽ���"),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","Toolhelp32ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","GetTempPathA",""),
			ApiBreakPointInfo("","GetTempPathW",""),
			ApiBreakPointInfo("","CreateProcessA","��������"),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","ShellExecuteA",""),
			ApiBreakPointInfo("","ShellExecuteW",""),
			ApiBreakPointInfo("","WinExec",""),
			ApiBreakPointInfo("","UrlDownloadToFileA","�����ļ�"),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
			ApiBreakPointInfo("","GetDesktopWindow",""),
		}
	},
	{
		// https://anti-debug.checkpoint.com/
		"�Կ�����",
		{
			ApiBreakPointInfo("","IsDebuggerPresent","��������"),
			ApiBreakPointInfo("","CheckRemoteDebuggerPresent","��������"),
			ApiBreakPointInfo("","NtQueryInformationProcess","�����־λ������������⸸����"),
			ApiBreakPointInfo("","UnhandledExceptionFilter",""),
			ApiBreakPointInfo("","OutputDebugStringA","��������̽�������"),
			ApiBreakPointInfo("","OutputDebugStringW",""),
			ApiBreakPointInfo("","GetThreadContext","̽��Ӳ���ϵ�"),
			ApiBreakPointInfo("","GetProcessHeap","LFH:����Ƭ��"),
			ApiBreakPointInfo("","GetProcAddress","���HOOK"),
			ApiBreakPointInfo("","NtSetInformationThread","������������߳�"),
			ApiBreakPointInfo("","NtYieldExecution","��������"),
			ApiBreakPointInfo("","ReadProcessMemory","int3�ϵ���"),
			ApiBreakPointInfo("","VirtualProtect","�޸��ڴ�Ȩ�޴����쳣��������"),
			ApiBreakPointInfo("","VirtualProtectEx","�޸��ڴ�Ȩ�޴����쳣��������"),
			ApiBreakPointInfo("","RtlQueryProcessHeapInformation","�ѱ�־λ��������"),
			ApiBreakPointInfo("","RtlQueryProcessDebugInformation","�ѱ�־λ��������"),
			ApiBreakPointInfo("","NtQuerySystemInformation","��������"),
			ApiBreakPointInfo("","OpenProcess","��csrss.exe�ɹ���ʾ�е�����"),
			ApiBreakPointInfo("","CreateFileA","��ռ��ʽ���ļ���ʧ�ܱ�ʾ�е�����"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","NtClose","����EXCEPTION_INVALID_HANDLE�쳣��ʾ���ڵ�����"),
			ApiBreakPointInfo("","CloseHandle",""),
			ApiBreakPointInfo("","NtQueryObject","̽����Զ���"),
			ApiBreakPointInfo("","SetUnhandledExceptionFilter","������ڵ���������ص�������"),
			ApiBreakPointInfo("","RaiseException","�׳�DBG_CONTROL_C�������쳣��δ�ӹ����е�����"),
			ApiBreakPointInfo("","RtlRaiseException","�׳�DBG_CONTROL_C�������쳣��δ�ӹ����е�����"),
			ApiBreakPointInfo("","GetLocalTime","ִ�к�ʱ���㣬��ʱ��Ϊ������"),
			ApiBreakPointInfo("","GetSystemTime","ִ�к�ʱ���㣬��ʱ��Ϊ������"),
			ApiBreakPointInfo("","GetTickCount","ִ�к�ʱ���㣬��ʱ��Ϊ������"),
			ApiBreakPointInfo("","NtGetTickCount","ִ�к�ʱ���㣬��ʱ��Ϊ������"),
			ApiBreakPointInfo("","QueryPerformanceCounter","ִ�к�ʱ���㣬��ʱ��Ϊ������"),
			ApiBreakPointInfo("","timeGetTime","ִ�к�ʱ���㣬��ʱ��Ϊ������"),
			ApiBreakPointInfo("","NtQueryVirtualMemory","�ڴ�ϵ���"),
			ApiBreakPointInfo("","AddVectoredExceptionHandler","ע��VEH"),
			ApiBreakPointInfo("","RemoveVectoredExceptionHandler","�Ƴ�VEH"),
			ApiBreakPointInfo("","DebugActiveProcess","�����ӽ��̵����Լ�"),
			ApiBreakPointInfo("","DbgUiDebugActiveProcess","�����ӽ��̵����Լ�"),
			ApiBreakPointInfo("","NtDebugActiveProcess","�����ӽ��̵����Լ�"),
			ApiBreakPointInfo("","SetConsoleCtrlHandler","����CTRL_C_EVENT�쳣"),
			ApiBreakPointInfo("","BlockInput","һֱ����TRUE������HOOK"),
			ApiBreakPointInfo("","EnumWindows","��⸸���̴��ڱ���"),
			ApiBreakPointInfo("","SwitchDesktop","�л����淴����"),
			ApiBreakPointInfo("","FindWindowA","̽���������������"),
			ApiBreakPointInfo("","FindWindowW","̽���������������"),
			ApiBreakPointInfo("","FindWindowExA","̽���������������"),
			ApiBreakPointInfo("","FindWindowExW","̽���������������"),
			ApiBreakPointInfo("","DbgSetDebugFilterState",""),
			ApiBreakPointInfo("","SwitchToThread",""),
			ApiBreakPointInfo("","GetWriteWatch",""),
		}
	},
	{
		"ע��",
		{
		}
	},
	{
		"����",
		{
			ApiBreakPointInfo("","send",""),
			ApiBreakPointInfo("","sendto",""),
			ApiBreakPointInfo("","WSASend",""),
			ApiBreakPointInfo("","WSASendTo",""),
			ApiBreakPointInfo("","recv",""),
			ApiBreakPointInfo("","inet_addr",""),
			ApiBreakPointInfo("","connect",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
		}
	},
	{
		"�Ի���",
		{
			ApiBreakPointInfo("","MessageBoxA","���Ի���"),
			ApiBreakPointInfo("","MessageBoxW",""),
			ApiBreakPointInfo("","MessageBoxExA",""),
			ApiBreakPointInfo("","MessageBoxExW",""),
			ApiBreakPointInfo("","MessageBoxIndirectA",""),
			ApiBreakPointInfo("","MessageBoxIndirectW",""),
			ApiBreakPointInfo("","CreateWindowExA","��������"),
			ApiBreakPointInfo("","CreateWindowExW",""),
			ApiBreakPointInfo("","CreateWindowA",""),
			ApiBreakPointInfo("","CreateWindowW",""),
			ApiBreakPointInfo("","DestroyWindow","���ٴ���"),
			ApiBreakPointInfo("","DialogBoxA","ģ̬�Ի���"),
			ApiBreakPointInfo("","DialogBoxW",""),
			ApiBreakPointInfo("","DialogBoxParamA",""),
			ApiBreakPointInfo("","DialogBoxParamW",""),
			ApiBreakPointInfo("","DialogBoxIndirectA",""),
			ApiBreakPointInfo("","DialogBoxIndirectW",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamA",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamW",""),
			ApiBreakPointInfo("","EndDialog","���ģ̬�Ի���"),
			ApiBreakPointInfo("","GetWindowTextA","ȡ�ؼ��ı�"),
			ApiBreakPointInfo("","GetWindowTextW",""),
			ApiBreakPointInfo("","SetWindowTextA","���ÿؼ��ı�"),
			ApiBreakPointInfo("","SetWindowTextW",""),
			ApiBreakPointInfo("","GetDlgItemTextA","ȡ�ؼ��ı�"),
			ApiBreakPointInfo("","GetDlgItemTextW",""),
			ApiBreakPointInfo("","SetDlgItemTextA","���ÿؼ��ı�"),
			ApiBreakPointInfo("","SetDlgItemTextW",""),
			ApiBreakPointInfo("","GetDlgItemInt","ȡ�ؼ�������"),
			ApiBreakPointInfo("","SetDlgItemInt","���ÿؼ�������"),
			ApiBreakPointInfo("","SendMessageA","����Ϣ"),
			ApiBreakPointInfo("","SendMessageW","����Ϣ"),
			ApiBreakPointInfo("","SendDlgItemMessage","����Ϣ"),
			ApiBreakPointInfo("","IsDialogMessageA",""),
			ApiBreakPointInfo("","IsDialogMessageW",""),
			ApiBreakPointInfo("","DispatchMessageA","��Ϣ�ɷ�"),
			ApiBreakPointInfo("","DispatchMessageW",""),
			ApiBreakPointInfo("","CallWindowProcA","���ô��ڹ���"),
			ApiBreakPointInfo("","CallWindowProcW",""),
			ApiBreakPointInfo("","DefWindowProcA","Ĭ����Ϣ����"),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","MessageBeep","ϵͳ������"),
			ApiBreakPointInfo("","DrawTextA","�ı���浽������"),
			ApiBreakPointInfo("","DrawTextW",""),
			ApiBreakPointInfo("","DrawTextExA",""),
			ApiBreakPointInfo("","DrawTextExW",""),
			ApiBreakPointInfo("","FindWindowA","��ȡ���ھ��"),
			ApiBreakPointInfo("","FindWindowW",""),
			ApiBreakPointInfo("","GetClipboardData","��ȡ����������"),
			ApiBreakPointInfo("","CoInitialize","��ʼ��COM��"),
			ApiBreakPointInfo("","CoCreateInstance","����COM����"),
			ApiBreakPointInfo("","LoadIconA","����ͼ����Դ"),
			ApiBreakPointInfo("","LoadIconW",""),
			ApiBreakPointInfo("","SetWindowLongA","���ô�������"),
			ApiBreakPointInfo("","SetWindowLongW",""),
			ApiBreakPointInfo("","SetWindowLongPtrA",""),
			ApiBreakPointInfo("","SetWindowLongPtrW",""),
			ApiBreakPointInfo("","ShowWindow","��ʾ����"),
			ApiBreakPointInfo("","UpdateWindow","���´���"),
			ApiBreakPointInfo("","TranslateMessage","��Ϣ����"),
			ApiBreakPointInfo("","GetMessageA","ȡ��Ϣ����"),
			ApiBreakPointInfo("","GetMessageW",""),
			ApiBreakPointInfo("","PeekMessageA","����Ϣ����"),
			ApiBreakPointInfo("","PeekMessageW",""),
			ApiBreakPointInfo("","SetMenu","���˵�"),
			ApiBreakPointInfo("","DestroyMenu","ɾ���˵�"),
			ApiBreakPointInfo("","DeleteMenu","ɾ���˵���"),
			ApiBreakPointInfo("","EnableMenuItem","�˵����ޱ��"),
			ApiBreakPointInfo("","EnableWindow","��ֹ�����������"),
		}
	},
	{
		"�ļ�����",
		{
			ApiBreakPointInfo("","CreateFileA","��������ļ�"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","OpenFile","���ļ�"),
			ApiBreakPointInfo("","ReadFile","���ļ�"),
			ApiBreakPointInfo("","WriteFile","д�ļ�"),
			ApiBreakPointInfo("","GetFileSize","ȡ�ļ���С"),
			ApiBreakPointInfo("","FindFirstFileA","�����ļ�"),
			ApiBreakPointInfo("","FindFirstFileW",""),
			ApiBreakPointInfo("","GetModuleFileNameA","��ģ��·��"),
			ApiBreakPointInfo("","GetModuleFileNameW",""),
			ApiBreakPointInfo("","OpenFileMappingA","���ļ�ӳ�����"),
			ApiBreakPointInfo("","OpenFileMappingW",""),
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","CreateFileMappingA","�����ļ�����"),
			ApiBreakPointInfo("","CreateFileMappingW",""),
			ApiBreakPointInfo("","CopyFileA","�����ļ�"),
			ApiBreakPointInfo("","CopyFileW",""),
			ApiBreakPointInfo("","CopyFileExA",""),
			ApiBreakPointInfo("","CopyFileExW",""),
			ApiBreakPointInfo("","SetFilePointer","�����ļ���дλ��"),
			ApiBreakPointInfo("","MoveFileA","�ƶ��ļ�"),
			ApiBreakPointInfo("","MoveFileW",""),
			ApiBreakPointInfo("","MoveFileExA",""),
			ApiBreakPointInfo("","MoveFileExW",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW","ɾ���ļ�"),
			ApiBreakPointInfo("","LoadCursorFromFileA","�����ļ����"),
			ApiBreakPointInfo("","LoadCursorFromFileW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA","INI������֤����"),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","GetPrivateProfileIntA",""),
			ApiBreakPointInfo("","GetPrivateProfileIntW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA","ȡ�ַ���"),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","WritePrivateProfileStringA","�����ַ���"),
			ApiBreakPointInfo("","WritePrivateProfileStringW",""),
		}
	},
	{
		"ʱ�䴦��",
		{
			ApiBreakPointInfo("","SetSystemTime","����ϵͳʱ��"),
			ApiBreakPointInfo("","TimerProc","�ص�����"),//what is this
			ApiBreakPointInfo("","SetLocalTime","���ñ���ʱ��"),
			ApiBreakPointInfo("","GetLocalTime","��ȡ����ʱ��"),
			ApiBreakPointInfo("","GetSystemTime","��ȡϵͳʱ��"),
			ApiBreakPointInfo("","GetCurrentTime","��ȡϵͳʱ��"),
			ApiBreakPointInfo("","GetFileTime","��ȡ�ļ�ʱ��"),
			ApiBreakPointInfo("","GetTickCount","ϵͳ�������������ĺ�����"),
			ApiBreakPointInfo("","CompareFileTime","�Ƚ��ļ�ʱ��"),
			ApiBreakPointInfo("","SetTimer","������ʱ��"),
			ApiBreakPointInfo("","KillTimer","�Ƴ���ʱ��"),
			ApiBreakPointInfo("","timeSetEvent","��ý�嶨ʱ��"),
		}
	},
	{
		"���̺���",
		{
			ApiBreakPointInfo("","CreateThread","�����߳�"),
			ApiBreakPointInfo("","CreateRemoteThread","����Զ���߳�"),
			ApiBreakPointInfo("","GetModuleHandleA","��ģ���ַ"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","OpenMutexA","�򿪻�����"),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","WriteProcessMemory","д�ڴ�"),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory","���ڴ�"),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
			ApiBreakPointInfo("","CreateProcessA","��������"),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","OpenProcess","�򿪽���"),
			ApiBreakPointInfo("","ExitProcess","��������"),
			ApiBreakPointInfo("","ExitThread","������ǰ�߳�"),
			ApiBreakPointInfo("","TerminateProcess","��ֹ����"),
			ApiBreakPointInfo("","TerminateThread","��ֹ�߳�"),
			ApiBreakPointInfo("","CreateToolhelp32Snapshot","���̿���"),
			ApiBreakPointInfo("","Process32First","ȡ���̾��"),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","Module32Next","ȡģ����"),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Heap32ListFirst","ȡ�Ѿ��"),
			ApiBreakPointInfo("","Heap32ListNext","ȡ�Ѿ��"),
			ApiBreakPointInfo("","GetProcessHeap","ȡ�Ѿ��"),
			ApiBreakPointInfo("","Heap32First","ȡ���̶������Ϣ"),
			ApiBreakPointInfo("","Heap32Next","ȡ���̶������Ϣ"),
			ApiBreakPointInfo("","PostQuitMessage","��ֹ�߳�"),
			ApiBreakPointInfo("","IsDebuggerPresent","��������"),
			ApiBreakPointInfo("","OpenProcessToken","��ȡ���̷������ƾ��"),
			ApiBreakPointInfo("","OpenThreadToken",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
		}
	},
	{
		"�ڴ�",
		{
			ApiBreakPointInfo("","FindWindow","ȡ���ھ��"),
			ApiBreakPointInfo("","GetWindowThreadProcessId","��ȡ���ڽ���ID"),
			ApiBreakPointInfo("","OpenProcess","�򿪽���"),
			ApiBreakPointInfo("","VirtualAllocEx","�����ڴ�"),
			ApiBreakPointInfo("","WriteProcessMemory","д�ڴ�"),
			ApiBreakPointInfo("","ReadProcessMemory","���ڴ�"),
			ApiBreakPointInfo("","CreateRemoteThread","����Զ���߳�"),
			ApiBreakPointInfo("","CreateMutexA","����������"),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","GetModuleHandleA","��ģ���ַ"),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetProcAddress","�麯����ַ"),
			ApiBreakPointInfo("","VirtualAlloc","�����ڴ�"),
			ApiBreakPointInfo("","HeapAlloc",""),
			ApiBreakPointInfo("","VirtualFree","�ͷ��ڴ�"),
			ApiBreakPointInfo("","HeapFree",""),
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","GetVersion","��ȡϵͳ�汾"),
			ApiBreakPointInfo("","ZwAllocateVirtualMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
		}
	},
	{
		"����",
		{
			ApiBreakPointInfo("","GetDiskFreeSpaceA","��ȡ������Ϣ"),
			ApiBreakPointInfo("","GetDiskFreeSpaceExA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExW",""),
			ApiBreakPointInfo("","GetDriveTypeA","�жϴ�������������"),
			ApiBreakPointInfo("","GetDriveTypeW",""),
			ApiBreakPointInfo("","GetLogicalDrives","ȡ��������ĸ"),
			ApiBreakPointInfo("","GetLogicalDriveStringsA","ȡ������·��"),
			ApiBreakPointInfo("","GetLogicalDriveStringsW",""),
		}
	},
	{
		"ע���",
		{
			ApiBreakPointInfo("","RegOpenKeyA","��ע�����"),
			ApiBreakPointInfo("","RegOpenKeyW",""),
			ApiBreakPointInfo("","RegOpenKeyExA","������֤����"),
			ApiBreakPointInfo("","RegOpenKeyExW",""),
			ApiBreakPointInfo("","RegCreateKeyExA",""),
			ApiBreakPointInfo("","RegCreateKeyExW",""),
			ApiBreakPointInfo("","RegQueryValueA","ȡע����ֵ"),
			ApiBreakPointInfo("","RegQueryValueW",""),
			ApiBreakPointInfo("","RegQueryValueExA",""),
			ApiBreakPointInfo("","RegQueryValueExW",""),
			ApiBreakPointInfo("","RegCreateKeyA","��������"),
			ApiBreakPointInfo("","RegCreateKeyW",""),
			ApiBreakPointInfo("","RegCloseKey","�ر�ע���"),
			ApiBreakPointInfo("","RegDeleteKeyA","ɾ����ֵ"),
			ApiBreakPointInfo("","RegDeleteKeyW",""),
			ApiBreakPointInfo("","RegEnumKeyExA","ö������"),
			ApiBreakPointInfo("","RegEnumKeyExW",""),
			ApiBreakPointInfo("","RegSetValueA","����Ĭ��ֵ"),
			ApiBreakPointInfo("","RegSetValueW",""),
			ApiBreakPointInfo("","RegSetValueExA","����ָ�����ֵ"),
			ApiBreakPointInfo("","RegSetValueExW",""),
		}
	},
	{
		"VB",
		{
			ApiBreakPointInfo("","FindResourceA","VBУ��"),
			ApiBreakPointInfo("","CreateFileA","VBУ��"),
			ApiBreakPointInfo("","GetVolumeInformation","���̾�"),
			ApiBreakPointInfo("","MultiByteToWideChar","AתU�ַ���"),
			ApiBreakPointInfo("","WideCharToMultiByte","UתA�ַ���"),
			ApiBreakPointInfo("","GetFileSize","��ȡ�ļ���С"),
			ApiBreakPointInfo("","VarCyFromStr","�ַ���ת����"),
			ApiBreakPointInfo("","arBstrFromI2","����ת�ַ���"),
			ApiBreakPointInfo("","rtcFileLen","VB��У��"),
			ApiBreakPointInfo("","rtcFileLenth",""),
			ApiBreakPointInfo("","rtcMsgBox","��ʾ�Ի���"),
			ApiBreakPointInfo("","rtcInputBox","�����"),
			ApiBreakPointInfo("","GetMemStr",""),
			ApiBreakPointInfo("","rtcR8ValFromBstr",""),
			ApiBreakPointInfo("","rtcGetPresendDate",""),
			ApiBreakPointInfo("","rtcBeep",""),
			ApiBreakPointInfo("","rtcTrimBstr","�ַ���ȥ���ո�"),
			ApiBreakPointInfo("","rtcMidCharVar","�ַ�����ȡ�ַ�"),
			ApiBreakPointInfo("","rtcLeftCharVar","�ַ������ȡ�ַ�"),
			ApiBreakPointInfo("","rtcRightCharVar","�ַ����ұ�ȡ�ַ�"),
			ApiBreakPointInfo("","StrConv","ת���ַ���"),
			ApiBreakPointInfo("","rtcT8ValFromBstr","�ַ���ת������"),
			ApiBreakPointInfo("","__vbaI2Str","�ַ�ת1�ֽ���ֵ"),
			ApiBreakPointInfo("","__vbaI4Str","�ַ�ת4�ֽ���ֵ"),
			ApiBreakPointInfo("","__vbar4Str","�ַ�ת4������"),
			ApiBreakPointInfo("","__vbar8Str","�ַ�ת8������"),
			ApiBreakPointInfo("","__vbavaradd","����ֵ���"),
			ApiBreakPointInfo("","__vbavarsub","����ֵ���"),
			ApiBreakPointInfo("","__vbavarmul","����ֵ���"),
			ApiBreakPointInfo("","__vbavaridiv","����ֵ���"),
			ApiBreakPointInfo("","__vbavarxor","����ֵ���"),
			ApiBreakPointInfo("","__vbavarcat","����ֵ����"),
			ApiBreakPointInfo("","__vbaStrCat","�ַ�������"),
			ApiBreakPointInfo("","__vbaVarCat","�����ִ�"),
			ApiBreakPointInfo("","__vbaStrCmp","�ַ����Ƚ�"),
			ApiBreakPointInfo("","__vbaStrComp","�ַ����Ƚ�"),
			ApiBreakPointInfo("","__vbaVarTstEq","�Ƚϱ���"),
			ApiBreakPointInfo("","__vbaFreeStr",""),
			ApiBreakPointInfo("","__vbaStrCopy",""),
			ApiBreakPointInfo("","__vbaLenBstr",""),
			ApiBreakPointInfo("","__vbavarfornext","ѭ���ṹ"),
			ApiBreakPointInfo("","__vbafreeobj","�ͷŶ���"),
		}
	},
	{
		"VC/MFC",
		{
			ApiBreakPointInfo("","lstrcmpA","�ַ����Ƚ�"),
			ApiBreakPointInfo("","DefWindowProcA","����Ĭ�ϴ��ڹ���"),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","RegisterClassA","ע�ᴰ����"),
			ApiBreakPointInfo("","RegisterClassW",""),
			ApiBreakPointInfo("","RegisterClassExA",""),
			ApiBreakPointInfo("","RegisterClassExW",""),
			ApiBreakPointInfo("","FindResourceA","������Դ"),
			ApiBreakPointInfo("","FindResourceW",""),
			ApiBreakPointInfo("","LoadResource","������Դ"),
			ApiBreakPointInfo("","SetHandleCount","ȡ������ַ"),
			ApiBreakPointInfo("","IsWindowEnabled","�ɷ��������"),
		}
	},
	{
		"���ܹ�/��ɽ��",
		{
			ApiBreakPointInfo("","CreateThread","Ѱ��OEP"),
			ApiBreakPointInfo("","GetModuleHandleA","ħ����ת"),
			ApiBreakPointInfo("","OpenMutexA","1ת���������θ���"),
			ApiBreakPointInfo("","GetSystemTime","����KEY"),
			ApiBreakPointInfo("","VirtualProtect","2EAXΪ401000����"),
			ApiBreakPointInfo("","CreateFileMappingA","����"),
			ApiBreakPointInfo("","LoadLibraryA","����DLL"),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","RefreshDeviceList","��˼3"),
			ApiBreakPointInfo("","DeviceIoControl","�����豸"),
			ApiBreakPointInfo("","Prestochangoselector",""),
			ApiBreakPointInfo("","FreeEnvironmentStringsA","�ͷŻ����ִ���"),
			ApiBreakPointInfo("","GetLogicalDriveStringsA","ȡ�б�"),
			ApiBreakPointInfo("","GetLogicalDrives","ȡ�������б�"),
			ApiBreakPointInfo("","GetDriveTypeA","�ж�����������"),
			ApiBreakPointInfo("","CreateFileA","��������"),
			ApiBreakPointInfo("","FindFirstFileA","�����ļ�"),
		}
	},
	{
		"����",
		{
			ApiBreakPointInfo("","FindFirstFileA","�����ļ�"),
			ApiBreakPointInfo("","ExitProcess","�����˳�"),
			ApiBreakPointInfo("","GetStartupInfoA","��ȡ������Ϣ"),
			ApiBreakPointInfo("","GetFileSize","��ȡ�ļ���С"),
			ApiBreakPointInfo("","VirtualProtect","Vmp�ѿ�"),
			ApiBreakPointInfo("","ExitWindowsEx","�ػ��ϵ�"),
			ApiBreakPointInfo("","CreateFileA","��У��"),
			ApiBreakPointInfo("","GetVersion","�������ѿ�"),
			ApiBreakPointInfo("","send","���ͷ��"),
			ApiBreakPointInfo("","WSASend","���ͷ��"),
			ApiBreakPointInfo("","recv","���շ��"),
			ApiBreakPointInfo("","RtlAdjustPrivilege","�����Կ��ٹػ�"),
			ApiBreakPointInfo("","SHFormatDrive","����API"),
			ApiBreakPointInfo("","RemoveDirectoryA","ɾ��Ŀ¼"),
			ApiBreakPointInfo("","DeleteFileA","ɾ���ļ�"),
			ApiBreakPointInfo("","GetLastError","���ش�����"),
		}
	},
};

#else

ApiGroup Groups[TAB_COUNT] =
{
	{
		"Common",
		{
			ApiBreakPointInfo("","FindFirstFileA","search file"),
			ApiBreakPointInfo("","ExitProcess",""),
			ApiBreakPointInfo("","GetStartupInfoA",""),
			ApiBreakPointInfo("","GetFileSize",""),
			ApiBreakPointInfo("","VirtualProtect","modify memory protect"),
			ApiBreakPointInfo("","ExitWindowsEx","shutdown breakpoint"),
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","GetVersion",""),
			ApiBreakPointInfo("","send",""),
			ApiBreakPointInfo("","WSASend",""),
			ApiBreakPointInfo("","recv",""),
			ApiBreakPointInfo("","RtlAdjustPrivilege",""),
			ApiBreakPointInfo("","SHFormatDrive","Format Disk"),
			ApiBreakPointInfo("","RemoveDirectoryA",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","GetLastError",""),
		}
	},
	{
		"Dialog",
		{
			ApiBreakPointInfo("","MessageBoxA","popup a message box"),
			ApiBreakPointInfo("","MessageBoxW",""),
			ApiBreakPointInfo("","MessageBoxExA",""),
			ApiBreakPointInfo("","MessageBoxExW",""),
			ApiBreakPointInfo("","MessageBoxIndirectA",""),
			ApiBreakPointInfo("","MessageBoxIndirectW",""),
			ApiBreakPointInfo("","GetWindowTextA","get control text"),
			ApiBreakPointInfo("","GetWindowTextW",""),
			ApiBreakPointInfo("","SetWindowTextA","set control text"),
			ApiBreakPointInfo("","SetWindowTextW",""),
			ApiBreakPointInfo("","GetDlgItemTextA",""),
			ApiBreakPointInfo("","GetDlgItemTextW",""),
			ApiBreakPointInfo("","SetDlgItemTextA","set control text"),
			ApiBreakPointInfo("","SetDlgItemTextW",""),
			ApiBreakPointInfo("","GetDlgItemInt",""),
			ApiBreakPointInfo("","SetDlgItemInt",""),
			ApiBreakPointInfo("","SendMessageA",""),
			ApiBreakPointInfo("","SendMessageW",""),
			ApiBreakPointInfo("","SendDlgItemMessage",""),
			ApiBreakPointInfo("","IsDialogMessageA",""),
			ApiBreakPointInfo("","IsDialogMessageW",""),
			ApiBreakPointInfo("","DispatchMessageA",""),
			ApiBreakPointInfo("","DispatchMessageW",""),
			ApiBreakPointInfo("","CallWindowProcA",""),
			ApiBreakPointInfo("","CallWindowProcW",""),
			ApiBreakPointInfo("","DefWindowProcA",""),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","MessageBeep",""),
			ApiBreakPointInfo("","DrawTextA",""),
			ApiBreakPointInfo("","DrawTextW",""),
			ApiBreakPointInfo("","DrawTextExA",""),
			ApiBreakPointInfo("","DrawTextExW",""),
			ApiBreakPointInfo("","FindWindowA",""),
			ApiBreakPointInfo("","FindWindowW",""),
			ApiBreakPointInfo("","GetClipboardData",""),
			ApiBreakPointInfo("","CoInitialize","initialize COM library"),
			ApiBreakPointInfo("","CoCreateInstance","create COM instance"),
			ApiBreakPointInfo("","LoadIconA",""),
			ApiBreakPointInfo("","LoadIconW",""),
			ApiBreakPointInfo("","SetWindowLongA","change window attribute"),
			ApiBreakPointInfo("","SetWindowLongW",""),
			ApiBreakPointInfo("","SetWindowLongPtrA",""),
			ApiBreakPointInfo("","SetWindowLongPtrW",""),
			ApiBreakPointInfo("","ShowWindow",""),
			ApiBreakPointInfo("","UpdateWindow",""),
			ApiBreakPointInfo("","CreateWindowExA",""),
			ApiBreakPointInfo("","CreateWindowExW",""),
			ApiBreakPointInfo("","CreateWindowA",""),
			ApiBreakPointInfo("","CreateWindowW",""),
			ApiBreakPointInfo("","DestroyWindow",""),
			ApiBreakPointInfo("","DialogBoxA",""),
			ApiBreakPointInfo("","DialogBoxW",""),
			ApiBreakPointInfo("","DialogBoxParamA",""),
			ApiBreakPointInfo("","DialogBoxParamW",""),
			ApiBreakPointInfo("","DialogBoxIndirectA",""),
			ApiBreakPointInfo("","DialogBoxIndirectW",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamA",""),
			ApiBreakPointInfo("","DialogBoxIndirectParamW",""),
			ApiBreakPointInfo("","EndDialog",""),
			ApiBreakPointInfo("","TranslateMessage",""),
			ApiBreakPointInfo("","GetMessageA",""),
			ApiBreakPointInfo("","GetMessageW",""),
			ApiBreakPointInfo("","PeekMessageA",""),
			ApiBreakPointInfo("","PeekMessageW",""),
			ApiBreakPointInfo("","SetMenu",""),
			ApiBreakPointInfo("","DestroyMenu",""),
			ApiBreakPointInfo("","DeleteMenu",""),
			ApiBreakPointInfo("","EnableMenuItem",""),
			ApiBreakPointInfo("","EnableWindow",""),
		}
	},
	{
		"File",
		{
			ApiBreakPointInfo("","CreateFileA","create or open file"),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","OpenFile",""),
			ApiBreakPointInfo("","ReadFile",""),
			ApiBreakPointInfo("","WriteFile",""),
			ApiBreakPointInfo("","GetFileSize",""),
			ApiBreakPointInfo("","FindFirstFileA",""),
			ApiBreakPointInfo("","FindFirstFileW",""),
			ApiBreakPointInfo("","GetModuleFileNameA",""),
			ApiBreakPointInfo("","GetModuleFileNameW",""),
			ApiBreakPointInfo("","OpenFileMappingA",""),
			ApiBreakPointInfo("","OpenFileMappingW",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetModuleHandleExA",""),
			ApiBreakPointInfo("","GetModuleHandleExW",""),
			ApiBreakPointInfo("","CreateFileMappingA",""),
			ApiBreakPointInfo("","CreateFileMappingW",""),
			ApiBreakPointInfo("","CopyFileA",""),
			ApiBreakPointInfo("","CopyFileW",""),
			ApiBreakPointInfo("","CopyFileExA",""),
			ApiBreakPointInfo("","CopyFileExW",""),
			ApiBreakPointInfo("","SetFilePointer",""),
			ApiBreakPointInfo("","MoveFileA",""),
			ApiBreakPointInfo("","MoveFileW",""),
			ApiBreakPointInfo("","MoveFileExA",""),
			ApiBreakPointInfo("","MoveFileExW",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","LoadCursorFromFileA",""),
			ApiBreakPointInfo("","LoadCursorFromFileW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA",""),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","GetPrivateProfileIntA",""),
			ApiBreakPointInfo("","GetPrivateProfileIntW",""),
			ApiBreakPointInfo("","GetPrivateProfileStringA",""),
			ApiBreakPointInfo("","GetPrivateProfileStringW",""),
			ApiBreakPointInfo("","WritePrivateProfileStringA",""),
			ApiBreakPointInfo("","WritePrivateProfileStringW",""),
		}
	},
	{
		"Register",
		{
			ApiBreakPointInfo("","RegOpenKeyA",""),
			ApiBreakPointInfo("","RegOpenKeyW",""),
			ApiBreakPointInfo("","RegOpenKeyExA",""),
			ApiBreakPointInfo("","RegOpenKeyExW",""),
			ApiBreakPointInfo("","RegCreateKeyExA",""),
			ApiBreakPointInfo("","RegCreateKeyExW",""),
			ApiBreakPointInfo("","RegQueryValueA",""),
			ApiBreakPointInfo("","RegQueryValueW",""),
			ApiBreakPointInfo("","RegQueryValueExA",""),
			ApiBreakPointInfo("","RegQueryValueExW",""),
			ApiBreakPointInfo("","RegCreateKeyA",""),
			ApiBreakPointInfo("","RegCreateKeyW",""),
			ApiBreakPointInfo("","RegCloseKey",""),
			ApiBreakPointInfo("","RegDeleteKeyA",""),
			ApiBreakPointInfo("","RegDeleteKeyW",""),
			ApiBreakPointInfo("","RegEnumKeyExA",""),
			ApiBreakPointInfo("","RegEnumKeyExW",""),
			ApiBreakPointInfo("","RegSetValueA",""),
			ApiBreakPointInfo("","RegSetValueW",""),
			ApiBreakPointInfo("","RegSetValueExA",""),
			ApiBreakPointInfo("","RegSetValueExW",""),
		}
	},
	{
		"Time/Date",
		{
			ApiBreakPointInfo("","SetSystemTime",""),
			ApiBreakPointInfo("","TimerProc",""),//what is this
			ApiBreakPointInfo("","SetLocalTime",""),
			ApiBreakPointInfo("","GetLocalTime",""),
			ApiBreakPointInfo("","GetSystemTime",""),
			ApiBreakPointInfo("","GetCurrentTime",""),
			ApiBreakPointInfo("","GetFileTime",""),
			ApiBreakPointInfo("","GetTickCount",""),
			ApiBreakPointInfo("","CompareFileTime",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","KillTimer",""),
			ApiBreakPointInfo("","timeSetEvent",""),
		}
	},
	{
		"Process",
		{
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
			ApiBreakPointInfo("","CreateProcessA",""),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","OpenProcess",""),
			ApiBreakPointInfo("","ExitProcess",""),
			ApiBreakPointInfo("","ExitThread",""),
			ApiBreakPointInfo("","TerminateProcess",""),
			ApiBreakPointInfo("","TerminateThread",""),
			ApiBreakPointInfo("","CreateToolhelp32Snapshot","enum process"),
			ApiBreakPointInfo("","Process32First",""),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","GetProcessHeap",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","IsDebuggerPresent",""),
			ApiBreakPointInfo("","OpenProcessToken",""),
			ApiBreakPointInfo("","OpenThreadToken",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
		}
	},
	{
		"Network",
		{
			ApiBreakPointInfo("","send",""),
			ApiBreakPointInfo("","sendto",""),
			ApiBreakPointInfo("","WSASend",""),
			ApiBreakPointInfo("","WSASendTo",""),
			ApiBreakPointInfo("","recv",""),
			ApiBreakPointInfo("","inet_addr",""),
			ApiBreakPointInfo("","connect",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
		}
	},
	{
		"Memory",
		{
			ApiBreakPointInfo("","FindWindow",""),
			ApiBreakPointInfo("","GetWindowThreadProcessId",""),
			ApiBreakPointInfo("","OpenProcess",""),
			ApiBreakPointInfo("","VirtualAllocEx",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","CreateMutexA",""),
			ApiBreakPointInfo("","CreateMutexW",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","GetModuleHandleW",""),
			ApiBreakPointInfo("","GetProcAddress",""),
			ApiBreakPointInfo("","VirtualAlloc",""),
			ApiBreakPointInfo("","HeapAlloc",""),
			ApiBreakPointInfo("","VirtualFree",""),
			ApiBreakPointInfo("","HeapFree",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","GetVersion",""),
			ApiBreakPointInfo("","ZwAllocateVirtualMemory",""),
			ApiBreakPointInfo("","ZwWriteVirtualMemory",""),
			ApiBreakPointInfo("","ZwReadVirtualMemory",""),
		}
	},
	{
		"Disk",
		{
			ApiBreakPointInfo("","GetDiskFreeSpaceA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExA",""),
			ApiBreakPointInfo("","GetDiskFreeSpaceExW",""),
			ApiBreakPointInfo("","GetDriveTypeA",""),
			ApiBreakPointInfo("","GetDriveTypeW",""),
			ApiBreakPointInfo("","GetLogicalDrives",""),
			ApiBreakPointInfo("","GetLogicalDriveStringsA",""),
			ApiBreakPointInfo("","GetLogicalDriveStringsW",""),
		}
	},
	{
		"Malware",
		{
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","CreateFileW",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","CreateProcessA",""),
			ApiBreakPointInfo("","CreateProcessW",""),
			ApiBreakPointInfo("","CreateRemoteThread",""),
			ApiBreakPointInfo("","WriteProcessMemory",""),
			ApiBreakPointInfo("","ReadProcessMemory",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","OpenMutexW",""),
			ApiBreakPointInfo("","CreateToolhelp32SnapShot",""),
			ApiBreakPointInfo("","Heap32ListFirst",""),
			ApiBreakPointInfo("","Heap32ListNext",""),
			ApiBreakPointInfo("","Heap32First",""),
			ApiBreakPointInfo("","Heap32Next",""),
			ApiBreakPointInfo("","Module32First",""),
			ApiBreakPointInfo("","Module32Next",""),
			ApiBreakPointInfo("","Module32FirstW",""),
			ApiBreakPointInfo("","Module32NextW",""),
			ApiBreakPointInfo("","Process32First",""),
			ApiBreakPointInfo("","Process32FirstW",""),
			ApiBreakPointInfo("","Process32Next",""),
			ApiBreakPointInfo("","Process32NextW",""),
			ApiBreakPointInfo("","PostQuitMessage",""),
			ApiBreakPointInfo("","Toolhelp32ReadProcessMemory",""),
			ApiBreakPointInfo("","ZwQueryInformationProcess",""),
			ApiBreakPointInfo("","SetTimer",""),
			ApiBreakPointInfo("","GetTempPathA",""),
			ApiBreakPointInfo("","GetTempPathW",""),
			ApiBreakPointInfo("","ReadFile",""),
			ApiBreakPointInfo("","WriteFile",""),
			ApiBreakPointInfo("","ShellExecuteA",""),
			ApiBreakPointInfo("","ShellExecuteW",""),
			ApiBreakPointInfo("","WinExec",""),
			ApiBreakPointInfo("","DeleteFileA",""),
			ApiBreakPointInfo("","DeleteFileW",""),
			ApiBreakPointInfo("","UrlDownloadToFileA",""),
			ApiBreakPointInfo("","UrlDownloadToFileW",""),
			ApiBreakPointInfo("","GetDesktopWindow",""),
		}
	},
	{
		"VB",
		{
			ApiBreakPointInfo("","FindResourceA",""),
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","GetVolumeInformation",""),
			ApiBreakPointInfo("","MultiByteToWideChar",""),
			ApiBreakPointInfo("","WideCharToMultiByte",""),
			ApiBreakPointInfo("","GetFileSize",""),
			ApiBreakPointInfo("","VarCyFromStr",""),
			ApiBreakPointInfo("","arBstrFromI2",""),
			ApiBreakPointInfo("","rtcFileLen",""),
			ApiBreakPointInfo("","rtcFileLenth",""),
			ApiBreakPointInfo("","rtcMsgBox",""),
			ApiBreakPointInfo("","rtcInputBox",""),
			ApiBreakPointInfo("","GetMemStr",""),
			ApiBreakPointInfo("","rtcR8ValFromBstr",""),
			ApiBreakPointInfo("","rtcGetPresendDate",""),
			ApiBreakPointInfo("","rtcBeep",""),
			ApiBreakPointInfo("","rtcTrimBstr",""),
			ApiBreakPointInfo("","rtcMidCharVar",""),
			ApiBreakPointInfo("","rtcLeftCharVar",""),
			ApiBreakPointInfo("","rtcRightCharVar",""),
			ApiBreakPointInfo("","StrConv","ת���ַ���"),
			ApiBreakPointInfo("","rtcT8ValFromBstr",""),
			ApiBreakPointInfo("","__vbaI2Str",""),
			ApiBreakPointInfo("","__vbaI4Str",""),
			ApiBreakPointInfo("","__vbar4Str",""),
			ApiBreakPointInfo("","__vbar8Str",""),
			ApiBreakPointInfo("","__vbavaradd",""),
			ApiBreakPointInfo("","__vbavarsub",""),
			ApiBreakPointInfo("","__vbavarmul",""),
			ApiBreakPointInfo("","__vbavaridiv",""),
			ApiBreakPointInfo("","__vbavarxor",""),
			ApiBreakPointInfo("","__vbavarcat",""),
			ApiBreakPointInfo("","__vbaStrCat",""),
			ApiBreakPointInfo("","__vbaVarCat",""),
			ApiBreakPointInfo("","__vbaStrCmp",""),
			ApiBreakPointInfo("","__vbaStrComp",""),
			ApiBreakPointInfo("","__vbaVarTstEq",""),
			ApiBreakPointInfo("","__vbaFreeStr",""),
			ApiBreakPointInfo("","__vbaStrCopy",""),
			ApiBreakPointInfo("","__vbaLenBstr",""),
			ApiBreakPointInfo("","__vbavarfornext",""),
			ApiBreakPointInfo("","__vbafreeobj",""),
		}
	},
	{
		"VC/MFC",
		{
			ApiBreakPointInfo("","lstrcmpA",""),
			ApiBreakPointInfo("","DefWindowProcA",""),
			ApiBreakPointInfo("","DefWindowProcW",""),
			ApiBreakPointInfo("","RegisterClassA",""),
			ApiBreakPointInfo("","RegisterClassW",""),
			ApiBreakPointInfo("","RegisterClassExA",""),
			ApiBreakPointInfo("","RegisterClassExW",""),
			ApiBreakPointInfo("","FindResourceA",""),
			ApiBreakPointInfo("","FindResourceW",""),
			ApiBreakPointInfo("","LoadResource",""),
			ApiBreakPointInfo("","SetHandleCount",""),
			ApiBreakPointInfo("","IsWindowEnabled",""),
		}
	},
	{
		"Unpack",
		{
			ApiBreakPointInfo("","CreateThread",""),
			ApiBreakPointInfo("","GetModuleHandleA",""),
			ApiBreakPointInfo("","OpenMutexA",""),
			ApiBreakPointInfo("","GetSystemTime",""),
			ApiBreakPointInfo("","VirtualProtect",""),
			ApiBreakPointInfo("","CreateFileMappingA",""),
			ApiBreakPointInfo("","LoadLibraryA",""),
			ApiBreakPointInfo("","LoadLibraryW",""),
			ApiBreakPointInfo("","LoadLibraryExA",""),
			ApiBreakPointInfo("","LoadLibraryExW",""),
			ApiBreakPointInfo("","RefreshDeviceList",""),
			ApiBreakPointInfo("","DeviceIoControl",""),
			ApiBreakPointInfo("","Prestochangoselector",""),
			ApiBreakPointInfo("","FreeEnvironmentStringsA",""),
			ApiBreakPointInfo("","GetLogicalDriveStringsA",""),
			ApiBreakPointInfo("","GetLogicalDrives",""),
			ApiBreakPointInfo("","GetDriveTypeA",""),
			ApiBreakPointInfo("","CreateFileA",""),
			ApiBreakPointInfo("","FindFirstFileA",""),
		}
	},
	{
		"Reserve",
		{
		}
	},
	{
		"Reserve2",
		{
		}
	},
};


#endif




DWORD WINAPI MsgLoopThread(LPVOID);
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
	_plugin_menuaddentry(hMenu, MENU_MAINWINDOW_POPUP, "Set Api Breakpoint");
}

// doing msg loop like WinMain
DWORD WINAPI MsgLoopThread(LPVOID)
{
	MSG msg;
	WNDCLASSA wc;
	HWND hwnd;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	wc.lpszMenuName = NULL;
	wc.lpszClassName = PLUGIN_NAME;

	RegisterClassA(&wc);

	hwnd = CreateWindowA(
		PLUGIN_NAME,
		"Standard Window",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		MAINWINDOW_WIDTH,
		MAINWINDOW_HEIGHT,
		NULL,
		NULL,
		g_hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	bIsMainWindowShow = false;

	return (int)msg.wParam;
}

VOID CenterDialog(HWND hDlg)
{
	HWND hwndOwner = NULL;
	RECT rcOwner, rcDlg, rc;
	// Get the owner window and dialog box rectangles. 			
	if ((hwndOwner = GetParent(hDlg)) == NULL)
	{
		hwndOwner = GetDesktopWindow();
	}
	GetWindowRect(hwndOwner, &rcOwner);
	GetWindowRect(hDlg, &rcDlg);
	CopyRect(&rc, &rcOwner);

	// Offset the owner and dialog box rectangles so that right and bottom 
	// values represent the width and height, and then offset the owner again 
	// to discard space taken up by the dialog box. 

	OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
	OffsetRect(&rc, -rc.left, -rc.top);
	OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);

	// The new position is the sum of half the remaining space and the owner's 
	// original position. 

	SetWindowPos(hDlg,
		HWND_TOP,
		rcOwner.left + (rc.right / 2),
		rcOwner.top + (rc.bottom / 2),
		0, 0,          // Ignores size arguments. 
		SWP_NOSIZE);
}

// called when tab changed, update checkbox check(uncheck) and show(hide) state
void UpdateCheckBoxs()
{
	CurTab = TabCtrl_GetCurSel(hTabControl);
	size_t len = Groups[CurTab].apiList.size();
	for (size_t i = 0; i < CHECK_COUNT; i++)
	{
		if (i < len)
		{
			SetWindowTextA(hChecks[i], std::string(Groups[CurTab].apiList[i].apiName + "  " + Groups[CurTab].apiList[i].description).c_str());
			if (Groups[CurTab].apiList[i].bWantToSetBp)
			{
				CheckDlgButton(hMain, IDC_CHECKS[i], BST_CHECKED);
			}
			else
			{
				CheckDlgButton(hMain, IDC_CHECKS[i], BST_UNCHECKED);
			}
			ShowWindow(hChecks[i], SW_SHOW);
		}
		else
		{
			ShowWindow(hChecks[i], SW_HIDE);
		}
	}
}

// initialize main window, register tab control and checkbox
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCITEMA ti;
	HFONT defaultFont;
	hMain = hwnd;

	switch (iMsg)
	{
	case WM_CREATE:
	{
		defaultFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

		InitCommonControls();

		hTabControl = CreateWindowA("SysTabControl32", "", WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
			0, 0, MAINWINDOW_WIDTH-20, 22, hwnd, (HMENU)IDC_TABCTRL, g_hInstance, NULL);

		for (int i = 0; i < TAB_COUNT; i++)
		{
			ti.mask = TCIF_TEXT;
			ti.pszText = (LPSTR)Groups[i].groupName.c_str();
			TabCtrl_InsertItem(hTabControl, i, &ti);
		}

		for (int i = 0; i < CHECK_COUNT; i++)
		{
			
			hChecks[i] = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "CreateThread(some descrition here)",
				WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_GROUP,
				5 + (i / 25) * (MAINWINDOW_WIDTH/3), 30 + 20 * (i % 25) + 5, (MAINWINDOW_WIDTH / 3), 20, 
				hwnd, (HMENU)IDC_CHECKS[i], g_hInstance, NULL);
			SendMessageA(hChecks[i], WM_SETFONT, (WPARAM)defaultFont, TRUE);
		}

		SendMessageA(hwnd, WM_SETFONT, (WPARAM)defaultFont, TRUE);
		SendMessageA(hTabControl, WM_SETFONT, (WPARAM)defaultFont, TRUE);

		TabCtrl_SetCurSel(hTabControl, 0);
		SetWindowTextA(hMain, PLUGIN_NAME);

		CenterDialog(hwnd);

		UpdateCheckBoxs();
	}
	return 0;
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)lParam)->code)
		{

		case TCN_SELCHANGE:
		{
			UpdateCheckBoxs();

			return TRUE;
		}
		}
	}
	return 0;
	case WM_COMMAND:
		for (int i = 0; i < CHECK_COUNT; i++)
		{
			if (LOWORD(wParam) == IDC_CHECKS[i])
			{
				if (IsDlgButtonChecked(hwnd, IDC_CHECKS[i]))
				{
					// checked, means user want to set bp here, then we'll try to use bp instruction set one.
					Groups[CurTab].apiList[i].bWantToSetBp = true;
					std::string cmd = "bp " + Groups[CurTab].apiList[i].apiName;
					Cmd(cmd.c_str());
				}
				else
				{
					Groups[CurTab].apiList[i].bWantToSetBp = false;
					std::string cmd = "bc " + Groups[CurTab].apiList[i].apiName;
					Cmd(cmd.c_str());
				}
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcA(hwnd, iMsg, wParam, lParam);
}


// set delay breakpoint when dll loaded
EXTERN_C __declspec(dllexport) void _cdecl CBLOADDLL(
	CBTYPE bType, // event type, one of the `cbType` CB_* values listed above
	PLUG_CB_LOADDLL* callbackInfo // pointer to a structure of information
)
{
	// check if there are any breakpoint can be set
	for (size_t i = 0; i < TAB_COUNT; i++)
	{
		for (size_t j = 0; j < Groups[i].apiList.size(); j++)
		{
			if (Groups[i].apiList[j].bWantToSetBp)
			{
				std::string cmd = "bp " + Groups[i].apiList[j].apiName;
				Cmd(cmd.c_str());
			}
		}
	}
}

// register menu to popup main window
extern "C" __declspec(dllexport) void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
	switch (info->hEntry)
	{
	case MENU_MAINWINDOW_POPUP:
		if (!bIsMainWindowShow && DbgIsDebugging())
		{
			CloseHandle(CreateThread(0, 0, MsgLoopThread, 0, 0, 0));
			bIsMainWindowShow = true;
		}

		break;
	}
}



