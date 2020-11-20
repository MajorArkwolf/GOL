#pragma once
#include <stack>
namespace golEngine {

    class Engine;

    template<class T>
    class GameStack {
    public:
        GameStack() = delete;

        ~GameStack() {
            while(!game_stack.empty()) {
                game_stack.pop();
            }
        }

        explicit GameStack(T state) {
            game_stack.emplace(state);
        }

        T& top() {
            return game_stack.top();
        }

        void pop_top() {
            pop_top_ = true;
        }

        bool check_top() {
            return pop_top_;
        }

        size_t stack_size() {
            return game_stack.size();
        }

    private:
        friend Engine;
        bool pop_top_ = false;
        std::stack<T> game_stack = {};

        void remove_top() {
            if (pop_top_) {
                game_stack.pop();
                pop_top_ = false;
            }
        }
    };
}