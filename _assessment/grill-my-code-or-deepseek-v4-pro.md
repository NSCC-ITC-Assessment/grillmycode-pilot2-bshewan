## Grill My Code

> **Generated:** 2026-05-11 11:27:14 UTC
> **Commits reviewed:** `4334237` → `ba1c843`

> **Files assessed:** `src/LinkedList.cpp`, `src/LinkedList.h`, `src/main.cpp`

---

**`src/LinkedList.h`**

```cpp
struct Bug {
    int id;
    std::string date;
    std::string briefDesc;
    std::string detailedDesc;
    std::string status;
    std::string severity;
    std::string comments[10];
    int commentCount;
};
```

1. In the `Bug` struct, why is `comments` declared as a fixed-size array of 10 `std::string` objects rather than a dynamically resizable container?

---

**`src/LinkedList.h`**

```cpp
struct BugNode {
    Bug data;
    BugNode* next;
};
```

2. What is the role of the `next` pointer within the `BugNode` struct, and how does it enable the linked list structure?

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

3. In the destructor, why is it necessary to save `current->next` into a local variable `next` before calling `delete current`?

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

4. In `addBug`, what is the significance of the condition `if (head == nullptr)`, and how does the subsequent `return` statement affect the flow of execution?

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

5. In `deleteBug`, what does the condition `prev == nullptr` indicate about the position of the node to be deleted within the list?

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

6. What does the `searchBug` function return when a bug with the specified `bugId` is not found, and how does the caller in `main.cpp` handle that return value?

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

7. In the `display` function, how does the loop `for (int i = 0; i < current->data.commentCount; i++)` know how many comments to print for each bug?

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

8. In the `sortById` function, what is the purpose of the `swapped` flag, and what condition causes the outer `do...while` loop to terminate?

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

9. When comparing `current->data.status > current->next->data.status` in `sortByStatus`, what property of `std::string` is being used to determine the sort order?

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

10. In `loadFromFile`, what is the role of `std::stringstream ss(line)` in processing each line read from the file?

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

11. Inside `loadFromFile`, what is the purpose of the condition `if (comment.empty()) break;` within the comment-reading loop, and how does it relate to the file format specification?

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
}
```

12. In `saveToFile`, why is the string `"||\n"` appended after writing all comments for a bug, and what does it represent according to the file format?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};
```

13. In the initialization of `b1` through `b5`, how is the single string `"Needs fix"` stored in the `Bug` struct given that `comments` is an array?

---

**`src/main.cpp`**

```cpp
list.loadFromFile("../docs/bugFile.txt");
list.addBug(b1);
list.addBug(b2);
list.addBug(b3);
list.addBug(b4);
list.addBug(b5);
```

14. What is the order of bugs in the linked list immediately after the five `addBug` calls, before any sorting is performed?

---

**`src/main.cpp`**

```cpp
list.sortById();
std::cout << "\nSorted by ID:\n";
list.display();
list.deleteBug(3);
std::cout << "\nAfter Deletion:\n";
list.display();
```

15. After `deleteBug(3)` is called, what does the subsequent `list.display()` output show regarding the bug with `id` 3?

---

**`src/main.cpp`**

```cpp
Bug* found = list.searchBug(2);
if (found) {
    std::cout << "\nFound Bug ID 2:\n";
    std::cout << found->briefDesc << std::endl;
}
```

16. If `searchBug(2)` were called after `deleteBug(2)` instead of `deleteBug(3)`, what would the value of `found` be and what would the program output?

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

17. In `addBug`, the parameter `bug` is passed by `const` reference. What is the benefit of this compared to passing by value for a struct containing multiple `std::string` members?

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
    // ...
}
```

18. In `deleteBug`, what happens if the function is called with a `bugId` that does not exist in the list, and how is this communicated to the caller?

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

19. In `sortById`, the swap operation exchanges the entire `Bug` data payload between nodes. What is the advantage of swapping data rather than rearranging node pointers?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    while (getline(file, line)) {
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
    // ...
}
```

20. In `loadFromFile`, what happens to comments beyond the 10th one for a single bug record, and why is this behavior present?

---

**`src/LinkedList.h`**

```cpp
struct Bug {
    int id;
    std::string date;
    std::string briefDesc;
    std::string detailedDesc;
    std::string status;
    std::string severity;
    std::string comments[10];
    int commentCount;
};
```

21. The `Bug` struct uses a C-style array for `comments`. How does the `commentCount` member relate to the valid elements within that array?

---

**`src/main.cpp`**

```cpp
list.sortByStatus();
std::cout << "\nSorted by Status:\n";
list.display();
```

22. After `sortByStatus()` is called, what determines the relative order of two bugs that have the same `status` string?

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
}
```

23. In `saveToFile`, if a bug has zero comments (`commentCount == 0`), what is the exact sequence of characters written to the file for that bug after the severity field?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
}
```

24. Why is it important to initialize `head` to `nullptr` in the `LinkedList` constructor, and what would happen if this initialization were omitted?

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

25. The `searchBug` function returns a raw pointer to a `Bug` stored inside a node. What risk does this pose if the node is later deleted from the list?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const {
    BugNode* current = head;
    while (current != nullptr) {
        // ... print fields ...
        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
        // ...
    }
}
```

26. In the `display` function, the `const` qualifier on the method declaration prevents modification of the list. What does this guarantee about the `head` pointer and the nodes during iteration?

---

**`src/main.cpp`**

```cpp
list.loadFromFile("../docs/bugFile.txt");
```

27. If the file `"../docs/bugFile.txt"` does not exist or cannot be opened, what is the observable behavior of the program based on the `loadFromFile` implementation?

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

28. In `loadFromFile`, after printing `"File not found.\n"` and returning, what is the state of the `LinkedList` object that called this function?

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

29. In `addBug`, memory for a new `BugNode` is allocated with `new`. Which part of the code is responsible for deallocating this memory, and under what circumstances is it called?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    // ...
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}
```

30. In `deleteBug`, after the node is deleted, what ensures that the linked list remains properly connected for the remaining nodes?

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

31. The `LinkedList` class manages a collection of dynamically allocated `BugNode` objects. Which special member functions, beyond the destructor, might need to be explicitly defined to prevent shallow copy issues, and why?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
```

32. In the aggregate initialization of `b1`, the string `"Needs fix"` is provided. How does this single string value populate the `comments` array and `commentCount` member?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;
    // ...
}
```

33. What is the purpose of the early return `if (!head) return;` in both `sortById` and `sortByStatus`, and what scenario does it guard against?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    // ...
    file.close();
}
```

34. In `saveToFile`, what happens to the contents of the output file if it already exists before this function is called?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    while (getline(file, line)) {
        // ...
        getline(ss, token, '|');
        bug.id = stoi(token);
        // ...
    }
}
```

35. In `loadFromFile`, the first token is converted to an integer using `stoi(token)`. What would happen if the first field of a line in the file contained non-numeric characters?

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
    // ...
}
```

36. In `deleteBug`, the loop condition uses `current->data.id != bugId`. If the list contains multiple bugs with the same `id`, which one will be deleted?

---

**`src/main.cpp`**

```cpp
list.addBug(b1);
list.addBug(b2);
list.addBug(b3);
list.addBug(b4);
list.addBug(b5);
```

37. The five bugs are added with hardcoded IDs 1 through 5. If the file loaded in `loadFromFile` already contained a bug with ID 3, how many bugs with ID 3 would exist in the list before `deleteBug(3)` is called?

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
    // ...
}
```

38. In `sortByStatus`, the comparison `current->data.status > current->next->data.status` uses lexicographical ordering. What would be the sorted order of the statuses `"WAITING"`, `"OPEN"`, `"IN PROGRESS"`, and `"CLOSED"`?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    // ...
    Bug bug;
    getline(ss, token, '|');
    bug.id = stoi(token);
    getline(ss, bug.date, '|');
    getline(ss, bug.briefDesc, '|');
    getline(ss, bug.detailedDesc, '|');
    getline(ss, bug.status, '|');
    getline(ss, bug.severity, '|');
    // ...
}
```

39. In `loadFromFile`, the code assumes exactly six pipe-delimited fields before the comments begin. How does this assumption align with the assignment's file format specification?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const {
    // ...
    std::cout << "Status: " << current->data.status << std::endl;
    std::cout << "Severity: " << current->data.severity << std::endl;
    // ...
}
```

40. In the `display` function, the `status` and `severity` fields are printed as raw strings. According to the assignment specification, what are the four possible values for each of these fields?

---

**`src/main.cpp`**

```cpp
list.saveToFile("../output/bugFile.txt");
```

41. The output file path is `"../output/bugFile.txt"`. What would happen if the `output` directory did not exist when the program attempts to save?

---

**`src/LinkedList.h`**

```cpp
struct Bug {
    int id;
    std::string date;
    std::string briefDesc;
    std::string detailedDesc;
    std::string status;
    std::string severity;
    std::string comments[10];
    int commentCount;
};
```

42. The `Bug` struct contains both `briefDesc` and `detailedDesc` as separate fields. How does the `display` function differentiate between these two when printing?

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

43. In `addBug`, the new node is always appended to the end of the list. How does the function locate the tail of the list to perform this insertion?

---

## Broader Questions

44. The assignment specifies that library data structures (e.g., `vector`) cannot be used. How does the custom `LinkedList` class fulfill this requirement for storing and managing the collection of bugs?

---

45. The assignment requires reading all bugs from a file into a linked list on application start and writing them back on application end. How do the `loadFromFile` and `saveToFile` functions work together to maintain data persistence between program runs?

---

46. The assignment requires displaying the list of bugs ordered by bug ID. How does the `sortById` function in `LinkedList.cpp` achieve this ordering, and what sorting algorithm does it implement?

---

47. The assignment requires deleting one bug based on its ID and re-displaying the list. How does the `deleteBug` function handle the three distinct cases of deleting the head node, a middle node, or a non-existent node?

---

48. The assignment requires searching for a bug based on its ID and displaying its details. How does the `searchBug` function traverse the linked list, and what information does `main.cpp` choose to display when a bug is found?

---

49. The assignment requires sorting bugs by status. How does the `sortByStatus` function differ from `sortById` in terms of the data member used for comparison, and why might the resulting order not match a severity-based priority?

---

50. The file format uses a pipe character as a delimiter and ends records with a double pipe. How does the `loadFromFile` function's use of `getline` with a delimiter and the empty-comment `break` condition correctly parse this format?

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · deepseek/deepseek-v4-pro via openrouter · main</sub>