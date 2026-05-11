# PROG2400 Answer Sheet: Bug Tracking Application

1. The struct uses a fixed-size array `comments[10]` to avoid dynamic library structures like `vector`, while the `commentCount` tracks the actual number of comments provided (from zero up to 10).
2. The `next` pointer holds the address of the following `BugNode`, enabling the linked list to connect disparate memory allocations together into a logical sequence.
3. Designating `head` as `private` ensures that external code cannot accidentally break the list's structure by modifying the pointer directly; only class methods can safely manage the links.
4. Setting `head` to `nullptr` explicitly signals that the linked list is currently empty when the object is created.
5. It iterates through every node, stores the location of the next node before deleting the current one, and finally sets `head` to `nullptr` to clear the list.
6. If `head` is null, the list is empty; trying to access `current->next` would cause a null pointer dereference crash.
7. It links the `next` pointer of the current last node to the newly created node, extending the chain.
8. By setting `prev->next` to `current->next`, the function bypasses the `current` node, essentially removing it from the sequence while keeping the rest of the list intact.
9. If the search loop completes and `current` is `nullptr`, the function simply returns without attempting any deletion.
10. Returning a pointer allows direct access to the bug data in the list (e.g., to print or update it) without the memory/time overhead of creating a duplicate object.
11. It uses a `for` loop that iterates up to `current->data.commentCount`.
12. Swapping the entire `Bug` data structure ensures that all data associated with that bug (ID, descriptions, status, etc.) stays grouped together during the sort.
13. If no swaps occur during a full traversal of the list, `swapped` remains `false`, indicating the list is fully ordered and the loop can terminate.
14. It sorts alphabetically based on the string values of the statuses (e.g., "CLOSED" comes before "OPEN").
15. It must be reset for every individual bug record being parsed so that comments from the previous record aren't accidentally carried over.
16. The code enters a `while` loop that reads additional tokens from the stringstream until it hits an empty field or the end of the line, allowing for any number of comments (up to 10).
17. `stringstream` allows the code to split a single string record into multiple pipe-delimited fields using `getline` in memory, which is safer and easier than parsing directly from a complex file stream.
18. It manually writes the `||` characters after the comments loop to signify the end of the record as required by the format.
19. It uses a `while` loop to traverse from `head` through every `next` pointer until it reaches the end (`nullptr`), ensuring every node in the dynamic list is saved.
20. `main.cpp` calls methods in order: `loadFromFile`, `addBug` x5, `sortById` and `display`, `deleteBug` and `display`, `sortByStatus` and `display`, `searchBug`, and `saveToFile`.
21. `searchBug` returns `nullptr` if the ID is not found; attempting to access members of `nullptr` would cause a segmentation fault crash.
22. If `prev` is `nullptr`, it means the bug to be deleted was the first one; therefore, `head` is updated to point to `current->next`.
23. By using `new BugNode;`, memory is manually allocated on the heap at runtime, allowing the list to grow dynamically without using pre-built library containers.
24. `stoi` converts the string token into an integer so it can be stored in the `int id` member defined in the struct.
25. `const` ensures the function is read-only regarding the list's members, guaranteeing that saving data to a file does not accidentally modify or delete the bugs in memory.
26. The pointer `current` is updated in each iteration to the address of the following node until it reaches the `nullptr` terminator.
27. The loop would execute exactly once (the `swapped` flag would remain false, and it would exit).
28. The program would crash or exhibit undefined behavior because you cannot safely access `current->next` after the memory for `current` has already been deleted.
29. Without setting it to `nullptr`, the new last node would contain a garbage memory address, causing future traversals to attempt accessing invalid memory.
30. It acts as the "not found" or "end of list" check; it stops the loop if the entire list has been searched without finding the target ID.
31. It reads 6 specific mandatory fields first, then enters a loop to read any remaining delimited fields as comments.
32. The loop `for (int i = 0; i < current->data.commentCount; i++)` ensures the output file only contains valid comment strings rather than empty array slots.
33. It only reorganizes the `Bug` data; the physical nodes and their `next` pointer connections remain in the same locations in memory.
34. It returns the address of the bug, allowing `main.cpp` to access and print the `briefDesc` and other details.
35. The requirement uses a double pipe `||` to end records; `loadFromFile` checks `if (comment.empty()) break;` to stop parsing when it encounters the empty field created by the final `||` sequence.
36. This ensures that the 5 new bugs are added to the list of existing bugs retrieved from the file.
37. The code uses a separate `current` pointer to traverse to the end of the list; the `head` pointer is only modified if the list was initially empty.
38. The `head` pointer will be set to `nullptr` because `current->next` (the next node) was `nullptr`.
39. It ensures that the loop stops at the last node, meaning `current->next` is guaranteed to be a valid pointer before it is dereferenced in the comparison.
40. The check `if (bug.commentCount < 10)` prevents the code from writing to indices outside the bounds of the `comments` array.
41. `ofstream` is for writing (Output File Stream). If the file exists, it is typically overwritten by default, refreshing the data as required on application end.
42. It prints a line of dashes `-------------------------` after every bug record is displayed.
43. `current` is initialized to `head` (which is `nullptr`); the `while` loop condition fails immediately, and the function returns.
44. It would create an infinite loop because the traversal pointer `current` would be reset to the beginning of the list every time it tried to move forward.
45. Closing the file ensures all buffered data is physically written to the disk and releases the file handle back to the operating system.
46. It calls `list.display();` immediately after the `list.deleteBug(3);` call.
47. Without it, attempting to access `current->next` on a null `head` would crash the application.
48. It would return the first one it finds; however, the specification requires the ID to be a "Unique Identifier," implying there should not be duplicates.
49. It traverses the entire linked list from `head` to `nullptr`, writing each bug record in the correct pipe-delimited format to the file.
50. By manually defining structs with pointers (`BugNode`), using heap allocation (`new`/`delete`), and traversing the list with loops, the student demonstrates fundamental Data Structures knowledge without relying on high-level library abstractions.
