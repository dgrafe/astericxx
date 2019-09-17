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

#ifndef REPETITIVE_DATA_ITEM_HPP
#define REPETITIVE_DATA_ITEM_HPP

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "ISerializeDeserialize.hpp"

namespace astericxx {

template <class T> 
class RepetitiveDataItem : public ISerializeDeserialize {

public:
  typedef typename std::vector<T> containertype;
  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;
  
  RepetitiveDataItem(){};
  
  // implementing ISerializeDeserialize
  bool dataExisting() {
    
    if (m_uData.size() == 0)
      return false;
    
    return std::any_of(m_uData.begin(), m_uData.end(), [](T& i) { return i.dataExisting(); });
  }
  
  size_t size_bytes() { 
   
    if (m_uData.size() > 0)
      return 1 + (m_uData.size() * m_uData[0].size_bytes());
    else
      return 0;
  }
  size_t size() { return m_uData.size(); }
  
  std::ostream& operator>> (std::ostream& stream) {
   
      // write the component count byte
      stream << std::noskipws << static_cast<uint8_t>(m_uData.size());
    
      std::for_each(m_uData.begin(), m_uData.end(), [&stream](T& i) { stream << std::noskipws << i;});
      
      return stream;
  }
  
  std::istream& operator<< (std::istream& stream) {
    
      uint8_t rep;
      
      // read the component count byte and create the necessary space
      stream >> std::noskipws >> rep;
      m_uData.resize(rep);
    
      std::for_each(m_uData.begin(), m_uData.end(), [&stream](T& i) { stream >> std::noskipws >> i;});
      
      return stream;
  }
  
  bool operator==(RepetitiveDataItem<T>& other) {
   
    if (this->m_uData.size() != other.m_uData.size())
      return false;
    
    for (int i=0; i<m_uData.size(); i++) {
     
      if (this->m_uData[i] != other.m_uData[i])
        return false;
    }
    
    return true;
  }
  
  bool operator!=(RepetitiveDataItem<T>& other) {
    
    return !this->operator==(other);
  }
  
  T& operator[](uint8_t index) {
    
    if (index >= m_uData.size())
      m_uData.resize(index + 1);
    
    return m_uData.at(index);
  }
  
  iterator begin() {
    return m_uData.begin();
  }
  
  iterator end() {
    return m_uData.end();
  }
  
  iterator cbegin() const {
    return m_uData.cbegin();
  }
  
  iterator cend() const {
    return m_uData.cend();
  }
  
private:
  containertype m_uData;
};
  
}

#endif