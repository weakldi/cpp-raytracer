#include "thread_pool.hpp"
#include <chrono>
thread_pool::thread_pool() {
    for(int i = 0; i < 8; i++){
        threads.push_back(std::thread(&thread_pool::thread_run, this));
    }
}

thread_pool::~thread_pool(){
    run = false;
    for(int i = 0; i < 8; i++){
        threads[i].join();
    }
}

std::optional<std::function<void()>> thread_pool::next_job(){
    std::scoped_lock l(mutex);
    if(!jobs.empty()){
        std::optional<std::function<void()>> toRet = {jobs.front()};
        jobs.pop();
        return toRet;
    } 
    return std::nullopt;
}
void thread_pool::thread_run(){
    using namespace std::chrono_literals;
    while(run){
        
        std::optional<std::function<void()>> f = next_job();
       
        if(f){
            f.value()();
        }else{
            queue_empty_cv.notify_all();
            std::unique_lock<std::mutex> lk(new_job_mutex);
            new_job_cv.wait_for(lk, 100ms); //Wait for new jobs
            lk.unlock();
        }
        
    }
}