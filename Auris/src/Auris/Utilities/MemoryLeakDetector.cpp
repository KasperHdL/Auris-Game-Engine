#include "Auris/Utilities/MemoryLeakDetector.hpp"

using namespace Auris;
MemoryLeakDetector::MemoryLeakDetector() {
	#ifdef _WIN32 // Windows
	//Total virt. mem.
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	totalVirtualMem = memInfo.ullTotalPageFile;

	//Virt. mem. in use
	virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

	//Virt. mem. used by this process
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	virtualMemUsedByMe = pmc.PrivateUsage;
	
	//Total phys. mem.
	totalPhysMem = memInfo.ullTotalPhys;

	//Phys. mem. used
	physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

	//Phys mem. used by this process	
	physMemUsedByMe = pmc.WorkingSetSize;

	//CPU currently used
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal); //note: removed "L" before second argument in PdhAddCounter call
	PdhCollectQueryData(cpuQuery);

	//CPU currently used by this process
	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));

	#elif __linux__ // Linux
	sysinfo(&memInfo);

	//Total virt. mem.
	totalVirtualMem = memInfo.totalram;
	//Add other values in next statement to avoid int overflow on right hand side
	totalVirtualMem += memInfo.totalswap;
	totalVirtualMem *= memInfo.mem_unit;

	//Virt. mem. currently used
	virtualMemUsed = memInfo.totalram - memInfo.freeram;
	//Add other values in next statement to avoid int overflow on right hand side
	virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
	virtualMemUsed *= memInfo.mem_unit;

	//Total phys. mem.
	totalPhysMem = memInfo.totalram;
	//Multiply in next statement to avoid int overflow on right hand side
	totalPhysMem *= memInfo.mem_unit;

	//Phys. mem. currently used
	physMemUsed = memInfo.totalram - memInfo.freeram;
	//Multiply in next statement to avoid int overflow on right hand side...
	physMemUsed *= memInfo.mem_unit;


	#elif __APPLE__ // MAC OS X
	// Total virt. mem.
	if (0 == statfs("/", &stats))
	{
		freeSwap = (uint64_t)stats.f_bsize * stats.f_bfree;
	}

	// Total virt. mem. currently used
	xsw_usage vmusage = { 0 };
	size = sizeof(vmusage);
	if (sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0) != 0)
	{
		perror("unable to get swap usage by calling sysctlbyname(\"vm.swapusage\",...)");
	}

	// Virt. and phys. mem. used by this process
	t_info_count = TASK_BASIC_INFO_COUNT;
	if (KERN_SUCCESS != task_info(mach_task_self(),
		TASK_BASIC_INFO, (task_info_t)&t_info,
		&t_info_count))
	{
		return -1;
	}
	// resident size is in t_info.resident_size;
	// virtual size is in t_info.virtual_size;

	// Total phys. mem.
	mib[0] = CTL_HW;
	mib[1] = HW_MEMSIZE;
	length = sizeof(int64_t);
	sysctl(mib, 2, &physical_memory, &length, NULL, 0);

	#else
	cout << "Error: Unsupported OS" << endl;
	#endif
}

void MemoryLeakDetector::leakDetect(float deltaTime) {
    double virtVal = getVirtMemUsedByMe();
    double physVal = getPhysMemUsedByMe();
    if (virtVal > highWaterMarkVirt) {
        if (virtRising > 60.0) {
            cout << "Warning: Memory leak - make sure there are no undeleted pointers." << endl;
        }
        else {
            highWaterMarkVirt = virtVal;
            virtRising += deltaTime;
        }
    }
    else {
        virtRising = 0.0;
    }
    if (physVal > highWaterMarkPhys) {
        if (physRising > 60.0) {
            cout << "Warning: Memory leak - make sure there are no undeleted pointers." << endl;
        }
        else {
            highWaterMarkPhys = physVal;
            physRising += deltaTime;
        }
    }
    else {
        physRising = 0.0;
    }
}


#ifdef _WIN32 // Windows
double MemoryLeakDetector::getTotalVirtMem() {
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	double val = memInfo.ullTotalPageFile;
	return val / MB_DIVIDER;
}

double MemoryLeakDetector::getVirtMemUsed() {
	double val = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
	return val / MB_DIVIDER;
}

double MemoryLeakDetector::getVirtMemUsedByMe()
{
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	return pmc.PrivateUsage / MB_DIVIDER;
}

double MemoryLeakDetector::getTotalPhysMem()
{
	return memInfo.ullTotalPhys / MB_DIVIDER;
}

double MemoryLeakDetector::getPhysMemUsed()
{
	return memInfo.ullTotalPhys - memInfo.ullAvailPhys / MB_DIVIDER;
}

double MemoryLeakDetector::getPhysMemUsedByMe()
{
	return pmc.WorkingSetSize / MB_DIVIDER;
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

#elif __linux__ // Linux
//Virt. mem. used by this process
int MemoryLeakDetector::parseLine(char* line) {
	// This assumes that a digit will be found and the line ends in "Kb"
	int i = strlen(line);
	const char* p = line;
	while (*p <'0' || *p > '9') p++;
	line[i - 3] = '\0';
	i = atoi(p);
	return i;
}

double MemoryLeakDetector::getTotalVirtMem() {

    return totalVirtualMem / MB_DIVIDER;
}

double MemoryLeakDetector::getVirtMemUsed() {
    return virtualMemUsed / MB_DIVIDER;
}

double MemoryLeakDetector::getTotalPhysMem()
{
    return totalPhysMem / MB_DIVIDER;
}

double MemoryLeakDetector::getPhysMemUsed()
{
    return physMemUsed / MB_DIVIDER;
}

double MemoryLeakDetector::getVirtMemUsedByMe() { //Note: this value is in KB!
	FILE* file = fopen("/proc/self/status", "r");
	int result = -1;
	char line[128];

	while (fgets(line, 128, file) != NULL) {
		if (strncmp(line, "VmSize:", 7) == 0) {
			result = parseLine(line);
			break;
		}
	}
	fclose(file);
	return result / MB_DIVIDER;
}

//Phys. mem. used by this process
double MemoryLeakDetector::getPhysMemUsedByMe() { //Note: this value is in KB!
	FILE* file = fopen("/proc/self/status", "r");
	int result = -1;
	char line[128];

	while (fgets(line, 128, file) != NULL) {
		if (strncmp(line, "VmRSS:", 6) == 0) {
			result = parseLine(line);
			break;
		}
	}
	fclose(file);
	return result / MB_DIVIDER;
}

// CPU currently used
void MemoryLeakDetector::initTotalCPUFile() {
	FILE* file = fopen("/proc/stat", "r");
	fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
		&lastTotalSys, &lastTotalIdle);
	fclose(file);
}

double MemoryLeakDetector::getCurrentTotalCPUValue() {
	double percent;
	FILE* file;
	unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

	file = fopen("/proc/stat", "r");
	fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
		&totalSys, &totalIdle);
	fclose(file);

	if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
		totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
		//Overflow detection. Just skip this value.
		percent = -1.0;
	}
	else {
		total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
			(totalSys - lastTotalSys);
		percent = total;
		total += (totalIdle - lastTotalIdle);
		percent /= total;
		percent *= 100;
	}

	lastTotalUser = totalUser;
	lastTotalUserLow = totalUserLow;
	lastTotalSys = totalSys;
	lastTotalIdle = totalIdle;

	return percent;
}

// CPU used by this process
void MemoryLeakDetector::initCurrentCPUFile() {
	FILE* file;
	struct tms timeSample;
	char line[128];

	lastCPU = times(&timeSample);
	lastSysCPU = timeSample.tms_stime;
	lastUserCPU = timeSample.tms_utime;

	file = fopen("/proc/cpuinfo", "r");
	numProcessors = 0;
	while (fgets(line, 128, file) != NULL) {
		if (strncmp(line, "processor", 9) == 0) numProcessors++;
	}
	fclose(file);
}

double MemoryLeakDetector::getCurrentProcessCPUValue() {
	struct tms timeSample;
	clock_t now;
	double percent;

	now = times(&timeSample);
	if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
		timeSample.tms_utime < lastUserCPU) {
		//Overflow detection. Just skip this value
		percent = -1.0;
	}
	else {
		percent = (timeSample.tms_stime - lastSysCPU) +
			(timeSample.tms_utime - lastUserCPU);
		percent /= (now - lastCPU);
		percent /= numProcessors;
		percent *= 100;
        }
	lastCPU = now;
	lastSysCPU = timeSample.tms_stime;
	lastUserCPU = timeSample.tms_utime;

	return percent;
}

#elif __APPLE__ // MAC OS X
// Phys. mem. currently used
int MemoryLeakDetector::getCurrentPhysMem(int argc, const char * argv[]) {
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics64_data_t vm_stats;

	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
		KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
		(host_info64_t)&vm_stats, &count))
	{
		long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

		long long used_memory = ((int64_t)vm_stats.active_count +
			(int64_t)vm_stats.inactive_count +
			(int64_t)vm_stats.wire_count) *  (int64_t)page_size;
		printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
	}

	return 0;
}

#else
cout << "Error: Unsupported OS" << endl;
#endif
