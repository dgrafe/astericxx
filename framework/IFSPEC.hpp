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

#ifndef IFSPEC_HPP
#define IFSPEC_HPP

#include <vector>
#include "ISerializeDeserialize.hpp"

namespace astericxx {

class IFSPEC : public ISerializeDeserialize {
  
public:
  typedef typename std::vector<ISerializeDeserialize*> containertype;
  typedef typename std::vector<uint8_t> fspectype;
  
  IFSPEC(){}
  
  // methods inherited from ISerializeDeserialize
  bool   dataExisting();
  size_t size_bytes();
  std::ostream& operator>> (std::ostream& stream);
  std::istream& operator<< (std::istream& stream);

protected:
  void addItemToProfile(ISerializeDeserialize* item);
  
private:
  void calculateFSPEC();
  
  containertype m_oProfile;
  fspectype     m_oFSPEC;
};

}

#endif