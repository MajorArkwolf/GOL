#include "Engine.hpp"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "GameStack.hpp"
#include "Game/BaseScene.hpp"
#include "Game/MainMenu/MainMenu.hpp"

void error_callback(int error, const char* description)
{
    std::cout << "Error: " << error << " " << description << "\n";
}

golEngine::Engine::Engine() {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW.\n";
        return;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);
    //glsl_version_ = "#version 150";

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                   GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

    GLFWwindow * window = glfwCreateWindow(window_x_size, window_y_size, "Game of Life", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window.\n";
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glfwSwapInterval(1);
}

golEngine::Engine::~Engine() {
    glfwTerminate();
}

golEngine::Engine &golEngine::Engine::get() {
    static Engine engine_{};
    return engine_;
}

void golEngine::Engine::run() {
    auto gameStack = GameStack<std::shared_ptr<BaseScene>>(std::make_shared<MainMenu>());
    gameStack.top()->Init();
    start_time = glfwGetTime();
    while (is_running) {
        double t = glfwGetTime();
        double dt = t - start_time;
        gameStack.top()->Update(t, dt);
        gameStack.top()->Draw();

        //Always must be the last check to avoid segfault.
        if (gameStack.check_top()) {
            gameStack.pop_top();
            if (gameStack.stack_size() == 0) {
                is_running = false;
            }
        }
    }
}
