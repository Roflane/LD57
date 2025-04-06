#pragma once
#include <iostream>

template<typename T>
class XVec {
private:
    // Fields
    T* _data;
    unsigned __int64 _size;
    unsigned __int64 _cap;

    // Methods
    void resize() {
        unsigned __int64 newCap = (_cap != 1) ? (_size * 1.5) : 2;
        T* newXVec = new T[newCap]();

        for (unsigned __int64 i = 0; i < _size; ++i) {
            newXVec[i] = _data[i];
        }
        delete[] _data;
        _data = newXVec;
        _cap = newCap;
    }
public:
    XVec() : _data(nullptr), _size(0), _cap(0) {}
    XVec(unsigned __int64 size) : _size(size), _cap(size) {
        _data = (_cap > 0) ? new T[_cap]() : nullptr;
    }
    XVec(std::initializer_list<T> init_list) : _size(init_list.size()), _cap(init_list.size()) {
        _data = new T[_cap]();
        unsigned __int64 index = 0;
        for (auto value : init_list) {
            if (index < _size) {
                _data[index++] = value;
            }
        }
    }
    XVec(const XVec& other) : _size(other._size), _cap(other._cap) {
        _data = new T[_cap]();
        for (unsigned __int64 i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    XVec(XVec&& other) noexcept : _data(other._data), _size(other._size), _cap(other._cap) {
        other._data = nullptr;
        other._size = 0;
        other._cap = 0;
    }
    ~XVec() {
        std::cout << "~XVec" << std::endl;

        for (unsigned __int64 i = 0; i < size(); ++i) {
            _data[i] = (T)0;
        }
        delete[] _data;
        _data = nullptr;
    }

    // Operator overloads
    XVec operator+(const XVec other) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);
        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            newXVec._data[i] = _data[i] + other._data[i];
        }
        return newXVec;
    }

    XVec operator-(const XVec other) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);
        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            newXVec._data[i] = _data[i] - other._data[i];
        }
        return newXVec;
    }

    XVec operator*(const XVec other) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);
        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            newXVec._data[i] = _data[i] * other._data[i];
        }
        return newXVec;
    }

    XVec operator/(const XVec other) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;
        XVec newXVec(actualSize);

        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            if (other._data[i] == 0) { return 0; }
            newXVec._data[i] = _data[i] / other._data[i];
        }
        return newXVec;
    }

    auto operator+=(const XVec other) -> decltype(_data) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;

        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            _data[i] += other._data[i];
        }
        return _data;
    }

    auto operator-=(const XVec other) -> decltype(_data) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;

        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            _data[i] -= other._data[i];
        }
        return _data;
    }

    auto operator*=(const XVec other) -> decltype(_data) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;

        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            _data[i] *= other._data[i];
        }
        return _data;
    }

    auto operator/=(const XVec other) -> decltype(_data) {
        unsigned __int64 actualSize = (_size > other._size) ? other.size() : _size;

        for (unsigned __int64 i = 0; i < actualSize; ++i) {
            _data[i] /= other._data[i];
        }
        return _data;
    }

    XVec& operator++() {
        for (unsigned __int64 i = 0; i < _size; ++i) {
            ++_data[i];
        }
        return *this;
    }

    XVec operator++(int) {
        XVec temp(*this);
        for (unsigned __int64 i = 0; i < _size; ++i) {
            ++_data[i];
        }
        return temp;
    }

    XVec& operator--() {
        for (unsigned __int64 i = 0; i < _size; ++i) {
            _data[i] -= 1;
        }
        return *this;
    }

    XVec operator--(int) {
        XVec temp = *this;
        --(*this);
        return temp;
    }

    T& operator[](unsigned __int64 index) {
        if (index >= _size) {
            return _data[_size - 1];
        }
        else if (index == _cap) { return _data[_size - 1]; }
        return _data[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const XVec& vec) {
        for (unsigned __int64 i = 0; i < vec.size(); ++i) {
            os << vec.get(i);
            if (i < vec.size() - 1) os << ", ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, XVec& vec) {
        for (unsigned __int64 i = 0; i < vec.size(); ++i) {
            is >> vec._data[i];
        }
        return is;
    }

    // Properties
    T get(unsigned __int64 index) const {
        if (index >= _size) { return T(); }
        return _data[index];
    }

    void set(T value, unsigned __int64 index) {
        if (index >= _size) {
            push_back(value);
        }
        _data[index] = value;
    }

    // Methods
    unsigned __int64 size() const { return _size; }
    unsigned __int64 cap()  const { return _cap; }

    void push_back(T value) {
        if (_size == _cap) { resize(); }
        _data[_size++] = value;
    }

    void insert(T value, unsigned __int64 index) {
        if (_size == _cap) { resize(); }
        if (index > _size) { index = _size; }

        for (unsigned __int64 i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }
        _data[index] = value;
        _size++;
    }

    void remove(unsigned __int64 index) {
        if (index >= _size - 1) { pop(); }

        for (unsigned __int64 i = index; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }
        _size--;
    }

    void pop() {
        if (_size == 0) return;

        _data[_size - 1] = 0x90;
        _size -= 1;
    }
};