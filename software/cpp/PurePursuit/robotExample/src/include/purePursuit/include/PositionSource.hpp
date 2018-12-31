#pragma once

#include <purePursuit/include/Point.hpp>

class PositionSource {

public:
    PositionSource();
    
    virtual Point get() = 0;

    ~PositionSource();
};