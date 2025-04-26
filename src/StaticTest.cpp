#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "StaticTest.hpp"

struct StaticSprite {
    Vector2 position;
};

void StaticTest::run() {
    std::vector<int> thresholds = { 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000 };
    std::filesystem::create_directories(RESULTS_PATH);
    std::ofstream out(std::string(RESULTS_PATH) + getName(), std::ios::app);
    out << "objects,fps" << std::endl;

    Texture2D texture = LoadTexture(IDLE_TEXTURE);

    for (int count : thresholds) {
        std::vector<StaticSprite> sprites;
        sprites.reserve(count);

        for (int i = 0; i < count; ++i) {
            float x = static_cast<float>(GetRandomValue(0, WINDOW_WIDTH  - texture.width));
            float y = static_cast<float>(GetRandomValue(0, WINDOW_HEIGHT - texture.height));
            sprites.push_back({ Vector2{ x, y } });
        }

        int frames = 0;
        float elapsed = 0.0f;

        while (!WindowShouldClose() && elapsed < TEST_DURATION_SECONDS) {
            float delta = GetFrameTime();
            elapsed += delta;

            BeginDrawing();
            ClearBackground(RAYWHITE);
            for (const auto& s : sprites)
                DrawTextureV(texture, s.position, WHITE);
            EndDrawing();

            ++frames;
        }

        float fps = frames / TEST_DURATION_SECONDS;
        std::cout << "Objects: " << count << ", FPS: " << fps << std::endl;
        out << count << "," << fps << std::endl;
    }

    UnloadTexture(texture);
    out.close();
}

const char* StaticTest::getName() const {
    return "raylib_static.csv";
}