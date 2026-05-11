## Grill My Code

> **Generated:** 2026-05-11 11:35:20 UTC
> **Commits reviewed:** `4334237` → `8d59852`

> **Files assessed:** `src/LinkedList.cpp`, `src/LinkedList.h`, `src/main.cpp`

---

**`src/LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
};
```

1. Why does the `LinkedList` constructor in src/LinkedList.cpp initialize `head` to `nullptr`?

---

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

2. How does the destructor of `LinkedList` in src/LinkedList.cpp ensure that all nodes are properly deallocated?

---

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

3. How does the `addBug` method in src/LinkedList.cpp add a new bug to the linked list, and where is the new bug inserted?

---

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

4. In src/LinkedList.cpp, what steps does `deleteBug` take to remove a bug with a specific `bugId` from the linked list?

---

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

5. How does the `searchBug` function in src/LinkedList.cpp locate a bug by `bugId`, and what does it return if the bug is not found?

---

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

6. In src/LinkedList.cpp, how does the `display` method output bug details, and how are comments for each bug handled?

---

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

7. What sorting algorithm does `sortById` in src/LinkedList.cpp implement, and how does it sort the bugs by their ID?

---

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

8. How does `sortByStatus` in src/LinkedList.cpp compare bug statuses, and what effect does this have on the ordering of the list?

---

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

9. How does `loadFromFile` in src/LinkedList.cpp parse bug information from a file, and how does it handle multiple comments for each bug?

---

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

10. In src/LinkedList.cpp, what is the purpose of the `saveToFile` function, and how does it format bug information for output?

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

11. How does the `Bug` struct in src/LinkedList.h represent a bug and its associated comments?

---

```h
struct BugNode {

    Bug data;
    BugNode* next;

};
```

12. What is the role of the `BugNode` struct in src/LinkedList.h, and how does it facilitate the linked list structure?

---

```h
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

13. According to src/LinkedList.h, which operations are provided by the `LinkedList` class for managing bugs?

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

14. In src/main.cpp, what sequence of operations is performed on the `LinkedList` instance to satisfy the assignment requirements?

---

15. How does the code in src/main.cpp demonstrate adding five bugs with varying contents to the bug list?

---

16. In src/main.cpp, what is the effect of calling `list.sortById()` followed by `list.display()`?

---

17. What is the purpose of calling `list.deleteBug(3)` in src/main.cpp, and how is its effect verified?

---

18. How does `list.sortByStatus()` in src/main.cpp change the ordering of bugs in the list?

---

19. In src/main.cpp, how is the result of `list.searchBug(2)` utilized, and what information is displayed if the bug is found?

---

20. What is the significance of the file paths passed to `list.loadFromFile()` and `list.saveToFile()` in src/main.cpp?

---

21. In src/main.cpp, how does the main function ensure that all bugs are written to the output file before program termination?

---

22. Why are the bug objects `b1` to `b5` initialized with only one comment each in src/main.cpp, and how does this relate to the `Bug` struct?

---

23. What would happen in src/main.cpp if a bug was searched for using an ID that does not exist in the list?

---

24. How does src/main.cpp demonstrate the use of the linked list for both file input and file output of bugs?

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

25. In src/LinkedList.cpp, how does the code ensure that no more than 10 comments are stored for a bug when loading from a file?

---

```cpp
for (int i = 0; i < current->data.commentCount; i++) {
    file << current->data.comments[i] << "|";
}
```

26. How does src/LinkedList.cpp guarantee that only the valid comments for a bug are written to the output file?

---

```cpp
if (!head) return;
```

27. In src/LinkedList.cpp, what is the purpose of the `if (!head) return;` check at the start of the sorting functions?

---

```cpp
Bug temp = current->data;
current->data = current->next->data;
current->next->data = temp;
```

28. Why does src/LinkedList.cpp swap the `Bug` data between nodes instead of rearranging node pointers during sorting?

---

**`src/LinkedList.h`**

```h
std::string  comments[10];
int commentCount;
```

29. How does the combination of `comments[10]` and `commentCount` in src/LinkedList.h help manage bug comments efficiently?

---

## Broader Questions

30. How does the linked list implementation in src/LinkedList.cpp and src/LinkedList.h avoid using library data structures, as per the assignment specification?

---

31. How is the bug file format specification from the assignment reflected in the implementation of `loadFromFile` and `saveToFile` in src/LinkedList.cpp?

---

32. What potential issues might arise when deleting a bug that does not exist in the list, based on the implementation in src/LinkedList.cpp?

---

33. How does the application ensure that each bug has a unique ID, and what are the implications if duplicate IDs are added?

---

34. In what way is sorting by status implemented, and how does it compare the status fields given they are strings?

---

35. Why is a destructor needed in the `LinkedList` class, and how does it relate to the use of dynamic memory?

---

36. How does the code handle the possibility of bugs having zero comments, according to the file loading and display logic?

---

37. What are the consequences of exceeding the maximum comment count for a bug, as enforced in `loadFromFile`?

---

38. How does the linked list structure facilitate searching for a bug by ID, and what is the efficiency of this approach?

---

39. What is the reasoning for displaying bug details immediately after sorting or deletion operations in src/main.cpp?

---

40. How does the code differentiate between mandatory and optional fields when reading from or writing to the bug file?

---

41. How would you add support for additional bug statuses or severities, given the current implementation?

---

42. What is the effect of calling `display` multiple times in the main function, and how does it help verify list contents?

---

43. How does the code structure ensure that bugs are not lost between file operations and linked list operations?

---

44. In what situations might the `searchBug` function return a `nullptr`, and how is this handled in the main function?

---

45. How does the application demonstrate the use of custom data structures and algorithms, aligning with the course requirements?

---

46. What role does the linked list play in maintaining the order of bugs, and how is this order affected by sorting functions?

---

47. How does the code ensure that bugs loaded from the file are preserved along with newly added bugs?

---

48. How could the file reading logic be affected by malformed bug records, and how is this handled in `loadFromFile`?

---

49. How does the main function coordinate the sequence of file I/O, adding, sorting, deletion, searching, and display operations?

---

50. How does the implementation reflect the requirement to demonstrate concepts such as linked lists, file I/O, and sorting/searching algorithms?
---

---

<sub>Generated by [grill-my-code](https://github.com/NSCC-ITC-Assessment/GrillMyCode) · gpt-4.1 via github-models · main</sub>