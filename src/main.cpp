#include "Engine/Engine.hpp"

int main(int argc, char* argv[]) {
    auto engine = golEngine::Engine::get();
    engine.run();
    return 0;
}
