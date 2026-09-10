# QN.5 Draw the Object Diagram for Library Management System

## Object Diagram

An **Object Diagram** is a UML diagram that represents a snapshot of a system at a particular moment in time. It shows objects (instances of classes), their attribute values, and the relationships between them.

### Components of Object Diagram

* **Object:** An instance of a class.
* **Attribute Value:** Actual data stored in an object.
* **Link:** Connection between objects.
* **Instance:** A real-world occurrence of a class.

---

## Object Diagram for Library Management System

The Object Diagram shows actual instances of Member, Book, Librarian, Transaction, and Fine objects and their relationships during a book borrowing process.

```mermaid id="n5r2pk"
classDiagram

    class member1 {
        memberId = 101
        name = "Ram Sharma"
        email = "ram@gmail.com"
    }

    class book1 {
        bookId = 501
        title = "Software Engineering"
        author = "Ian Sommerville"
    }

    class librarian1 {
        librarianId = 1
        name = "Hari Prasad"
    }

    class transaction1 {
        transactionId = 1001
        issueDate = "2025-09-01"
        dueDate = "2025-09-15"
    }

    class fine1 {
        fineId = 201
        amount = 50
    }

    member1 --> transaction1 : borrows
    book1 --> transaction1 : issued
    librarian1 --> transaction1 : manages
    transaction1 --> fine1 : generates
```

---

## Object Description

* **member1** represents a library member named Ram Sharma.
* **book1** represents the book "Software Engineering".
* **librarian1** manages the transaction.
* **transaction1** records the issue details of the book.
* **fine1** represents the fine generated for late return.

---

## Conclusion

The Object Diagram provides a snapshot of the Library Management System at a specific time by showing actual objects and their relationships. It helps in understanding how class instances interact during system execution.
