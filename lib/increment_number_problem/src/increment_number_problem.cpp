#include <increment_number_problem/increment_number_problem.hpp>

#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

namespace {

struct object_t;
void odd(object_t & object, size_t max_num) noexcept;
void even(object_t & object, size_t max_num) noexcept;
void stop(object_t & object) noexcept;

struct object_t final // NOLINT(altera-struct-pack-align)
{
    std::condition_variable odd_cv;
    std::condition_variable even_cv;
    std::mutex mutex;

    size_t num{1U};
    std::once_flag stop_flag;
    bool stopped{false};
};

// An odd number is an integer of the form n=2k+1, where k is an integer.
void odd(object_t & object, size_t const max_num) noexcept
{
    while (true) {
        std::unique_lock<std::mutex> lock(object.mutex);
        while ((object.num & 1U) != 1U && !object.stopped) {
            auto const & ref = object;
            object.odd_cv.wait(lock, [&ref]() {
                return (ref.num & 1U) == 1U || ref.stopped;
            });
        }

        if (object.num >= max_num) {
            break;
        }

        ++object.num;

        lock.unlock();
        object.even_cv.notify_one();
    }

    stop(object);
}

// An even number is an integer of the form n=2k, where k is an integer.
void even(object_t & object, size_t const max_num) noexcept
{
    while (true) {
        std::unique_lock<std::mutex> lock(object.mutex);
        while ((object.num & 1U) != 0U && !object.stopped) {
            auto const & ref = object;
            object.even_cv.wait(lock, [&ref]() {
                return (ref.num & 1U) == 0U || ref.stopped;
            });
        }

        if (object.num >= max_num) {
            break;
        }

        ++object.num;

        lock.unlock();
        object.odd_cv.notify_one();
    }

    stop(object);
}

void stop(object_t & object) noexcept
{
    std::call_once(object.stop_flag, [&object]() {
        std::unique_lock<std::mutex> lock(object.mutex);
        object.stopped = true;
    });

    object.odd_cv.notify_one();
    object.even_cv.notify_one();
}

} // namespace

size_t increase_number(size_t num, size_t n)
{
    std::vector<std::thread> threads;
    threads.reserve(n);

    object_t object{};
    for (size_t i = 0; i < n / 2; ++i) {
        threads.emplace_back(odd, std::ref(object), num);
        threads.emplace_back(even, std::ref(object), num);
    }

    for (auto & thread : threads) {
        thread.join();
    }

    return object.num;
}
