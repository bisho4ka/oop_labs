#include "../include/coroutine.h"

CoroutineTask CoroutineTask::promise_type::get_return_object() {
    return CoroutineTask{ handle::from_promise(*this) };
}

std::suspend_always CoroutineTask::promise_type::initial_suspend() { 
    return {}; 
}

std::suspend_always CoroutineTask::promise_type::final_suspend() {
    return std::suspend_always {}; 
}

void CoroutineTask::promise_type::return_void() noexcept {}

void CoroutineTask::promise_type::unhandled_exception() {
    std::terminate();
}

CoroutineTask::CoroutineTask(handle h) : co_handle(h) {}

CoroutineTask::CoroutineTask(CoroutineTask&& other) noexcept : co_handle(other.co_handle) { 
    other.co_handle = nullptr;
}

CoroutineTask& CoroutineTask::operator=(CoroutineTask&& other) noexcept {
    if (this != &other) {
        if (co_handle) 
            co_handle.destroy(); 
        co_handle = other.co_handle; 
        other.co_handle = nullptr; 
    }
    return *this;
}

void CoroutineTask::resume() {
    if (co_handle && !co_handle.done()) {
        co_handle.resume();
    }
}

bool CoroutineTask::done() const noexcept {
    return !co_handle || co_handle.done();
}

CoroutineTask::~CoroutineTask() {
    if (co_handle)
        co_handle.destroy();
}



Scheduler& Scheduler::instance() {
    static Scheduler scheduler;
    return scheduler;
}

void Scheduler::schedule(CoroutineTask&& task) {
    tasks.push_back(std::move(task));
}

void Scheduler::start() {
    if (!tasks.empty()) {
        CoroutineTask task = std::move(tasks.front());
        tasks.pop_front();
        task.resume();
        if (!task.done()) {
            tasks.push_back(std::move(task));
        }
    }
}