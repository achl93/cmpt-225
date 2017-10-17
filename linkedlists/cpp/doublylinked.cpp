#include <string>
// #include "error.h"
#include <cctype>
#include <iostream>

using namespace std;

class Exam_database {
private:
    struct Node {
      string name;
      int score;
      Node * nextAlpha;
      Node * prevAlpha;
      Node * nextScore;
      Node * prevScore;
    };
    Node * headAlpha;
    Node * tailAlpha;
    Node * headScore;
    Node * tailScore;

public:
    Exam_database()
    : headAlpha(NULL), tailAlpha(NULL), headScore(NULL), tailScore(NULL) { }

    ~Exam_database() {
      while (headAlpha != NULL) {
        Node * tmp = headAlpha;
        headAlpha = headAlpha->nextAlpha;
        delete tmp;
      }
    }

    void add_exam(const string& n, int s) {
        string errMsg = "Empty name or score entered, please try again";
        int index = 0;
        // checks for blank/space for name input and throws an error
        if (isblank(n[index]) || isspace(n[index])) {
            // error::error(errMsg);
            return;
        }
        // case for adding to empty list
        if (headAlpha == NULL && tailAlpha == NULL && headScore == NULL && tailScore == NULL) {
          Node * newNode = new Node;
          newNode->name = n;
          newNode->score = s;
          newNode->nextAlpha = NULL;
          newNode->prevAlpha = NULL;
          newNode->nextScore = NULL;
          newNode->prevScore = NULL;
            headAlpha = newNode;
            tailAlpha = newNode;
            headScore = newNode;
            tailScore = newNode;
            return;
        }
        // case for when there is only a single node in the list
        else if (headAlpha->nextAlpha == NULL && headAlpha->prevAlpha == NULL && headScore->nextScore == NULL && headScore->prevScore == NULL) {
          Node * newNode = new Node;
          newNode->name = n;
          newNode->score = s;
          newNode->nextAlpha = NULL;
          newNode->prevAlpha = NULL;
          newNode->nextScore = NULL;
          newNode->prevScore = NULL;
          if (headAlpha->name > newNode->name) {
            headAlpha->prevAlpha = newNode;
            tailAlpha = headAlpha;
            headAlpha->nextAlpha = NULL;
            newNode->nextAlpha = headAlpha;
            headAlpha = newNode;
          }
          if (headAlpha->name < newNode->name) {
            headAlpha->nextAlpha = newNode;
            newNode->prevAlpha = headAlpha;
            newNode->nextAlpha = NULL;
            tailAlpha = newNode;
          }
          // exception for duplicate name
          if (headAlpha->name == newNode->name) {
            headAlpha->score = newNode->score;
            return;
          }
          if (headScore->score >= newNode->score) {
            headScore->nextScore = newNode;
            newNode->prevScore = headScore;
            newNode->nextScore = NULL;
            tailScore = newNode;
          }
          if (headScore->score < newNode->score) {
            headScore->prevScore = newNode;
            tailScore = headScore;
            headScore->nextScore = NULL;
            newNode->nextScore = headScore;
            headScore = newNode;
          }
          return;
        }
        // all other cases
        else {
            // for name list
            Node * newNode = new Node;
            newNode->name = n;
            newNode->score = s;
            newNode->nextAlpha = NULL;
            newNode->prevAlpha = NULL;
            newNode->nextScore = NULL;
            newNode->prevScore = NULL;
            Node * alphaCpy = headAlpha;
            // runs as long as the name is out of alphabetical order
            while (alphaCpy->name <= newNode->name && alphaCpy != NULL) {
                // exception for duplicate name
                if (alphaCpy->name == newNode->name) {
                    alphaCpy->score = newNode->score;
                    return;
                }
                // for cases where new node needs to be inserted in between two existing nodes
                else if (alphaCpy->nextAlpha != NULL && alphaCpy->name < newNode->name && newNode->name < alphaCpy->nextAlpha->name) {
                    newNode->nextAlpha = alphaCpy->nextAlpha;
                    newNode->prevAlpha = alphaCpy;
                    alphaCpy->nextAlpha->prevAlpha = newNode;
                    alphaCpy->nextAlpha = newNode;
                    break;
                }
                // for cases where the new node goes at the very end of the list
                else if (alphaCpy->name < newNode->name && alphaCpy->nextAlpha == NULL) {
                  newNode->nextAlpha = NULL;
                  newNode->prevAlpha = alphaCpy;
                  alphaCpy->nextAlpha = newNode;
                  tailAlpha = newNode;
                  break;
                }
                else alphaCpy = alphaCpy->nextAlpha;
            }
            // for cases where the new node goes at the very front of the list
            if (alphaCpy->name > newNode->name) {
              newNode->nextAlpha = alphaCpy;
              alphaCpy->prevAlpha = newNode;
              newNode->prevAlpha = NULL;
              headAlpha = newNode;
            }
            // for score list
            Node * scoreCpy = headScore;
            // runs as long as the new score is less than or equal to the current node score
            while (scoreCpy->score >= newNode->score && scoreCpy != NULL) {
                // for cases where new node needs to be inserted in between two existing nodes
                if (scoreCpy->nextScore != NULL && scoreCpy->score >= newNode->score && newNode->score >= scoreCpy->nextScore->score) {
                    newNode->nextScore = scoreCpy->nextScore;
                    newNode->prevScore = scoreCpy;
                    scoreCpy->nextScore->prevScore = newNode;
                    scoreCpy->nextScore = newNode;
                    break;
                }
                // for cases where the new node goes at the very end of the list
                else if (scoreCpy->score >= newNode->score && scoreCpy->nextScore == NULL) {
                    newNode->nextScore = NULL;
                    newNode->prevScore = scoreCpy;
                    scoreCpy->nextScore = newNode;
                    tailScore = newNode;
                    break;
                }
                else scoreCpy = scoreCpy->nextScore;
            }
            // for cases where the new node goes at the very front of the list
            if (scoreCpy->score < newNode->score) {
              newNode->nextScore = scoreCpy;
              newNode->prevScore = NULL;
              scoreCpy->prevScore = newNode;
              headScore = newNode;
            }
        }
        return;
    }

    void remove_exam(const string& n) {
        Node * tmp = headAlpha;
        // empty list
        if (tmp == NULL) {
          delete tmp;
          return;
        }
        while (tmp != NULL) {
            if (tmp->name != n) tmp = tmp->nextAlpha;
            else if (tmp->name == n && tmp->prevAlpha != NULL && tmp->nextAlpha != NULL) {
                tmp->prevAlpha->nextAlpha = tmp->nextAlpha;
                tmp->nextAlpha->prevAlpha = tmp->prevAlpha;
                delete tmp;
                return;
            }
            else if (tmp->name == n && tmp->prevAlpha == NULL && tmp->nextAlpha == NULL) {
              delete tmp;
              headAlpha = NULL;
              tailAlpha = NULL;
              headScore = NULL;
              tailScore = NULL;
              return;
            }
            else if (tmp->name == n && tmp->prevAlpha == NULL && tmp->nextAlpha != NULL) {
              headAlpha = tmp->nextAlpha;
              tmp->nextAlpha->prevAlpha = NULL;
              delete tmp;
              return;
            }
            else if (tmp->name == n && tmp->prevAlpha != NULL && tmp->nextAlpha == NULL) {
              tmp->prevAlpha->nextAlpha = NULL;
              delete tmp;
              return;
            }
        }
    }

    void print_by_name() const {
        Node * tmp = headAlpha;
        if (tmp == NULL) cout << "Empty list";
        while (tmp != NULL) {
            cout << tmp->name << ", " << tmp->score << "\n";
            tmp = tmp->nextAlpha;
        }
        delete tmp;
        return;
    }

    void print_by_name_rev() const {
        Node * tmp = tailAlpha;
        if (tmp == NULL) cout << "Empty list";
        while (tmp != NULL) {
            cout << tmp->name << ", " << tmp->score << "\n";
            tmp = tmp->prevAlpha;
        }
        delete tmp;
        return;
    }

    void print_by_score_ascending() const {
        Node * tmp = tailScore;
        if (tmp == NULL) cout << "Empty list";
        while (tmp != NULL) {
            cout << tmp->name << ", " << tmp->score << "\n";
            tmp = tmp->prevScore;
        }
        delete tmp;
        return;
    }

    void print_by_score_descending() const {
        Node * tmp = headScore;
        if (tmp == NULL) cout << "Empty list";
        while (tmp != NULL) {
            cout << tmp->name << ", " << tmp->score << "\n";
            tmp = tmp->nextScore;
        }
        delete tmp;
        return;
    }
};