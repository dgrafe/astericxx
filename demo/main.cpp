#include <iostream>
#include <fstream>
#include "astericxx.hpp"

struct SectorHandler {
  
  SectorHandler() {}
  template <class T>
  void operator()(T& record) {
   
    switch(record.Item000.MessageType()) {
      case astericxx::item000MessageType::NorthMarker:
        std::cout << "NorthMarker received" << std::endl;
        std::cout << "   TimeOfDay: " << record.Item030.TimeOfDay() << std::endl;
      break;
      
      case astericxx::item000MessageType::SectorCrossing:
        std::cout << "SectorCrossing received" << std::endl;
        std::cout << "   TimeOfDay: " << record.Item030.TimeOfDay() << std::endl;
        std::cout << "   Sector...: " << (int)record.Item020.SectorNumber() << std::endl;
      break;
      
      default:
      break;
    };
  }
};

int main(int argc, char** argv) {

  // one north marker message followed by two sector crossing messages
  uint8_t test[] = { 0x22, 0x00, 0x1a, 0xe0, 0x03, 0x05, 0x01, 0x00, 0x04, 0xd2, 0xf0, 0x03, 0x05, 0x02, 0x00, 0x04, 0xd3, 0x7b, 0xf0, 0x03, 0x05, 0x02, 0x00, 0x04, 0xd4, 0x7c };
  
  // Deserializing the byte stream
  astericxx::Datablockcat34 Cat34(test, sizeof(test));

  // iterating the records from the datablock
  SectorHandler s = std::for_each(Cat34.begin(), Cat34.end(), SectorHandler());

  // Creating a new NorthMarker message
  Cat34.clear();
  astericxx::cat34 northMarkerRecord;
  northMarkerRecord.Item010.setSAC(12);
  northMarkerRecord.Item010.setSIC(13);
  northMarkerRecord.Item000.setMessageType(astericxx::item000MessageType::NorthMarker);
  northMarkerRecord.Item030.setTimeOfDay(5678);
  Cat34.push_back(northMarkerRecord);
  
  // (1) displaying the byte stream using the "serialize to vector" option
  std::cout << "New NorthMarker Message: " << std::endl;
  for (auto& i : Cat34.serialize())
    std::cout << " " << std::hex << (int)i; 
  std::cout << std::endl;
  
  // (2) streaming directly to a file
  std::ofstream myfile;
  myfile.open("test.raw");
  myfile << Cat34;
  myfile.close();
  
  return 0;
}