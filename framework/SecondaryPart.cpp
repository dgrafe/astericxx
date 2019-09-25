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

#include "SecondaryPart.hpp"

namespace astericxx {

bool SecondaryPart::updateFXIndicator(bool previousPartSet) {
  
  // set FX indicators if there was a value set in one of
  // the previous parts
  if (previousPartSet)
    FixedLength::m_uData[FixedLength::m_uData.size()-1] |= 0x01;
  else
   FixedLength::m_uData[FixedLength::m_uData.size()-1] &= 0xFE;
  
  bool thisPartSet=false;
  for (int i = FixedLength::m_uData.size(); i > 0; i--)
    if ((FixedLength::m_uData[i-1] & 0xFE) != 0x00) {
      thisPartSet = true;
      break;
    }
  
  return thisPartSet;
}

bool SecondaryPart::getFXIndicator() {
 
  return (FixedLength::m_uData[FixedLength::m_uData.size()-1] & 0x01) != 0x00 ? true : false;
}

};
