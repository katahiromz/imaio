#ifndef IMAIO_IMPL_H_
#define IMAIO_IMPL_H_

#define IMAIO_BUILDING 1

#include "imaio.h"

#include <tchar.h>
#include <string.h>
#include <mbstring.h>
#include <assert.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <setjmp.h>

#define II_WIDTHBYTES(i) (((i) + 31) / 32 * 4)

typedef struct tagII_BITMAPINFOEX
{
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[256];
} II_BITMAPINFOEX, FAR * LPII_BITMAPINFOEX;

#ifndef LR_LOADREALSIZE
    #define LR_LOADREALSIZE 128
#endif

#endif  /* ndef IMAIO_IMPL_H_ */
