#pragma once
#include <iostream>

#ifdef _WIN32 // Windows
#define NOMINMAX

#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <Pdh.h>

#elif __linux__ // Linux
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "sys/times.h"
#include "sys/vtimes.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


#elif __APPLE__ // MAC OS X
#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

#endif


namespace Auris{
using namespace std;



#ifdef _WIN32 // Windows

static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;
static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

#elif __linux__ // Linux

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;
static clock_t lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;

#endif

static float MB_DIVIDER = 1024 * 1024;

//! The MemoryLeadDetector class.

    /*! Detects if there are memory leaks in the engine.

    */
class MemoryLeakDetector {
public:

    double highWaterMarkVirt = 0.0; /*!< A double value: highWaterMarkVirt. The highest value the virtual memory have had. */
    double highWaterMarkPhys = 0.0; /*!< A double value: highWaterMarkPhys. The highest value the physical memory have had. */
    double virtRising = 0.0; /*!< A double value: virtRising. The current value the virtual memory have. */
    double physRising = 0.0;/*!< A double value: physRising. The current value the physical memory have. */

    //! A getTotalVirtMem method.
        /*! Gets the total virtual memory available.
         * \return double. The total virtual memory available.
        */
	double getTotalVirtMem();

    //! A getVirtMemUsed method.
        /*! Gets the virtual memory used by the computer.
         * \return double. The used virtual memory by the computer.
        */
	double getVirtMemUsed();

    //! A getVirtMemUsedByMe method.
        /*! Gets the virtual memory used by the engine.
         * \return double. The used virtual memory by the engine.
        */
	double getVirtMemUsedByMe();

    //! A getTotalPhysMem method.
        /*! Gets the total physical memory available.
         * \return double. The total physical memory available.
        */
	double getTotalPhysMem();

    //! A getPhysMemUsed method.
        /*! Gets the physical memory used by the computer.
         * \return double. The used physical memory by the computer.
        */
	double getPhysMemUsed();

    //! A getPhysMemUsedByMe method.
        /*! Gets the physical memory used by the engine.
         * \return double. The used physical memory by the engine.
        */
	double getPhysMemUsedByMe();

    //! A getCurrentTotalCPUValue method.
        /*! Gets the total cpu available.
         * \return double. The total cpu available.
        */
	double getCurrentTotalCPUValue();

    //! A getCurrentProcessCPUValue method.
        /*! Gets the cpu used by the engine.
         * \return double. The cpu used by the engine.
        */
	double getCurrentProcessCPUValue();

    //! A leakDetect method, taking 1 argument.
        /*! Detects if there is a leak happening.
         * \param dt a float value. The delta time in seconds.
        */
    void leakDetect(float dt);

    //! The MemoryLeadDetector constructor.
        /*!
         * Does nothing.
        */
	MemoryLeakDetector();

    //! The MemoryLeadDetector destructor.
        /*!
         * Does nothing.
        */
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

	#elif __linux__ // Linux
    struct sysinfo memInfo; /*!< A sysinfo struct: memInfo. The memory info. */
    long long totalVirtualMem; /*!< A long long value: totalVirtualMem. The total virtual memory. */
    long long virtualMemUsed; /*!< A long long value: virtualMemUsed. The virtual memory used. */
    long long totalPhysMem; /*!< A long long value: totalPhysMem. The total physical memory. */
    long long physMemUsed; /*!< A long long value: physMemUsed. The physical memory used. */

    //! A parseLine method, taking 1 argument.
         /*! Parse file output from CPU file.
          * \param line a char pointer. The char to parse.
          * \return int. The parsed int
         */
	int parseLine(char* line);

    //! A initTotalCPUFile method.
        /*! Initializes the total CPU.
        */
	void initTotalCPUFile();

    //! A initCurrentCPUFile method.
        /*! Initializes the current CPU.
        */
    void initCurrentCPUFile();

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
}





