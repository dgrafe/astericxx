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

#ifndef ISERIALIZE_DESERIALIZE
#define ISERIALIZE_DESERIALIZE

#include <iostream>

namespace astericxx {

struct imembuf: std::streambuf {
  imembuf(uint8_t const* base, size_t size) {
    char* p(const_cast<char*>(reinterpret_cast<const char*>(base)));
    this->setg(p, p, p + size);
  }
};

struct imemstream: virtual imembuf, std::istream {
  imemstream(uint8_t const* base, size_t size)
      : imembuf(base, size)
      , std::istream(static_cast<std::streambuf*>(this)) {
  }
};

struct omembuf: std::streambuf {
  omembuf(uint8_t* base, size_t size){
    this->setp(reinterpret_cast<char*>(base), reinterpret_cast<char*>(base) + size);
  }
};

struct omemstream: virtual omembuf, std::ostream {
  omemstream(uint8_t* base, size_t size)
      : omembuf(base, size)
      , std::ostream(static_cast<std::streambuf*>(this)){
  }
};

class ISerializeDeserialize {

public:
  virtual bool   dataExisting() {
    return false;
  }
  virtual size_t size_bytes() {
    return 0;
  };

  virtual std::istream& operator<<(std::istream& stream) {
    return stream;
  }
  virtual std::ostream &operator>>(std::ostream &stream) {
    return stream;
  }

  friend std::ostream& operator<<(std::ostream& out, ISerializeDeserialize& obj);
  friend std::istream& operator>>(std::istream& in, ISerializeDeserialize& obj);

private:

};

} 

#endif