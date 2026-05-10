## Grill My Code

> **Generated:** 2026-05-10 13:47:42 UTC
> **Commits reviewed:** `4334237` → `22da5ce`

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
struct BugNode {
    Bug data;
    BugNode* next;
};
```

1. What is the purpose of the `commentCount` field in the `Bug` struct?

---

2. Why does `BugNode` contain a `Bug` object (`data`) rather than just storing the fields directly?

---

3. What is the relationship between `Bug` and `BugNode` in terms of memory layout?

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

4. Why is `head` declared as `private` instead of `public`?

---

5. Why does `searchBug` return a pointer (`Bug*`) instead of returning the `Bug` object directly by value?

---

6. Why does `saveToFile` have the `const` qualifier while `loadFromFile` does not?

---

7. What would happen if `addBug` was declared `const`?

---

8. Why is `display` declared as `const` while `sortById` is not?

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```

9. Why is `head` initialized to `nullptr` in the constructor?

---

10. What would be the consequence if the constructor did not initialize `head`?

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

11. Why is `next` saved before calling `delete current`?

---

12. What memory leak would occur if `next` was not saved before deletion?

---

13. Why is `head` set to `nullptr` at the end of the destructor?

---

14. What would happen if the destructor was not implemented (or was empty)?

---

15. In what order does the destructor traverse and delete the nodes—starting from `head` or from the tail?

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

16. Where in the linked list is each new bug added—at the beginning or at the end?

---

17. What is the time complexity of `addBug` when the list contains `n` nodes?

---

18. Why is the parameter `bug` passed by `const` reference (`const Bug&`) instead of by value?

---

19. What would happen if `node->next` was not set to `nullptr` before insertion?

---

20. How many iterations of the while loop occur when adding a bug to an empty list?

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

21. What happens when attempting to delete a bug ID that does not exist in the list?

---

22. Under what condition is `prev == nullptr` true, and what does this condition represent?

---

23. How is the linked list reconnected after deleting a node that is not at the head?

---

24. What would happen if the `delete current` line was removed from the function?

---

25. How many pointers are modified when deleting a node in the middle of the list?

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

26. What does `searchBug` return if the bug with the specified ID is not found?

---

27. Why does `searchBug` return `&current->data` (a pointer to `data`) rather than `&current` (a pointer to the `BugNode`)?

---

28. What is the danger of returning `&current->data` when the linked list is later modified?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::display() const{
    BugNode* current = head;

    while (current != nullptr) {
        std::cout << "ID: " << current->data.id << std::endl;
        // ... print other fields ...
        for (int i = 0; i < current->data.commentCount; i++) {
            std::cout << "Comment " << i + 1 << ": "
                      << current->data.comments[i] << std::endl;
        }
        current = current->next;
    }
}
```

29. Why does the `display` function access `current->data` even though `display` is declared `const`?

---

30. What would happen if `current->data.commentCount` was negative or greater than 10?

---

31. What is the purpose of the `commentCount` variable in controlling the loop?

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

32. What sorting algorithm is implemented in `sortById`?

---

33. Why is a `do-while` loop used instead of a simple `while` loop?

---

34. What is the purpose of the `swapped` variable?

---

35. How does the algorithm know when the list is fully sorted?

---

36. Why are the entire `Bug` structs swapped (`current->data = current->next->data`) rather than just swapping the `id` fields?

---

37. What is the time complexity of this sorting algorithm in the worst case?

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
    while (getline(file, line)) {
        // ... parsing ...
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

38. What character is used as a delimiter to separate fields in the file?

---

39. What is the purpose of the `comment.empty()` check inside the inner while loop?

---

40. Why is there a limit of 10 comments (`bug.commentCount < 10`)?

---

41. What happens if the input file contains more than 10 comments for a single bug?

---

42. After loading from file, what is the initial value of `commentCount` before parsing comments?

---

**`src/LinkedList.cpp`**

```cpp
void LinkedList::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    BugNode* current = head;

    while (current != nullptr) {
        file << current->data.id << "|"
             << current->data.date << "|"
             // ... other fields ...
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

43. Why does the output end with `||\n` (two consecutive pipe characters followed by newline)?

---

44. How does the `loadFromFile` function use the double pipe (`||`) when parsing?

---

45. Why can `current` be modified in `saveToFile` even though the function is `const`?

---

**`src/main.cpp`**

```cpp
int main() {
    LinkedList list;
    list.loadFromFile("../docs/bugFile.txt");
    
    Bug b1 = {1, "2026-04-24", "Crash", "App crashes", "OPEN", "HIGH", "Needs fix"};
    // ... b2, b3, b4, b5 ...
    
    list.addBug(b1);
    list.addBug(b2);
    // ...
    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();

    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();
    
    list.saveToFile("../output/bugFile.txt");
    return 0;
}
```

46. In what order will the bugs appear after `sortById()` is called?

---

47. After `deleteBug(3)` is executed, which bug is removed from the list?

---

48. What will be the first bug displayed after calling `sortByStatus()`?

---

49. Why is the path `../docs/bugFile.txt` used for loading but `../output/bugFile.txt` for saving?

---

50. What happens if the directory `../docs/` does not exist when `loadFromFile` is called?

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · minimax/minimax-m2.7 via openrouter · main</sub>