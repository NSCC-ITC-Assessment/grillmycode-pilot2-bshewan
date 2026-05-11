## Grill My Code

> **Generated:** 2026-05-11 17:53:12 UTC
> **Commits reviewed:** `4334237` → `ad6ba65`

> **Files assessed:** `src/LinkedList.cpp`, `src/LinkedList.h`, `src/main.cpp`

---

**`src/LinkedList.cpp`**
```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```
1. What is the purpose of initializing `head` to `nullptr` in the `LinkedList` constructor, and what would happen if this initialization were omitted?

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
2. In the destructor, why is the temporary pointer `next` used inside the `while` loop, and why is `head` set to `nullptr` after the loop completes?

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
3. Under what condition does `addBug` exit early without entering the `while` loop, and how does this affect the structure of the list?

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
4. In `addBug`, how does the traversal `while (current->next != nullptr)` guarantee that the new node becomes the last element, and what is the time complexity of this insertion?

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
5. What is the purpose of the condition `if (prev == nullptr)` inside `deleteBug`, and how does the function’s behavior differ when deleting the first node versus a later node?

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
6. When `deleteBug` reaches `if (current == nullptr)`, what does that condition indicate about the requested `bugId`, and what does the function do in response?

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
7. Why does `searchBug` return a pointer to `&current->data` instead of a copy of the `Bug` object, and what risk does this create for the caller if the node is later deleted?

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
8. How does the loop termination condition `while (current != nullptr)` ensure that the function returns `nullptr` when the `bugId` is not found, and what would happen if the loop accidentally overran the list?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::display() const {
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
9. In `display`, why does the inner `for` loop use `current->data.commentCount` as its bound instead of a constant like `10`, and what would happen if `commentCount` is not correctly updated?

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
10. What sorting algorithm does `sortById` implement, and why does it choose to swap the entire `Bug` data rather than rearranging the `BugNode` pointers?

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
11. In `sortById`, what condition causes the outer `do-while` loop to repeat, and what guarantees that the list is fully sorted when it terminates?

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
    } while (swapped);
}
```
12. Using `>` on `std::string` members like `status`, what ordering does `sortByStatus` produce for statuses such as `"OPEN"`, `"IN PROGRESS"`, `"WAITING"`, and `"CLOSED"`, and why might this not align with a meaningful priority order?

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
13. In `loadFromFile`, how does the line `while (getline(ss, comment, '|'))` together with `if (comment.empty()) break;` determine when to stop reading comments, and how does this relate to the final `"||\n"` written by `saveToFile`?

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
14. Why does the code reset `bug.commentCount = 0` before reading comments, and what would happen if a loaded bug record contained more than 10 comment fields?

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
15. In `loadFromFile`, what happens if the input file contains a line with a non‑numeric `id` field, and how does the call to `stoi` handle this situation?

---

**`src/LinkedList.cpp`**
```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    BugNode* current = head;

    while (current != nullptr) {
        file << current->data.id << "|"
             << current->data.date << "|"
             << current->data.b

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · deepseek/deepseek-v4-pro via openrouter · 18-assignment-context</sub>