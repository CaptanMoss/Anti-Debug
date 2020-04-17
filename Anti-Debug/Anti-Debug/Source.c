#include "Header.h"

int main()
{
    IsDebuggerPresentAPI();
    CheckRemoteDebuggerPresentAPI();
    PEBBeingDebugged();
    PEBNtGlobalFlag();
    PEBProcessHeap();
    NTDebuggerPort();
    NTDebugFlags();
    NTDebugObject();


    return 0x1;
}

void IsDebuggerPresentAPI() //Data Teype : BOOL User-mode debugging detection
{
    if (IsDebuggerPresent())
    {
        printf_s("IsDebuggerPresent() Function detected Debbuger !\n");
        //ExitProcess(1);
    }
    else
    {
        printf_s("No Debugger !\n");
    }
}
void CheckRemoteDebuggerPresentAPI() //Data Type : BOOL Process is being debugged.
{
    PBOOL pbDebuggerPresent = FALSE; //default no debbuger mode
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &pbDebuggerPresent);
    if (pbDebuggerPresent) //Function call NTDLL NtQueryInformationProcess function and set to ProcessDebugPort= 7
    {
        printf_s("CheckRemoteDebuggerPresent() Function detected Debbuger!\n");
        //ExitProcess(2);
    }
    else
    {
        printf_s("No Debugger !\n");
    }
}
void PEBBeingDebugged()
{
    char dbg[] = "PEBBeingDebugged() detected Debbuger!\n";
    char ndbg[] = "No Debugger !\n";
    __asm
    {
        mov eax,fs:[0x30] //Get PEB structure address
        cmp byte ptr[eax+0x2],0 //Beingdebugged offset is 0x2
        jz exit
        jmp message
     message:
        lea ebx,dbg
        push ebx
        call printf
        pop ebx
        leave
        ret
    exit:
        lea eax,ndbg
        push eax
        call printf
        pop eax
        leave
        ret
    }
}

void PEBNtGlobalFlag()
{
    //Default NtGlobalFlag = 0x0
    char dbg[] = "PEBNtGlobalFlag() detected Debbuger!\n";
    char ndbg[] = "No Debugger !\n";


    __asm
    {
        mov eax, fs: [0x30] //Get PEB structure address
        cmp dword ptr[eax + 0x68], 0x70//Compate default value and eax
        jz exit
        jmp message
        message:
            lea ebx, dbg
            push ebx
            call printf
            pop ebx
            leave
            ret
        exit:
            lea eax,ndbg
            push eax
            call printf
            pop eax
            leave
            ret
    }
}

void PEBProcessHeap()
{
    //DEfault ForceFlags = 0x0 
    //Default Falgs = 0x0
    char dbg[] = "PEBProcessHeap() detected Debbuger!\n";
    char ndbg[] = "No Debugger !\n";


    __asm
    {
        mov eax, fs: [0x30] //Get PEB structure address
        cmp dword ptr[eax + 0x18], 0//Compate default value and eax
        jz exit
        jmp message
        message :
            lea ebx, dbg
            push ebx
            call printf
            pop ebx
            leave
            ret
        exit :
            lea eax, ndbg
            push eax
            call printf
            pop eax
            leave
            ret
    }
}

void NTDebuggerPort()
{
    DWORD_PTR debugPort = 0x0; //Default 
    PULONG returnSize = 0x0; 

    HMODULE hNtdll = LoadLibrary(TEXT("ntdll.dll"));

    if (hNtdll == NULL)
    {
        printf_s("%d",GetLastError());
    }

    _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)(GetProcAddress(hNtdll,"NtQueryInformationProcess")); //_NtQueryInformationProcess structına NtQueryInformationProcess fonksiyonun adresini yükledik

    if (NtQueryInformationProcess == NULL) //struct boş mu diye bakıyoruz
    {
        printf_s("%d", GetLastError());
    }
    unsigned long ret = NtQueryInformationProcess(GetCurrentProcess(),0x7,&debugPort,sizeof(debugPort),&returnSize);//debugport hakkında bilgi almak istiyoruz bu sebeble debugport hakkındaki bilgileri çekiyoruz
    
    if (ret == 0x00000000)
    {
        printf_s("NtDebuggerPort() Function detected Debbuger !\n");
    }
    else
    {
        printf_s("No Debugger !\n");
    }
}
void NTDebugFlags()
{
    DWORD_PTR debugFlags = 0x1F;

    HMODULE hNtdll = LoadLibrary(TEXT("ntdll.dll"));

    if (hNtdll == NULL)
    {
        printf_s("%d", GetLastError());
    }

    _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)(GetProcAddress(hNtdll, "NtQueryInformationProcess")); //_NtQueryInformationProcess structına NtQueryInformationProcess fonksiyonun adresini yükledik

    if (NtQueryInformationProcess == NULL) //struct boş mu diye bakıyoruz
    {
        printf_s("%d", GetLastError());
    }

    unsigned long ret = NtQueryInformationProcess(GetCurrentProcess(), 0x1F, &debugFlags, sizeof(debugFlags), NULL);//debugport hakkında bilgi almak istiyoruz bu sebeble debugport hakkındaki bilgileri çekiyoruz

    //if (ret == 0x00000000)
    if(ret == 0x00000000 && debugFlags==FALSE)
    {
        printf_s("NtDebuggerPort() Function detected Debbuger !\n");
    }
    else
    {
        printf_s("No Debugger !\n");
    }
}
void NTDebugObject()
{
    DWORD_PTR debugObject = 0x1E;

    HMODULE hNtdll = LoadLibrary(TEXT("ntdll.dll"));

    if (hNtdll == NULL)
    {
        printf_s("%d", GetLastError());
    }

    _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)(GetProcAddress(hNtdll, "NtQueryInformationProcess")); //_NtQueryInformationProcess structına NtQueryInformationProcess fonksiyonun adresini yükledik

    if (NtQueryInformationProcess == NULL) //struct boş mu diye bakıyoruz
    {
        printf_s("%d", GetLastError());
    }

    unsigned long ret = NtQueryInformationProcess(GetCurrentProcess(), 0x1E, &debugObject, sizeof(debugObject), NULL);//debugport hakkında bilgi almak istiyoruz bu sebeble debugport hakkındaki bilgileri çekiyoruz

    //if (ret == 0x00000000)
    if (ret == 0x00000000 && debugObject)
    {
        printf_s("NtDebuggerPort() Function detected Debbuger !\n");
    }
    else
    {
        printf_s("No Debugger !\n");
    }
}
