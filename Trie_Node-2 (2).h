
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// Struct to hold guest details
struct Guest {
    std::string name;
    std::string number;
    std::string dob; // Date of Birth in format YYYY-MM-DD
    std::string city;

    Guest(const std::string& n, const std::string& num, const std::string& d, const std::string& c)
        : name(n), number(num), dob(d), city(c) {}
};

// Trie Node structure
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;  // Children nodes
    bool isEndOfWord;                              // Indicates if the word ends at this node
    std::vector<Guest> guests;                     // List of guests for the current prefix

    TrieNode() : isEndOfWord(false) {}
};

// Trie class definition
class Trie {
public:
    Trie();
    ~Trie();

    void insert(const std::string& key, const Guest& guest);
    bool search(const std::string& key, std::vector<Guest>& result);
    void deleteGuest(const std::string& key, const std::string& number);
    void printGuests(const std::vector<Guest>& guests);
    void autocomplete(const std::string& prefix, std::vector<Guest>& result);

    // Validation and Formatting functions
    bool isValidPhoneNumber(const std::string& phoneNumber);
    bool isValidDate(const std::string& dob);
    bool isValidCity(std::string& city);
    std::string formatPhoneNumber(const std::string& phoneNumber);
    std::string formatDateOfBirth(const std::string& dob);

private:
    TrieNode* root;

    // Helper functions for deletion and cleanup
    void deleteRecursively(TrieNode* node);
    TrieNode* findNode(const std::string& key);
};

