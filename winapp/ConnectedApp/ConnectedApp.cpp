#include <iostream>
#include <thread>
#include "CommonObject.h"
#include "DrawThread.h"
#include "DownloadThread.h"

/**
 * @brief Main function to run the application.
 * Initializes common objects and starts the draw and download threads.
 * @return Exit status of the application.
 */
int main()
{
    CommonObjects common;
    DrawThread draw;
    auto draw_th = std::jthread([&] {draw(common); });
    DownloadThread down;
    auto down_th = std::jthread([&] {down(common); });
    down.SetUrl("https://open.er-api.com/v6/latest/USD");
    std::cout << "running...\n";
    down_th.join();
    draw_th.join();
}
