## Grill My Code

> **Generated:** 2026-05-10 15:07:29 UTC
> **Commits reviewed:** `4334237` → `778e876`

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
1. What is the purpose of the `comments` array and the `commentCount` member inside the `Bug` struct?

---

**`src/LinkedList.h`**
```cpp
struct BugNode {
    Bug data;
    BugNode* next;
};
```
2. Why does `BugNode` contain a `Bug data` member and a `BugNode* next` pointer?

---

**`src/LinkedList.cpp`**
```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```
3. What is the effect of setting `head = nullptr` in the `LinkedList` constructor?

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
4. What is the purpose of the `while (current != nullptr)` loop in the `LinkedList` destructor?

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
    ...
}
```
5. In `addBug`, what condition determines that the newly created node becomes the head of the linked list?

---

**`src/LinkedList.cpp`**
```cpp
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = node;
```
6. What does the `while (current->next != nullptr)` loop in `addBug` accomplish?

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
7. In `deleteBug`, how does the function handle the case where the bug to be deleted is the first node (the head) of the list?

---

**`src/LinkedList.cpp`**
```cpp
    BugNode* prev = nullptr;
    ...
    if (prev == nullptr) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
```
8. What is the role of the `prev` pointer in the `deleteBug` function?

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
9. What does `searchBug` return when no bug with the given `bugId` exists in the list?

---

**`src/LinkedList.cpp`**
```cpp
        if (current->data.id == bugId) {
            return &current->data;
        }
```
10. What is the significance of returning `&current->data` from the `searchBug` function?

---

**`src/LinkedList.cpp`**
```cpp
        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
```
11. In the `display` method, what does the inner `for` loop accomplish?

---

**`src/LinkedList.cpp`**
```cpp
        std::cout << "-------------------------" << std::endl;
```
12. What is the purpose of printing the line `"-------------------------"` inside the `display` method?

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
13. What sorting algorithm is implemented in the `sortById` method?

---

**`src/LinkedList.cpp`**
```cpp
            if (current->data.id > current->next->data.id) {
                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
```
14. In `sortById`, what condition triggers a swap between the data of two adjacent nodes?

---

**`src/LinkedList.cpp`**
```cpp
            if (current->data.status > current->next->data.status) {
```
15. In `sortByStatus`, how does the comparison `current->data.status > current->next->data.status` determine the final order of the bugs?

---

**`src/LinkedList.cpp`**
```cpp
        std::stringstream ss(line);
```
16. In `loadFromFile`, what is the purpose of creating a `std::stringstream` object from the `line` string?

---

**`src/LinkedList.cpp`**
```cpp
        getline(ss, token, '|');
        bug.id = stoi(token);
```
17. How does `loadFromFile` extract the bug ID from the current line, and what role does `stoi` play?

---

**`src/LinkedList.cpp`**
```cpp
        while (getline(ss, comment, '|')) {
            if (comment.empty()) break;
            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
        }
```
18. What is the role of the `while (getline(ss, comment, '|'))` loop in `loadFromFile`?

---

**`src/LinkedList.cpp`**
```cpp
            if (comment.empty()) break;
```
19. In `loadFromFile`, what condition causes the comment‑reading loop to stop early?

---

**`src/LinkedList.cpp`**
```cpp
            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
```
20. Why is the check `bug.commentCount < 10` necessary before storing a comment in the `Bug` struct?

---

**`src/LinkedList.cpp`**
```cpp
        addBug(bug);
```
21. After parsing a complete bug from a line, what does the call `addBug(bug)` do in `loadFromFile`?

---

**`src/LinkedList.cpp`**
```cpp
        file << "||\n";
```
22. In `saveToFile`, what is the significance of writing the string `"||\n"` at the end of each bug record?

---

**`src/LinkedList.cpp`**
```cpp
        for (int i = 0; i < current->data.commentCount; i++) {
            file << current->data.comments[i] << "|";
        }
```
23. How does `saveToFile` write the comments of a bug to the output file?

---

**`src/main.cpp`**
```cpp
    list.loadFromFile("../docs/bugFile.txt");
```
24. What is the effect of calling `list.loadFromFile("../docs/bugFile.txt")` at the beginning of `main`?

---

**`src/main.cpp`**
```cpp
    Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
    Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
    Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
    Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
    Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};
```
25. How are the five `Bug` objects initialized in `main`, and what fields are provided in the brace‑initializer lists?

---

**`src/main.cpp`**
```cpp
    Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
```
26. After the initialization `Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};`, what will be the value of `b1.commentCount`?

---

**`src/main.cpp`**
```cpp
    list.addBug(b1);
    list.addBug(b2);
    list.addBug(b3);
    list.addBug(b4);
    list.addBug(b5);
```
27. After calling `addBug` for `b1` through `b5` in that order, what is the sequence of bugs in the linked list?

---

**`src/main.cpp`**
```cpp
    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();
```
28. What does `list.sortById()` accomplish before the first call to `display`?

---

**`src/main.cpp`**
```cpp
    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();
```
29. After executing `list.deleteBug(3)`, what happens to the bug with ID 3 in the linked list?

---

**`src/main.cpp`**
```cpp
    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();
```
30. After calling `list.sortByStatus()`, what determines the order in which the bugs are displayed?

---

**`src/main.cpp`**
```cpp
    Bug* found = list.searchBug(2);
```
31. What does `list.searchBug(2)` return if a bug with ID 2 exists in the list?

---

**`src/main.cpp`**
```cpp
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }
```
32. When `found` is not `nullptr`, what specific piece of information is printed by `std::cout << found->briefDesc`?

---

**`src/main.cpp`**
```cpp
    list.saveToFile("../output/bugFile.txt");
```
33. What is the purpose of calling `list.saveToFile("../output/bugFile.txt")` at the end of `main`?

---

**`src/LinkedList.h`**
```cpp
class LinkedList {
private:
    BugNode* head = nullptr;
public:
    ...
};
```
34. Why is the `BugNode* head` member declared as `private` inside the `LinkedList` class?

---

**`src/LinkedList.h`**
```cpp
    void display() const;
```
35. What does the `const` qualifier at the end of `void display() const` indicate about the method?

---

**`src/LinkedList.h`**
```cpp
    void loadFromFile(const std::string& filename);
```
36. What does the parameter type `const std::string& filename` in `loadFromFile` signify?

---

**`src/LinkedList.cpp`**
```cpp
    file.close();
```
37. In `loadFromFile`, what is the effect of calling `file.close()` after the reading loop?

---

**`src/LinkedList.cpp`**
```cpp
    head = nullptr;
```
38. In the destructor, why is `head` set to `nullptr` after all nodes have been deleted?

---

**`src/LinkedList.cpp`**
```cpp
    if (!head) return;
```
39. In `sortById`, what is the purpose of the early return `if (!head) return;`?

---

**`src/LinkedList.cpp`**
```cpp
    bool swapped;
    do {
        swapped = false;
        ...
    } while (swapped);
```
40. What is the role of the `swapped` flag in the `do‑while` loop of the sorting functions?

---

**`src/LinkedList.cpp`**
```cpp
            if (current->data.id > current->next->data.id) {
```
```cpp
            if (current->data.status > current->next->data.status) {
```
41. What is the key difference between the comparison used in `sortById` and the comparison used in `sortByStatus`?

---

**`src/LinkedList.cpp`**
```cpp
    while (getline(file, line)) {
        ...
    }
```
42. If `loadFromFile` is called on an empty file (zero lines), how many times does the body of the `while` loop execute?

---

**`src/LinkedList.cpp`**
```cpp
        bug.id = stoi(token);
```
43. What does `stoi(token)` do, and what could happen if `token` does not represent a valid integer?

---

**`src/LinkedList.cpp`**
```cpp
        file << "||\n";
```
44. How does the line `file << "||\n";` in `saveToFile` ensure that each bug record conforms to the required file format?

---

**`src/main.cpp`**
```cpp
    Bug b1 = {1, ...};
    Bug b2 = {2, ...};
    Bug b3 = {3, ...};
    Bug b4 = {4, ...};
    Bug b5 = {5, ...};
```
45. Why are the bug IDs in `main` hardcoded as 1, 2, 3, 4, and 5?

---

**`src/LinkedList.h`**
```cpp
    std::string  comments[10];
```
46. Based on the declaration `std::string comments[10]`, what is the maximum number of comments a single `Bug` object can store?

---

**`src/LinkedList.cpp`**
```cpp
#include <fstream>
#include <sstream>
```
47. Why does `LinkedList.cpp` include the `<fstream>` and `<sstream>` headers?

---

**`src/LinkedList.cpp`**
```cpp
    do {
        ...
    } while (swapped);
```
48. In the sorting functions, what is the significance of using a `do‑while` loop instead of a plain `while` loop?

---

**`src/LinkedList.cpp`**
```cpp
                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
```
49. What does the sequence of assignments using `Bug temp` accomplish during a swap in the sorting functions?

---

**`src/LinkedList.cpp`**
```cpp
    delete current;
```
50. In `deleteBug`, what is the effect of the statement `delete current;` after the node has been unlinked from the list?

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · deepseek/deepseek-v4-pro via openrouter · main</sub>