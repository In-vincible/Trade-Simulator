//
// Created by Bikram Bharti on 08-06-2023.
//

#ifndef CMAKE_TEMPLATE_SHARED_MEMORY_WRAPPER_H
#define CMAKE_TEMPLATE_SHARED_MEMORY_WRAPPER_H

#include <iostream>
#include <vector>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

template<typename T>
class SharedVector2D {
public:
    using Allocator = boost::interprocess::allocator<T, boost::interprocess::managed_shared_memory::segment_manager>;

    SharedVector2D(const std::string& segmentName, std::size_t rows, std::size_t cols)
            : segmentName_(segmentName), rows_(rows), cols_(cols) {
        createSharedMemory();
        createVector();
    }

    ~SharedVector2D() {
        destroyVector();
        destroySharedMemory();
    }

    void setElement(std::size_t row, std::size_t col, const T& value) {
        if (row < rows_ && col < cols_) {
            vector_[row][col] = value;
        }
    }

    T getElement(std::size_t row, std::size_t col) const {
        if (row < rows_ && col < cols_) {
            return vector_[row][col];
        }
        return T();  // Return a default-constructed value if indices are out of bounds
    }

private:
    std::string segmentName_;
    std::size_t rows_;
    std::size_t cols_;
    boost::interprocess::managed_shared_memory segment_;
    std::vector<T, Allocator>** vector_;

    void createSharedMemory() {
        segment_ = boost::interprocess::managed_shared_memory(boost::interprocess::open_or_create, segmentName_.c_str(), rows_ * sizeof(std::vector<T, Allocator>*));
    }

    void destroySharedMemory() {
        boost::interprocess::shared_memory_object::remove(segmentName_.c_str());
    }

    void createVector() {
        Allocator allocator(segment_.get_segment_manager());
        vector_ = segment_.construct<std::vector<T, Allocator>*>("SharedVector2D")[boost::interprocess::anonymous_instance](rows_, allocator);
        for (std::size_t i = 0; i < rows_; ++i) {
            vector_[i] = segment_.construct<std::vector<T, Allocator>>(boost::interprocess::anonymous_instance)(cols_, allocator);
        }
    }

    void destroyVector() {
        for (std::size_t i = 0; i < rows_; ++i) {
            segment_.destroy_ptr(vector_[i]);
        }
        segment_.destroy_ptr(vector_);
    }
};

#endif //CMAKE_TEMPLATE_SHARED_MEMORY_WRAPPER_H
