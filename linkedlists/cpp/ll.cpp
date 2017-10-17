#include <iostream>
#include <string> // string functions erase, etc...
#include <cctype> // ispunct, isdigit

using namespace std;

string remove_non_letters (string s);
string remove_non_letters (string s) {
    int current = 0;
    int len = s.length();
    while (current < len) {
        if (ispunct(s[current]) || isdigit(s[current]) || s[current] == ' ') {
            s.erase(current, 1);
            len--;
        }
        else current++;
    }
  return s;
}

class LinkedList {
private:
    struct Node {
        string val;
        Node * next;
    };
    Node * head;
public:
    LinkedList()
    : head(NULL) { }
    ~LinkedList() {
        while (head != NULL) {
            Node * p = head;
            head = head->next;
            delete p;
        }
    }

    int size() {
        int counter = 0;
        Node * p = head;
        while (p != NULL) {
            counter++;
            p = p->next;
        }
        delete p;
        return counter;
    }

    void add(string s) {
        int flag = 0;
        Node * p = new Node;
        p->val = s;
        p->next = NULL;
        if (head == NULL) {
          head = p;
        }
        else {
            for (Node * current = head; current != NULL; current = current->next) {
                if (p->val == current->val) flag++;
            }
            if (flag == 0) {
                p->next = head;
                head = p;
            }
            else if (flag > 0) delete p;
        }
    }

    void print() {
      int num = 1;
      Node * p = head;
      while (p != NULL) {
        cout << num;
        cout << ". ";
        cout << p->val;
        cout << "\n";
        p = p->next;
        num++;
      }
    }
};
