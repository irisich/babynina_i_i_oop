#include <../include/arrayd/arrayd.hpp>
#include <stdexcept>
#include <algorithm>

ArrayD::ArrayD(const ArrayD& rhs){
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data = new double[capacity_];
    for (size_t i = 0; i < size(); i++){
        *(data + i) = *(rhs.data + i);
    }
}

ArrayD::~ArrayD(){
    delete[] data;
}

ArrayD& ArrayD::operator= (const ArrayD &rhs) {
    if (capacity_ >= rhs.size())
        size_ = rhs.size_;
    else
    {
        capacity_ = 2 * rhs.size() + 1;
        size_ = rhs.size();
        data = new double[capacity_];
    }
    for (std::ptrdiff_t i = 0; i < size_; i++)
    {
        *(data + i) = *(rhs.data + i);
    }
    return *this;
}

ArrayD::ArrayD(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::logic_error("size is negative");
    }
    capacity_ = 2 * size + 1;
    size_ = size;
    data = new double[capacity_];
    //std::fill(*data, *(data + size_), 0.0);
    for (std::ptrdiff_t i = 0; i < size_; i++) {
        *(data + i) = 0.0;
    }
}

double& ArrayD::operator[] (const std::ptrdiff_t i){
    if (i < 0 || i >= size()) {
        throw std::out_of_range("Wrong Index");
    }
    return *(data + i);
}

const double& ArrayD::operator[] (const std::ptrdiff_t i) const{
    if (i < 0 || i >= size()) {
        throw std::out_of_range("Wrong Index");
    }
    return *(data + i);
}

void ArrayD::resize(const std::ptrdiff_t size){
    if (size < 0) {
        throw std::logic_error("size is negative");
    }
    if (size > capacity_)
    {
        capacity_ = 2 * size + 1;
        double* temp = new double[capacity_];
        for (std::ptrdiff_t i = 0; i < size_; i++)
            *(temp + i) = *(data+ i);
        data = temp;
    }
    for (std::ptrdiff_t i = size_; i < size; i++)
        *(data + i) = 0.0;
    size_ = size;
}

void ArrayD::insert(const std::ptrdiff_t index, const double value){
    this -> resize(size_ + 1);
    for(std::ptrdiff_t i = size_ -1; i > index; i -= 1){
        *(data_ + i) = *(data_ + i - 1);
    }
    *(data_ + index) = value;
}

void ArrayD::remove(const std::ptrdiff_t index){
    for(std::ptrdiff_t i = index; i < size_-1; i += 1){
        *(data_ + i) = *(data_ + i + 1);
    }
    this -> resize(size_ - 1);
}