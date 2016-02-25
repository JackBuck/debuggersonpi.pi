//------------------------------------------------------------------------------
// File:        ExifToolPipe.h
//
// Description: Piped output from exiftool application
//
// License:     Copyright 2013, Phil Harvey (phil at owl.phy.queensu.ca)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// History:     2013-11-23 - Phil Harvey Created
//------------------------------------------------------------------------------
#ifndef __EXIFTOOLPIPE_H__
#define __EXIFTOOLPIPE_H__

class ExifToolPipe
{
public:
    ExifToolPipe();
    ~ExifToolPipe();
    void    Init(int fd, int pid, int initialSize);
    int     Read();     // read exiftool response
    void    Free();     // free buffer memory
    void    Flush();    // remove previous response from buffer
    char  * GetString() { return (mString && mString[0]) ? mString : (char *)0; }

private:
    int     mFile;      // read file descriptor
    char  * mBuff;      // buffer pointer
    int     mSize;      // buffer size
    int     mLen;       // length of data in buffer
    int     mPos;       // current read position in buffer
    int     mSearchPos; // current search position in buffer
    int     mBlockSize; // initial buffer size
    char  * mString;    // returned string from last Read()
    int     mPid;       // process id for other side of the pipe
};

#endif // __EXIFTOOLPIPE_H__
