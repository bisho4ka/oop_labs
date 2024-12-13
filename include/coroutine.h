#pragma once

#include <coroutine>
#include <memory>
#include <deque>
#include <functional>

class CoroutineTask {
public:
    struct promise_type;
    using handle = std::coroutine_handle<promise_type>;

    struct promise_type {
        CoroutineTask get_return_object();
        std::suspend_always initial_suspend();
        std::suspend_always final_suspend();
        void return_void() noexcept;
        void unhandled_exception();
    };

    CoroutineTask(handle h);

    CoroutineTask(const CoroutineTask&) = delete; 
    CoroutineTask& operator=(const CoroutineTask&) = delete;

    CoroutineTask(CoroutineTask&& other) noexcept;
    CoroutineTask& operator=(CoroutineTask&& other) noexcept;

    void resume();
    bool done() const noexcept;

    ~CoroutineTask();

private:
    handle co_handle;
};



class Scheduler {
private:
    std::deque<CoroutineTask> tasks;
public:
    void schedule(CoroutineTask&& task);
    void start();

    static Scheduler& instance();
};