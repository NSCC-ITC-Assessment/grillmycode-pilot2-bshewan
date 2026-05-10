## Grill My Code

> **Generated:** 2026-05-10 14:52:21 UTC
> **Commits reviewed:** `4334237` → `cef8fab`

> **Files assessed:** `src/LinkedList.cpp`, `src/LinkedList.h`, `src/main.cpp`

---

**`src/LinkedList.cpp`**
```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```
1. What is the purpose of `head = nullptr;` in the constructor?

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
2. What does the `while` loop in the destructor accomplish?

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
3. Where in the list does `addBug` insert the new node?

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
    } else {
        prev->next = current->next;
    }
    delete current;
}
```
4. What does the condition `current != nullptr && current->data.id != bugId` in the `while` loop ensure?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::deleteBug(int bugId) {
    // ...
    if (current == nullptr) {
        return;
    }
    // ...
}
```
5. What happens when `current == nullptr` after the search loop in `deleteBug`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::deleteBug(int bugId) {
    // ...
    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    delete current;
}
```
6. Why is the `prev` pointer needed in `deleteBug`?

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
7. What does `searchBug` return when a bug with the given `bugId` is found?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::display() const {
    BugNode* current = head;
    while (current != nullptr) {
        // ... prints fields ...
        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
        std::cout << "-------------------------" << std::endl;
        current = current->next;
    }
}
```
8. How does `display` decide how many comments to print for each bug?

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
    } while (swapped);
}
```
9. What sorting algorithm does `sortById` implement?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::sortByStatus() {
    // ...
    while (current->next != nullptr) {
        if (current->data.status > current->next->data.status) {
            Bug temp = current->data;
            current->data = current->next->data;
            current->next->data = temp;
            swapped = true;
        }
        current = current->next;
    }
}
```
10. How are two bugs compared in `sortByStatus` to determine if they need to be swapped?

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
        getline(ss, token, '|');
        bug.id = stoi(token);
        // ...
    }
}
```
11. What delimiter is used by `getline(ss, token, '|')` to extract the bug ID from a line?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    bug.commentCount = 0;
    while (getline(ss, comment, '|')) {
        if (comment.empty()) break;
        if (bug.commentCount < 10) {
            bug.comments[bug.commentCount++] = comment;
        }
    }
    addBug(bug);
}
```
12. What is the purpose of setting `bug.commentCount = 0;` before reading comments in `loadFromFile`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    while (getline(ss, comment, '|')) {
        if (comment.empty()) break;
        // ...
    }
}
```
13. How does the comment-reading loop in `loadFromFile` know when to stop reading comments for a bug?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    // ...
    for (int i = 0; i < current->data.commentCount; i++) {
        file << current->data.comments[i] << "|";
    }
    file << "||\n";
}
```
14. What does the line `file << "||\n";` write to the output file?

---

**`src/main.cpp`**
```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};
```
15. What is the value of `commentCount` for `b1` immediately after its initialization in `main.cpp`?

---

**`src/main.cpp`**
```cpp
list.addBug(b1);
list.addBug(b2);
// ...
list.display();
```
16. What potential problem could occur when `display()` is called after adding `b1` (and the other bugs) due to the way `b1` is initialized?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::deleteBug(int bugId) {
    // ...
    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    delete current;
}
```
17. What happens to the `head` pointer when the node to be deleted is the first node in the list?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::addBug(const Bug& bug) {
    BugNode* node = new BugNode;
    node->data = bug;
    node->next = nullptr;
    // ...
}
```
18. What is the initial value of `node->next` after a new `BugNode` is created in `addBug`?

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
19. Why is it necessary to save `current->next` into `next` before calling `delete current`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::sortById() {
    if (!head) return;
    // ...
}
```
20. What does the early return `if (!head) return;` in `sortById` guard against?

---

**`src/LinkedList.cpp`**
```cpp
Bug* LinkedList::searchBug(int bugId) {
    // ...
    return &current->data;
}
```
21. What is the lifetime of the `Bug` object whose address is returned by `searchBug`?

---

**`src/LinkedList.h`**
```cpp
struct BugNode {
    Bug data;
    BugNode* next;
};
```
22. Why is `next` declared as a pointer (`BugNode*`) rather than a plain `BugNode` object?

---

**`src/LinkedList.h`**
```cpp
struct Bug {
    // ...
    std::string comments[10];
    int commentCount;
};
```
23. What does the field `commentCount` represent in the `Bug` struct?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File not found.\n";
        return;
    }
    // ...
}
```
24. What condition is checked by `if (!file)` in `loadFromFile`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    bug.id = stoi(token);
    // ...
}
```
25. What does `stoi(token)` do in `loadFromFile`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    // ...
}
```
26. Why is `saveToFile` declared with the `const` qualifier at the end of its signature?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::display() const {
    // ...
    std::cout << "-------------------------" << std::endl;
    // ...
}
```
27. What is the purpose of printing `"-------------------------"` in `display`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::sortById() {
    // ...
    do {
        swapped = false;
        // ...
        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}
```
28. What is the role of the `swapped` flag in `sortById`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::deleteBug(int bugId) {
    // ...
    if (current == nullptr) {
        return;
    }
    // ...
}
```
29. What does `deleteBug` do if the list is empty when it is called?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::addBug(const Bug& bug) {
    // ...
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = node;
}
```
30. What is the time complexity of adding a bug to the end of the list using this implementation of `addBug`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    while (getline(ss, comment, '|')) {
        if (comment.empty()) break;
        if (bug.commentCount < 10) {
            bug.comments[bug.commentCount++] = comment;
        }
    }
}
```
31. What is the maximum number of comments that can be stored for a single bug when reading from a file?

---

**`src/main.cpp`**
```cpp
list.loadFromFile("../docs/bugFile.txt");
// ...
list.saveToFile("../output/bugFile.txt");
```
32. Why does the program use different directory paths for the input and output files?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::sortByStatus() {
    // ...
    if (current->data.status > current->next->data.status) {
        Bug temp = current->data;
        current->data = current->next->data;
        current->next->data = temp;
        swapped = true;
    }
}
```
33. When `sortByStatus` swaps two bugs, does it change the linked list’s node connections or only the data inside the nodes?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::display() const {
    BugNode* current = head;
    while (current != nullptr) {
        // ...
        current = current->next;
    }
}
```
34. What does `current = current->next;` accomplish inside the `while` loop of `display`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::deleteBug(int bugId) {
    // ...
    delete current;
}
```
35. After `delete current;` executes, what happens to the memory that was allocated for that `BugNode`?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::addBug(const Bug& bug) {
    // ...
    if (head == nullptr) {
        head = node;
        return;
    }
    // ...
}
```
36. What does `addBug` do when the list is empty (i.e., `head == nullptr`)?

---

**`src/LinkedList.cpp`**
```cpp
LinkedList::~LinkedList() {
    // ...
    head = nullptr;
}
```
37. Why is `head = nullptr;` executed at the end of the destructor even though the `LinkedList` object is about to be destroyed?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::stringstream ss(line);
    // ...
}
```
38. What is the purpose of creating a `std::stringstream` object from `line` in `loadFromFile`?

---

**`src/LinkedList.cpp`**
```cpp
void

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · deepseek/deepseek-v4-pro via openrouter · main</sub>