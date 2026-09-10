# QN.3 Draw the Use Case Diagram for Library Management System

## Use Case Diagram

A **Use Case Diagram** is a behavioral diagram in UML that represents the interactions between users (actors) and a system. It shows the functionalities provided by the system and identifies who can access them.

### Components of Use Case Diagram

* **Actor:** A person or external system that interacts with the system.
* **Use Case:** A function or service provided by the system.
* **System Boundary:** Defines the scope of the system.
* **Association:** Interaction between an actor and a use case.

---

## Use Case Diagram for Library Management System

The Library Management System allows members to search, borrow, and return books. Librarians manage books and transactions, while administrators manage users and system settings.

```mermaid
flowchart LR

    Member[👤 Member]

    subgraph LMS[Library Management System]
        direction LR

        UC1((Register))
        UC2((Search Book))
        UC3((Issue Book))
        UC4((Return Book))
        UC5((Pay Fine))

        UC6((Manage Books))
        UC7((Manage Transactions))
        UC8((Generate Reports))

        UC9((Manage Users))
        UC10((Configure System))

        UC1 ~~~ UC2 ~~~ UC3 ~~~ UC4 ~~~ UC5
        UC6 ~~~ UC7 ~~~ UC8
        UC9 ~~~ UC10
    end

    Librarian[🧑‍💼 Librarian]
    Admin[⚙️ Administrator]

    Member --- UC1
    Member --- UC2
    Member --- UC3
    Member --- UC4
    Member --- UC5

    Librarian --- UC2
    Librarian --- UC6
    Librarian --- UC7
    Librarian --- UC8

    Admin --- UC8
    Admin --- UC9
    Admin --- UC10
```

---

## Use Case Description

* **Member** can register, search books, issue books, return books, and pay fines.
* **Librarian** manages books, handles issue/return transactions, and generates reports.
* **Administrator** manages users, configures the system, and monitors reports.
* All use cases are performed within the Library Management System boundary.

---

## Conclusion

The Use Case Diagram provides a high-level view of the functionalities offered by the Library Management System and the interactions of different actors with those functionalities. It helps in understanding system requirements from the user's perspective.
