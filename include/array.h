#pragma once
#include <memory>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        auto new_data = std::make_unique<T[]>(new_capacity);
        
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data[i]);
        }
        
        data = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    Array() : size_(0), capacity_(0), data(nullptr) {}
    
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data = std::make_unique<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            data[i] = other.data[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : size_(other.size_), capacity_(other.capacity_), data(std::move(other.data)) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data = std::make_unique<T[]>(capacity_);
            for (size_t i = 0; i < size_; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data = std::move(other.data);
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    void push_back(T value) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data[size_++] = std::move(value);
    }
    
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size_;
    }
    
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    bool empty() const { return size_ == 0; }
    
    void clear() {
        size_ = 0;
    }
};
