#include "bigram_base.h"
#include <string>
#include <vector>
#include <iostream>

#define NOT_FOUND -9999                                                 // used for indicating key does not exist in map

class Bigram : public Bigram_base {
public:
    struct keyPair {
        Bigram_key key;
        int val;
    };
    vector<keyPair*> hashtable;
    Bigram()
    : hashtable(50, NULL) {}
    ~Bigram() {}
    int hash(const Bigram_key& key) const {
        string tmp = key.first + key.second;
        int i, sum;
        for (sum=0, i=0; i<tmp.length(); i++) {
            sum = (sum+tmp[i]);                                         // sums up the catenated strings by their ASCII val
        }
        return sum % capacity();                                        // sum mod mapsize as the basic hash function
    }
    void rehash() {
        vector<keyPair*> tmpVec (capacity()*2, NULL);                   // tmp vector to hold rehashed map
        hashtable.resize(capacity()*2, NULL);                           // resized so that hash() will work properly
        int tmp;
        int j=0;
        for (int i=0; i<capacity(); i++) {
            if (hashtable[i] != NULL) {
                tmp = hash(hashtable[i]->key);                          // generates new hash value for each pre-existing pair
                if (tmpVec[tmp] == NULL) tmpVec[tmp] = hashtable[i];    // moves keypairs over to their new positions
                else {
                    while (tmpVec[tmp] != NULL) {
                        j++;
                        tmp = (tmp+(j*j)) % tmpVec.capacity();
                        if (tmp > tmpVec.capacity()) {
                            tmp = tmp-tmpVec.capacity();
                        }
                    }
                    tmpVec[tmp] = hashtable[i];
                    j = 0;
                }
            }
        }
        hashtable = tmpVec;
        return;
    }

    virtual int size() const {
        int count = 0;
        for (int i=0; i<capacity(); i++) {
            if (hashtable[i] != NULL) count++;
        }
        return count;
    }

    virtual int capacity() const {
        return hashtable.capacity();
    }

    virtual bool contains(const Bigram_key& key) const {
        int x = hash(key);
        int i = 0;
        int complete = 0;
        while (x <= capacity()) {
            if (complete > capacity()) break;
            if (hashtable[x] != NULL) {
                if (hashtable[x]->key.first == key.first && hashtable[x]->key.second == key.second) return true;
                else { // quadratic probing
                    complete++;
                    i++;
                    x = (x+(i*i)) % capacity();
                    if (x > capacity()) {
                        x = x-capacity();
                    }
                }
            }
            else {
                complete++;
                i++;
                x = (x+(i*i)) % capacity();
                if (x > capacity()) {
                    x = x-capacity();
                }
            }
        }
        return false;
    }
    //    Returns the value associated with key.
    virtual int value_of(const Bigram_key& key) const {
        int x = hash(key);
        int i = 0;
        int complete = 0;
        while (x <= capacity()) {
            if (complete > capacity()) break;
            if (hashtable[x] != NULL) {
                if ((hashtable[x]->key.first == key.first) && (hashtable[x]->key.second == key.second)) return hashtable[x]->val;
                else { // quadratic probing
                    complete++;
                    i++;
                    x = (x+(i*i)) % capacity();
                    if (x > capacity()) {
                        x = x-capacity();
                    }
                }
            }
            else {
                complete++;
                i++;
                x = (x+(i*i)) % capacity();
                if (x > capacity()) {
                    x = x-capacity();
                }
            }
        }
        return NOT_FOUND; // value indicates no such key
    }
    //    contains(key) and value_of(key) == val
    virtual void put(const Bigram_key& key, int val) {
        if (load_factor() >= 0.5) {
            rehash();
        }
        int x = hash(key);
        int i = 0;
        keyPair * tmp = new keyPair;
        tmp->key = key;
        tmp->val = val;
        while (x <= capacity()) {
            if (hashtable[x] == NULL) {
                hashtable[x] = tmp;
                return;
            }
            else if (hashtable[x] != NULL) {    // quadratic probing
                i++;
                x = (x+(i*i)) % capacity();
                if (x > capacity()) {
                    x = x-capacity();
                }
            }
        }
        return;
    }
    //    !contains(key)
    virtual void remove(const Bigram_key& key) {
        int x = hash(key);
        int i = 0;
        int complete = 0;                       // counter for scanning map
        while (x <= capacity()) {
            if (complete > capacity()) break;   // breaks out of while loop to terminate function once every position in map has been scanned
            if (hashtable[x] == NULL) return;   // if the first position is NULL then key must not exist and will just end the function
            if (hashtable[x] != NULL) {
                if (hashtable[x]->key.first == key.first && hashtable[x]->key.second == key.second) {
                    hashtable[x] = NULL;        // overwrites the index w/key to be removed
                    break;
                }
                else {                          // quadratic probing
                    complete++;
                    i++;
                    x = (x+(i*i)) % capacity();
                    if (x > capacity()) {
                        x = x-capacity();
                    }
                }
            }
        }
        return;
    }

    virtual Bigram_key max() const {
        int currMax = 0;
        int j = 0;
        while (j <= capacity()) {               // finds first existing element to set as currMax
            if (hashtable[j] != NULL) {
              currMax = j;
              break;
            }
            else j++;
        }
        if (size() == 1) return hashtable[currMax]->key;
        for (int i=0; i<capacity(); i++) {
            if (hashtable[i] != NULL && hashtable[i]->val > hashtable[currMax]->val) {
                currMax = i;
            }
            else if (hashtable[i] != NULL && hashtable[i]->val == hashtable[currMax]->val) {
                if (hashtable[i]->key <= hashtable[currMax]->key) {
                    currMax = i;
                }
            }
        }
        return hashtable[currMax]->key;
    }

    virtual Bigram_key min() const {
        int currMin = 0;
        for (int j=0; j<capacity(); j++) {      // finds first existing element to set as currMin, just like max() but done with a forloop
            if (hashtable[j] != NULL) {
                currMin = j;
                break;
            }
        }
        if (size() == 1) return hashtable[currMin]->key;
        for (int i=0; i<capacity(); i++) {
            if (hashtable[i] != NULL && hashtable[i]->val < hashtable[currMin]->val) {
                currMin = i;
            }
            else if (hashtable[i] != NULL && hashtable[i]->val == hashtable[currMin]->val) {
                if (hashtable[i]->key <= hashtable[currMin]->key) {
                    currMin = i;
                }
            }
        }
        return hashtable[currMin]->key;
    }
};