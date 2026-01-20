# Stock-Management-System
A console-based C++ application that implements a warehouse management system with an intuitive menu-driven interface.

## Main Functionality
The application provides a numbered conosole menu where users can choose one of the following options.

```md
- Add a new product to the system
- Search for an existing product
    - by article number
    - by part of the product name
- View all stored products
- Update the quantity of a product
    - adding quantity
    - subtracting quantity
- Remove a product from the system
- Save and Exit
```

## How the system works
The application loads data from a file at startup, processes all changes in memory, and saves them before exiting.

```md
- Data is read from a CSV file when the program starts
- Products are sorted in an unordered_map during runtime
- All user actions modify data in memory first
- Updated data is written back to the CSV file on exit
```

## How to Run 
The aplication is run from te terminal after compilation 

```md
1. Compile the project with C++ compiler( Visual Studio/g++)
2. Ensure the CSV file is in the same directory
3. Run the executable
4. Follow the on-screen menu
```

## Technologies Used
- C++
- Object-Oriented Programming
- Data Structures
- CSV file handling

## What I learned
- Designing a larger C++ project using OOP and data structures
- Working with files and persistent data storage
- Handling exceptions and implementing error reporting

## Future Inprovements 
```md
- Develop a graphical user interface (GUI)
- Connect the system to a database instead using a CSV file
- Add additional functionalities such as filtering and product categories
- Improve input validation and error handling
```

### This project was developed during my summer internship at Kostal.
