#ifndef ARRAYD_ARRAYD_H
#define ARRAYD_ARRAYD_H
#endif //ARRAYD_ARRAYD_H

#include<iosfwd>
#include<array>

class ArrayD
{
    public:
        ArrayD() = default;
        explicit ArrayD(const std::ptrdiff_t size);
        ArrayD(const ArrayD& rhs);
        ArrayD& operator= (const ArrayD& rhs);
        ~ArrayD();

        double& operator[] (const std::ptrdiff_t i);
        const double& operator[] (const std::ptrdiff_t i) const;
        void resize(const std::ptrdiff_t size);
        void insert(const std::ptrdiff_t i, const double value);
        void remove(const std::ptrdiff_t i);
        std::ptrdiff_t size() const{
            return size_;
        }
        std::ptrdiff_t capacity() const{
            return capacity_;
        }
    private:
        std::ptrdiff_t size_ {0};
        std::ptrdiff_t capacity_ {0};
        double* data{nullptr};
};