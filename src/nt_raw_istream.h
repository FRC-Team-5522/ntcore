/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#ifndef NT_RAW_ISTREAM_H_
#define NT_RAW_ISTREAM_H_

#include <cstddef>

namespace NtImpl {

class raw_istream
{
    void anchor();
public:
    raw_istream() {}
    virtual ~raw_istream() {}
    virtual bool read(void *data, std::size_t len) = 0;
    virtual void close() = 0;
private:
    raw_istream(const raw_istream&);
    raw_istream& operator= (const raw_istream&);
};

class raw_mem_istream : public raw_istream
{
public:
    raw_mem_istream(const char *mem, std::size_t len)
        : m_cur(mem), m_left(len)
    {}
    virtual ~raw_mem_istream() {}
    virtual bool read(void *data, std::size_t len);
    virtual void close() {}
private:
    const char *m_cur;
    std::size_t m_left;
};

} // namespace NtImpl

#endif /* NT_RAW_ISTREAM_H_ */