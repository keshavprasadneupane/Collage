# QN.1 Write the DFD for Inventory Management System

## Data Flow Diagram (DFD)

A **Data Flow Diagram (DFD)** is a graphical representation of the flow of data through an information system. It shows how data enters the system, how it is processed, where it is stored, and how it is delivered to users.

### Components of DFD

* **External Entity:** Source or destination of data outside the system.
* **Process:** Activity that transforms input data into output data.
* **Data Store:** Place where data is stored.
* **Data Flow:** Movement of data between entities, processes, and data stores.

---

## Level 0 DFD (Context Diagram)

The Level 0 DFD represents the entire Inventory Management System as a single process and shows its interaction with external entities such as Supplier, Manager, and Customer.

```mermaid
graph TD

    Supplier["Supplier"]
    Manager["Manager"]
    Customer["Customer"]

    IMS(("0.0 Inventory Management System"))

    Supplier -->|Product Supply Information| IMS
    IMS -->|Purchase Orders| Supplier

    Manager -->|Inventory Updates / Requests| IMS
    IMS -->|Inventory Reports| Manager

    Customer -->|Product Purchase Request| IMS
    IMS -->|Product Availability / Invoice| Customer
```

---

## Level 1 DFD

The Level 1 DFD decomposes the Inventory Management System into major processes such as Product Management, Stock Management, Order Management, and Report Generation along with their respective data stores.

```mermaid
graph TD

    Supplier["Supplier"]
    Manager["Manager"]
    Customer["Customer"]

    P1(("1.0 Product Management"))
    P2(("2.0 Stock Management"))
    P3(("3.0 Order Management"))
    P4(("4.0 Report Generation"))

    D1[("D1 Product Database")]
    D2[("D2 Stock Database")]
    D3[("D3 Order Records")]
    D4[("D4 Supplier Records")]

    Manager -->|Add / Update Product| P1
    P1 --> D1
    D1 --> P1

    Supplier -->|Supply Details| P2
    P2 --> D2
    P2 --> D4

    Customer -->|Purchase Request| P3
    P3 --> D1
    D1 --> P3

    P3 --> D2
    D2 --> P3

    P3 --> D3
    P3 -->|Invoice / Confirmation| Customer

    Manager -->|Report Request| P4
    P4 --> D1
    P4 --> D2
    P4 --> D3
    P4 -->|Inventory Report| Manager
```

---

## Conclusion

The Level 0 DFD provides an overall view of the Inventory Management System and its interaction with external entities. The Level 1 DFD shows the internal processes, data stores, and data flow involved in managing products, stock, orders, and reports.
