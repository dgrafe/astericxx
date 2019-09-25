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

#ifndef SECONDARY_PART_LENGTH_HPP
#define SECONDARY_PART_LENGTH_HPP

#include "FixedLength.hpp"

namespace astericxx {

class SecondaryPart : public FixedLength {

public:
  SecondaryPart() = delete;
  SecondaryPart(SecondaryPart& other) = delete;
  SecondaryPart& operator=(const SecondaryPart& other) {
   
    std::cout << " assignmen secondary part: " << std::hex << (int)FixedLength::m_uData[0] << std::endl;
    
    FixedLength::m_uData = other.m_uData;
    return *this;
  };
  
  SecondaryPart(uint16_t nrBytes) : FixedLength(nrBytes){}
  bool updateFXIndicator(bool previousPartSet);
  bool getFXIndicator();
};

};

#endif