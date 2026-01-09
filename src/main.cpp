#include <spdlog/spdlog.h>
#include "core/Application.h"
int main() {
    spdlog::info("Wimzee Engine Started!");
    Application app;
    app.Run();
    spdlog::info("Wimzee Engine shutdown!");

    return 0;
}