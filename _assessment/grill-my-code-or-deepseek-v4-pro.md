## Grill My Code

> **Generated:** 2026-05-10 15:14:18 UTC
> **Commits reviewed:** `4334237` → `7400319`

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

1. In the `Bug` struct, why is `comments` declared as a fixed-size array of 10 `std::string` elements rather than using a dynamic container?

---

**`src/LinkedList.h`**

```cpp
struct BugNode {
    Bug data;
    BugNode* next;
};
```

2. What role does the `next` pointer play in the `BugNode` struct, and how does it enable the linked list structure required by the assignment?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```

3. What is the purpose of setting `head = nullptr` in the `LinkedList` constructor, and what would happen if this initialization were omitted?

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

4. In the `LinkedList` destructor, why is the temporary pointer `next` necessary during the `while` loop that deletes each `BugNode`?

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

5. In `addBug`, when `head` is not `nullptr`, the code traverses to the end of the list before inserting. How does the loop condition `current->next != nullptr` ensure that the new node is appended rather than prepended?

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

6. In `deleteBug`, what is the significance of the `prev` pointer, and how does the code handle the case where the node to be deleted is the first node in the list?

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

7. The `searchBug` function returns a pointer to a `Bug` (`&current->data`). What are the implications of returning the address of a member of a heap-allocated `BugNode` in terms of the pointer's lifetime?

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

8. In the `display` function, the `for` loop uses `current->data.commentCount` as its bound. How does the `loadFromFile` function ensure that `commentCount` accurately reflects the number of comments stored in the `comments` array?

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

9. The `sortById` function swaps the entire `Bug` data payload between nodes rather than rearranging node pointers. What is one advantage and one potential disadvantage of this approach when sorting a linked list of large data structures?

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

10. The `sortByStatus` function uses the `>` operator to compare `current->data.status` with `current->next->data.status`. How does the behavior of `std::string`’s `operator>` determine the resulting sort order for bug statuses like `"OPEN"`, `"CLOSED"`, `"IN PROGRESS"`, and `"WAITING"`?

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

11. In `loadFromFile`, the inner `while` loop breaks when `comment.empty()` is true. How does this condition relate to the double-pipe `||` record terminator specified in the bug file format?

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

12. In `saveToFile`, the code writes `"||\n"` after the comment loop. How does this output satisfy the record format requirement that each record ends with a double pipe symbol?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
Bug b3 = {3, "2026-04-26", "UI issue", "Button broken", "WAITING", "LOW", "Minor"};
Bug b4 = {4, "2026-04-27", "Slow app", "Performance lag", "OPEN", "MEDIUM", "Investigating"};
Bug b5 = {5, "2026-04-28", "Security", "Vulnerability", "CLOSED", "CRITICAL", "Fixed"};
```

13. In `main.cpp`, the `Bug` objects `b1` through `b5` are initialized using aggregate initialization with only seven arguments, but the `Bug` struct contains eight fields (including `commentCount`). What value will `commentCount` have for these objects, and why?

---

**`src/main.cpp`**

```cpp
list.loadFromFile("../docs/bugFile.txt");
```

14. The `loadFromFile` call uses a relative path `"../docs/bugFile.txt"`. What is the significance of the `..` in this path relative to the executable’s working directory?

---

**`src/main.cpp`**

```cpp
list.sortById();
std::cout << "\nSorted by ID:\n";
list.display();
```

15. After calling `list.sortById()` and then `list.display()`, what determines the order in which bugs are printed to the console?

---

**`src/main.cpp`**

```cpp
list.deleteBug(3);
std::cout << "\nAfter Deletion:\n";
list.display();
```

16. After `list.deleteBug(3)` is called, what would `list.searchBug(3)` return, and why?

---

**`src/main.cpp`**

```cpp
list.sortByStatus();
std::cout << "\nSorted by Status:\n";
list.display();
```

17. When `list.sortByStatus()` is invoked, the bugs are sorted lexicographically by their `status` string. Based on the status values assigned in `main.cpp`, what would be the first and last statuses displayed after this sort?

---

**`src/main.cpp`**

```cpp
Bug* found = list.searchBug(2);
if (found) {
    std::cout << "\nFound Bug ID 2:\n";
    std::cout << found->briefDesc << std::endl;
}
```

18. In the `searchBug` usage within `main.cpp`, the code checks `if (found)` before dereferencing the pointer. Why is this check necessary, and what could happen if it were omitted and the bug ID did not exist?

---

**`src/main.cpp`**

```cpp
list.saveToFile("../output/bugFile.txt");
```

19. The `saveToFile` call writes to `"../output/bugFile.txt"`. What must be true about the `output` directory relative to the executable for this operation to succeed?

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

20. The `LinkedList` class manages a singly linked list using only a `head` pointer. How does the absence of a `tail` pointer affect the time complexity of the `addBug` function as currently implemented?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    ...
    bug.commentCount = 0;
    while (getline(ss, comment, '|')) {
        if (comment.empty()) break;
        if (bug.commentCount < 10) {
            bug.comments[bug.commentCount++] = comment;
        }
    }
    ...
}
```

21. In `loadFromFile`, the comment-reading loop has a guard `if (bug.commentCount < 10)`. What is the consequence for bug records in the file that contain more than 10 comments?

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
    ...
}
```

22. In `deleteBug`, if the list is empty (`head == nullptr`), what does the initial `while` loop condition evaluate to, and what does the function ultimately do?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    ...
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

23. The `sortById` function implements a bubble sort algorithm. What property of the `swapped` flag causes the outer `do...while` loop to terminate?

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

24. The `Bug` struct contains a `comments` array with a fixed capacity of 10. How does the `commentCount` field relate to the valid elements within the `comments` array when iterating in `display` and `saveToFile`?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const {
    ...
    for (int i = 0; i < current->data.commentCount; i++) {
        std::cout << "Comment " << i + 1 << ": "
                  << current->data.comments[i] << std::endl;
    }
    ...
}
```

25. In the `display` function, the comment loop uses `i + 1` for numbering. If a bug has zero comments, how many iterations does this loop execute, and what is printed for comments?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
```

26. In `main.cpp`, the `Bug` objects are created with hardcoded ID values (1 through 5). What potential problem could arise if the file loaded by `loadFromFile` already contains a bug with the same ID as one of these hardcoded values?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {
    BugNode* node = new BugNode;
    node->data = bug;
    node->next = nullptr;
    ...
}
```

27. In `addBug`, the new `BugNode` is allocated with `new`. Which function or language feature is responsible for deallocating this memory when the bug is removed from the list?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    ...
    while (getline(file, line)) {
        std::stringstream ss(line);
        ...
        getline(ss, token, '|');
        bug.id = stoi(token);
        ...
    }
    ...
}
```

28. In `loadFromFile`, the first token read from each line is converted to an integer using `stoi(token)`. What would happen if the first token in a line of the input file were not a valid integer string?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    ...
    file.close();
};
```

29. The `saveToFile` function opens an `ofstream` with the provided filename. If a file with that name already exists, what happens to its previous contents when this function executes?

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

30. The `searchBug` function performs a linear search through the linked list. How does the loop condition `current != nullptr` ensure that the function correctly returns `nullptr` when the `bugId` is not found?

---

**`src/main.cpp`**

```cpp
list.addBug(b1);
list.addBug(b2);
list.addBug(b3);
list.addBug(b4);
list.addBug(b5);
```

31. In `main.cpp`, five bugs are added to the list after loading from the file. In what order will these five bugs appear relative to the bugs loaded from the file before `sortById` is called?

---

**`src/LinkedList.h`**

```cpp
struct BugNode {
    Bug data;
    BugNode* next;
};
```

32. The `BugNode` struct contains a `Bug data` member rather than a pointer to a `Bug`. What does this imply about the memory layout of each node in the linked list with respect to the `Bug` object?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    ...
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}
```

33. In `deleteBug`, after updating the appropriate pointer (`head` or `prev->next`), the code calls `delete current`. Why is it safe to delete `current` at this point, and what would be the consequence of not deleting it?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortByStatus() {
    ...
    while (current->next != nullptr) {
        if (current->data.status > current->next->data.status) {
            Bug temp = current->data;
            current->data = current->next->data;
            current->next->data = temp;
            swapped = true;
        }
        current = current->next;
    }
    ...
}
```

34. In `sortByStatus`, the comparison `current->data.status > current->next->data.status` uses lexicographic ordering. Given the status strings `"CLOSED"`, `"IN PROGRESS"`, `"OPEN"`, and `"WAITING"`, which status would appear first after sorting in ascending order?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File not found.\n";
        return;
    }
    ...
}
```

35. In `loadFromFile`, the function checks `if (!file)` after attempting to open the file. Under what specific circumstances would `!file` evaluate to `true`, causing the "File not found." message to be printed?

---

**`src/main.cpp`**

```cpp
int main() {
    LinkedList list;
    list.loadFromFile("../docs/bugFile.txt");
    ...
    list.saveToFile("../output/bugFile.txt");
    return 0;
}
```

36. The `main` function creates a `LinkedList` object on the stack. When `main` returns, what mechanism ensures that the `LinkedList` destructor is called, and what does that destructor do?

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

37. In the destructor, after the `while` loop completes, `head` is set to `nullptr`. Given that the `LinkedList` object is being destroyed, what is the practical purpose of setting `head` to `nullptr` at this point?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {
    BugNode* node = new BugNode;
    node->data = bug;
    node->next = nullptr;
    ...
}
```

38. In `addBug`, the parameter `bug` is passed by `const` reference. What is the benefit of using `const Bug&` instead of passing by value for this function?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const {
    BugNode* current = head;
    while (current != nullptr) {
        ...
        current = current->next;
    }
}
```

39. The `display` function is marked as `const`. What restriction does this place on the implementation of `display`, and why is it appropriate for a function that only prints the list contents?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    ...
    while (current != nullptr) {
        file << current->data.id << "|"
             << current->data.date << "|"
             ...
        for (int i = 0; i < current->data.commentCount; i++) {
            file << current->data.comments[i] << "|";
        }
        file << "||\n";
        current = current->next;
    }
    ...
}
```

40. In `saveToFile`, the code writes a pipe `|` after each comment in the loop, and then writes `"||\n"` after the loop. If a bug has zero comments, what exact sequence of characters is written to the file for that bug after the severity field?

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

41. The `Bug` struct uses `std::string` for all text fields. How does the use of `std::string` (as opposed to C-style character arrays) affect the ability to store variable-length descriptions and comments?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;
    ...
}
```

42. In both `sortById` and `sortByStatus`, the first line checks `if (!head) return;`. What scenario does this guard against, and why would proceeding without this check be problematic?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    ...
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string comment;
        Bug bug;
        getline(ss, token, '|');
        bug.id = stoi(token);
        ...
        addBug(bug);
    }
    file.close();
}
```

43. In `loadFromFile`, a new local `Bug bug` is created for each line read from the file. What happens to this local `bug` object after `addBug(bug)` is called, and how does `addBug` ensure the data persists beyond the scope of the loop iteration?

---

**`src/main.cpp`**

```cpp
Bug* found = list.searchBug(2);
if (found) {
    std::cout << "\nFound Bug ID 2:\n";
    std::cout << found->briefDesc << std::endl;
}
```

44. In `main.cpp`, after finding bug ID 2, only `found->briefDesc` is printed. According to the assignment requirement to "display the details of that bug," what additional fields might be expected to be displayed that are not shown here?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    ...
    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }
    ...
}
```

45. In `deleteBug`, the `while` loop condition uses `current->data.id != bugId`. If the list contains multiple bugs with the same `bugId`, which one would be deleted by this function?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    ...
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

46. In `sortById`, the inner `while` loop condition is `current->next != nullptr`. Why is it necessary to check `current->next` rather than just `current != nullptr` to avoid accessing invalid memory when swapping data?

---

## Broader Questions

47. The assignment specification states that students "cannot use library data structures (e.g. vector) to perform any functionality." How does the custom `LinkedList` class and its manual memory management satisfy this constraint?

---

48. The bug file format uses a pipe `|` as a field delimiter and a double pipe `||` as a record terminator. Why might a single-character delimiter like `|` be problematic if the data fields themselves could contain that character, and how does the assignment specification mitigate this concern?

---

49. The `sortByStatus` function sorts bugs alphabetically by their status string. Given the four defined statuses (`OPEN`, `CLOSED`, `IN PROGRESS`, `WAITING`), does alphabetical order correspond to any meaningful logical order? What does this imply about the suitability of string comparison for sorting by status?

---

50. The `main` function demonstrates a specific sequence of operations: load, add, sort by ID, display, delete, display, sort by status, display, search, save. How does this sequence directly map to the numbered application requirements (1 through 7) listed in the assignment specification?

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · deepseek/deepseek-v4-pro via openrouter · main</sub>