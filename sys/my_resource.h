#ifndef _MY_RESOURCE_H_
#define _MY_RESOURCE_H_

//TODO make guards for mingw and not msc_ver since MSBuild does not support this!

#include <sys/time.h> //only available in mingw but not in MSBuild
#include <unistd.h>
#include <windows.h>	

#define RUSAGE_SELF 1337

#define _SC_PAGESIZE 1437

#ifdef _MSC_VER

typedef struct timeval {
	long tv_sec;
	long tv_usec;
} TIMEVAL, * PTIMEVAL, * LPTIMEVAL;

#endif

struct rusage
{
	struct timeval ru_utime; /* user CPU time used */
	struct timeval ru_stime; /* system CPU time used */
	long   ru_maxrss;        /* maximum resident set size */
	long   ru_ixrss;         /* integral shared memory size */
	long   ru_idrss;         /* integral unshared data size */
	long   ru_isrss;         /* integral unshared stack size */
	long   ru_minflt;        /* page reclaims (soft page faults) */
	long   ru_majflt;        /* page faults (hard page faults) */
	long   ru_nswap;         /* swaps */
	long   ru_inblock;       /* block input operations */
	long   ru_oublock;       /* block output operations */
	long   ru_msgsnd;        /* IPC messages sent */
	long   ru_msgrcv;        /* IPC messages received */
	long   ru_nsignals;      /* signals received */
	long   ru_nvcsw;         /* voluntary context switches */
	long   ru_nivcsw;        /* involuntary context switches */
};

static inline int getrusage(int who, struct rusage *rusage) {
	FILETIME	starttime;
	FILETIME	exittime;
	FILETIME	kerneltime;
	FILETIME	usertime;
	ULARGE_INTEGER li;

	if (who != RUSAGE_SELF)
	{
		/* Only RUSAGE_SELF is supported in this implementation for now */
		errno = EINVAL;
		return -1;
	}

	if (rusage == (struct rusage *) NULL)
	{
		errno = EFAULT;
		return -1;
	}
	memset(rusage, 0, sizeof(struct rusage));
	if (GetProcessTimes(GetCurrentProcess(),
						&starttime, &exittime, &kerneltime, &usertime) == 0)
	{
		GetLastError();
		return -1;
	}

	/* Convert FILETIMEs (0.1 us) to struct timeval */
	memcpy(&li, &kerneltime, sizeof(FILETIME));
	li.QuadPart /= 10L;			/* Convert to microseconds */
	rusage->ru_stime.tv_sec = li.QuadPart / 1000000L;
	rusage->ru_stime.tv_usec = li.QuadPart % 1000000L;

	memcpy(&li, &usertime, sizeof(FILETIME));
	li.QuadPart /= 10L;			/* Convert to microseconds */
	rusage->ru_utime.tv_sec = li.QuadPart / 1000000L;
	rusage->ru_utime.tv_usec = li.QuadPart % 1000000L;
	return 0;
}

// check https://stackoverflow.com/questions/3351940/detecting-the-memory-page-size

long sysconf ( int name)
{
	if ( name == _SC_PAGESIZE)
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		return sysInfo.dwPageSize;
	}
	return 0;
}

#endif // _MY_RESOURCE_H_