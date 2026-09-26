# QN.1 Write the DFD for Library Management System

## Data Flow Diagram (DFD)

A **Data Flow Diagram (DFD)** is a graphical representation of how data moves through a system. It shows the flow of data between external entities, processes, and data stores.

### Components of DFD

* **External Entity:** Source or destination of data outside the system.
* **Process:** Activity that transforms input data into output data.
* **Data Store:** Repository where data is stored.
* **Data Flow:** Movement of data between entities, processes, and data stores.

---

## Level 0 DFD (Context Diagram)

The Level 0 DFD represents the entire Library Management System as a single process and shows its interaction with external entities such as Member, Librarian, and Administrator.

```mermaid
graph TD

    Member["Member / Student"]
    Librarian["Librarian"]
    Admin["Administrator"]

    LMS(("0.0 Library Management System"))

    Member -->|Search / Issue /<br/> Return Request| LMS
    LMS -->|Search Result / Issue <br/> Details / Fine Information| Member

    Librarian -->|Book Updates /<br/> Transaction Approval| LMS
    LMS -->|Inventory Status /<br/> Reports| Librarian

    Admin -->|Configuration &<br/> User Management| LMS
    LMS -->|Audit Logs & Reports| Admin
```

---

## Level 1 DFD

The Level 1 DFD decomposes the Library Management System into major processes such as User Management, Catalog & Search, Book Issue & Return, and Fine Management. It also shows the data stores used by these processes.

```mermaid id="v5y2ui"
%%{init: {'themeVariables': { 'fontSize': '26px' }}}%%
graph TD

    Member["Member"]
    Librarian["Librarian"]

    P1(("1.0 User Management"))
    P2(("2.0 Catalog & Search"))
    P3(("3.0 Book Issue & Return"))
    P4(("4.0 Fine Management"))

    D1[("D1 Member Database")]
    D2[("D2 Book Database")]
    D3[("D3 Transaction Records")]
    D4[("D4 Fine Records")]

    Member -->|Registration<br/>Details| P1
    P1 -->|Member Data| D1
    D1 -->|Member<br/>Information| P1

    Member -->|Search Request| P2
    P2 -->|Book Query| D2
    D2 -->|Book Details| P2
    P2 -->|Search Result| Member

    Librarian -->|Book Updates| P2
    P2 -->|Updated Book<br/>Records| D2

    Member -->|Issue / Return<br/>Request| P3
    P3 -->|Member Verification<br/>Request| D1
    D1 -->|Member Status| P3

    P3 -->|Book Availability<br/>Request| D2
    D2 -->|Book Availability<br/>Details| P3

    P3 -->|Transaction<br/>Record| D3
    P3 -->|Issue Slip /<br/>Confirmation| Member

    Librarian -->|Approve<br/>Transaction| P3

    D3 -->|Overdue<br/>Information| P4

    P4 -->|Fine Notice| Member
    Member -->|Fine Payment| P4

    P4 -->|Fine Record| D4
    P4 -->|Receipt| Member
```

This keeps the DFD exactly the same while making it noticeably taller on the page.

---

## Conclusion

The Level 0 DFD provides a high-level view of the Library Management System and its interaction with external entities. The Level 1 DFD provides a detailed view of the internal processes, data stores, and data flows involved in managing library operations.
