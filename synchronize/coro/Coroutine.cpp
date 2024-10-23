#include "Coroutine.hpp"

namespace coro {

using Task = std::function<void(SuspendContext)>;

class StackfullCoroutine;

thread_local StackfullCoroutine* current_coroutine_{nullptr};

void CoroutineLogic(boost::context::detail::transfer_t transfer); 

// ==================================================================================

void SuspendContext::Suspend() {
        *transfer_ = boost::context::detail::jump_fcontext(transfer_->fctx, 0);
}

SuspendContext::SuspendContext(boost::context::detail::transfer_t* transfer)
    : transfer_(transfer) {
}

// ==================================================================================

StackfullCoroutine::StackfullCoroutine(Task task, size_t stack_size) : task_(task), stack_size_(stack_size) {
    stack_ctx_ = allocator_.allocate();
    coro_context_ = boost::context::detail::make_fcontext(
        stack_ctx_.sp, 
        stack_ctx_.size,                             
        CoroutineLogic                        
    );
    current_coroutine_ = this; // cringe method to pass Coro object into function context
    Resume();
}

void StackfullCoroutine::Resume() {
    running_ = true;
    auto transfer = boost::context::detail::jump_fcontext(coro_context_, 0);
    coro_context_ = transfer.fctx;
    completed_ = completed_body_.load();
    running_ = false;
}

bool StackfullCoroutine::IsCompleted() {
    return completed_;
}

StackfullCoroutine::~StackfullCoroutine() {
  allocator_.deallocate(stack_ctx_);
}

bool StackfullCoroutine::Running() {
    return running_;
}

// ==================================================================================
// CORO LOGIC IMPLEMENTATION

void CoroutineLogic(
    boost::context::detail::transfer_t transfer_
) {
    boost::context::detail::transfer_t transfer = transfer_;
    auto* coro = current_coroutine_;
    current_coroutine_ = nullptr;
    SuspendContext self(&transfer);
    self.Suspend();
    coro->task_(self);
    coro->completed_body_ = true;
    self.Suspend();
}

}