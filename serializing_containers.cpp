#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&pod), sizeof(pod));
}

void Serialize(const std::string& str, std::ostream& out) {
    size_t sz = str.size();
    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    for (size_t i = 0; i < sz; ++i) {
        Serialize(str[i], out);
    }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
    size_t sz = data.size();
    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    for (const T& item : data) {
        Serialize(item, out);
    }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
    size_t sz = data.size();
    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
    for (auto [key, value] : data) {
        Serialize(key, out);
        Serialize(value, out);
    }
}

template <typename T>
void Deserialize(std::istream& in, T& pod) {
    in.read(reinterpret_cast<char*>(&pod), sizeof(pod));
}

void Deserialize(std::istream& in, std::string& str) {
    size_t sz;
    in.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    str.resize(sz);
    for (size_t i = 0; i < sz; ++i) {
        Deserialize(in, str[i]);
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
    size_t sz;
    in.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    data.resize(sz);
    for (size_t i = 0; i < sz; ++i) {
        Deserialize(in, data[i]);
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
    size_t sz;
    in.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    for (size_t i = 0; i < sz; ++i) {
        T1 key;
        T2 value;
        Deserialize(in, key);
        Deserialize(in, value);
        data[key] = value;
    }
}
