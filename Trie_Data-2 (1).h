
#include "Trie_Node.h"
#include <fstream>

#include <regex>
#include <limits>
#include <unordered_set>

// Constructor
Trie::Trie() {
    root = new TrieNode();
}

// Destructor to clean up dynamically allocated memory
Trie::~Trie() {
    deleteRecursively(root);
}

// Helper function to delete nodes recursively
void Trie::deleteRecursively(TrieNode* node) {
    for (auto& child : node->children) {
        deleteRecursively(child.second);
    }
    delete node;
}

// Insert a new guest into the trie
void Trie::insert(const std::string& key, const Guest& guest) {
    TrieNode* node = root;

    for (char c : key) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->guests.push_back(guest);
    node->isEndOfWord = true;
    std::cout << "Guest " << guest.name << " added successfully.\n";
    std::cout << std::endl;

}

// Search for guests by a prefix (key)
bool Trie::search(const std::string& key, std::vector<Guest>& result) {
    TrieNode* node = findNode(key);
    if (!node) {
        return false;
    }

    result = node->guests;
    return true;
}

// Autocomplete function to search by prefix
void Trie::autocomplete(const std::string& prefix, std::vector<Guest>& result) {
    TrieNode* node = findNode(prefix);
    if (!node) {
        return;
    }

    result = node->guests;
}

// Delete a guest by name and number
void Trie::deleteGuest(const std::string& key, const std::string& number) {
    TrieNode* node = findNode(key);
    if (!node) {
        std::cout << "Guest not found.\n";
        std::cout << std::endl;
        return;
    }

    for (auto it = node->guests.begin(); it != node->guests.end(); ++it) {
        if (it->number == number) {
            std::cout << "Guest " << it->name << " deleted successfully.\n";
            node->guests.erase(it);
            std::cout << std::endl;
            return;
        }
    }
    std::cout << "Guest not found by the given number.\n";
}

// Find the node corresponding to a key (prefix)
TrieNode* Trie::findNode(const std::string& key) {
    TrieNode* node = root;
    for (char c : key) {
        if (node->children.find(c) == node->children.end()) {
            return nullptr;
        }
        node = node->children[c];
    }
    return node;
}

// Print out guests' information in a readable format
void Trie::printGuests(const std::vector<Guest>& guests) {
    for (const Guest& guest : guests) {
        std::cout << "Name: " << guest.name << "\n";
        std::cout << "Phone Number: " << guest.number << "\n";
        std::cout << "Date of Birth: " << guest.dob << "\n";
        std::cout << "City: " << guest.city << "\n";
        std::cout << "----------------------------\n";
    }
}

// Validate the phone number (10 digits, US format, not all zeros)
bool Trie::isValidPhoneNumber(const std::string& phoneNumber) {
    if (phoneNumber.length() != 10 || !std::all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {
        return false;
    }

    // Check if the number is all zeros
    if (phoneNumber == "0000000000") {
        return false;
    }

    // Check the area code (first 3 digits): cannot start with 0 or 1
    if (phoneNumber[0] == '0' || phoneNumber[0] == '1') {
        return false;
    }

    // Check the exchange code (next 3 digits): cannot start with 0 or 1
    if (phoneNumber[3] == '0' || phoneNumber[3] == '1') {
        return false;
    }

    return true;
}

// Validate the date of birth

bool Trie::isValidDate(const std::string& dob) {
    if (dob.length() != 8 || !std::all_of(dob.begin(), dob.end(), ::isdigit)) {
        return false;
    }

    int year = std::stoi(dob.substr(0, 4));
    int month = std::stoi(dob.substr(4, 2));
    int day = std::stoi(dob.substr(6, 2));

    // Check if the month is valid (1-12)
    if (month < 1 || month > 12) return false;

    // Check if the day is valid based on the month
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2 && day > 29) return false;  // Assume leap years are valid
    if (month == 2 && day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) return false;

    // Check if the person is at least 18 years old
    int currentYear = 0, currentMonth = 0, currentDay = 0;
    time_t now = time(0);
    tm ltm;  // Declare the tm struct
    localtime_s(&ltm, &now);  // Use localtime_s instead of localtime

    currentYear = 1900 + ltm.tm_year;
    currentMonth = 1 + ltm.tm_mon;
    currentDay = ltm.tm_mday;

    int age = currentYear - year;
    if (currentMonth < month || (currentMonth == month && currentDay < day)) {
        age--;
    }

    if (age < 18) return false;

    return true;
}

// Validate if the city is valid (dummy example of city validation)
bool Trie::isValidCity(std::string& city) {

    std::unordered_set<std::string> valid_Cities;
    std::fstream file;
    file.open("US_Cities.txt");

    if (!file.is_open()) {
        std::cerr << "Error Opening File" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        valid_Cities.insert(line);
    }
    file.close();

    return valid_Cities.find(city) != valid_Cities.end();
}

// Format the phone number (from 10 digits to (XXX) XXX-XXXX)
std::string Trie::formatPhoneNumber(const std::string& phoneNumber) {

    std::string patter1 = "\\d{10}";
    std::string pattern2 = "\\(\\d{3}\\)s*-\\s*\\d{3}-\\s*\\d{4}";


    std::regex re1 (patter1);
    std::regex re2 (pattern2);
   
    return phoneNumber;


}

// Format the date of birth (from YYYYMMDD to YYYY-MM-DD)
std::string Trie::formatDateOfBirth(const std::string& dob) {
    if (dob.length() == 8 && std::all_of(dob.begin(), dob.end(), ::isdigit)) {
        return dob.substr(0, 4) + "-" + dob.substr(4, 2) + "-" + dob.substr(6, 2);
    }
    return dob;
}


