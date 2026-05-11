
# PROG2400 Supplementary Assignment — Bug Tracking Application

## Introduction
Your task is to create the beginnings of a bug tracking application to demonstrate major concepts from the course.
The application will maintain a list of bugs that are stored in a text file with the following format.

## Bug File Format
    `<Bug ID#>|<Date Added>|<Brief Desc>|<Detailed Desc>|<Status>|<Severity>|<Comment>|<Comment>|…||`

Bug ID#: Bug Unique Identifier
Date Added: The date the bug was created.
Brief Desc.: A brief description of the bug.
Detailed Desc.: A complete description of the bug.
Status: One of four different statuses: (OPEN, CLOSED, IN PROGRESS, WAITING)
Severity: One of four different severities: (LOW, MEDIUM, HIGH, CRITICAL)
Comments: Zero or more comments on the bug.

## Notes:
  • Each field is separated by a single pipe symbol. (|)
  • The comment fields are optional. All others are mandatory.
  • The entire record ends with a double pipe symbol. (||)

## Example:
  BUG0001|04-19-2024|Sample Bug #1|This is bug number one.|OPEN|HIGH|comment 1|comment 2||
  BUG0003|04-19-2024|Sample Bug #3|This is bug number three.|CLOSED|HIGH|Initial comment|Another comment||
  BUG0004|04-19-2024|Sample Bug #1|This is bug number one.|OPEN|HIGH||
  BUG0005|04-19-2024|Sample Bug #2|This is bug number two.|OPEN|LOW|Initial comment.|Second comment.||
  BUG0006|04-19-2024|Sample Bug #3|This is bug number three.|CLOSED|HIGH|Initial comment|Another comment||

## Application Requirements
1. Read all bugs stored in the file into a linked list on application start.
2. Add five (5) new bugs with varying contents.
3. Display the list of bugs ordered by bug id to the console.
4. Delete one (1) bug based on its bug id # and re-display the list of bugs.
5. Sort the bugs by status and re-display the list of bugs.
6. Search the list of bugs for one, based on its id, and display the details of that bug.
7. Write all bugs in the linked list to the file on application end.
8. You cannot use library data structures (e.g. vector) to perform any functionality.
9. You can use standard datatypes (e.g. string), and you are allowed to use code that was provided to you.
