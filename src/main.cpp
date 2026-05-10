#include <iostream>


#include "LinkedList.h"

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