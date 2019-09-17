#ifndef IDATABLOCK_HPP
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

#define IDATABLOCK_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <arpa/inet.h>
#include "IFSPEC.hpp"

namespace astericxx {

template <class T> 
class IDatablock : public ISerializeDeserialize {
  
public:
  static const uint8_t identifier = T::identifier;
  typedef typename std::vector<T> containertype;
  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;
  
  IDatablock(){}
  IDatablock(const uint8_t* data, size_t size) {
    imemstream dataStream(data, size);
    dataStream >> *this;
  }
  
  IDatablock(std::vector<uint8_t> data) {
    imemstream dataStream(data.data(), data.size());
    dataStream >> *this;
  }
  
  bool size() { return m_oRecords.size(); };
  bool empty() const noexcept { return m_oRecords.empty(); }
  void clear() noexcept { m_oRecords.clear(); }
  
  bool operator==(const IDatablock<T>& other) {
    
    if (this->m_oRecords.size() != other.m_oRecords.size())
      return false;
    
    for (int i=0; i<this->m_oRecords.size(); i++) {
      
      if (this->m_oRecords.at(i).operator!=(const_cast<T&>(other.m_oRecords.at(i))))
        return false;
    }
    
    return true;
  }
  
  bool operator!=(const IDatablock<T>& other) { return !this->operator==(other); }

  std::vector<uint8_t> serialize() {
    
    std::vector<uint8_t> buf(this->size_bytes());
    omemstream oStream(buf.data(), buf.size());
    *this >> oStream;
    
    // relying on the compiler to use the move constructor
    return buf;
  }
  
  // methods used for accessing the internal record data
  iterator begin() {
    return m_oRecords.begin();
  }
  
  iterator end() {
    return m_oRecords.end();
  }
  
  iterator cbegin() const {
    return m_oRecords.cbegin();
  }
  
  iterator cend() const {
    return m_oRecords.cend();
  }
  
  T& operator[](uint32_t index) {
    return m_oRecords[index];
  }
  
  void push_back(const T& record) {
    m_oRecords.push_back(record);
  }
  
  // methods inherited from ISerializeDeserialize
  bool dataExisting() {
    
    if (!m_oRecords.size())
      return false;
    
    return std::any_of(m_oRecords.begin(), m_oRecords.end(), [](ISerializeDeserialize i) { return i.dataExisting(); });
  }
  
  size_t size_bytes() {
  
    size_t count=0;
  
    // if there are records: add the size of the identifier and
    // the size of the length field
    if (m_oRecords.size())
      count += 3;
    
    for (auto& record : m_oRecords)
      if (record.dataExisting())
        count += record.size_bytes();

    return count;  
  }
  
  std::ostream& operator>> (std::ostream& stream) {
   
    uint16_t length;
    
    if (!m_oRecords.size())
      return stream;
    
    // stream out the datablock header information
    stream << std::noskipws << this->identifier;
    length = static_cast<uint16_t>(this->size_bytes());
    length = htons(length);             // ensure big endian
    stream.write(reinterpret_cast<char*>(&length), sizeof(length));
    
    // stream out the sequnce of records
    for (auto& record : m_oRecords)
      if (record.dataExisting())
        stream << record;

    return stream;
  }
  
  std::istream& operator<< (std::istream& stream) {
  
    uint8_t  identifier;
    uint8_t  lengthComponents[2];
    uint16_t length;
  
    // stream in the identfier and length information
    stream >> std::noskipws >> identifier;
    stream.read(reinterpret_cast<char*>(&length), sizeof(length));

    // big endian to host byte ordering
    length = ntohs(length);
    
    if (identifier != this->identifier)
      throw std::invalid_argument("Category expected: "
                                  + std::to_string(this->identifier) 
                                  + ", Category given: "
                                  + std::to_string(identifier));
  
    // clear the list of records
    m_oRecords.clear();
      
    // stream down the payload, that is means we are skipping the
    //  three bytes of the datablock header information
    int32_t byte_count = length - 3;
    do {
      T record;
      
      stream >> record;
      
      this->push_back(record);
      byte_count -= record.size_bytes();
    } while (byte_count > 0);

    return stream;
  }
  
private:
  containertype m_oRecords;
};

}

#endif