
#include "Trie_Data.h"

// Function declarations
void displayMenu();
void addGuest(Trie& trie);
void searchGuest(Trie& trie);
void deleteGuest(Trie& trie);
bool Login(std::unordered_map<std::string, std::string>& User, const std::string username, const std::string password);

// Variables for login authentication
std::string username;
std::string passcode;
int attempts = 0;
const int max_attempts = 3;
std::unordered_map<std::string, std::string> User = {{ "MoneyFive7", "4887" }};
bool authentication = false;

// Login Authentication
bool Login(std::unordered_map<std::string, std::string>& User, const std::string username, const std::string password) {
    auto it = User.find(username);
    return it != User.end() && it->second == password;
}   
    
    

// Function to display the main menu
void displayMenu() {

    // Allow guard to login with username and passcode with limited attempts 
    while (attempts < max_attempts) {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << std::endl;

        std::cout << "Enter passcode: ";
        std:: cin >> passcode;
        std::cout << std:: endl;

        if (Login(User, username, passcode)) {
            authentication = true;
            break;
        }
        else {
            attempts++;
            std::cout << "Wrong username or password. You have " << (max_attempts - attempts) << " attempts";
            std::cout << std:: endl;
        }
    }
    // Ask the guard to try again later if attempts are maxed
    if (!authentication) {
        std:: cout << "Maxed attempts. Try again later. \n";
        exit(0);
    }
    std::cout << "------------------- Nightclub Guest List -------------------\n";
    std::cout << "1. Add Guest\n";
    std::cout << "2. Search for a Guest\n";
    std::cout << "3. Delete Guest\n";
    std::cout << "4. Exit\n";
    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

// Main function
int main() {
    Trie trie;
    int choice;
    int attempts = 0;
    std::string username;
    std::string passcode;
    const int max_attempts = 3;
    std::unordered_map<std::string, std::string> User = { { "MoneyBusiness7", "4887" } };
    bool authentication = false;

    do {

        

        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: addGuest(trie); break;
        case 2: searchGuest(trie); break;
        case 3: deleteGuest(trie); break;
        case 4:
            std::cout << "Exiting...\n";
            return 0;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining input
            break;
        }
    } while (true);

    return 0;
}

// Function to add a guest
void addGuest(Trie& trie) {
    std::string name, number, dob, city;

    std::cout << "Enter guest name: ";
    std::cin.ignore(); // To ignore the newline character left by previous input
    std::getline(std::cin, name);

    std::cout << "Enter phone number: ";
    std::cin >> number;
    while (!trie.isValidPhoneNumber(number)) {
        std::cout << "Invalid phone number. Please enter a valid 10-digit phone number: ";
        std::cin >> number;
    }
    number = trie.formatPhoneNumber(number);

    std::cout << "Enter date of birth (YYYYMMDD): ";
    std::cin >> dob;
    while (!trie.isValidDate(dob)) {
        std::cout << "Invalid date of birth. Please enter a valid date (YYYYMMDD): ";
        std::cin >> dob;
    }
    dob = trie.formatDateOfBirth(dob);

    std::cout << "Enter city: ";
    std::cin >> city;
    while (!trie.isValidCity(city)) {
        std::cout << "Invalid city. Please enter a valid city: ";
        std::cin >> city;
    }

    Guest guest(name, number, dob, city);
    trie.insert(name, guest);
}

// Function to search for a guest
void searchGuest(Trie& trie) {
    std::string key;
    std::cout << "Enter name or part of name to search: ";
    std::cin.ignore();
    std::getline(std::cin, key);

    std::vector<Guest> results;
    if (trie.search(key, results)) {
        trie.printGuests(results);
    }
    else {
        std::cout << "No guests found with that name.\n";
    }
}

// Function to delete a guest
void deleteGuest(Trie& trie) {
    std::string name, number;
    std::cout << "Enter name of guest to delete: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter phone number of guest to delete: ";
    std::cin >> number;

    trie.deleteGuest(name, number);
}
