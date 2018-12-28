#pragma once

#include <purePursuit/include/Point.hpp>

class PositionSource {

public:
    PositionSource();

    virtual bool ping();

    virtual Point get() = 0;

    ~PositionSource();
};