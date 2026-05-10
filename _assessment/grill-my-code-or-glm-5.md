## Grill My Code

> **Generated:** 2026-05-10 13:47:39 UTC
> **Commits reviewed:** `4334237` → `22da5ce`

> **Files assessed:** `src/LinkedList.cpp`, `src/LinkedList.h`, `src/main.cpp`

---

**`src/LinkedList.h`**

```h
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

1. What is the maximum number of comments that can be stored in the `comments` array for a single `Bug` instance?

---

**`src/LinkedList.h`**

```h
struct BugNode {

    Bug data;
    BugNode* next;

};
```

2. What is the relationship between the `BugNode` struct and the `Bug` struct in this linked list implementation?

---

**`src/LinkedList.h`**

```h
class LinkedList {

private:
    BugNode* head = nullptr;
```

3. What does the `head` pointer represent in the context of this linked list data structure?

---

**`src/LinkedList.h`**

```h
LinkedList();            
~LinkedList();           
```

4. What is the purpose of the `~LinkedList()` function declaration in this class?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```

5. Why is the `head` pointer set to `nullptr` in the `LinkedList` constructor?

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

6. Why does the destructor store `current->next` in a separate variable before executing `delete current`?

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

7. What would happen if the destructor did not save `current->next` before deleting `current`?

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

8. What condition does the `if (head == nullptr)` block handle in the `addBug` function?

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

9. In the `addBug` function, why does the `while` loop check `current->next != nullptr` instead of `current != nullptr`?

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

10. What does the condition `current == nullptr` indicate when the `while` loop terminates?

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

11. In the `deleteBug` function, what scenario does the condition `if (prev == nullptr)` handle?

---

**`src/LinkedList.cpp`**

```cpp
if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
```

12. What is the purpose of the statement `prev->next = current->next` in the `deleteBug` function?

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

13. What does the `searchBug` function return when no bug with the specified `bugId` is found?

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

14. What does the expression `&current->data` return in the `searchBug` function?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const{

    BugNode* current = head;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
```

15. What does the `const` keyword in the `display()` function signature indicate about the function?

---

**`src/LinkedList.cpp`**

```cpp
for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
```

16. Why does the `display` function iterate using `current->data.commentCount` instead of a fixed value like 10?

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

17. What sorting algorithm is implemented in the `sortById` function?

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

18. In the `sortById` function, what does the `swapped` variable track?

---

**`src/LinkedList.cpp`**

```cpp
Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
```

19. In the `sortById` function, does the code swap the node pointers or the data contained within the nodes?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;
```

20. What is the purpose of the `if (!head) return;` statement at the beginning of `sortById`?

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

21. How does the comparison in `sortByStatus` differ from the comparison in `sortById` in terms of data types being compared?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }
```

22. What does the condition `if (!file)` check in the `loadFromFile` function?

---

**`src/LinkedList.cpp`**

```cpp
std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
```

23. What does `getline(file, line)` return to control the `while` loop in `loadFromFile`?

---

**`src/LinkedList.cpp`**

```cpp
std::stringstream ss(line);
        std::string token;
        std::string comment;

        Bug bug;
        getline(ss, token, '|');
        bug.id = stoi(token);
```

24. What is the purpose of the `'|'` character in the `getline(ss, token, '|')` call?

---

**`src/LinkedList.cpp`**

```cpp
getline(ss, token, '|');
        bug.id = stoi(token);
```

25. Why is `stoi(token)` used when assigning to `bug.id` but not used for `bug.date` or `bug.briefDesc`?

---

**`src/LinkedList.cpp`**

```cpp
bug.commentCount = 0;

        while (getline(ss, comment, '|')) {
            if (comment.empty()) break;

            if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
        }
```

26. What is the purpose of the condition `if (comment.empty()) break;` in the comment parsing loop?

---

**`src/LinkedList.cpp`**

```cpp
if (bug.commentCount < 10) {
                bug.comments[bug.commentCount++] = comment;
            }
```

27. Why is the condition `bug.commentCount < 10` necessary when adding comments to the `bug.comments` array?

---

**`src/LinkedList.cpp`**

```cpp
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

28. In `loadFromFile`, what does `bug.commentCount++` accomplish after storing a comment in the array?

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

29. What is the purpose of writing `"||\n"` at the end of each bug record in `saveToFile`?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
```

30. What does the `const` keyword after the function parameter list indicate about `saveToFile`?

---

**`src/main.cpp`**

```cpp
int main() {
    LinkedList list;

    list.loadFromFile("../docs/bugFile.txt");
```

31. What happens to the `list` object's `head` pointer if `loadFromFile` cannot find the specified file?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
    Bug b2 = {2, "2026-04-25", "Login bug", "Can't login", "IN PROGRESS", "CRITICAL", "Working on it"};
```

32. Based on the `Bug` struct definition, which member is initialized by the value `"Needs fix"` in the `b1` initialization?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
```

33. When `b1` is initialized with this brace-enclosed list, which struct member receives the value `"Needs fix"`?

---

**`src/main.cpp`**

```cpp
list.addBug(b1);
    list.addBug(b2);
    list.addBug(b3);
    list.addBug(b4);
    list.addBug(b5);

    list.sortById();
```

34. After all five bugs are added via `addBug`, in what order will they be stored in the linked list before `sortById` is called?

---

**`src/main.cpp`**

```cpp
list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();
```

35. Which bug will be removed from the linked list when `deleteBug(3)` is called?

---

**`src/main.cpp`**

```cpp
list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();
```

36. When `sortByStatus` is called, how will bugs with status `"CLOSED"` compare to bugs with status `"OPEN"` when using the `>` operator on strings?

---

**`src/main.cpp`**

```cpp
Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }
```

37. What does the condition `if (found)` check in this code snippet?

---

**`src/main.cpp`**

```cpp
Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }
```

38. If `searchBug(2)` returns `nullptr`, what will happen when `if (found)` is evaluated?

---

**`src/main.cpp`**

```cpp
list.saveToFile("../output/bugFile.txt");

    return 0;
}
```

39. When `main()` returns 0, what happens to the `LinkedList` object named `list`?

---

**`src/LinkedList.h`**

```h
std::string  briefDesc;
    std::string  detailedDesc;
```

40. What is the significance of the double spaces between `string` and `briefDesc` or `detailedDesc` in the struct definition?

---

**`src/LinkedList.cpp`**

```cpp
while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {

                Bug temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = true;
            }
            current = current->next;
        }
```

41. In the `sortById` function, what happens when `current->data.id` equals `current->next->data.id`?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;
```

42. What does the `new` operator do in the `addBug` function?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;
```

43. Why is `node->next` set to `nullptr` when creating a new `BugNode` in `addBug`?

---

**`src/LinkedList.h`**

```h
#ifndef SUPPLEMENTAL_LINKEDLIST_H
#define SUPPLEMENTAL_LINKEDLIST_H
```

44. What is the purpose of the `#ifndef SUPPLEMENTAL_LINKEDLIST_H` directive at the top of the header file?

---

**`src/LinkedList.h`**

```h
#ifndef SUPPLEMENTAL_LINKEDLIST_H
#define SUPPLEMENTAL_LINKEDLIST_H
```

45. What problem does the include guard prevent when this header file is included in multiple source files?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.\n";
        return;
    }
```

46. What happens to the linked list's existing contents when `loadFromFile` is called on a non-empty list?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    BugNode* current = head;

    while (current != nullptr) {
```

47. What would happen if `saveToFile` is called when the linked list is empty (head is nullptr)?

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
```

48. What happens when `deleteBug` is called with a `bugId` that does not exist in the linked list?

---

**`src/main.cpp`**

```cpp
list.addBug(b1);
    list.addBug(b2);
    list.addBug(b3);
    list.addBug(b4);
    list.addBug(b5);
```

49. After executing these five `addBug` calls, which bug will be at the head of the linked list?

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

50. Why is `head = nullptr` set at the end of the destructor even though the object is being destroyed?

---

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · z-ai/glm-5 via openrouter · main</sub>