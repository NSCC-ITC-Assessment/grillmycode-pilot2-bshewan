# PROG2400 Comprehension Questions: Bug Tracking Application

**`LinkedList.h`**

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

1. How does the `Bug` structure design in **`LinkedList.h`** use the `std::string comments[10]` array and `int commentCount` to satisfy the assignment requirement that a bug may have "Zero or more comments" while also adhering to the constraint against using library data structures like vectors?

---

**`LinkedList.h`**

```cpp
struct BugNode {

    Bug data;
    BugNode* next;

};

```

2. In the `BugNode` structure, what is the architectural purpose of the `BugNode* next` member, and how does it facilitate the requirement to store bugs in a "linked list" rather than a contiguous array?

---

**`LinkedList.h`**

```cpp
class LinkedList {

private:
    BugNode* head = nullptr;

public:
    LinkedList();            // constructor
    ~LinkedList();           // destructor

    void addBug(const Bug& bug);     // add bug
    void deleteBug(int bugId);       // remove per ID
    Bug* searchBug(int bugId);       // search per ID
    void display() const;            // show all
    void sortById();                 // order by id
    void sortByStatus();             // order by status

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};

```

3. Within the `LinkedList` class, why is the `BugNode* head` pointer designated as `private` while the management functions are `public`, and how does this support the concept of encapsulation?

---

**`LinkedList.cpp`**

```cpp
LinkedList::LinkedList() {
    head = nullptr;
};

```

4. In the `LinkedList::LinkedList()` constructor, what is the operational significance of setting `head` to `nullptr` for the initial state of the application?

---

**`LinkedList.cpp`**

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

5. How does the logic within the `LinkedList::~LinkedList()` destructor prevent memory leaks when the application ends, specifically regarding the role of the temporary `BugNode* next` pointer?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    //empty list
    if (head == nullptr) {
        head = node;
        return;
    }
    //find last node
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

```

6. In the `addBug` function, why must the code check if `head == nullptr` before attempting the `while (current->next != nullptr)` loop?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    //empty list
    if (head == nullptr) {
        head = node;
        return;
    }
    //find last node
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

```

7. How does the `current->next = node;` assignment in `addBug` ensure that the linked list remains connected as a single sequence of data?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    // Bug not find
    if (current == nullptr) {
        return;
    }
    //delete the first node
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}

```

8. In the `deleteBug` function, how does the use of the `BugNode* prev` pointer allow the application to "stitch" the list back together after a node is removed?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    // Bug not find
    if (current == nullptr) {
        return;
    }
    //delete the first node
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}

```

9. How does the `deleteBug` implementation handle the edge case where the user attempts to delete a `bugId` that does not exist in the current list?

---

**`LinkedList.cpp`**

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

10. In `searchBug`, what is the advantage of returning a `Bug*` pointer to the actual data within the list rather than returning a copy of the `Bug` object?

---

**`LinkedList.cpp`**

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

11. How does the `display` function determine how many times to execute the `std::cout` statement for comments, and which member of the `Bug` struct facilitates this?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                //swap
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

12. In the `sortById` function, why is it necessary to swap the entire `Bug temp = current->data` rather than just swapping the `id` member?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                //swap
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

13. How does the `bool swapped` variable control the execution of the `do-while` loop to ensure the list is fully ordered by bug ID?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortByStatus() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.status > current->next->data.status) {
                //swap
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

14. Given that the `status` member is a `std::string`, how does the `>` operator in `sortByStatus` determine the sorting order for the four required statuses (OPEN, CLOSED, IN PROGRESS, WAITING)?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.
";
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

15. In `loadFromFile`, why is `bug.commentCount = 0;` reset inside the `while (getline(file, line))` loop but before the `comment` parsing loop?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.
";
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

16. How does the `getline(ss, comment, '|')` loop handle the specific requirement that "The comment fields are optional"?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File not found.
";
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

17. Why is the `std::stringstream ss(line)` used within `loadFromFile` to parse individual records instead of reading directly from the `std::ifstream file` object?

---

**`LinkedList.cpp`**

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
        file << "||
";
        current = current->next;
    }



    file.close();
};

```

18. In `saveToFile`, how does the output sequence `file << "||\n";` ensure that the resulting text file complies with the specified "Bug File Format" record terminator?

---

**`LinkedList.cpp`**

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
        file << "||
";
        current = current->next;
    }



    file.close();
};

```

19. Why does `saveToFile` iterate using `while (current != nullptr)` rather than a fixed loop, and how does this relate to the requirement of writing "all bugs in the linked list"?

---

**`main.cpp`**

```cpp
int main() {
    LinkedList list;

    // 1. Load file
    list.loadFromFile("../docs/bugFile.txt");

    // 2. Add 5 bugs
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

    // 3. Display sorted by ID
    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();

    // 4. Delete one bug
    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

    // 5. Sort by status
    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();

    // 6. Search
    Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }

    // 7. Save
    list.saveToFile("../output/bugFile.txt");

    return 0;
}

```

20. How does the sequence of function calls in `main.cpp` specifically map to the "Application Requirements" 1 through 7 listed in the assignment specification?

---

**`main.cpp`**

```cpp
int main() {
    LinkedList list;

    // 1. Load file
    list.loadFromFile("../docs/bugFile.txt");

    // 2. Add 5 bugs
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

    // 3. Display sorted by ID
    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();

    // 4. Delete one bug
    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

    // 5. Sort by status
    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();

    // 6. Search
    Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }

    // 7. Save
    list.saveToFile("../output/bugFile.txt");

    return 0;
}

```

21. In `main.cpp`, why is the `if (found)` check necessary after calling `list.searchBug(2)`, and what would happen if the code attempted to access `found->briefDesc` without this check if the ID was not found?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    // Bug not find
    if (current == nullptr) {
        return;
    }
    //delete the first node
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}

```

22. Within `deleteBug`, what logic ensures that the `head` pointer is correctly updated if the bug to be removed is the first item in the list?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    //empty list
    if (head == nullptr) {
        head = node;
        return;
    }
    //find last node
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

```

23. How does the manual allocation `new BugNode;` in the `addBug` function support the requirement to build a custom data structure without using library data structures like `std::vector`?

---

**`LinkedList.cpp`**

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

24. In the `loadFromFile` function, how does the `stoi(token)` call handle the numeric "Bug ID#" field, and why is this conversion necessary given the `Bug` struct definition in **`LinkedList.h`**?

---

**`LinkedList.cpp`**

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
        file << "||
";
        current = current->next;
    }



    file.close();
};

```

25. Why is the `saveToFile` function marked with the `const` keyword, and what guarantee does this provide about the state of the `LinkedList` after saving?

---

**`LinkedList.cpp`**

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

26. In `display`, how does the traversal logic `current = current->next;` ensure that every bug loaded into the system is eventually printed to the console?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                //swap
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

27. If the linked list was already sorted by ID when `sortById` was called, how many times would the `do-while` loop execute?

---

**`LinkedList.cpp`**

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

28. In the destructor, what would happen if the line `BugNode* next = current->next;` was placed *after* the `delete current;` line?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    //empty list
    if (head == nullptr) {
        head = node;
        return;
    }
    //find last node
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

```

29. Why is it critical to set `node->next = nullptr;` for the new node created in `addBug` before adding it to the end of the list?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    // Bug not find
    if (current == nullptr) {
        return;
    }
    //delete the first node
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}

```

30. In `deleteBug`, what role does the condition `current != nullptr` play in the `while` loop, and how does it prevent the application from crashing?

---

**`LinkedList.cpp`**

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

31. Given the file format `ID|Date|Brief|Detailed|Status|Severity|Comment|Comment|...||`, how does `loadFromFile` identify where the mandatory fields end and the optional comments begin?

---

**`LinkedList.cpp`**

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
        file << "||
";
        current = current->next;
    }



    file.close();
};

```

32. How does the `saveToFile` function use the `current->data.commentCount` variable to ensure that only populated comment slots are written to the file?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortByStatus() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.status > current->next->data.status) {
                //swap
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

33. Does the `sortByStatus` function reorganize the physical nodes in memory or only the `Bug` data stored inside those nodes?

---

**`LinkedList.cpp`**

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

34. How does `searchBug` meet requirement 6 of the assignment, which asks to "display the details of that bug" based on its ID?

---

**`LinkedList.cpp`**

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

35. If a bug record in the text file has no comments (e.g., `1|date|brief|detail|OPEN|LOW|||`), how does the `while (getline(ss, comment, '|'))` loop handle the empty tokens to ensure `commentCount` remains zero?

---

**`main.cpp`**

```cpp
int main() {
    LinkedList list;

    // 1. Load file
    list.loadFromFile("../docs/bugFile.txt");

    // 2. Add 5 bugs
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

    // 3. Display sorted by ID
    list.sortById();
    std::cout << "\nSorted by ID:\n";
    list.display();

    // 4. Delete one bug
    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

    // 5. Sort by status
    list.sortByStatus();
    std::cout << "\nSorted by Status:\n";
    list.display();

    // 6. Search
    Bug* found = list.searchBug(2);
    if (found) {
        std::cout << "\nFound Bug ID 2:\n";
        std::cout << found->briefDesc << std::endl;
    }

    // 7. Save
    list.saveToFile("../output/bugFile.txt");

    return 0;
}

```

36. In `main.cpp`, why are the 5 new bugs added *after* the `loadFromFile` call rather than before?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    //empty list
    if (head == nullptr) {
        head = node;
        return;
    }
    //find last node
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

```

37. How does the `addBug` function ensure that it does not accidentally overwrite the existing `head` pointer when there are already multiple bugs in the list?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    // Bug not find
    if (current == nullptr) {
        return;
    }
    //delete the first node
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}

```

38. If the list contains only one bug and `deleteBug` is called with that bug's ID, what will the `head` pointer be equal to after the function completes?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                //swap
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

39. In `sortById`, how does the condition `current->next != nullptr` prevent the code from attempting to access a null pointer during the comparison `current->data.id > current->next->data.id`?

---

**`LinkedList.cpp`**

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

40. How does the `loadFromFile` function ensure that it doesn't try to store more than 10 comments, even if the text file record contains more than that?

---

**`LinkedList.cpp`**

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
        file << "||
";
        current = current->next;
    }



    file.close();
};

```

41. Why does the `saveToFile` function use `std::ofstream` instead of `std::ifstream`, and what would happen if the file name provided already existed on the system?

---

**`LinkedList.cpp`**

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

42. How does the `display` function differentiate between different bug records in the console output to make the list readable for the user?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::deleteBug(int bugId) {
    BugNode* current = head;
    BugNode* prev = nullptr;

    while (current != nullptr && current->data.id != bugId) {
        prev = current;
        current = current->next;
    }

    // Bug not find
    if (current == nullptr) {
        return;
    }
    //delete the first node
    if (prev == nullptr) {
        head = current->next;
    }else {
        prev->next = current->next;
    }
    delete current;
}

```

43. If `deleteBug` is called when the list is completely empty, what is the initial value of `current`, and how does the function terminate?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::addBug(const Bug& bug) {

    BugNode* node = new BugNode;

    node->data = bug;
    node->next = nullptr;

    //empty list
    if (head == nullptr) {
        head = node;
        return;
    }
    //find last node
    BugNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
}

```

44. What would happen if the `current = head;` line in `addBug` was accidentally placed inside the `while` loop?

---

**`LinkedList.cpp`**

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

45. In `loadFromFile`, why is it important to call `file.close();` after the `while` loop completes?

---

**`main.cpp`**

```cpp
    // 4. Delete one bug
    list.deleteBug(3);
    std::cout << "\nAfter Deletion:\n";
    list.display();

```

46. How does the requirement to "re-display the list of bugs" after a deletion in requirement 4 get implemented in `main.cpp`?

---

**`LinkedList.cpp`**

```cpp
void LinkedList::sortById() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        BugNode* current = head;

        while (current->next != nullptr) {
            if (current->data.id > current->next->data.id) {
                //swap
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

47. Why is the base case `if (!head) return;` at the start of `sortById` necessary for the stability of the function?

---

**`LinkedList.cpp`**

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

48. If multiple bugs had the same ID, which one would `searchBug` return, and how does this relate to the requirement that the Bug ID be a "Unique Identifier"?

---

**`LinkedList.cpp`**

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
        file << "||
";
        current = current->next;
    }



    file.close();
};

```

49. How does `saveToFile` satisfy requirement 7, which states "Write all bugs in the linked list to the file on application end"?

---

## Broader Questions

50. Based on the overall implementation of `LinkedList.cpp` and `main.cpp`, explain how you ensured that no library data structures (like `std::vector`) were used, and why this demonstrates the core concepts of the PROG2400 course.
