# QN.6 Draw the Component Diagram for Library Management System

## Component Diagram

A **Component Diagram** is a UML structural diagram that shows the organization and dependencies among software components of a system. It illustrates how different modules interact to provide system functionality.

### Components of Component Diagram

* **Component:** A modular part of the system that provides specific functionality.
* **Interface:** A point through which components communicate.
* **Dependency:** Relationship showing one component depends on another.
* **Connection:** Communication path between components.

---

## Component Diagram for Library Management System

The Library Management System consists of components such as User Management, Catalog Management, Transaction Management, Fine Management, and Database components that work together to provide library services.

 # use https://plantuml.com/ to render


@startuml

actor User

component "User Interface" as UI

component "User Management" as UM
component "Catalog Management" as CM
component "Transaction Management" as TM
component "Fine Management" as FM

database "Library Database" as DB

User --> UI

UI --> UM
UI --> CM
UI --> TM
UI --> FM

UM --> DB
CM --> DB
TM --> DB
FM --> DB

@enduml


---

## Component Description

The User Interface allows users to interact with the Inventory Management System. Product Management manages product information, Stock Management handles inventory updates, Order Management processes customer orders and invoices, and Report Management generates inventory and sales reports. All related data is stored in the Inventory Database.

---

## Conclusion

The Component Diagram shows the major software modules of the Library Management System and their dependencies. It helps in understanding the overall software architecture and module interactions.

---