// Oliver Kovacs 2023 MIT

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>

#define SECOND 1000
#define MINUTE (60 * SECOND)
#define HOUR (60 * MINUTE)
#define EMPTY ""

auto clear() -> void {
    std::cout << "\e[1;1H\e[2J" << std::endl;
}

auto input(std::string *s, bool *run) -> void {
    std::cin >> *s;
    *run = false;
}

auto output(int64_t milliseconds, bool *run) -> void {
    int64_t difference_ms;
    int64_t delta_ms;
    int64_t delta_h;
    int64_t delta_min;
    int64_t delta_s;
    const auto start = std::chrono::steady_clock::now();

    clear();

    do {
        const auto difference = std::chrono::steady_clock::now() - start;
        difference_ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(difference)
                .count();

        delta_ms = milliseconds - difference_ms;
        delta_h = delta_ms / HOUR;
        delta_ms = delta_ms % HOUR;
        delta_min = delta_ms / MINUTE;
        delta_ms = delta_ms % MINUTE;
        delta_s = delta_ms / SECOND;
        
        printf("%02" PRId64 ":%02" PRId64 ":%02" PRId64 " \r",
            delta_h,
            delta_min,
            delta_s);

        std::cout.flush();
    }
    while (difference_ms < milliseconds && *run);
}

template<typename T>
auto prompt(std::string text) -> T {
    clear();
    T out;
    std::cout << text;
    std::cin >> out;
    return out;
}

auto main() -> int {

    auto password = prompt<std::string>("Enter a password: ");
    auto minutes = prompt<float>("Enter a duration (min): ");

    int64_t milliseconds = minutes * MINUTE;
    
    bool run = true;
    std::string out = EMPTY;
    std::thread o (output, milliseconds, &run);
    std::thread i (input, &out, &run);

    o.join();
    i.detach();
    
    if (out == EMPTY) {
        std::cout << "Time is up!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "\r         \r";
    if (out != password) {
        std::cout << "Incorrect!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Correct!" << std::endl;
    return EXIT_SUCCESS;
}
