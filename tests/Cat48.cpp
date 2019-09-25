#include <boost/test/unit_test.hpp>

#include "astericxx.hpp"

BOOST_AUTO_TEST_SUITE(Cat48_Tests)


BOOST_AUTO_TEST_CASE(Item020){
  
    uint8_t data[] = { 0x92, 0x00 };
    astericxx::imemstream istream(data, sizeof(data));
    astericxx::omemstream ostream(data, sizeof(data));
    astericxx::item48_020 item020;
    
    // first part
    item020 << istream;
    BOOST_CHECK(item020.part1.Typ() == astericxx::item020Typ::ModeSAllCall);
    BOOST_CHECK(item020.part1.SIM() == astericxx::item020SIM::SimulatedTargetReport);
    
    item020.part1.setRDP(astericxx::item020RDP::RDPChain2);
    
    // sceond part
    item020.part2.setERR(astericxx::item020ERR::ExtendedRange);
    item020.part2.setFOE(astericxx::item020FOE::NoReply);
    
    ostream << item020;
    BOOST_CHECK_EQUAL(data[0], 0x9B);
    BOOST_CHECK_EQUAL(data[1], 0x46);
}

BOOST_AUTO_TEST_SUITE_END()