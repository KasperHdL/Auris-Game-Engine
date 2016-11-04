#include "MemoryLeakDetector.hpp"

MemoryLeakDetector::MemoryLeakDetector() {

	//Total virt. mem.
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	totalVirtualMem = memInfo.ullTotalPageFile;

	cout << "Total virtual memory:\t\t" << totalVirtualMem << endl;

	//Virt. mem. in use
	virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

	cout << "Virtual memory currently used:\t\t" << virtualMemUsed << endl;

	//Virt. mem. used by this process
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	virtualMemUsedByMe = pmc.PrivateUsage;

	cout << "Virt. mem. currently used by this process:\t" << virtualMemUsedByMe << endl;
	
	//Total phys. mem.
	totalPhysMem = memInfo.ullTotalPhys;

	cout << "Total physical memory (RAM):\t\t" << totalPhysMem << endl;

	//Phys. mem. used
	physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

	cout << "Physical memory currently used:\t\t" << totalPhysMem << endl;

	//Phys mem. used by this process	
	physMemUsedByMe = pmc.WorkingSetSize;

	cout << "Phys. mem. currently used by this process:\t" << totalPhysMem << endl;

	//CPU currently used
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal); //note: removed "L" before second argument in PdhAddCounter call
	PdhCollectQueryData(cpuQuery);

	//CPU currently used by this process
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));

}

double MemoryLeakDetector::getCurrentTotalCPUValue() {
	PDH_FMT_COUNTERVALUE counterVal;

	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	return counterVal.doubleValue;
}


double MemoryLeakDetector::getCurrentProcessCPUValue() {
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;

	return percent * 100;
}