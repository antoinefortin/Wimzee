#include <spdlog/spdlog.h>
#include "core/Application.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


int main() {
    spdlog::info("Wimzee Engine Started!");
    Application app;
    app.Run();
    spdlog::info("Wimzee Engine shutdown!");

    return 0;
}