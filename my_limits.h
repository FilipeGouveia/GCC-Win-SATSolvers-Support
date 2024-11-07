#ifndef _MY_LIMITS_H_
#define _MY_LIMITS_H_

#if defined(_MSC_VER) || defined(__MINGW32__)

//from https://man7.org/linux/man-pages/man2/getrlimit.2.html

typedef unsigned long long rlim_t;  /* Unsigned integer type */

struct rlimit {
    rlim_t  rlim_cur;  /* Soft limit */
    rlim_t  rlim_max;  /* Hard limit (ceiling for rlim_cur) */
};

//TODO 
#define RLIMIT_CPU -1
#define RLIM_INFINITY -1
#define RLIMIT_AS -1

//TODO: check https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-jobobject_basic_limit_information?redirectedfrom=MSDN
int getrlimit(int resource, struct rlimit *rlim)
{
    //TODO
    return -1; // Not implemented
};

int setrlimit(int resource, const struct rlimit *rlim)
{
    //TODO
    return -1; // Not implemented
};


// int prlimit(pid_t pid, int resource,
//             const struct rlimit *_Nullable new_limit,
//             struct rlimit *_Nullable old_limit);

#endif

#endif // _MY_LIMITS_H_