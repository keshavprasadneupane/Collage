# QN.4 Draw the Class Diagram for Library Management System

## Class Diagram

A **Class Diagram** is a structural UML diagram that represents the classes of a system, their attributes, methods, and relationships. It provides a blueprint of the system's structure and is widely used during object-oriented design.

### Components of Class Diagram

* **Class:** Represents an object or entity in the system.
* **Attribute:** Data members of a class.
* **Method:** Functions or operations performed by a class.
* **Association:** Relationship between classes.
* **Multiplicity:** Specifies how many objects participate in a relationship.

---

## Class Diagram for Library Management System

The Library Management System consists of classes such as Member, Book, Librarian, Transaction, and Fine. These classes interact to perform book issue, return, and fine management operations.

```mermaid
classDiagram

    class Member {
        +int memberId
        +string name
        +string email
        +string phone
        +searchBook()
        +borrowBook()
        +returnBook()
    }

    class Book {
        +int bookId
        +string title
        +string author
        +string publisher
        +int quantity
        +checkAvailability()
    }

    class Librarian {
        +int librarianId
        +string name
        +string email
        +addBook()
        +updateBook()
        +removeBook()
    }

    class Transaction {
        +int transactionId
        +date issueDate
        +date dueDate
        +date returnDate
        +issueBook()
        +returnBook()
    }

    class Fine {
        +int fineId
        +float amount
        +calculateFine()
        +payFine()
    }

    Member "1" --> "0..*" Transaction : performs
    Book "1" --> "0..*" Transaction : involved_in
    Librarian "1" --> "0..*" Transaction : manages
    Transaction "1" --> "0..1" Fine : generates
```

---

## Class Description

* **Member** stores member information and performs borrowing and returning operations.
* **Book** stores book details and availability information.
* **Librarian** manages book records and library operations.
* **Transaction** records issue and return details of books.
* **Fine** stores overdue fine information and payment details.

---

## Conclusion

The Class Diagram represents the static structure of the Library Management System by showing classes, their attributes, methods, and relationships. It serves as the foundation for object-oriented design and implementation.
