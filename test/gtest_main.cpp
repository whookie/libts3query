
#include <gtest/gtest.h>

#include "communication/TS3Command_test.hpp"
#include "communication/TS3ResponseValue_test.hpp"
#include "communication/TS3Response_test.hpp"
#include "connection/transport/NetworkTools_test.hpp"
#include "connection/TS3ServerConnection_test.hpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
