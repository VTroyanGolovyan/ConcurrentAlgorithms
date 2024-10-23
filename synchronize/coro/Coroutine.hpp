#ifndef COROUTINE_HPP
#define COROUTINE_HPP

#include <boost/context/detail/fcontext.hpp>
#include <boost/context/protected_fixedsize_stack.hpp>

#include <exception>
#include <functional>
#include <stdexcept>

namespace coro {

class SuspendContext {
    friend void CoroutineLogic(boost::context::detail::transfer_t transfer);

    friend class StackfullCoroutine;

    public:
        void Suspend();
    private:
        explicit SuspendContext(boost::context::detail::transfer_t* transfer);

        boost::context::detail::transfer_t* transfer_;
};

using Task = std::function<void(SuspendContext)>;

class StackfullCoroutine {
public:
    friend void CoroutineLogic(boost::context::detail::transfer_t transfer);

    explicit StackfullCoroutine(Task task, size_t stack_size = 124 * 1024);

    void Resume();

    bool IsCompleted();
    
    bool Running();

    ~StackfullCoroutine();

private:
    boost::context::detail::fcontext_t coro_context_;
    boost::context::protected_fixedsize_stack allocator_;
    boost::context::stack_context stack_ctx_; 

    void* stack_;
    size_t stack_size_;
    Task task_;
    std::atomic<bool> running_{false};
    std::atomic<bool> completed_body_{false};
    std::atomic<bool> completed_{false};

    std::exception_ptr exception_;
};


}

#endif
