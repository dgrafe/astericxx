/* astericxx - A C++11 implementation of the ASTERIX data format
 * Copyright (C) 2019  Daniel Grafe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef FIXED_LENGTH_HPP
#define FIXED_LENGTH_HPP

#include <cstdint>
#include <vector>
#include <stdexcept>
#include "ISerializeDeserialize.hpp"

namespace astericxx {
 
class FixedLength : public ISerializeDeserialize {

public:
  FixedLength(uint16_t nrBytes);
  bool operator==(FixedLength& other);
  bool operator!=(FixedLength& other);
  
  // implementing ISerializeDeserialize
  bool dataExisting();
  size_t size_bytes() { return m_uData.size(); }
  std::ostream& operator>> (std::ostream& stream);
  std::istream& operator<< (std::istream& stream);
  
protected:
  template <class T>
  void setFixedValue(T value, uint16_t bitlength, uint16_t offset_bits, uint64_t mask) {
    
    uint16_t sizeBits = this->size_bytes() * 8;
    uint8_t  involvedBytes = m_uData.size();
    uint64_t bitmask = mask;
    uint64_t buf=0;
    
    if (offset_bits + bitlength > sizeBits)
      throw std::runtime_error("Invalid Offset given in FixedLength::setFixedValue");
    
    buf = static_cast<uint64_t>(value);
    
    // left shift until mask indicates byte boundary
    while (!(bitmask & 0x01)) {
      
      bitmask >>= 1;
      buf     <<= 1;
    }
    
    // TODO: Byte Ordering currently not taken into account
    for (unsigned int i = involvedBytes; i > 0; i--) {
     
      bitmask = (0xFF & mask);
      m_uData[i - 1] &= ~bitmask;
      m_uData[i - 1] |= (buf & bitmask);
      
      buf >>= 8;
      mask >>= 8;
    }
  }
  
  template <class T>
  T getFixedValue(uint16_t bitlength, uint16_t offset_bits, uint64_t mask) {
    
    uint16_t sizeBits = this->size_bytes() * 8;
    uint8_t  involvedBytes = m_uData.size();
    uint64_t bitmask = mask;
    uint64_t buf=0;
    
    if (offset_bits + bitlength > sizeBits)
      throw std::runtime_error("Invalid Offset given in FixedLength::setFixedValue");

    // TODO: Byte Ordering currently not taken into account
    for (unsigned int i = 0; i < involvedBytes; i++) {
     
      buf <<= 8;
      bitmask = (0xFF & (mask >> ((involvedBytes - 1 - i) * 8)));
      buf |= (m_uData[i]  & bitmask);
    }
    
    // right shift until mask indicates byte boundary
    while (!(mask & 0x01)) {
      
      mask >>= 1;
      buf  >>= 1;
    }
    
    return static_cast<T>(buf);
  }
  
private:
  std::vector<uint8_t> m_uData;
};
  
}

#endif