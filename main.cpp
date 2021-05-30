
#include <iostream>
#include "integrity_check.h"
int main()
{
	DWORD MappedTable = 0;
	if (initialize_table((DWORD)GetModuleHandleA(NULL), MappedTable)) {
		printf("table mapped at 0x%x\n", MappedTable);
		while (true) {
			if (!check_text_section())
				printf("bruhhhhhhhhhh\n");
			Sleep(1000);
		}
	}
}