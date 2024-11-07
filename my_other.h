#ifndef _MY_OTHER_H_
#define _MY_OTHER_H_

#include <stdio.h>

//HACK for putcunlocked function not defined in stdio.h
#if defined(_MSC_VER) || defined(__MINGW32__)
int putc_unlocked(int _Ch,FILE *_File)
{
    return putc(_Ch, _File);
}
#endif

#endif // _MY_OTHER_H_