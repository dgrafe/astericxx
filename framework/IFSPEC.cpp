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
#include "IFSPEC.hpp"

namespace astericxx {
 
  
bool IFSPEC::dataExisting() {
 
  return std::any_of(m_oProfile.begin(), m_oProfile.end(), [](ISerializeDeserialize* i) { return i->dataExisting(); });
}

void IFSPEC::addItemToProfile(ISerializeDeserialize* item) {
  
  m_oProfile.push_back(item);
}

size_t IFSPEC::size_bytes() {
 
  size_t count=0;
  
  this->calculateFSPEC();
  count += m_oFSPEC.size();
  
  for (auto& item : m_oProfile)
    if (item->dataExisting())
      count += item->size_bytes();
    
  return count;
}

std::istream& IFSPEC::operator<< (std::istream& stream) {
  
  // (1) stream in the fspec sequence first
  m_oFSPEC.clear();
  
  uint8_t fspec;
  do {
    stream >> fspec;
    m_oFSPEC.push_back(fspec);
  } while (fspec & 0x01);
  
  // (2) continue streaming to those items that are listed in the
  //     FSPEC sequence
  uint8_t itemIndex=0;
  uint8_t offsetFSPEC=0x80;
  for (auto& fspec : m_oFSPEC) {
    
    do {
      
      // FSPEC indicates item availability?
      if ((fspec & offsetFSPEC) && m_oProfile[itemIndex] != nullptr)
        *m_oProfile[itemIndex] << stream;
      
      itemIndex++;
      offsetFSPEC >>=1;
      
    } while(offsetFSPEC != 0x01);
    offsetFSPEC=0x80;
  }
  
  return stream;
}

std::ostream& IFSPEC::operator>> (std::ostream& stream) {

  // (1) stream out the FSPEC sequence first
  this->calculateFSPEC();
  for (auto& fspec : m_oFSPEC)
    stream << std::noskipws << fspec;
  
  // (2) stream out the items that actually hold data
  for (auto& item : m_oProfile)
    if (item->dataExisting())
     stream << std::noskipws << *item;
    
  return stream;
}

void IFSPEC::calculateFSPEC() {
  
  uint8_t lastItemSet;
  uint8_t numFSPECFields;
  
  if (m_oProfile.size() == 0)
    return;
  
  // identifying the last actually set item as this last items determins
  // the resulting length of the FSPEC sequence
  for (lastItemSet = m_oProfile.size(); lastItemSet > 0; lastItemSet--)
    if (m_oProfile[lastItemSet - 1]->dataExisting())
      break;
    
  // preparing the necessary number of FSPEC fields to hold the
  // item availability bitmap
  numFSPECFields = (lastItemSet / 7) + (lastItemSet % 7 != 0 ? 1 : 0);
  this->m_oFSPEC.resize(numFSPECFields);
  
  // Setting the corresponding bit for every set item from the profile
  uint8_t indexFSPEC=0;
  uint8_t offsetFSPEC=0x80;
  for (uint32_t item = 1; item <= m_oProfile.size(); item++) {
    
      if (m_oProfile[item-1]->dataExisting())
        m_oFSPEC[indexFSPEC] |= offsetFSPEC;
      
      offsetFSPEC >>=1;
      if (offsetFSPEC == 0x01 && item < lastItemSet) {
        
          // Set the Field Extension Identifier and proceed to the next FSPEC
          m_oFSPEC[indexFSPEC] |= offsetFSPEC;
          offsetFSPEC = 0x80;
          indexFSPEC++;
      }
  }
}

}