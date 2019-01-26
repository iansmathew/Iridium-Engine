#pragma once

#include "BaseSingleton.h"
#include <windows.h>
#include <string>
#include <sstream>

extern "C" {
#include <Powrprof.h>
}
#pragma comment(lib, "Powrprof.lib")


/**
	This class contains methods to display various system information about the current target.
*/
class SysCheck
{
public:
	/**
		Displays the users CPU speed and architecture of the system
	*/
	void DisplayCPUStats()
	{
		typedef struct _PROCESSOR_POWER_INFORMATION {
			ULONG Number;
			ULONG MaxMhz;
			ULONG CurrentMhz;
			ULONG MhzLimit;
			ULONG MaxIdleState;
			ULONG CurrentIdleState;
		} PROCESSOR_POWER_INFORMATION, *PPROCESSOR_POWER_INFORMATION;

		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);

		// allocate buffer to get info for each processor
		const int size = sysInfo.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
		LPBYTE pBuffer = new BYTE[size];
		CallNtPowerInformation(ProcessorInformation, NULL, 0, pBuffer, size);
		PPROCESSOR_POWER_INFORMATION ppi = (PPROCESSOR_POWER_INFORMATION)pBuffer;

		std::ostringstream buffer;
		buffer << "Processor Speed: " << ppi->MaxMhz << ". \nCPU Architecture Value: " << sysInfo.wProcessorArchitecture << ".";
		int msgboxID = MessageBox(
			nullptr,
			buffer.str().c_str(),
			"CPU Specs",
			NULL
		);
	}

	/**
		Checks if the user has enough physical and virtual memory to run the program.

		@return Returns the result check
	*/
	bool HasFreeMemory()
	{
		MEMORYSTATUSEX memoryStruct = {};
		memoryStruct.dwLength = sizeof(memoryStruct);

		GlobalMemoryStatusEx(&memoryStruct);

		std::ostringstream buffer;
		buffer << "Physical Memory Available: " << memoryStruct.ullAvailPhys / (1024 * 1024) << " MB." << "\nVirtual Memory Available: " << memoryStruct.ullAvailVirtual / (1024 * 1024) << " MB.";
		int msgboxID = MessageBox(
			nullptr,
			buffer.str().c_str(),
			"Memory Available",
			NULL
		);

		return true;
	}

	/**
		Checks if the system has the required storage space needed to run the program.
		The required space is a placeholder value.
		Displays a message box with the result.

		@return Returns true if the system has free space.
	*/
	bool HasFreeDiskSpace()
	{
		bool result = false;
		int requiredSpace = 300; //program space spec requirement in MB.
		ULARGE_INTEGER ulFreeSpace;
		ULARGE_INTEGER ulTotalSpace;
		ULARGE_INTEGER ulTotalFreeSpace;
		std::string msgTxt;

		GetDiskFreeSpaceEx("C:", &ulFreeSpace, &ulTotalSpace, &ulTotalFreeSpace);

		int totalFreeSpaceInMb = (ulTotalFreeSpace.QuadPart / (1024 * 1024));

		if (requiredSpace < totalFreeSpaceInMb)
		{
			std::ostringstream buffer;
			buffer << "Sufficient space. \nDisk space required: " << requiredSpace << "MB" << ".\nDisk space available: " << totalFreeSpaceInMb << "MB";

			msgTxt = buffer.str();
			result = true;
		}
		else
		{
			std::ostringstream buffer;
			buffer << "Insufficient space. \nDisk space required: " << requiredSpace << "MB" << ".\nDisk space available: " << totalFreeSpaceInMb << "MB";

			msgTxt = buffer.str();
			result = false;
		}

		int msgboxID = MessageBox(
			nullptr,
			msgTxt.c_str(),
			"Storage check",
			MB_ICONINFORMATION
		);

		return result;
	}

};