#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

class BST {
private:
    struct Node {
        string value;
        Node * left;
        Node * right;
    };

    Node * head;
    class LLStack {
    public:
        struct LLNode {
            BST::Node * val;
            LLNode * next;
        };
        LLNode * head;
        LLNode * tail;
        LLStack()
        : head(NULL), tail(NULL) { }
        ~LLStack() {
            while (head != NULL) {
                LLNode * p = head;
                head = head->next;
                delete p;
            }
            assert(head == NULL && tail == NULL);
        }

        int LLsize() {
            int counter = 0;
            LLNode * p = head;
            while (p != NULL) {
                counter++;
                p = p->next;
            }
            delete p;
            return counter;
        }

        bool empty() {
            if (head == NULL && tail == NULL) return true;
            else return false;
        }

        void push(BST::Node * s) {
            LLNode * p = new LLNode;
            p->val = s;
            p->next = NULL;
            if (head == NULL && tail == NULL) {
              head = p;
              tail = p;
            }
            else if (head == tail) {
                p->next = head;
                head = p;
            }
            else {
                p->next = head;
                head = p;
            }
        }

        BST::Node * pop() {
            if (head == NULL && tail == NULL) return 0;
            if (head == tail) {
              LLNode * p = head;
              head = NULL;
              tail = NULL;
              BST::Node * tmp = p->val;
              delete p;
              return tmp;
            }
            if (head->next == tail) {
              LLNode * p = head;
              head = tail;
              BST::Node * tmp = p->val;
              delete p;
              return tmp;
            }
            else {
                LLNode * p = head;
                head = head->next;
                BST::Node * tmp = p->val;
                delete p;
                return tmp;
            }
        }
    };
public:
    BST()
    : head(NULL) {
    }

    ~BST() {
        traversedelete();
    }

    void traversedelete() {
        BST::LLStack * stack = new BST::LLStack;
        Node * root = head;
        while (root != NULL || !stack->empty()) {
            if (root != NULL) {
                if (root->right != NULL) stack->push(root->right);
                stack->push(root);
                root = root->left;
            }
            else {
                root = stack->head->val;
                delete stack->pop();
                if (!stack->empty() && root->right == stack->head->val && root->right != NULL) {
                    delete stack->pop();
                    stack->push(root);
                    root = root->right;
                }
                else {
                    root = NULL;
                }
            }
        }
        delete root;
        delete stack;
    }

    int size() const {
        Node * current;
        Node * prev;
        int count = 0;
        if (head == NULL) return 0;
        current = head;
        while (current != NULL) {
            if (current->left == NULL) {
                count++;
                current = current->right;
            }
            else {
                prev = current->left;
                while (prev->right != NULL && prev->right != current) prev = prev->right;
                if (prev->right == NULL) {
                    prev->right = current;
                    current = current->left;
                }
                else {
                    prev->right = NULL;
                    count++;
                    current = current->right;
                }
            }
        }
        return count;
    }

    int height() const {
        if (head == NULL || (head->left == NULL && head->right == NULL)) return 0;
        BST::LLStack * stack = new BST::LLStack;
        Node * root = head;
        stack->push(root);
        int height = 0;
        Node * prev = NULL;
        while (stack->empty() == false) {
            Node * current = stack->head->val;
            if (prev == NULL || prev->left == current || prev->right == current) {
                if (current->left != NULL) stack->push(current->left);
                else if (current->right != NULL) stack->push(current->right);
            }
            else if (current->left == prev) {
                if (current->right != NULL) stack->push(current->right);
            }
            else stack->pop();
            prev = current;
            if (stack->LLsize() > height) height = stack->LLsize()-1;
        }
        delete stack;
        return height;
    }

    bool contains(const string& s) const {
        Node * temp = head;
        while (temp != NULL) {
            if (temp->value == s) return true;
            if (s > temp->value) temp = temp->right;
            else if (s < temp->value) temp = temp->left;
        }
        return false;
    }

    void insert(const string& s) {
        Node * tmpNode = new Node;
        tmpNode->value = s;
        tmpNode->left = NULL;
        tmpNode->right = NULL;
        if (head == NULL) {
            head = tmpNode;
            return;
        }
        Node * root = head;
        Node * current = head;
        if (tmpNode->value < current->value) current = current->left;
        else current = current->right;
        while (current != NULL) {
            root = current;
            if (tmpNode->value < current->value) current = current->left;
            else current = current->right;
        }
        if (tmpNode->value < root->value) root->left = tmpNode;
        if (tmpNode->value > root->value) root->right = tmpNode;
    }

    void remove(const string& s) {
        Node * ptr;
        Node * ptrPrev;
        if (head == NULL) {
            return;
        }
        else {
            ptr = head;
            while (ptr != NULL) {
                if (ptr->value > s) {
                    ptrPrev = ptr;
                    ptr = ptr->left;
                }
                if (ptr->value < s) {
                    ptrPrev = ptr;
                    ptr = ptr->right;
                }
                else if (ptr->value == s) {
                  if (ptr->right != NULL && ptr->left == NULL) {
                      if (ptr->right->right == NULL && ptr->right->left == NULL) {
                          head = ptr->right;
                          delete ptr;
                          return;
                      }
                    ptrPrev->right = ptr->right;
                    delete ptr;
                    return;
                  }
                  if (ptr->left != NULL && ptr->right == NULL) {
                      if (ptr->left->left == NULL && ptr->left->right == NULL) {
                          head = ptr->left;
                          delete ptr;
                          return;
                      }
                    ptrPrev->right = ptr->left;
                    delete ptr;
                    return;
                  }
                  if (ptr->left == NULL && ptr->right == NULL) {
                      if (ptrPrev->left == ptr) {
                          ptrPrev->left = NULL;
                          delete ptr;
                          return;
                      }
                      if (ptrPrev->right == ptr) {
                          ptrPrev->right = NULL;
                          delete ptr;
                          return;
                      }
                      else {
                          delete ptr;
                          head = NULL;
                          return;
                      }
                  }
                  if (ptr->left != NULL && ptr->right != NULL) {
                    ptr->value = findMin(ptr);
                    return;
                  }
                }
            }
        }
    }

    string findMin(Node * root) {
        Node * min = root;
        Node * prev;
        string tmp;
        while (true) {
            prev = min;
            min = min->right;
            if (min->left == NULL) {
                tmp = min->value;
                if (min->right == NULL) {
                    prev->right = NULL;
                    delete min;
                    return tmp;
                }
                else {
                    prev->right = min->right;
                    delete min;
                    return tmp;
                }
            }
            else {
                while (true) {
                    min = min->left;
                    if (min->left == NULL) {
                        tmp = min->value;
                        prev->left = NULL;
                        delete min;
                        return tmp;
                    }
                }
            }
        }
    }

    void print_preorder() const {
      BST::LLStack * stack = new BST::LLStack;
      Node * root = head;
      if (root == NULL) return;
      stack->push(root);
      while (!stack->empty()) {
        Node * tmp = stack->head->val;
        cout << tmp->value;
        stack->pop();
        if (tmp->right) stack->push(tmp->right);
        if (tmp->left) stack->push(tmp->left);
      }
      delete stack;
      return;
    }

    void print_inorder() const {
        BST::LLStack * stack = new BST::LLStack;
        Node * root = head;
        Node * current = root;
        bool fin = false;
        while (fin == false) {
            if (current != NULL) {
                stack->push(current);
                current = current->left;
            }
            else {
                if (!stack->empty()) {
                    current = stack->pop();
                    cout << current->value;
                    current = current->right;
                }
                else fin = true;
            }
        }
        delete stack;
        return;
    }

    void print_postorder() const {
        BST::LLStack * stack = new BST::LLStack;
        Node * root = head;
        while (root != NULL || !stack->empty()) {
            if (root != NULL) {
                if (root->right != NULL) stack->push(root->right);
                stack->push(root);
                root = root->left;
            }
            else {
                root = stack->head->val;
                stack->pop();
                if (!stack->empty() && root->right == stack->head->val && root->right != NULL) {
                    stack->pop();
                    stack->push(root);
                    root = root->right;
                }
                else {
                    cout << root->value;
                    root = NULL;
                }
            }
        }
        delete stack;
        return;
    }
};
