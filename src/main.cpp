#include "StaticTest.hpp"
#include "AlphaTest.hpp"
#include "RotateTest.hpp"
#include "MoveTest.hpp"
#include "definitions.hpp"
#include <memory>
#include <vector>
#include <iostream>

int main() {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(0);

    std::vector<std::unique_ptr<PerformanceTest>> tests;
    tests.push_back(std::make_unique<StaticTest>());
    tests.push_back(std::make_unique<AlphaTest>());
    tests.push_back(std::make_unique<RotateTest>());
    tests.push_back(std::make_unique<MoveTest>());

    for (const auto& test : tests) {
        std::cout << "Uruchomiony test: " << test->getName() << std::endl;
        test->run();
    }

    CloseWindow();
    return 0;
}
