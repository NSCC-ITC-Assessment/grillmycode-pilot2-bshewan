## Grill My Code

> **Generated:** 2026-05-11 11:36:11 UTC
> **Commits reviewed:** `4334237` → `8d59852`

> **Files assessed:** `src/LinkedList.cpp`, `src/LinkedList.h`, `src/main.cpp`

---

**`src/LinkedList.h`**

```cpp
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
```

1. Why does the `Bug` struct use a fixed-size array `comments[10]` instead of a dynamic container for storing comments, and how does this relate to the assignment restriction on library data structures?

---

**`src/LinkedList.h`**

```cpp
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
```

2. What is the purpose of the `commentCount` member variable in the `Bug` struct, and what would happen if it were not properly initialized before adding comments?

---

**`src/LinkedList.h`**

```cpp
struct BugNode {

    Bug data;
    BugNode* next;

};
```

3. In the `BugNode` struct, what does the `next` pointer represent in the context of the linked list data structure, and why is it necessary for implementing the list?

---

**`src/LinkedList.h`**

```cpp
class LinkedList {

private:
    BugNode* head = nullptr;

public:
    LinkedList();            
    ~LinkedList();           

    void addBug(const Bug& bug);     
    void deleteBug(int bugId);       
    Bug* searchBug(int bugId);       
    void display() const;            
    void sortById();                 
    void sortByStatus();             

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};
```

4. Why is the `head` pointer declared as `private` in the `LinkedList` class, and what would be the consequences of making it `public`?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```

5. What is the purpose of initializing `head` to `nullptr` in the constructor, and what could go wrong if this initialization were omitted?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::~LinkedList() {

    BugNode* current = head;

    while (current != nullptr) {
        BugNode* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}
```

6. In the destructor, why is a separate `BugNode* next` variable needed before deleting `current`, instead of simply writing `current = current->next; delete current;`?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::~LinkedList() {

    BugNode* current = head;

    while (current != nullptr) {
        BugNode* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}
```

7. What would happen if the destructor were never called when a `LinkedList` object goes out of scope, particularly in terms of memory management?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        return;
    }

    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}
```

8. Why does the `addBug` function use `const Bug& bug` as a parameter instead of `Bug bug`, and what advantage does this provide?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        return;
    }

    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}
```

9. In the `addBug` function, what is the purpose of the `if (head == nullptr)` check, and how does the code path differ when this condition is true versus false?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        return;
    }

    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}
```

10. What is the time complexity of the `addBug` function, and how would it differ if the linked list maintained a `tail` pointer in addition to `head`?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}
```

11. In the `deleteBug` function, what does the condition `current == nullptr` after the while loop indicate, and why does the function simply return in this case?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}
```

12. Why does the `deleteBug` function need to handle the case where `prev == nullptr` separately from the case where `prev` is not null?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}
```

13. What would happen if the `delete current;` statement were omitted from the `deleteBug` function, and what type of programming issue would this create?

---

**`src/LinkedList.cpp`**

```cpp
  Bug* LinkedList::searchBug(int bugId) {

    BugNode* current = head;

    while (current != nullptr) {
        if (current->data.id == bugId) {
            return &current->data;
        }
        current = current->next;
    }

    return nullptr;
}
```

14. Why does the `searchBug` function return a pointer to `Bug` (`Bug*`) rather than returning a `Bug` object directly, and what advantage does this provide?

---

**`src/LinkedList.cpp`**

```cpp
  Bug* LinkedList::searchBug(int bugId) {

    BugNode* current = head;

    while (current != nullptr) {
        if (current->data.id == bugId) {
            return &current->data;
        }
        current = current->next;
    }

    return nullptr;
}
```

15. What are the potential implications of returning `&current->data` from the `searchBug` function, particularly if the returned pointer is used after the linked list is modified or destroyed?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const{

    BugNode* current = head;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
        std::cout << "Date: " << current->data.date << std::endl;
        std::cout << "Brief: " << current->data.briefDesc << std::endl;
        std::cout << "Detail: " << current->data.detailedDesc << std::endl;
        std::cout << "Status: " << current->data.status << std::endl;
        std::cout << "Severity: " << current->data.severity << std::endl;

        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
        std::cout << "-------------------------" << std::endl;

        current = current->next;
    }

}
```

16. Why is the `display()` method declared with the `const` keyword, and what would happen if this method attempted to modify any member variables of the `LinkedList` class?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const{

    BugNode* current = head;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
        std::cout << "Date: " << current->data.date << std::endl;
        std::cout << "Brief: " << current->data.briefDesc << std::endl;
        std::cout << "Detail: " << current->data.detailedDesc << std::endl;
        std::cout << "Status: " << current->data.status << std::endl;
        std::cout << "Severity: " << current->data.severity << std::endl;

        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
        std::cout << "-------------------------" << std::endl;

        current = current->next;
    }

}
```

17. How does the `display()` function handle bugs that have zero comments, and what role does `commentCount` play in determining what is printed?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {

                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }
            current = current->next;
        }
    }while (swapped);
}
```

18. What sorting algorithm is implemented in the `sortById()` function, and how does the `swapped` variable contribute to determining when the sort is complete?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {

                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }
            current = current->next;
        }
    }while (swapped);
}
```

19. Why does the `sortById()` function swap the `data` member of nodes rather than rearranging the `next` pointers to reorder the nodes themselves?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {

                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }
            current = current->next;
        }
    }while (swapped);
}
```

20. What is the purpose of the condition `if (!head) return;` at the beginning of the `sortById()` function, and what would happen if this check were omitted?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortByStatus() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.status > current->next->data.status) {

                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }
            current = current->next;
        }
    }while (swapped);
}
```

21. Given that the `status` field is a `std::string`, how does the `sortByStatus()` function determine the ordering of statuses, and what would the alphabetical sorting order be for the values "OPEN", "CLOSED", "IN PROGRESS", and "WAITING"?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }

    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string comment;

        Bug bug;
        getline(ss, token, '|');
        bug.id = stoi(token);

        getline(ss, bug.date, '|');
        getline(ss, bug.briefDesc, '|');
        getline(ss, bug.detailedDesc, '|');
        getline(ss, bug.status, '|');
        getline(ss, bug.severity, '|');

       bug.commentCount = 0;

        while (getline(ss, comment, '|')) {
            if (comment.empty()) break;

            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
        }

        addBug(bug);
    }
    file.close();
}
```

22. In the `loadFromFile` function, how does the code handle the double pipe `||` delimiter that marks the end of each bug record according to the file format specification?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }

    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string comment;

        Bug bug;
        getline(ss, token, '|');
        bug.id = stoi(token);

        getline(ss, bug.date, '|');
        getline(ss, bug.briefDesc, '|');
        getline(ss, bug.detailedDesc, '|');
        getline(ss, bug.status, '|');
        getline(ss, bug.severity, '|');

       bug.commentCount = 0;

        while (getline(ss, comment, '|')) {
            if (comment.empty()) break;

            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
        }

        addBug(bug);
    }
    file.close();
}
```

23. Why is `bug.commentCount` explicitly set to `0` before parsing comments, and what could go wrong if this initialization were omitted?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }

    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string comment;

        Bug bug;
        getline(ss, token, '|');
        bug.id = stoi(token);

        getline(ss, bug.date, '|');
        getline(ss, bug.briefDesc, '|');
        getline(ss, bug.detailedDesc, '|');
        getline(ss, bug.status, '|');
        getline(ss, bug.severity, '|');

       bug.commentCount = 0;

        while (getline(ss, comment, '|')) {
            if (comment.empty()) break;

            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
        }

        addBug(bug);
    }
    file.close();
}
```

24. What is the purpose of the condition `if (bug.commentCount < 10)` in the comment parsing loop, and how does this relate to the `Bug` struct definition?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }

    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string comment;

        Bug bug;
        getline(ss, token, '|');
        bug.id = stoi(token);

        getline(ss, bug.date, '|');
        getline(ss, bug.briefDesc, '|');
        getline(ss, bug.detailedDesc, '|');
        getline(ss, bug.status, '|');
        getline(ss, bug.severity, '|');

       bug.commentCount = 0;

        while (getline(ss, comment, '|')) {
            if (comment.empty()) break;

            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
        }

        addBug(bug);
    }
    file.close();
}
```

25. Why does the `loadFromFile` function use `stoi(token)` to convert the bug ID from a string to an integer, and what would happen if the file contained a non-numeric value in the ID field?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    BugNode* current = head;

    while (current != nullptr) {
        file << current->data.id << "|"
             << current->data.date << "|"
             << current->data.briefDesc << "|"
             << current->data.detailedDesc << "|"
             << current->data.status << "|"
             << current->data.severity << "|";

        for (int i = 0; i < current->data.commentCount; i++) {
            file << current->data.comments[i] << "|";
        }
        file << "||\n";
        current = current->next;
    }

    file.close();
};
```

26. How does the `saveToFile` function ensure that the output file format matches the specification's requirement of ending each record with a double pipe `||`?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    BugNode* current = head;

    while (current != nullptr) {
        file << current->data.id << "|"
             << current->data.date << "|"
             << current->data.briefDesc << "|"
             << current->data.detailedDesc << "|"
             << current->data.status << "|"
             << current->data.severity << "|";

        for (int i = 0; i < current->data.commentCount; i++) {
            file << current->data.comments[i] << "|";
        }
        file << "||\n";
        current = current->next;
    }

    file.close();
};
```

27. Why is `saveToFile` declared as a `const` method, and what does this indicate about how the method interacts with the `LinkedList` object?

---

**`src/main.cpp`**

```cpp
int main() {
    LinkedList list;

    list.loadFromFile("../docs/bugFile.txt");

    Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
    Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
    Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
    Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
    Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};

    list.addBug(b1);
    list.addBug(b2);
    list.addBug(b3);
    list.addBug(b4);
    list.addBug(b5);

    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();

    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();

    Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }

    list.saveToFile("../output/bugFile.txt");

    return 0;
}
```

28. In `main()`, what is the order of operations, and why is `loadFromFile` called before adding the five new bugs?

---

**`src/main.cpp`**

```cpp
    Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
    Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
    Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
    Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
    Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};
```

29. How does the aggregate initialization syntax used for `b1` through `b5` initialize the `comments` array and `commentCount` members of the `Bug` struct?

---

**`src/main.cpp`**

```cpp
    Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
    Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
    Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
    Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
    Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};
```

30. When using aggregate initialization for `b1`, the value "Needs fix" is provided as the seventh field. Given the `Bug` struct definition, which member does this value initialize?

---

**`src/main.cpp`**

```cpp
    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();
```

31. What will happen if `deleteBug(3)` is called but there is no bug with ID 3 in the list, and how does the `deleteBug` function handle this case?

---

**`src/main.cpp`**

```cpp
    Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }
```

32. Why is it necessary to check `if (found)` before accessing `found->briefDesc`, and what would happen if this check were omitted and the bug was not found?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }
    // ... rest of function
}
```

33. What happens in the `loadFromFile` function if the specified file does not exist, and how does this behavior align with graceful error handling?

---

**`src/LinkedList.h`**

```cpp
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
```

34. According to the assignment specification, the bug ID should be in the format "BUG0001". How does the implementation's use of `int id` differ from this specification, and what are the implications for file I/O?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                // swap logic
            }
            current = current->next;
        }
    }while (swapped);
}
```

35. What is the time complexity of the sorting algorithm used in `sortById()`, and why might this be acceptable or concerning depending on the expected number of bugs?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    if (head == nullptr) {
        head = node;
        return;
    }

    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}
```

36. What does the assignment statement `node->data = bug;` accomplish in terms of copying data, and how does the `Bug` struct's composition affect this operation?

---

**`src/LinkedList.h`**

```cpp
#ifndef SUPPLEMENTAL_LINKEDLIST_H
#define SUPPLEMENTAL_LINKEDLIST_H
```

37. What is the purpose of the `#ifndef`, `#define`, and `#endif` preprocessor directives in the header file, and what problem would occur if these were omitted?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    BugNode* current = head;

    while (current != nullptr) {
        file << current->data.id << "|"
             << current->data.date << "|"
             << current->data.briefDesc << "|"
             << current->data.detailedDesc << "|"
             << current->data.status << "|"
             << current->data.severity << "|";

        for (int i = 0; i < current->data.commentCount; i++) {
            file << current->data.comments[i] << "|";
        }
        file << "||\n";
        current = current->next;
    }

    file.close();
};
```

38. How does the `saveToFile` function handle bugs that have zero comments, and what will the output look like for such bugs in terms of the pipe delimiters?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ... setup code ...
    while (getline(file, line)) {
        // ... parsing code ...
        addBug(bug);
    }
    file.close();
}
```

39. Why does the `loadFromFile` function call `addBug(bug)` for each parsed bug instead of directly manipulating the linked list nodes within the function?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return;
    }

    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}
```

40. In the `deleteBug` function, what would happen if the while loop condition were changed from `current->data.id != bugId` to `current->data.id == bugId`, and how would this affect the deletion logic?

---

**`src/main.cpp`**

```cpp
    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();

    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();
```

41. According to the assignment requirements, the list should be displayed after sorting by ID, after deletion, and after sorting by status. How does the order of operations in `main()` fulfill these requirements?

---

**`src/LinkedList.h`**

```cpp
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
```

42. Why does `loadFromFile` not have the `const` qualifier while `saveToFile` does, and what does this indicate about how each method interacts with the object's state?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const{

    BugNode* current = head;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
        // ... other fields ...
        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
        std::cout << "-------------------------" << std::endl;

        current = current->next;
    }
}
```

43. How does the `display()` function's output format compare to the file format specification, and what information is included or excluded in the console output versus the file output?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortByStatus() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.status > current->next->data.status) {

                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }
            current = current->next;
        }
    }while (swapped);
}
```

44. When sorting by status using string comparison, what would be the resulting order of bugs with statuses "OPEN", "CLOSED", "IN PROGRESS", and "WAITING" when sorted alphabetically?

---

**`src/LinkedList.h`**

```cpp
struct Bug {

    int id;
    std::string date;
    std::string  briefDesc;
    std::string  detailedDesc;
    std::string  status;
    std::string  severity;
    std::string

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · z-ai/glm-5 via openrouter · main</sub>