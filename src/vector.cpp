#include <algorithm>
#include "vector.h"

Vector::Iterator::Iterator(Vector::ValueType* pointer) {
    ptr_ = pointer;
}

Vector::ValueType& Vector::Iterator::operator*() const {
    return *ptr_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
    return ptr_;
}

Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    ptr_ = other.ptr_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    ++ptr_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator--() {
    --ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator new_pointer(*this);
    ++*this;
    return new_pointer;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    Iterator new_pointer(*this);
    --*this;
    return new_pointer;
}

Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    Iterator new_pointer(ptr_ + shift);
    return new_pointer;
}

Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return ptr_ - other.ptr_;
}

Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    ptr_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    ptr_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return ptr_ == other.ptr_;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return ptr_ != other.ptr_;
}

std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    DifferenceType dif = ptr_ - other.ptr_;
    if (dif == 0) {
        return std::strong_ordering::equal;
    } else if (dif > 0) {
        return std::strong_ordering::greater;
    } else {
        return std::strong_ordering::less;
    }
}

Vector::Vector(size_t size) {
    size_ = size;
    capacity_ = size;
    array_ = new ValueType[size];
    for (size_t i = 0; i < size; ++i) {
        array_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    size_ = list.size();
    capacity_ = list.size();
    array_ = new ValueType[size_];
    size_t i = 0;
    for (auto& current_element : list) {
        array_[i++] = current_element;
    }
}

Vector::Vector(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = other.array_;
}

Vector& Vector::operator=(const Vector& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    array_ = other.array_;
    return *this;
}

Vector::~Vector() {
    delete[] array_;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType* Vector::Data() const {
    return array_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return array_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return array_[position];
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.Size()) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (array_[i] != other[i]) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    for (size_t i = 0; i < std::min(size_, other.Size()); ++i) {
        if (array_[i] > other[i]) {
            return std::strong_ordering::greater;
        } else if (array_[i] < other[i]) {
            return std::strong_ordering::less;
        }
    }
    if (size_ < other.Size()) {
        return std::strong_ordering::less;
    } else if (size_ > other.Size()) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}

void Vector::Reserve(Vector::SizeType new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    int* new_array = new ValueType[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_array[i] = array_[i];
    }
    capacity_ = new_capacity;
    std::swap(array_, new_array);
    delete[] new_array;
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const Vector::ValueType& new_element) {
    if (capacity_ == size_) {
        Reserve(capacity_ != 0 ? 2 * capacity_ : 1);
    }
    array_[size_] = new_element;
    ++size_;
}

void Vector::PopBack() {
    if (size_ != 0) {
        --size_;
    }
}

void Vector::Swap(Vector& other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
}

Vector::Iterator Vector::Begin() {
    return Iterator(array_);
}

Vector::Iterator Vector::End() {
    return Iterator(array_ + size_);
}

Vector::Iterator Vector::begin() {
    return Iterator(array_);
}

Vector::Iterator Vector::end() {
    return Iterator(array_ + size_);
}
