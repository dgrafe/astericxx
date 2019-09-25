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

#ifndef IEXTENDED_LENGTH_HPP
#define IEXTENDED_LENGTH_HPP

#include <vector>
#include "ISerializeDeserialize.hpp"
#include "SecondaryPart.hpp"

namespace astericxx {

class IExtendedLength: public ISerializeDeserialize {
  
public:
  typedef typename std::vector<SecondaryPart*> containertype;
  
  IExtendedLength(){}
  IExtendedLength(IExtendedLength& other)=delete;
  
  // methods inherited from ISerializeDeserialize
  bool   dataExisting();
  size_t size_bytes();
  std::ostream& operator>> (std::ostream& stream);
  std::istream& operator<< (std::istream& stream);

protected:
  void addItemToSequence(SecondaryPart* item);
  
private:
  void updateFXIndicators();
  containertype m_oPartSequence;
};

}

#endif