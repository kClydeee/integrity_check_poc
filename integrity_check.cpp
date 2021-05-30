#include "integrity_check.h"
namespace globals
{
	DWORD Table = 0;
	DWORD Base = 0;
	DWORD Size = 0;
	bool binited = false;
}
bool initialize_table(DWORD ModuleBase, DWORD &Table) {
	globals::Base = ModuleBase + 0x1000;
	PIMAGE_DOS_HEADER pIDH;
	PIMAGE_NT_HEADERS pINH;
	pIDH = (PIMAGE_DOS_HEADER)ModuleBase;
	pINH = (PIMAGE_NT_HEADERS)((LPBYTE)ModuleBase + pIDH->e_lfanew);
	globals::Size = pINH->OptionalHeader.SizeOfCode;
	globals::Table = (DWORD)VirtualAlloc(NULL, globals::Size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (globals::Table) {
		for (int i = 0; i < globals::Size / 4 - 1; i++)
		{
			DWORD Encypt_Key = 0xDEADC0DE ^ (i + 0x1A) << 0x5A;
			*(DWORD*)(globals::Table + (i * 4)) = *(DWORD*)(globals::Base + (i * 4)) ^ *(DWORD*)(globals::Base + (i * 4) + 4) ^ Encypt_Key;
		}
		globals::binited = true;
		Table = globals::Table;
		return true;
	}
	return false;
}
bool check_text_section() {
	for (int i = 0; i < globals::Size / 4 - 1; i++)
	{
		DWORD Encypt_Key = 0xDEADC0DE ^ (i + 0x1A) << 0x5A;
		DWORD Encrypted_DWORD = *(DWORD*)(globals::Base + i * 0x4) ^ *(DWORD*)(globals::Base + (i * 0x4) + 0x4) ^ Encypt_Key;
		if (*(DWORD*)(globals::Table + i * 0x4) != Encrypted_DWORD) {
			return false;
		}
	}
	return true;
}