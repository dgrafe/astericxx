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
#include "IExtendedLength.hpp"

namespace astericxx {

bool   IExtendedLength::dataExisting() {
  
  return std::any_of(m_oPartSequence.begin(), m_oPartSequence.end(), [](SecondaryPart* i) { return i->dataExisting(); });
}

size_t IExtendedLength::size_bytes() {
  
  size_t count=0;
  
  for (int i = m_oPartSequence.size(); i > 0; i--) {
    
    if (m_oPartSequence[i-1]->dataExisting())
      count += m_oPartSequence[i-1]->size_bytes();
  }
  
  return count;
}

std::ostream& IExtendedLength::operator>> (std::ostream& stream) {
  
  this->updateFXIndicators();
  for (auto& part : m_oPartSequence)
    if (part->dataExisting())
      stream << *part;
    
  return stream;
}

std::istream& IExtendedLength::operator<< (std::istream& stream) {
  
  for (auto& part : m_oPartSequence) {
    
    *part << stream;
    if (!part->getFXIndicator())
      break;
  }
 
  return stream;
}

void IExtendedLength::addItemToSequence(SecondaryPart* item) {
  
  m_oPartSequence.push_back(item);
}

void IExtendedLength::updateFXIndicators() {
  
   bool previousPartSet = false;
   for (int i = m_oPartSequence.size(); i > 0; i--)
     previousPartSet = m_oPartSequence[i-1]->updateFXIndicator(previousPartSet);
}
  
};