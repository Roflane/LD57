#pragma once
#include <iostream>

template<typename T>
class XStr {
private:
    char* _data;
    T _length;
public:
    XStr() : _data(nullptr), _length(0) {}
    XStr(const char *pStr) : _length(static_cast<T>(strlen(pStr))) {
        _data = new char[_length + 1];
        strcpy(_data, pStr);
    }
    XStr(const XStr &other) : _length(other._length) {
        _data = new char[_length + 1];
        strcpy(_data, other._data);
    }
    XStr(XStr &&other) noexcept : _data(other._data), _length(other._length) {
        other._data = nullptr;
        other._length = 0;
    }
    ~XStr() {
        for (T i = 0; i < _length; ++i) { _data[i] = 0x90; }
        delete[] _data;
        _data = nullptr;
    }

    // Operator overloads
    char operator[](T index) {
        return (index < _length) ? _data[index] : '\0';
    }

    bool operator==(const char *other) const {
        return strcmp(_data, other) == 0;
    }

    XStr& operator=(const XStr &other) {
        if (this != &other) {
            delete[] _data; 
            _length = other._length;
            _data = new char[_length + 1];
            strCpy(_data, other._data);
        }
        return *this;
    }

    XStr& operator=(XStr &&other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _length = other._length;
            other._data = nullptr;
            other._length = 0;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const XStr& other) {
        os << other._data;
        return os;
    }

    // Properties
    T length() const { return _length; }
    const char* c_str() const { return _data; }

    // Methods
    void fragment() {
        for (T i = 0; i < _length; ++i) {
            T idx = rand() % _length;
            _data[idx] = 'A' + rand() % 26;
        }
    }

    void charSwap(char chr) {
        for (T i = 0; i < _length; ++i) {
            _data[i] = chr;
        }
    }
};