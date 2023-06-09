#define BOOST_TEST_MODULE "Random Test"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(random_test) {
    BOOST_CHECK_MESSAGE(1 == 1, "Numbers aren't equal as intended");
}