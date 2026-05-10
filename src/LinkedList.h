//
// Created by emill on 4/24/2026.
//

#ifndef SUPPLEMENTAL_LINKEDLIST_H
#define SUPPLEMENTAL_LINKEDLIST_H
#include <string>

struct Bug {

    int id;
    std::string date;
    std::string  briefDesc;
    std::string  detailedDesc;
    std::string  status;
    std::string  severity;
    std::string  comments[10];
    int commentCount;
};
struct BugNode {

    Bug data;
    BugNode* next;

};

class LinkedList {

private:
    BugNode* head = nullptr;

public:
    LinkedList();            // constructor
    ~LinkedList();           // destructor

    void addBug(const Bug& bug);     // add bug
    void deleteBug(int bugId);       // remove per ID
    Bug* searchBug(int bugId);       // search per ID
    void display() const;            // show all
    void sortById();                 // order by id
    void sortByStatus();             // order by status

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};


#endif //SUPPLEMENTAL_LINKEDLIST_H