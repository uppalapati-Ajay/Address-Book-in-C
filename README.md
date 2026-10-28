# 📒 Address Book Management System in C

A menu-driven **Address Book Management System** developed using the C programming language to manage contact information efficiently. The application allows users to create, search, edit, delete, display, and sort contacts through an interactive console interface.

The project demonstrates practical implementation of **C programming, structures, functions, string manipulation, input validation, sorting algorithms, and file handling**.

## 📌 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Project Structure](#-project-structure)
- [How It Works](#-how-it-works)
- [Input Validation](#-input-validation)
- [Sorting Mechanism](#-sorting-mechanism)
- [File Handling](#-file-handling)
- [Compilation and Execution](#-compilation-and-execution)
- [Sample Execution](#-sample-execution)
- [Learning Outcomes](#-learning-outcomes)
- [Future Improvements](#-future-improvements)
- [Author](#-author)

## 🚀 About the Project

The Address Book Management System is a console-based application designed to simplify contact management. It provides a menu-driven interface through which users can perform different operations on stored contact details.

Each contact contains three fields:

- **Name:** Contact person's name
- **Phone:** Contact phone number
- **Email:** Contact email address

The application uses structures to organize contact information, functions to separate program operations, and file handling to save and load contacts between program executions.

The project also includes validation checks to reduce invalid entries and prevent duplicate names, phone numbers, and email addresses.

## ✨ Features

### 1. Add Contact
- Add a new contact to the address book.
- Validate the entered name, phone number, and email address.
- Prevent duplicate contact details.
- Save the updated contact list to a file.

### 2. Search Contact
- Search contacts by name.
- Search contacts by phone number.
- Search contacts by email address.
- Display matching contacts and allow the user to select a result.

### 3. Edit Contact
- Select an existing contact.
- Update the name, phone number, and email address.
- Validate the updated information before saving.

### 4. Delete Contact
- Select the contact to be deleted.
- Confirm the deletion before proceeding.
- Rearrange the remaining contacts after deletion.
- Save the updated contact list.

### 5. Display and Sort Contacts
- Display the stored contacts in a formatted table.
- Sort contacts alphabetically by name.
- Sort contacts by phone number.
- Sort contacts by email address.

### 6. Data Persistence
- Save contact details in a text file.
- Load previously saved contacts when the application starts.
- Retain contact information between program executions.

### 7. Input Validation
- Check name format and minimum letter count.
- Validate phone number length and digits.
- Validate email format according to the project's rules.
- Prevent duplicate names, phone numbers, and email addresses.

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C Programming | Core application development |
| Structures | Organizing contact information |
| Functions | Modular program design |
| Arrays | Storing multiple contacts |
| Strings | Processing names, phone numbers, and emails |
| Pointers | Passing the address book to functions |
| File Handling | Saving and loading contact records |
| String Library | Comparing and copying strings |
| Character Handling | Validating characters |
| Bubble Sort | Sorting contact records |
| Makefile | Managing the build process |

## 📂 Project Structure

```text
Address-Book-in-C/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── Makefile
├── README.md
└── .gitignore
```

**File descriptions:**

- `main.c` — Contains the main function, menu display, and user interaction.
- `contact.c` — Implements contact creation, searching, editing, deletion, sorting, and validation.
- `contact.h` — Defines the contact structures, maximum contact count, and function declarations.
- `file.c` — Implements saving contacts to a file and loading contacts at startup.
- `file.h` — Contains declarations for the file-handling functions.
- `populate.c` — Provides sample contacts for initial population when no saved contacts are loaded.
- `populate.h` — Declares the sample-contact population function.
- `Makefile` — Contains build instructions for compiling the project.
- `README.md` — Documents the project and explains how to use it.
- `.gitignore` — Specifies files that should not be tracked by Git.

**Note:** The program creates or uses `contacts.txt` at runtime to store contact information. This data file is not required to be included in the public repository.

## ⚙️ How It Works

The application follows a menu-driven approach.

1. Initialize the address book.
2. Load previously saved contacts from the data file.
3. Populate sample contacts if no contacts are loaded.
4. Display the main menu.
5. Accept the user's choice.
6. Execute the selected contact management operation.
7. Save changes when contacts are added, edited, or deleted.
8. Continue until the user selects Exit.

### Main Menu

```text
╔═════════════════════════════════════════════╗
║              ADDRESS BOOK                   ║
╠═════════════════════════════════════════════╣
║  1. Add Contact                             ║
║  2. Search Contact                          ║
║  3. Edit Contact                            ║
║  4. Delete Contact                          ║
║  5. List / Sort Contacts                    ║
║  6. Exit                                    ║
╚═════════════════════════════════════════════╝
```

## 🔐 Input Validation

The project implements validation functions to check the information entered by the user.

### Name Validation
- The name must not be empty.
- The name must contain at least three alphabetic characters.
- Only alphabetic characters and spaces are accepted.
- Duplicate names are rejected.

### Phone Number Validation
- The phone number must contain exactly ten digits.
- The first digit must be between 6 and 9.
- Only numeric digits are accepted.
- Duplicate phone numbers are rejected.

### Email Validation
- The email must not be empty.
- Exactly one `@` symbol is required.
- Exactly one dot is allowed.
- Characters must appear before `@`, between `@` and `.`, and after the dot.
- Only lowercase letters, digits, `@`, and `.` are accepted.
- The email must end with `.com`.
- Duplicate email addresses are rejected.

These checks follow the validation rules implemented in the current project and are not intended to cover every valid real-world email address.

## 🔄 Sorting Mechanism

The application uses the **Bubble Sort algorithm** to arrange contacts according to the selected field.

Available sorting options:

- Sort by name
- Sort by phone number
- Sort by email address

The program compares adjacent contact fields and swaps the corresponding contact records when they are out of order.

**Time complexity:** Bubble Sort has an average and worst-case time complexity of \(O(n^2)\), making it suitable for understanding sorting with the project's limited contact capacity.

## 💾 File Handling

File handling is used to preserve contact information between executions.

### Saving Contacts
- Opens `contacts.txt` in write mode.
- Writes each contact's name, phone number, and email separated by commas.
- Closes the file after writing.

### Loading Contacts
- Opens `contacts.txt` in read mode when the program starts.
- Reads stored contact records.
- Loads records into the address book until the file ends or the contact limit is reached.
- Uses sample contacts if no records are loaded.

The application supports a maximum of **100 contacts**, as defined by `MAX_CONTACTS`.

## 💻 Compilation and Execution

### Prerequisites

- A C compiler such as GCC.
- A terminal or command prompt.
- Make, if you want to use the provided Makefile.

### Compile Using GCC

From the project directory, run:

```bash
gcc main.c contact.c file.c populate.c -o address_book
```

### Run on Linux

```bash
./address_book
```

### Run on Windows

```bash
address_book.exe
```

### Compile Using Makefile

If your Makefile defines the appropriate build target, run:

```bash
make
```

Then execute the generated program according to the target and output filename defined in the Makefile.

## 🧪 Sample Execution

```text
Enter your choice: 1

CREATE NEW CONTACT

Enter name: Ravi Kumar
Enter phone number: 9876543210
Enter email: ravi@example.com

Contact created successfully!
```

The application validates each field before creating the contact. If a value does not satisfy the project's validation rules or already exists, an error message is displayed and the user is prompted again.

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Writing modular C programs using functions.
- Defining and using structures.
- Working with arrays, pointers, and strings.
- Implementing Create, Read, Update, and Delete (CRUD) operations.
- Performing input validation and duplicate checking.
- Implementing Bubble Sort.
- Reading from and writing to text files.
- Managing source files using header files.
- Compiling and organizing a multi-file C application.
- Using GitHub for source code management and project presentation.

## 🔮 Future Improvements

Potential enhancements for future versions include:

- Case-insensitive duplicate detection.
- More flexible email validation.
- Improved handling of malformed or corrupted data files.
- Confirmation and recovery options for data-changing operations.
- Search by partial name and more advanced search filters.
- Improved portability of the console interface.
- Unit tests for validation and contact management functions.

## 👨‍💻 Author

**Ajay Uppalapati**

Electronics and Communication Engineering graduate interested in Embedded Systems, C Programming, Linux, and software development.

### Connect With Me

- GitHub: [uppalapati-Ajay](https://github.com/uppalapati-Ajay)
- LinkedIn: www.linkedin.com/in/ajay-uppalapati-06865124b

---

If you find this project useful for learning C programming, feel free to explore the source code and suggest improvements.
