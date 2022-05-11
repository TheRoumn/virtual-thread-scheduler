#ifndef PRIORITY_SCHEDULER_HPP
#define PRIORITY_SCHEDULER_HPP

#include <limits>
#include <memory>

constexpr size_t CACHE_LINE_SIZE = 64;

/**
 * @brief The main scheduler class
 *
 * @tparam VTLS_T virtual thread local storage type. Must be default constructable.
 */
template<typename VTLS_T>
class scheduler {
public:
    /**
     * @brief Virtual thread ID
     *
     */
    using vthread_id_t = size_t;

    /**
     * @brief An invalid virtual thread ID
     *
     */
    static constexpr size_t INVALID_VTHREAD_ID = std::numeric_limits<vthread_id_t>::max();

    /**
     * @brief A class holding information about a virtual thread
     */
    class alignas(CACHE_LINE_SIZE) vthread_info {
    public:
        /**
         * @brief Returns the virtual thread ID
         */
        vthread_id_t id() const {}

        /**
         * @brief Returns a thread local data of the virtual thread
         */
        VTLS_T& data() {}
    };

    /**
     * @brief A simple unit executed atop of the virtual threads
     */
    class task {
    public:
        virtual ~task() {}

        /**
         * @brief A function implementing the main body of the task. Each task executes this function and terminates
         *
         * @param s A scheduler invoking this task
         * @param info Information about the virtual thread executing the task
         */
        virtual void run(scheduler& s, vthread_info& info) = 0;
    };

    /**
     * @brief Construct a new scheduler object
     *
     * @param num_threads Number of real threads
     * @param time_to_idle_ms Time in milliseconds before a thread goes to sleep
     */
    scheduler(size_t num_threads, size_t time_to_idle_ms) {}

    /**
     * @brief Add a new task into the scheduler's queue
     * @note Can be called in parallel
     *
     * @param task Task to be added
     */
    void add_task(std::unique_ptr<task>&& t) {}
};

#endif // PRIORITY_SCHEDULER_HPP
#pragma once
