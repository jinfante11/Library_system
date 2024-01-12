#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

struct LibraryMember {
    int id;
    std::string name;
    std::string address;
    std::vector<int> borrowedBooks;
};

struct LibraryBook {
    int bookId;
    std::string title;
    std::string authorFirstName;
    std::string authorLastName;
    bool isBorrowed;
    time_t dueDate;
    std::string bookType;
};


// Function to add a new member to the library
void addMember(std::vector<LibraryMember>& members, int id, const std::string& name, const std::string& address) {
    LibraryMember newMember = {id, name, address};
    members.push_back(newMember);
    std::cout << "Member added successfully.\n";
    // Display the details of the new member
    std::cout << "Member Details:\n";
    std::cout << "ID: " << id << ", Name: " << name << ", Address: " << address << "\n";
}


// Function to add a new book to the library
void addBook(std::vector<LibraryBook>& books, int bookId, const std::string& title, const std::string& authorFirstName,
             const std::string& authorLastName, int pageCount, const std::string& bookType) {
    LibraryBook newBook = {bookId, title, authorFirstName, authorLastName, pageCount, false, 0, bookType};
    books.push_back(newBook);
    std::cout << "Book added successfully.\n";
    // Display the details of the new book
    std::cout << "Book Details:\n";
    std::cout << "ID: " << bookId << ", Title: " << title << ", Author: " << authorFirstName << " " << authorLastName
              << ", Page Count: " << pageCount << ", Type: " << bookType << "\n";
}


// Function to issue a book to a member
void issueBook(std::vector<LibraryBook>& books, std::vector<LibraryMember>& members, int memberId, int bookId) {
    for (auto& book : books) {
        if (book.bookId == bookId && !book.isBorrowed) {
            book.isBorrowed = true;
            book.dueDate = std::time(0) + 3 * 24 * 60 * 60; // Due date is set to 3 days from the issue date

            for (auto& member : members) {
                if (member.id == memberId) {
                    member.borrowedBooks.push_back(bookId);
                    std::cout << "Book issued successfully.\n";
                    return;
                }
            }
        }
    }

    std::cout << "Book not available or invalid member ID.\n";
}


// Function to return a book from a member
void returnBook(std::vector<LibraryBook>& books, std::vector<LibraryMember>& members, int memberId, int bookId) {
    for (auto& book : books) {
        if (book.bookId == bookId && book.isBorrowed) {
            book.isBorrowed = false;

            for (auto& member : members) {
                if (member.id == memberId) {
                    auto it = std::find(member.borrowedBooks.begin(), member.borrowedBooks.end(), bookId);
                    if (it != member.borrowedBooks.end()) {
                        member.borrowedBooks.erase(it);
                        std::cout << "Book returned successfully.\n";

                        // Check for overdue and calculate fine
                        time_t currentDate = std::time(0);
                        if (currentDate > book.dueDate) {
                            int daysOverdue = static_cast<int>((currentDate - book.dueDate) / (24 * 60 * 60));
                            int fine = daysOverdue * 1; // £1 per day overdue
                            std::cout << "Fine calculated for overdue: £" << fine << "\n";
                        }

                        return;
                    }
                }
            }
        }
    }

    std::cout << "Book not found or not borrowed by the given member.\n";
}


// Function to display all books borrowed by a member
void displayBorrowedBooks(const std::vector<LibraryMember>& members, int memberId) {
    for (const auto& member : members) {
        if (member.id == memberId) {
            if (member.borrowedBooks.empty()) {
                std::cout << "No books borrowed by this member.\n";
            } else {
                std::cout << "Books borrowed by Member " << memberId << ":\n";
                for (int bookId : member.borrowedBooks) {
                    std::cout << "Book ID: " << bookId << "\n";
                }
            }
            return;
        }
    }

    std::cout << "Member not found.\n";
}


// Function to calculate fines for overdue books
void calculateFine(const std::vector<LibraryBook>& books, const std::vector<LibraryMember>& members, int memberId) {
    for (const auto& member : members) {
        if (member.id == memberId) {
            for (int bookId : member.borrowedBooks) {
                for (const auto& book : books) {
                    if (book.bookId == bookId && book.isBorrowed) {
                        time_t currentDate = std::time(0);
                        if (currentDate > book.dueDate) {
                            int daysOverdue = static_cast<int>((currentDate - book.dueDate) / (24 * 60 * 60));
                            int fine = daysOverdue * 1; // £1 per day overdue
                            std::cout << "Fine for Book ID " << bookId << ": £" << fine << "\n";
                        }
                    }
                }
            }
            return;
        }
    }

    std::cout << "Member not found.\n";
}


int main() {
    std::vector<LibraryMember> libraryMembers;
    std::vector<LibraryBook> libraryBooks;

    std::cout << "Welcome, Librarian!\n";

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add a Member\n";
        std::cout << "2. Issue a Book\n";
        std::cout << "3. Return a Book\n";
        std::cout << "4. Display Borrowed Books by a Member\n";
        std::cout << "5. Calculate Fine\n";
        std::cout << "6. Exit\n";

        int choice;
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::string name, address;
                std::cout << "Enter Member ID: ";
                std::cin >> id;
                std::cin.ignore(); // Clear the newline character from the buffer
                std::cout << "Enter Member Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Member Address: ";
                std::getline(std::cin, address);

                addMember(libraryMembers, id, name, address);
                break;
            }
            case 2:
                // Call function to issue a book
                int memberId, bookId;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter Book ID: ";
                std::cin >> bookId;

                issueBook(libraryBooks, libraryMembers, memberId, bookId);
                break;
            case 3:
                // Call function to return a book
                int memberId, bookId;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;
                std::cout << "Enter Book ID: ";
                std::cin >> bookId;

                returnBook(libraryBooks, libraryMembers, memberId, bookId);
                break;
            case 4:
                // Call function to display borrowed books
                int memberId;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;

                displayBorrowedBooks(libraryMembers, memberId);
                break;
            case 5:
                // Call function to calculate fines
                int memberId;
                std::cout << "Enter Member ID: ";
                std::cin >> memberId;

                calculateFine(libraryBooks, libraryMembers, memberId);
                break;
            case 6:
                std::cout << "Exiting the Library Management System. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }

    return 0;
}