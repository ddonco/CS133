// CS 133 Project 4: 20 Questions

// A special queue type required by the Vader GUI to deal with concurrency 
// (multiple threads running at the same time). This class forces the program  
// to stop and wait for the user to enter input 

#ifndef _blockingqueue_h_
#define _blockingqueue_h_ 

#include <mutex>
#include <condition_variable>
#include <deque>

using namespace std;

template <typename T>
class BlockingQueue {
private:
    // a lock - only one thing can hold this at once
    mutex d_mutex;

    // a method of sending signals between threads so that we can tell if data
    // is ready and waiting for us
    condition_variable d_condition;

    // a queue to store our data
    deque<T> d_queue;
public:
    // adds the passed in value to the queue and notifies that 
    void push(T const& value) {
        { // extra parens give us internal scope block
            unique_lock<mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        // tell the other thread that there is now data in the queue 
        this->d_condition.notify_one();
    }

    // removes the first value from the queue and returns it
    T pop() {
        unique_lock<std::mutex> lock(this->d_mutex);
        // if the queue is empty, wait until we are notified something is in it
        this->d_condition.wait(lock, 
            [=]{ 
                return !this->d_queue.empty(); 
            });
        T rc(move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }
};

#endif