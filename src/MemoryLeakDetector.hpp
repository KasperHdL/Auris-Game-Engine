#pragma once

#include "windows.h"
#include "psapi.h"
#include "TCHAR.h"
#include "pdh.h"
#include <iostream>

using namespace std;

static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

class MemoryLeakDetector {
private:
	MEMORYSTATUSEX memInfo;

	DWORDLONG totalVirtualMem;
	DWORDLONG virtualMemUsed;
	PROCESS_MEMORY_COUNTERS_EX pmc;
	
	SIZE_T virtualMemUsedByMe;

	DWORDLONG totalPhysMem;

	DWORDLONG physMemUsed;

	SIZE_T physMemUsedByMe;

	MemoryLeakDetector();
	~MemoryLeakDetector() {}
	double getCurrentTotalCPUValue();
	double getCurrentProcessCPUValue();
};