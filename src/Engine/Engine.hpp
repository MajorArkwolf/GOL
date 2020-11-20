#pragma once

namespace golEngine {
    class Engine {
    public:
        static Engine& get();
        Engine& operator=(const Engine&) = delete;
        ~Engine();

        void run();

    private:
        bool is_running = true;
        double start_time = 0;
        int window_x_size = 1920;
        int window_y_size = 1080;
        Engine();
    };
}
