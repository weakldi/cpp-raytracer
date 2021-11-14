#ifndef THREAD_POOL_HPP
#define  THREAD_POOL_HPP

#include <thread>
#include <fstream>
#include <functional>
#include <future>
#include <tuple>
#include <vector>
#include <queue>
#include <cstdint>
#include <mutex>
#include <optional>
#include <iostream>
#include  <chrono>
class thread_pool{
    public:
        thread_pool();
        ~thread_pool();
        template<typename FUNC, typename ... ARGS >
        void add(const FUNC &f, const ARGS& ...args ){
            std::scoped_lock l(mutex);
            jobs.push([f, args...]{ f(args...);});
            //std::cout << "new job\n";
            new_job_cv.notify_one();
        }
        void wait_for_finish(){
            while(!jobs.empty()){
                //std::cout << "Jobs left: " << jobs.size()<< std::endl;
                std::unique_lock<std::mutex> empty_lock(queue_empty_mutex);
                queue_empty_cv.wait(empty_lock);
                
                empty_lock.unlock();

                std::this_thread::yield();
                //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        std::optional<std::function<void()>> next_job();
    private:
        void thread_run();
    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> jobs;
        std::mutex mutex;
        std::mutex new_job_mutex;
        std::mutex  queue_empty_mutex;
        std::condition_variable new_job_cv;
        std::condition_variable queue_empty_cv;
    public:
        bool run = true;
};


#endif  // THREAD_POOL_HPP 