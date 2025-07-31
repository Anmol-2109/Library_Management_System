# 📚 C++ Library Management System

A console-based Library Management System built with modern C++ design practices. It uses OOP, SOLID principles, and core design patterns to manage library operations such as issuing and returning books, managing members, and maintaining library ownership control.

---

## 🚀 Tech Stack

- **Language**: C++17
- **Build Tool**: g++ / clang++
- **Execution Environment**: Command-Line Interface (CLI)
- **Architecture**: Object-Oriented + Design Patterns

---

## 🎯 Core Features

- 📖 Manage different types of books (EBook and HardCopy)
- 👥 Handle Members and the Owner of the library
- 📌 Issue and return books
- 🧾 Track issued books per member
- 🚫 Owner can remove members (only if they’ve returned all books)
- 🧩 Extensible structure using abstract base classes

---

## 🧠 Object-Oriented Principles Used

- **Encapsulation**: All data members are private/protected and exposed via public methods.
- **Inheritance**: `Book` → `EBook`, `HardCopy`; `User` → `Member`, `Owner`
- **Polymorphism**: Virtual methods allow dynamic behavior (e.g., book type handling).
- **Abstraction**: Abstract base classes (`Book`, `User`) hide unnecessary implementation details.

---

## 📐 SOLID Principles Applied

| Principle | Description |
|----------|-------------|
| **S** - Single Responsibility | Each class has a single responsibility (e.g., `Book`, `Library`, `Member`) |
| **O** - Open/Closed | Code is open for extension, closed for modification via inheritance and polymorphism |
| **L** - Liskov Substitution | Derived classes (`EBook`, `HardCopy`) can replace their base class `Book` without issues |
| **I** - Interface Segregation | Abstract base classes ensure each user/book type only uses relevant functionality |
| **D** - Dependency Inversion | Strategy pattern decouples issue/return behavior from core classes |

---

## 🏗️ Design Patterns Used

| Pattern | Description |
|--------|-------------|
| **Singleton** | The `Library` class is a singleton — only one instance manages the entire library |
| **Strategy** | Different strategies for issuing/returning books (can be extended if needed) |
| **Factory (Partial)** | Object creation logic for books (`EBook`, `HardCopy`) and users is abstracted in logic blocks (can be fully extended later) |

---

## 📌 UML Diagram (Class Structure)

```plaintext
              +--------------------+
              |      Book          |  <<abstract>>
              +--------------------+
              | -id                |
              | -title             |
              | -author            |
              +--------------------+
              | +displayDetails()  |
              +--------------------+
                 /         \
                /           \
+------------------+   +-------------------+
|     EBook        |   |   HardCopy        |
+------------------+   +-------------------+
| -downloadLink    |   | -shelfNumber      |
+------------------+   +-------------------+
| +displayDetails()|   | +displayDetails() |
+------------------+   +-------------------+

              +---------------------+
              |       User          | <<abstract>>
              +---------------------+
              | -id                 |
              | -name               |
              +---------------------+
              | +displayInfo()      |
              +---------------------+
                  /         \
                 /           \
+-------------------+   +--------------------+
|      Member       |   |       Owner        |
+-------------------+   +--------------------+
| -borrowedBooks[]  |   |                    |
+-------------------+   +--------------------+
| +borrowBook()     |   | +add/remove member |
| +returnBook()     |   | +view stats        |
+-------------------+   +--------------------+

                +-------------------+
                |     Library       | <<Singleton>>
                +-------------------+
                | -books[]          |
                | -members[]        |
                | -owner            |
                +-------------------+
                | +getInstance()    |
                | +addBook()        |
                | +issueBook()      |
                | +removeMember()   |
                +-------------------+

```

---

## 📈 Future Improvements

- 🧑‍💻 Admin/Staff Roles: Introduce additional roles like Librarian or Staff, with permission levels between Owner and Member, for tasks like issuing books or managing daily operations.
- 🗃️ Persistent Storage: Replace in-memory storage with file I/O or a database (like SQLite or MySQL) to persist library data between sessions.
- 🌐 GUI Support: Build a lightweight GUI using libraries like Qt or ImGui to make it more user-friendly than the CLI.
- 🔒 Role-Based Access Control (RBAC): Strengthen access checks through an RBAC system to restrict features by user role more securely.

---

## Author

- Anmol kumar
- linkedin - https://www.linkedin.com/in/anmol-kumar-1ba37b324/
