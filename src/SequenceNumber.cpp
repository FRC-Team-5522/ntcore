/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2015. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "SequenceNumber.h"

namespace ntimpl {

bool operator<(const SequenceNumber& lhs, const SequenceNumber& rhs) {
  if (lhs.m_val < rhs.m_val)
    return (rhs.m_val - lhs.m_val) < (1u << 15);
  else if (lhs.m_val > rhs.m_val)
    return (lhs.m_val - rhs.m_val) > (1u << 15);
  else
    return false;
}

bool operator>(const SequenceNumber& lhs, const SequenceNumber& rhs) {
  if (lhs.m_val < rhs.m_val)
    return (rhs.m_val - lhs.m_val) > (1u << 15);
  else if (lhs.m_val > rhs.m_val)
    return (lhs.m_val - rhs.m_val) < (1u << 15);
  else
    return false;
}

}  // namespace ntimpl