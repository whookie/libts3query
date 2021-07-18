#pragma once

#include "../../src/communication/TS3ResponseValue.hpp"
#include <gtest/gtest.h>

using namespace ts3query::communication;


TEST(TS3ResponseValue, isInt_int) {
    TS3ResponseValue v("1");
    EXPECT_TRUE(v.isInt());
}

TEST(TS3ResponseValue, isInt_letter) {
    TS3ResponseValue v("a");
    EXPECT_FALSE(v.isInt());
}

TEST(TS3ResponseValue, isInt_int_letter) {
    TS3ResponseValue v("-10a");
    EXPECT_TRUE(v.isInt());
}

TEST(TS3ResponseValue, asInt) {
    TS3ResponseValue v("-10a");
    EXPECT_EQ(v.asInt(), -10);
}

TEST(TS3ResponseValue, asString) {
    TS3ResponseValue v("Hello World!");
    EXPECT_EQ(v.asString(), "Hello World!");
}

TEST(TS3ResponseValue, asBool_emptyString) {
    TS3ResponseValue v("");
    EXPECT_FALSE(v.asBool());
}

TEST(TS3ResponseValue, asBool_nonemptyString) {
    TS3ResponseValue v("test");
    EXPECT_TRUE(v.asBool());
}

TEST(TS3ResponseValue, asBool_usingTrueNumber) {
    TS3ResponseValue v("123a");
    EXPECT_TRUE(v.asBool());
}

TEST(TS3ResponseValue, asBool_usingFalseNumbers) {
    TS3ResponseValue v("0");
    EXPECT_FALSE(v.asBool());
}
