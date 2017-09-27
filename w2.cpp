#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef uint64_t U;
typedef vector<U> V;


class BigInt {
public:
    BigInt() = default;
    ~BigInt() = default;
    friend istream &operator>>(istream &stream, BigInt &num);
    friend ostream &operator<<(ostream &stream, BigInt const &num);
    BigInt operator*(BigInt const &other);
private:
    static const size_t DIGITS_PER_SEGMENT = 9;
    static const U BASE = static_cast<U>(pow(10, DIGITS_PER_SEGMENT));
    static V conv(V const &v1, V const &v2);
    void carry();   // in-place
    V data;         // store as little-endian
};

int main() {
    int N;
    BigInt a, b;
    cin >> N;
    while (N-- > 0) {
        cin >> a >> b;
        cout << a * b << endl;
    }
    return 0;
}

istream &operator>>(istream &stream, BigInt &num)
{
    num.data.clear();
    string s;
    stream >> s;
    reverse(s.begin(), s.end());
    for (size_t i = 0; i < s.size(); i += BigInt::DIGITS_PER_SEGMENT) {
        string ss = s.substr(i, BigInt::DIGITS_PER_SEGMENT);
        reverse(ss.begin(), ss.end());
        num.data.push_back(stoull(ss));
    }
    return stream;
}

ostream &operator<<(ostream &stream, BigInt const &num)
{
    for (auto iter = num.data.rbegin(); iter != num.data.rend(); ++iter) {
        if (iter == num.data.rbegin()) {
            stream << *iter;
        } else {
            stream << setfill('0') << setw(BigInt::DIGITS_PER_SEGMENT) << *iter;
        }
    }
    return stream;
}

BigInt BigInt::operator*(BigInt const &other) {
    BigInt prod;
    prod.data = conv(data, other.data);
    prod.carry();
    return prod;
}

V BigInt::conv(V const &v1, V const &v2) {
    V result = V(v1.size() + v2.size() - 1, 0);
    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v2.size(); ++j) {
            result[i + j] += v1[i] * v2[j];
        }
    }
    return result;
}

void BigInt::carry() {
    for (size_t i = 0; i < data.size(); ++i) {
        U q = data[i] / BASE, m = data[i] % BASE;
        data[i] = m;
        if (i < data.size() - 1) {
            data[i + 1] += q;
        } else if (q > 0) {
            data.push_back(q);
        }
    }
}
