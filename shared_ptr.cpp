#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct State {
    T* ptr;
    int counter = 0;

    ~State() {
        delete ptr;
    }
};

template <typename T>
class SharedPtr {
public:
    SharedPtr() = default;

    SharedPtr(T* ptr) : state_(new State<T>{ptr, 1}) {
    }

    SharedPtr(const SharedPtr& rhs) {
        state_ = rhs.state_;
        ++(state_->counter);
    }

    SharedPtr(SharedPtr&& rhs) {
        state_ = rhs.state_;
        rhs.state_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr rhs) {
        std::swap(state_, rhs.state_);
        return *this;
    }

    T* operator->() {
        if (state_ == nullptr) {
            return nullptr;
        }
        return state_->ptr;
    }

    T* operator->() const {
        if (state_ == nullptr) {
            return nullptr;
        }
        return state_->ptr;
    }

    T& operator*() {
        return *state_->ptr;
    }

    T& operator*() const {
        return *state_->ptr;
    }

    void reset(T * ptr) {
        if (state_) {
            --state_->counter;
            if (state_->counter == 0) {
                delete state_;
            }
        }
        state_ = new State<T>{ptr, 1};
    }

    void swap(SharedPtr& other) {
        std::swap(state_, other.state_);
    }

    T * get() const {
        if (state_ == nullptr) {
            return nullptr;
        }
        return state_->ptr;
    }

    explicit operator bool() const {
        if (state_ == nullptr) {
            return false;
        } else {
            if (state_->ptr == nullptr) {
                return false;
            }
            return true;
        }
    }

    ~SharedPtr() {
        if (state_) {
            --state_->counter;
            if (state_->counter == 0) {
                delete state_;
            }
        }
    }

private:
    State<T>* state_ = nullptr;
};
