#pragma once

#include "TS3Error.hpp"


namespace ts3query::error {

class TS3LogicError : public TS3Error
{
public:
    using TS3Error::TS3Error;
};

}
