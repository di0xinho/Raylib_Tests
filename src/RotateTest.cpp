#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "RotateTest.hpp"

struct RotateSprite {
    Vector2 position;
    float rotation;
};

void RotateTest::run() {
    std::vector<int> thresholds = { 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000 };
    std::filesystem::create_directories(RESULTS_PATH);
    std::ofstream out(std::string(RESULTS_PATH) + getName(), std::ios::app);
    out << "objects,fps" << std::endl;

    Texture2D texture = LoadTexture(IDLE_TEXTURE);
    Vector2 origin = { (float)texture.width / 2, (float)texture.height / 2 };

    for (int count : thresholds) {
        std::vector<RotateSprite> sprites;
        sprites.reserve(count);

        for (int i = 0; i < count; ++i) {
            float x = static_cast<float>(GetRandomValue(origin.x, WINDOW_WIDTH - origin.x));
            float y = static_cast<float>(GetRandomValue(origin.y, WINDOW_HEIGHT - origin.y));
            sprites.push_back({ Vector2{ x, y }, 0.0f });
        }

        int frames = 0;
        float elapsed = 0.0f;

        while (!WindowShouldClose() && elapsed < TEST_DURATION_SECONDS) {
            float delta = GetFrameTime();
            elapsed += delta;

            BeginDrawing();
            ClearBackground(RAYWHITE);
            for (auto& s : sprites) {
                s.rotation += 1.0f;
                DrawTexturePro(
                    texture,
                    { 0, 0, (float)texture.width, (float)texture.height },
                    { s.position.x, s.position.y, (float)texture.width, (float)texture.height },
                    origin,
                    s.rotation,
                    WHITE
                );
            }
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

const char* RotateTest::getName() const {
    return "raylib_rotate.csv";
}