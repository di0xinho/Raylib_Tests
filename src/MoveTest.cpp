#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "MoveTest.hpp"

struct MovingSprite {
    Vector2 position;
    Vector2 velocity;
    int currentFrame = 0;
    float animationTimer = 0.0f;
};

void MoveTest::run() {
    std::vector<int> thresholds = { 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000 };
    std::filesystem::create_directories(RESULTS_PATH);
    std::ofstream out(std::string(RESULTS_PATH) + getName(), std::ios::app);
    out << "objects,fps" << std::endl;

    Texture2D walkTextures[3];
    if (!(
        walkTextures[0] = LoadTexture(RUN_TEXTURE_1),
        walkTextures[1] = LoadTexture(RUN_TEXTURE_2),
        walkTextures[2] = LoadTexture(RUN_TEXTURE_3),
        walkTextures[0].id && walkTextures[1].id && walkTextures[2].id )) {
        std::cerr << "Failed to load walk animation textures." << std::endl;
        return;
    }

    for (int count : thresholds) {
        std::vector<MovingSprite> sprites;
        sprites.reserve(count);

        for (int i = 0; i < count; ++i) {
            float x = static_cast<float>(GetRandomValue(0, WINDOW_WIDTH - walkTextures[0].width));
            float y = static_cast<float>(GetRandomValue(0, WINDOW_HEIGHT - walkTextures[0].height));
            float vx = static_cast<float>(GetRandomValue(-50, 50)) / 10.0f;
            float vy = static_cast<float>(GetRandomValue(-50, 50)) / 10.0f;
            sprites.push_back({ Vector2{ x, y }, Vector2{ vx, vy } });
        }

        int frames = 0;
        float elapsed = 0.0f;

        while (!WindowShouldClose() && elapsed < TEST_DURATION_SECONDS) {
            float delta = GetFrameTime();
            elapsed += delta;

            for (auto& s : sprites) {
                s.position.x += s.velocity.x;
                s.position.y += s.velocity.y;

                if (s.position.x < 0 || s.position.x + walkTextures[0].width > WINDOW_WIDTH) s.velocity.x *= -1;
                if (s.position.y < 0 || s.position.y + walkTextures[0].height > WINDOW_HEIGHT) s.velocity.y *= -1;

                s.animationTimer += delta;
                if (s.animationTimer >= 0.1f) {
                    s.animationTimer = 0.0f;
                    s.currentFrame = (s.currentFrame + 1) % 3;
                }
            }

            BeginDrawing();
            ClearBackground(BLACK);
            for (const auto& s : sprites)
                DrawTextureV(walkTextures[s.currentFrame], s.position, WHITE);
            EndDrawing();

            ++frames;
        }

        float fps = frames / TEST_DURATION_SECONDS;
        std::cout << "Objects: " << count << ", FPS: " << fps << std::endl;
        out << count << "," << fps << std::endl;
    }

    for (int i = 0; i < 4; ++i)
        UnloadTexture(walkTextures[i]);

    out.close();
}

const char* MoveTest::getName() const {
    return "raylib_move.csv";
}
