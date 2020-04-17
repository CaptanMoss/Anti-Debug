#pragma once
#include <stdio.h>
#include <Windows.h>
#include <debugapi.h>
#include <winternl.h>
#include <errhandlingapi.h>

void IsDebuggerPresentAPI(); //Reference : https://docs.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent
void CheckRemoteDebuggerPresentAPI(); //Reference : https://docs.microsoft.com/tr-tr/windows/win32/api/debugapi/nf-debugapi-checkremotedebuggerpresent
void PEBBeingDebugged(); // Reference : https://www.aldeid.com/wiki/PEB-Process-Environment-Block/BeingDebugged
void PEBNtGlobalFlag(); // Reference : https://www.aldeid.com/wiki/PEB-Process-Environment-Block/NtGlobalFlag
void PEBProcessHeap(); // Reference : https://www.aldeid.com/wiki/PEB-Process-Environment-Block/ProcessHeap
void NTDebuggerPort(); // Reference : https://github.com/mrexodia/TitanHide/blob/master/TitanHideTest/main.cpp
void NTDebugFlags(); //// Reference : https://github.com/mrexodia/TitanHide/blob/master/TitanHideTest/main.cpp
void NTDebugObject();

typedef NTSTATUS(NTAPI* _NtQueryInformationProcess)(
    HANDLE ProcessHandle,
    DWORD ProcessInformationClass, /* can't be bothered defining the whole enum */
    PVOID ProcessInformation,
    DWORD ProcessInformationLength,
    PDWORD ReturnLength
    );

/*

ntqueryinformationprocess (ntdll)

- Belirtilen process hakkında PEB sayesinde bilgi almamızı sağlar.

*/



/*
PEB - Process Enviroment Block

Uygulamalar tarafından kullanılan user-mode data structure'dır.

struct _PEB {
    0x000 BYTE InheritedAddressSpace;
    0x001 BYTE ReadImageFileExecOptions;
    0x002 BYTE BeingDebugged;
    0x003 BYTE SpareBool;
    0x004 void* Mutant;
    0x008 void* ImageBaseAddress;
    0x00c _PEB_LDR_DATA* Ldr;
    0x010 _RTL_USER_PROCESS_PARAMETERS* ProcessParameters;
    0x014 void* SubSystemData;
    0x018 void* ProcessHeap;
    0x01c _RTL_CRITICAL_SECTION* FastPebLock;
    0x020 void* FastPebLockRoutine;
    0x024 void* FastPebUnlockRoutine;
    0x028 DWORD EnvironmentUpdateCount;
    0x02c void* KernelCallbackTable;
    0x030 DWORD SystemReserved[1];
    0x034 DWORD ExecuteOptions:2; // bit offset: 34, len=2
    0x034 DWORD SpareBits:30; // bit offset: 34, len=30
    0x038 _PEB_FREE_BLOCK* FreeList;
    0x03c DWORD TlsExpansionCounter;
    0x040 void* TlsBitmap;
    0x044 DWORD TlsBitmapBits[2];
    0x04c void* ReadOnlySharedMemoryBase;
    0x050 void* ReadOnlySharedMemoryHeap;
    0x054 void** ReadOnlyStaticServerData;
    0x058 void* AnsiCodePageData;
    0x05c void* OemCodePageData;
    0x060 void* UnicodeCaseTableData;
    0x064 DWORD NumberOfProcessors;
    0x068 DWORD NtGlobalFlag;
    0x070 _LARGE_INTEGER CriticalSectionTimeout;
    0x078 DWORD HeapSegmentReserve;
    0x07c DWORD HeapSegmentCommit;
    0x080 DWORD HeapDeCommitTotalFreeThreshold;
    0x084 DWORD HeapDeCommitFreeBlockThreshold;
    0x088 DWORD NumberOfHeaps;
    0x08c DWORD MaximumNumberOfHeaps;
    0x090 void** ProcessHeaps;
    0x094 void* GdiSharedHandleTable;
    0x098 void* ProcessStarterHelper;
    0x09c DWORD GdiDCAttributeList;
    0x0a0 void* LoaderLock;
    0x0a4 DWORD OSMajorVersion;
    0x0a8 DWORD OSMinorVersion;
    0x0ac WORD OSBuildNumber;
    0x0ae WORD OSCSDVersion;
    0x0b0 DWORD OSPlatformId;
    0x0b4 DWORD ImageSubsystem;
    0x0b8 DWORD ImageSubsystemMajorVersion;
    0x0bc DWORD ImageSubsystemMinorVersion;
    0x0c0 DWORD ImageProcessAffinityMask;
    0x0c4 DWORD GdiHandleBuffer[34];
    0x14c void (*PostProcessInitRoutine)();
    0x150 void* TlsExpansionBitmap;
    0x154 DWORD TlsExpansionBitmapBits[32];
    0x1d4 DWORD SessionId;
    0x1d8 _ULARGE_INTEGER AppCompatFlags;
    0x1e0 _ULARGE_INTEGER AppCompatFlagsUser;
    0x1e8 void* pShimData;
    0x1ec void* AppCompatInfo;
    0x1f0 _UNICODE_STRING CSDVersion;
    0x1f8 void* ActivationContextData;
    0x1fc void* ProcessAssemblyStorageMap;
    0x200 void* SystemDefaultActivationContextData;
    0x204 void* SystemAssemblyStorageMap;
    0x208 DWORD MinimumStackCommit;
);

*/
