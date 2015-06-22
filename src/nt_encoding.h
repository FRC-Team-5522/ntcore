/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef NT_UTIL_H_
#define NT_UTIL_H_

namespace NtImpl {

inline void
Write8(char* &buf, unsigned int val)
{
    *buf++ = (char)(val & 0xff);
}

inline void
Write16(char* &buf, unsigned int val)
{
    *buf++ = (char)((val >> 8) & 0xff);
    *buf++ = (char)(val & 0xff);
}

inline void
Write32(char* &buf, unsigned long val)
{
    *buf++ = (char)((val >> 24) & 0xff);
    *buf++ = (char)((val >> 16) & 0xff);
    *buf++ = (char)((val >> 8) & 0xff);
    *buf++ = (char)(val & 0xff);
}

void WriteDouble(char* &buf, double val);

} // namespace NtImpl

#endif /* NT_UTIL_H */