#pragma once
#include "PerformanceTest.hpp"
#include "definitions.hpp"

class StaticTest : public PerformanceTest {
public:
    void run() override;
    const char* getName() const override;
};
