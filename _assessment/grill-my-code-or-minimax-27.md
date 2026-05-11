## Grill My Code

> **Generated:** 2026-05-11 11:35:07 UTC
> **Commits reviewed:** `4334237` → `8d59852`

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

struct BugNode {
    Bug data;
    BugNode* next;
};
```

1. What is the purpose of the `BugNode` struct in `src/LinkedList.h`, and how does its design enable the linked list structure to function?

2. Why is `commentCount` necessary as a separate field in the `Bug` struct when an array `comments[10]` is already provided?

3. What would happen if the `comments` array in the `Bug` struct were changed to a dynamic array (e.g., `std::vector<std::string>`)? Would the code still compile given the assignment constraints?

4. In the `BugNode` struct, why is `data` placed before `next`? How might reversing their order affect memory layout or access patterns?

5. What is the purpose of the `head` pointer being private in the `LinkedList` class?

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

6. Why is it necessary to store `current->next` in a separate variable `next` before calling `delete current`?

7. What memory leak scenario could occur if the line `BugNode* next = current->next;` were removed from the destructor?

8. What is the purpose of setting `head = nullptr` at the end of the destructor?

9. Why does the destructor iterate through the entire linked list rather than just deleting `head`?

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

10. What is the time complexity of the `addBug` function, and why?

11. Why is the function parameter passed by `const Bug&` instead of by value or by pointer?

12. In what scenario would the condition `if (head == nullptr)` evaluate to true, and what happens in that case?

13. After adding a bug to an empty list, what is the state of the linked list's `head` pointer?

14. Why does the loop `while (current->next != nullptr)` stop at the last node rather than including the last node?

15. What would happen if `addBug` is called multiple times in succession without any deletions?

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

16. What happens when `deleteBug` is called with a bug ID that does not exist in the list?

17. Why are both `current` and `prev` pointers needed to delete a node from the middle of the list?

18. What specific condition does `prev == nullptr` detect, and why does this require special handling?

19. What would happen if the line `delete current;` were omitted from the `deleteBug` function?

20. Trace through the `deleteBug` function step by step when deleting the first node (assuming the list has at least one node). What happens to `head`?

21. Why does the function return early if `current == nullptr` without performing any deletion?

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

22. Why does `searchBug` return a pointer (`Bug*`) instead of a copy of the `Bug` object?

23. What is the significance of returning `nullptr` when the bug is not found?

24. In `src/main.cpp`, the returned pointer is used as follows:

```cpp
Bug* found = list.searchBug(2);
if (found) {
    std::cout << "\nFound Bug ID 2:\n";
    std::cout << found->briefDesc << std::endl;
}
```

Why is the `if (found)` check necessary before accessing `found->briefDesc`?

25. What potential issue arises if the linked list is modified (e.g., a bug is added or deleted) after calling `searchBug` but before using the returned pointer?

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

26. What sorting algorithm is implemented in `sortById`? Describe how it works.

27. Why is the outer loop a `do-while` instead of a `for` loop?

28. What is the purpose of the `swapped` boolean variable?

29. What would happen if the inner condition were changed from `>` to `<`?

30. The function swaps entire `Bug` objects using `current->data = current->next->data`. What are the implications of this approach regarding efficiency and data integrity?

31. Trace through the first pass of `sortById` if the list contains bugs with IDs in the order: 5, 3, 1. Show which swaps occur.

32. What is the worst-case time complexity of this sorting algorithm?

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

33. How does `sortByStatus` compare to `sortById` in terms of implementation? What is the key difference?

34. Since `status` is a `std::string`, what does the comparison `current->data.status > current->next->data.status` actually compare?

35. According to the assignment specification, valid status values are: OPEN, CLOSED, IN PROGRESS, WAITING. What is the alphabetical ordering of these strings, and how does this affect the sorted result?

36. Would the sorting result be the same if the comparison operator were changed from `>` to `>=`? Explain why or why not.

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

37. What happens if a line in the file does not contain any pipe delimiters (e.g., an empty line)?

38. Why is `bug.commentCount` set to 0 before entering the comment-parsing loop?

39. What is the purpose of the condition `if (bug.commentCount < 10)` in the comment-parsing loop?

40. The assignment specification states that each record ends with a double pipe symbol (`||`). How does the parsing logic handle this, and what potential issue exists with how comments are processed?

41. What would happen if `stoi(token)` is called on a non-numeric string (e.g., "BUG0001" instead of "1")?

42. Why is `std::stringstream` used instead of parsing the file character by character?

43. What resource management issue exists regarding file handling, and how is it addressed?

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

44. Why is the `||` delimiter written after all comments instead of being handled during the comment loop?

45. What would happen if the linked list contains a bug with zero comments? How would the output file look for that bug?

46. The function is marked `const`. Explain what this means and why it is appropriate here.

47. Compare `loadFromFile` and `saveToFile`. What asymmetry exists between how they handle file errors?

---

**`src/main.cpp`**

```cpp
Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
```

48. When initializing `Bug b1` using aggregate initialization, how does the compiler map the values to the struct members? What value will `commentCount` have?

49. The bug severity is set to "HIGH" (uppercase), but the assignment specification lists severities as: LOW, MEDIUM, HIGH, CRITICAL. What potential issue exists if a user enters "high" (lowercase) in the input file?

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

50. The `display` function is marked `const`, yet it traverses the linked list and modifies the `current` pointer. Explain how this is possible and why it does not violate const-correctness.

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · minimax/minimax-m2.7 via openrouter · main</sub>