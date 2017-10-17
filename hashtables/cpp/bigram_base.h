#include <string>

using namespace std;

struct Bigram_key {
    string first;
    string second;
};

// Defines a comparison operator for Bigram_key objects
bool operator<=(const Bigram_key& a, const Bigram_key& b) {
    if (a.first == b.first) {
        return a.second <= b.second;;
    } else {
        return a.first <= b.first;
    }
}

//
// Bigram_base is an abstract base class for a map that stores (key, value)
// pairs, where the key is a Bigram and its associated value is an int.
//
class Bigram_base {
public:
    virtual ~Bigram_base() { }

    virtual int size() const = 0;

    virtual int capacity() const = 0;

    double load_factor() const {
        if (capacity() == 0) {
            return 0;
        } else {
            return double(size()) / capacity();
        }
    }

    virtual bool contains(const Bigram_key& key) const = 0;

    virtual int value_of(const Bigram_key& key) const = 0;

    virtual void put(const Bigram_key& key, int val) = 0;

    virtual void remove(const Bigram_key& key) = 0;

    virtual Bigram_key max() const = 0;

    virtual Bigram_key min() const = 0;
};