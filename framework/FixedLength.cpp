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

#include <algorithm>
#include "FixedLength.hpp"

namespace astericxx {

FixedLength::FixedLength(uint16_t nrBytes)
 : m_uData(nrBytes, 0)
{}

bool FixedLength::operator==(FixedLength& other) {
  
  if (other.size_bytes() != this->size_bytes())
    return false;
  
  for (int i=0; i < this->size_bytes(); i++) {
    
    if (this->m_uData[i] != other.m_uData[i])
      return false;
  }
  
  return true;
}

bool FixedLength::operator!=(FixedLength& other) {
  
  return !this->operator==(other);
}

bool FixedLength::dataExisting() {
 
  return std::any_of(m_uData.begin(), m_uData.end(), [](uint8_t i) { return i != 0; });
}

std::istream& FixedLength::operator<< (std::istream& stream) {
  
  std::for_each(m_uData.begin(), m_uData.end(), [&stream](uint8_t& i) { stream >> std::noskipws >> i; });
  
  return stream;
}

std::ostream& FixedLength::operator>> (std::ostream& stream) {
  
  std::for_each(m_uData.begin(), m_uData.end(), [&stream](uint8_t i) { stream << std::noskipws << i;});
  
  return stream;
}

}