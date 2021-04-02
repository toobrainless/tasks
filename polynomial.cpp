#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Polynomial {
private:
    int degree;
    std::vector<T> data;

    void SetData() {
        if (data == std::vector<T>(data.size())) {
            degree = -1;
            data.clear();
        } else {
            while (*(data.end() - 1) == T(0)) {
                data.pop_back();
            }

            degree = data.size() - 1;
        }
    }

public:
    Polynomial(const std::vector<T>& args) : data(args) {
        SetData();
    }

    template<typename iterator>
    Polynomial(const iterator& begin, const iterator& end) : data(begin, end) {
        SetData();
    }

    Polynomial(const T& arg = T(0)) {
        if (arg == T(0)) {
            degree = -1;
        } else {
            data.push_back(arg);
            degree = 0;
        }
    }

    int Degree() const {
        return degree;
    }

    friend bool operator== (const Polynomial& rhs, const Polynomial& lhs) {
        return (rhs.data == lhs.data);
    }

    friend bool operator!= (const Polynomial& rhs, const Polynomial& lhs) {
        return (rhs.data != lhs.data);
    }

    Polynomial& operator+= (const Polynomial& rhs) {
        if (rhs.degree > degree) {
            data.resize(rhs.degree + 1, T(0));
            degree = rhs.degree;
            for (int i = 0; i <= degree; ++i) {
                data[i] += rhs.data[i];
            }
        } else {
            for (int i = 0; i <= rhs.degree; ++i) {
                data[i] += rhs.data[i];
            }

            SetData();
        }

        return (*this);
    }

    friend Polynomial operator+ (const Polynomial& lhs, const Polynomial& rhs) {
        Polynomial ans(lhs);
        ans += rhs;

        return ans;
    }

    Polynomial& operator-= (const Polynomial& rhs) {
        if (rhs.degree > degree) {
            data.resize(rhs.degree + 1);
            degree = rhs.degree;
            for (int i = 0; i <= degree; ++i) {
                data[i] -= rhs.data[i];
            }
        } else {
            for (int i = 0; i <= rhs.degree; ++i) {
                data[i] -= rhs.data[i];
            }

            SetData();
        }
        return (*this);
    }

    friend Polynomial operator- (const Polynomial& lhs, const Polynomial& rhs) {
        Polynomial ans(lhs);
        ans -= rhs;

        return ans;
    }

    friend Polynomial operator* (const Polynomial& lhs, const Polynomial& rhs) {
        Polynomial ans;
        if (rhs.degree == -1 || lhs.degree == -1) {
            return ans;
        }
        ans.degree = lhs.degree + rhs.degree;
        ans.data.resize(lhs.degree + rhs.degree + 1);
        for (int j = 0; j <= rhs.degree; ++j) {
            for (int i = 0; i <= lhs.degree; ++i) {
                ans.data[i + j] += rhs.data[j] * lhs.data[i];
            }
        }

        return ans;
    }

    Polynomial& operator*= (const Polynomial& rhs) {
        (*this) = (*this) * rhs;
        return (*this);
    }

    const T operator[] (size_t i) const {
        if (degree == -1) {
            return T(0);
        } else if (i > static_cast<size_t>(degree)) {
            return T(0);
        } else {
            return data[i];
        }
    }

    typename std::vector<T>::const_iterator begin() const {
        return data.begin();
    }

    typename std::vector<T>::const_iterator end() const {
        return data.end();
    }

    T operator() (const T& arg) const {
        if (degree == -1) {
            return T(0);
        }
        T ans = data[0];
        auto deg = arg;

        for (int i = 1; i <= degree; ++i) {
            ans += deg * data[i];
            deg *= arg;
        }

        return ans;
    }

    friend Polynomial operator& (const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.degree == -1) {
            return lhs;
        } else if (rhs.degree == -1) {
            return Polynomial(lhs.data[0]);
        } else if (lhs.degree == 0) {
            return lhs;
        } else if (rhs.degree == 0) {
            return Polynomial(lhs(rhs.data[0]));
        } else {
            Polynomial ans(lhs[0]);
            Polynomial deg(rhs);
            for (int i = 1; i <= lhs.degree; ++i) {
                ans += lhs[i] * deg;
                deg *= rhs;
            }

            return ans;
        }
    }

    friend Polynomial operator/ (const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.degree >= rhs.degree) {
            Polynomial copy(lhs);
            Polynomial ans;
            std::vector<Polynomial> degs;
            Polynomial x({0, 1, 0});
            degs.push_back(Polynomial(1));
            for (int i = 1; i <= lhs.degree - rhs.degree; ++i) {
                degs.push_back(degs[degs.size() - 1] * x);
            }

            while (copy.degree >= rhs.degree) {
                ans += (copy[copy.degree] / rhs[rhs.degree]) * degs[copy.degree - rhs.degree];
                copy -= (copy[copy.degree] / rhs[rhs.degree]) *
                        rhs * degs[copy.degree - rhs.degree];
            }

            return ans;
        } else {
            return Polynomial(T(0));
        }
    }

    friend Polynomial operator% (const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.degree >= rhs.degree) {
            Polynomial copy(lhs);
            Polynomial ans;
            std::vector<Polynomial> degs;
            Polynomial x({0, 1, 0});
            degs.push_back(Polynomial(1));
            for (int i = 1; i <= lhs.degree - rhs.degree; ++i) {
                degs.push_back(degs[degs.size() - 1] * x);
            }

            while (copy.degree >= rhs.degree) {
                copy -= (copy[copy.degree] / rhs[rhs.degree]) *
                        rhs * degs[copy.degree - rhs.degree];
            }

            return copy;
        } else {
            return Polynomial(lhs);
        }
    }

    friend Polynomial operator, (const Polynomial& lhs, const Polynomial& rhs) {
        if (rhs.degree == 0 || lhs.degree == 0) {
            return T(1);
        }
        if (rhs.degree == -1) {
            return lhs;
        }
        if (lhs.degree == -1) {
            return rhs;
        }
        Polynomial copy_lhs(lhs);
        Polynomial copy_rhs(rhs);
        while (copy_rhs.degree >= 0) {
            Polynomial r = copy_lhs % copy_rhs;
            copy_lhs = copy_rhs;
            copy_rhs = r;
        }

        return (copy_lhs / Polynomial(copy_lhs.data[copy_lhs.data.size() - 1]));
       return Polynomial(1);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& p) {
    if (p.Degree() == 0) {
        std::cout << p[0];
    } else if (p.Degree() == -1) {
        out << T(0);
    } else if (p.Degree() == 1) {
        if (p[1] != T(0)) {
            if (p[1] == T(1)) {
                out << "x";
            } else if (p[1] == T(-1)) {
                out << "-x";
            } else if (p[1] > T(0)) {
                out  << p[1] << "*" << "x";
            } else if (p[1] < T(0)) {
                out << p[1] << "*" << "x";
            }
        }

        if (p[0] != T(0)) {
            if (p[0] < T(0)) {
                out << p[0];
            } else {
                out << "+" << p[0];
            }
        }
    } else {
        if (p[p.Degree()] == T(-1)) {
            out << "-" << "x^" << p.Degree();
        } else if (p[p.Degree()] == T(1)) {
            out << "x^" << p.Degree();
        } else {
            out << p[p.Degree()] << "*" << "x^" << p.Degree();
        }
        for (int i = p.Degree() - 1; i > 1; --i) {
            if (p[i] == T(0)) {
                continue;
            } else if (p[i] == T(1)) {
                out << "+";
            } else if (p[i] == T(-1)) {
                out << "-";
            } else if (p[i] > T(0)) {
                out << "+" << p[i] << "*";
            } else if (p[i] < T(0)) {
                out << p[i] << "*";
            }
            out << "x^" << i;
        }
        if (p[1] != T(0)) {
            if (p[1] == T(1)) {
                out << "+";
            } else if (p[1] == T(-1)) {
                out << "-";
            } else if (p[1] > T(0)) {
                out << "+" << p[1] << "*";
            } else if (p[1] < T(0)) {
                out << p[1] << "*";
            }
            out << "x";
        }

        if (p[0] != T(0)) {
            if (p[0] < T(0)) {
                out << p[0];
            } else {
                out << "+" << p[0];
            }
        }
    }

    return out;
}
