/**************************************************************************

                       时间处理函数

**************************************************************************/

#include <windows.h>
#include <time.h>

void TimetToFileTime(time_t t, LPFILETIME pft)
{
    ULARGE_INTEGER time_value;
    time_value.QuadPart = (t * 10000000LL) + 116444736000000000LL;
    pft->dwLowDateTime = time_value.LowPart;
    pft->dwHighDateTime = time_value.HighPart;
}