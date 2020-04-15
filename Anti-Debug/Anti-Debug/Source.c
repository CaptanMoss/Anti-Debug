#include <stdio.h>
#include <Windows.h>
#include <debugapi.h>
#include "Header.h"

int main()
{
    IsDebuggerPresentAPI();
    CheckRemoteDebuggerPresentAPI();
    PEBBeingDebugged();
    PEBNtGlobalFlag();
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
    if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &pbDebuggerPresent)) //Function call NTDLL NtQueryInformationProcess function and set to ProcessDebugPort= 7
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
        mov eax, dword ptr fs : [0x18]
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
    //Debbuger NTGlobalFlag = 0x70
    char dbg[] = "PEBNtGlobalFlag() detected Debbuger!\n";
    char ndbg[] = "No Debugger !\n";


    __asm
    {
        mov eax, fs: [0x30] //Get PEB structure address
        cmp byte ptr[eax + 0x68], 0x70//Compate default value and eax
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