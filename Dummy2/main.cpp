#include <iostream>
#include <Windows.h>



int main() {
	
	DWORD pid = 0;
	std::cout << "Enter pid: ";
	std::cin >> pid;
	std::cout << "PID is: " << pid << '\n';

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		std::cout << "Opening process\n";
		if (hProcess == NULL) {
			std::cout << "OpenProcess failed, reason: " << GetLastError() << '\n';
			system("pause");
			return EXIT_FAILURE;
		}
		
		uintptr_t memoryaddress = 0x0; //0x00dcfc60
		std::cout << "what memory address we readin'? (in hexadecimal): 0x";
		std::cin >> std::hex >> memoryaddress;
		std::cout << "reading memory at address: " << std::hex << std::uppercase << memoryaddress << " ..." << '\n';
		int ptrRead = 0;
		int intRead = 0;

		//first we read the pointer
		bool rpmreturn = ReadProcessMemory(hProcess, (LPCVOID)memoryaddress, &ptrRead, sizeof(int), NULL);
		if (rpmreturn == FALSE) {
			std::cout << "readprocessmemory failed, reason: " << std::dec << GetLastError() << '\n';
			system("pause");
			return EXIT_FAILURE;
			}

		std::cout << "ptrRead = " << std::dec << ptrRead << '\n';

		//then we read pointers value to get the correct result
		uintptr_t intMemAddress = ptrRead;
		bool rp2return = ReadProcessMemory(hProcess, (LPCVOID)intMemAddress, &intRead, sizeof(int), NULL);
		if (rpmreturn == FALSE) {
			std::cout << "readprocessmemory failed, reason: " << std::dec << GetLastError() << '\n';
			system("pause");
			return EXIT_FAILURE;
		}

		std::cout << "intRead = " << std::dec << intRead << '\n';


	
		BOOL close = CloseHandle(hProcess);
		if (close == TRUE)
		{
			std::cout << "We done, closed handle";
		}



	return 0;

}