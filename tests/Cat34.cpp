#include <boost/test/unit_test.hpp>

#include "astericxx.hpp"

BOOST_AUTO_TEST_SUITE(Cat34_Tests)


BOOST_AUTO_TEST_CASE(Item000){

    uint8_t data[] = { 0x01 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item000 item000;
    
    istream >> item000;
    BOOST_CHECK(item000.MessageType() == astericxx::item000MessageType::NorthMarker);
    
    item000.setMessageType(astericxx::item000MessageType::JammingStrobe);
    ostream << item000;
    BOOST_CHECK_EQUAL(data[0], 4);
}

BOOST_AUTO_TEST_CASE(Item010){

    uint8_t data[] = { 0x01, 0x02 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item010 item010;
    
    istream >> item010;
    BOOST_CHECK_EQUAL(item010.SAC(), 1);
    BOOST_CHECK_EQUAL(item010.SIC(), 2);
    
    item010.setSAC(5);
    item010.setSIC(6);
    ostream << item010;
    BOOST_CHECK_EQUAL(data[0], 5);
    BOOST_CHECK_EQUAL(data[1], 6);
}

BOOST_AUTO_TEST_CASE(Item020){

    uint8_t data[] = { 0xAB };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item020 item020;
    
    istream >> item020;
    BOOST_CHECK_EQUAL(item020.SectorNumber(), 0xAB);
    
    item020.setSectorNumber(0xCD);
    ostream << item020;
    BOOST_CHECK_EQUAL(data[0], 0xCD);
}

BOOST_AUTO_TEST_CASE(Item030){

    uint8_t data[] = { 0xAB, 0xCD, 0xEF  };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item030 item030;
    
    istream >> item030;
    BOOST_CHECK_EQUAL(item030.TimeOfDay(), 0xABCDEF);
    
    item030.setTimeOfDay(0x1357BD);
    ostream << item030;
    BOOST_CHECK_EQUAL(data[0], 0x13);
    BOOST_CHECK_EQUAL(data[1], 0x57);
    BOOST_CHECK_EQUAL(data[2], 0xBD);
}

BOOST_AUTO_TEST_CASE(Item041){

    uint8_t data[] = { 0xAB, 0xCD };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item041 item041;
    
    istream >> item041;
    BOOST_CHECK_EQUAL(item041.AntennaRotationSpeed(), 0xABCD);
    
    item041.setAntennaRotationSpeed(0x1357);
    ostream << item041;
    BOOST_CHECK_EQUAL(data[0], 0x13);
    BOOST_CHECK_EQUAL(data[1], 0x57);
}

BOOST_AUTO_TEST_CASE(Item050){

    uint8_t data[] = { 0x84, 0x02, 0x80, 0x80, 0x00 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item050 item050;
    
    istream >> item050;
    BOOST_CHECK(item050.COM.TSV() == astericxx::item050TSV::Invalid);
    BOOST_CHECK(item050.MDS.ANT() == astericxx::item050MDSANT::Antenna2);
    BOOST_CHECK(item050.MDS.OVL_DLF() == astericxx::item050DLFOVL::Overload);
    
    // extending the compound
    item050.SSR.setMSC(astericxx::item050SSRMSC::MonitoringSystemDisconnected);
    ostream << item050;
    BOOST_CHECK_EQUAL(data[0], 0x8C);
    BOOST_CHECK_EQUAL(data[1], 0x02);
    BOOST_CHECK_EQUAL(data[2], 0x08);
    BOOST_CHECK_EQUAL(data[3], 0x80);
    BOOST_CHECK_EQUAL(data[4], 0x80);
}

BOOST_AUTO_TEST_CASE(Item060){

    uint8_t data[] = { 0x84, 0x40, 0x10, 0x00 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item060 item060;
    
    istream >> item060;
    BOOST_CHECK(item060.COM.RED_RDP() == astericxx::item060RED_RDP::ReductionStep4);
    BOOST_CHECK(item060.MDS.CLU() == astericxx::item060MDSCLU::NotAutonomous);
    
    // extending the compound
    item060.PSR.setPOL(astericxx::item060POL::CircularPolarization);
    ostream << item060;
    BOOST_CHECK_EQUAL(data[0], 0x94);
    BOOST_CHECK_EQUAL(data[1], 0x40);
    BOOST_CHECK_EQUAL(data[2], 0x80);
    BOOST_CHECK_EQUAL(data[3], 0x10);
}

BOOST_AUTO_TEST_CASE(Item070){

    uint8_t data[] = { 0x02, 0x15, 0xAA, 0x52, 0x34, 0x00, 0x00 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item070 item070;
    
    istream >> item070;
    BOOST_CHECK_EQUAL(item070.size(), 2);
    BOOST_CHECK(item070[0].Type() == astericxx::item070CounterType::SingleSSRReport);
    BOOST_CHECK_EQUAL(item070[0].Counter(), 0x05AA);
    BOOST_CHECK(item070[1].Type() == astericxx::item070CounterType::FilterPSR);
    BOOST_CHECK_EQUAL(item070[1].Counter(), 0x234);
    
    item070[2].setType(astericxx::item070CounterType::FilterPSREnhancedSSR);
    item070[2].setCounter(0x421);
    BOOST_CHECK_EQUAL(item070.size(), 3);
    ostream << item070;
    BOOST_CHECK_EQUAL(data[0], 0x03);
    BOOST_CHECK_EQUAL(data[1], 0x15);
    BOOST_CHECK_EQUAL(data[2], 0xAA);
    BOOST_CHECK_EQUAL(data[3], 0x52);
    BOOST_CHECK_EQUAL(data[4], 0x34);
    BOOST_CHECK_EQUAL(data[5], 0x84);
    BOOST_CHECK_EQUAL(data[6], 0x21);
}

BOOST_AUTO_TEST_CASE(Item090){

    uint8_t data[] = { 0xEC, 0x0F };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item090 item090;
    
    istream >> item090;
    BOOST_CHECK_EQUAL(item090.RangeError(), -20);
    BOOST_CHECK_EQUAL(item090.AzimuthError(), 15);
    
    item090.setRangeError(5);
    ostream << item090;
    BOOST_CHECK_EQUAL(data[0], 0x05);
    BOOST_CHECK_EQUAL(data[1], 0x0F);
}

BOOST_AUTO_TEST_CASE(Item100){

    uint8_t data[] = { 0x01, 0x02, 0x10, 0x20, 0x03, 0x04, 0x04, 0x03 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item100 item100;
    
    istream >> item100;
    BOOST_CHECK_EQUAL(item100.RhoStart(), 0x0102);
    BOOST_CHECK_EQUAL(item100.RhoEnd(), 0x1020);
    BOOST_CHECK_EQUAL(item100.ThetaStart(), 0x0304);
    BOOST_CHECK_EQUAL(item100.ThetaEnd(), 0x0403);
    
    item100.setRhoStart(0x1234);
    item100.setRhoEnd(0x5678);
    item100.setThetaStart(0x9ABC);
    item100.setThetaEnd(0xAABB);
    ostream << item100;
    BOOST_CHECK_EQUAL(data[0], 0x12);
    BOOST_CHECK_EQUAL(data[1], 0x34);
    BOOST_CHECK_EQUAL(data[2], 0x56);
    BOOST_CHECK_EQUAL(data[3], 0x78);
    BOOST_CHECK_EQUAL(data[4], 0x9A);
    BOOST_CHECK_EQUAL(data[5], 0xBC);
    BOOST_CHECK_EQUAL(data[6], 0xAA);
    BOOST_CHECK_EQUAL(data[7], 0xBB);
}

BOOST_AUTO_TEST_CASE(Item110){

    uint8_t data[] = { 0x08 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item110 item110;
    
    istream >> item110;
    BOOST_CHECK(item110.Type() == astericxx::item110DataFilterType::FilterPSREnhancedSSRMDSNotPrime);

    
    // extending the compound
    item110.setType(astericxx::item110DataFilterType::FilterWeatherData);
    ostream << item110;
    BOOST_CHECK_EQUAL(data[0], 0x01);
}

BOOST_AUTO_TEST_CASE(Item120){

    uint8_t data[] = { 0x01, 0x02, 0x10, 0x20, 0x03, 0x04, 0x04, 0x03 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item120 item120;
    
    istream >> item120;
    BOOST_CHECK_EQUAL(item120.Height(), 0x0102);
    BOOST_CHECK_EQUAL(item120.Latitude(), 0x102003);
    BOOST_CHECK_EQUAL(item120.Longitude(), 0x040403);
    
    item120.setHeight(0x1234);
    item120.setLatitude(0x56789A);
    item120.setLongitude(0x9ABCDE);
    ostream << item120;
    BOOST_CHECK_EQUAL(data[0], 0x12);
    BOOST_CHECK_EQUAL(data[1], 0x34);
    BOOST_CHECK_EQUAL(data[2], 0x56);
    BOOST_CHECK_EQUAL(data[3], 0x78);
    BOOST_CHECK_EQUAL(data[4], 0x9A);
    BOOST_CHECK_EQUAL(data[5], 0x9A);
    BOOST_CHECK_EQUAL(data[6], 0xBC);
    BOOST_CHECK_EQUAL(data[7], 0xDE);
}

BOOST_AUTO_TEST_CASE(Serialize_Deserialize_Datablock) {
  
  astericxx::Datablockcat34 Cat34out;
  
  astericxx::cat34 testRecord;
  testRecord.Item010.setSAC(12);
  testRecord.Item010.setSIC(13);
  testRecord.Item000.setMessageType(astericxx::item000MessageType::NorthMarker);
  testRecord.Item070[0].setType(astericxx::item070CounterType::FilterPSR);
  testRecord.Item070[0].setCounter(1234);
  testRecord.Item070[1].setType(astericxx::item070CounterType::SingleSSRReport);
  testRecord.Item070[1].setCounter(4321);
  Cat34out.push_back(testRecord);
  
  astericxx::Datablockcat34 Cat34in(Cat34out.serialize());
  BOOST_CHECK(Cat34out == Cat34in);
  
  // random sample
  BOOST_CHECK(Cat34in[0].Item070[0].Type() == astericxx::item070CounterType::FilterPSR);
  BOOST_CHECK(Cat34in[0].Item070[0].Counter() == 1234);
}

BOOST_AUTO_TEST_SUITE_END()
