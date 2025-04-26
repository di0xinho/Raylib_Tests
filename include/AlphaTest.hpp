#pragma once
#include "PerformanceTest.hpp"
#include "definitions.hpp"

class AlphaTest : public PerformanceTest {
public:
    void run() override;
    const char* getName() const override;
};
