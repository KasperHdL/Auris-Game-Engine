#pragma once
#include <iostream>
using namespace std;

#ifdef _WIN32 // Windows
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <Pdh.h>

static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;
static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;
static float MB_DIVIDER = 1024 * 1024;

#elif __linux__ // Linux
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
static clock_t lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;

#elif __APPLE__ // MAC OS X
#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#else
cout << "Error: Unsupported OS" << endl;
#endif


class MemoryLeakDetector {
public:
	MemoryLeakDetector();
	~MemoryLeakDetector() {}

	#ifdef _WIN32 // Windows
	MEMORYSTATUSEX memInfo;
	DWORDLONG totalVirtualMem;
	DWORDLONG virtualMemUsed;
	PROCESS_MEMORY_COUNTERS_EX pmc;
	SIZE_T virtualMemUsedByMe;
	DWORDLONG totalPhysMem;
	DWORDLONG physMemUsed;
	SIZE_T physMemUsedByMe;
	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	double getTotalVirtMem();
	double getVirtMemUsed();
	double getVirtMemUsedByMe();
	double getTotalPhysMem();
	double getPhysMemUsed();
	double getPhysMemUsedByMe();
	double getCurrentTotalCPUValue();
	double getCurrentProcessCPUValue();

	#elif __linux__ // Linux
	struct sysinfo memInfo;
	long long totalVirtualMem;
	long long virtualMemUsed;
	long long totalPhysMem;
	long long physMemUsed;

	int parseLine(char* line);
	int getCurrentVirtMemValue();
	int getCurrentPhysMemValue();
	void initTotalCPUFile();
	double getCurrentTotalCPUValue();
    void initCurrentCPUFile();
    double getCurrentProcessCPUValue();

	#elif __APPLE__ // MAC OS X
	struct statfs stats;
	size_t size;
	struct task_basic_info t_info;
	mach_msg_type_number_t t_info_count;
	int mib[2];
	int64_t physical_memory;

	int getCurrentPhysMem(int argc, const char * argv[]);

	#else
	cout << "Error: Unsupported OS" << endl;
	#endif
};





