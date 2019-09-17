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

#ifndef ITEM_SPARE_HPP
#define ITEM_SPARE_HPP

#include <cstdint>
#include "ISerializeDeserialize.hpp"

namespace astericxx {
 
class Spare : public ISerializeDeserialize {

public:
  Spare() {}
  
  bool operator==(Spare& other) { return true; }
  bool operator!=(Spare& other) { return false; }
  
  // implementing ISerializeDeserialize
  bool dataExisting();
  size_t size_bytes() { return 0; }
  std::ostream& operator>> (std::ostream& stream);
  std::istream& operator<< (std::istream& stream);
};
  
}

#endif