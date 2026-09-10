# QN.2 Draw the ER Diagram for Inventory Management System

## Entity Relationship (ER) Diagram

An **Entity Relationship (ER) Diagram** is a graphical representation of the entities, attributes, and relationships in a database system. It helps in designing and organizing the database structure.

### Components of ER Diagram

* **Entity:** A real-world object about which data is stored.
* **Attribute:** A property or characteristic of an entity.
* **Primary Key (PK):** Uniquely identifies each record.
* **Foreign Key (FK):** Connects one entity with another.
* **Relationship:** Shows the association between entities.

---

## ER Diagram for Inventory Management System

The main entities are **Product, Supplier, Customer, Order, and Inventory**. These entities maintain information about products, stock, suppliers, and customer orders.

```mermaid id="q4v8zn"
erDiagram

    PRODUCT {
        int product_id PK
        string name
        string category
        float price
    }

    INVENTORY {
        int inventory_id PK
        int product_id FK
        int quantity
        string stock_status
    }

    SUPPLIER {
        int supplier_id PK
        string name
        string contact
        string address
    }

    CUSTOMER {
        int customer_id PK
        string name
        string phone
        string email
    }

    ORDER {
        int order_id PK
        int customer_id FK
        int product_id FK
        int quantity
        date order_date
    }

    PRODUCT ||--|| INVENTORY : has
    SUPPLIER ||--o{ PRODUCT : supplies
    CUSTOMER ||--o{ ORDER : places
    PRODUCT ||--o{ ORDER : included_in
```

---

## Relationship Description

* A **Product** has a corresponding inventory record that stores its stock information.
* A **Supplier** can supply multiple products.
* A **Customer** can place multiple orders.
* A **Product** can be included in multiple orders.

---

## Conclusion

The ER Diagram represents the database structure of the Inventory Management System by showing its main entities, attributes, and relationships. It provides a clear foundation for designing the system database.
