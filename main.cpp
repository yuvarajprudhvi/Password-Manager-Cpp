#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

struct PasswordEntry {
    std::string website;
    std::string username;
    std::string password;
};

class PasswordManager {
private:
    std::vector<PasswordEntry> passwordDatabase;

public:
    void addPassword(const std::string& website, const std::string& username, const std::string& password) {
        PasswordEntry entry;
        entry.website = website;
        entry.username = username;
        entry.password = password;
        passwordDatabase.push_back(entry);
    }

    void viewPasswords() {
        if (passwordDatabase.empty()) {
            std::cout << "No passwords stored yet." << std::endl;
            return;
        }

        std::cout << "Stored Passwords:\n";
        for (const PasswordEntry& entry : passwordDatabase) {
            std::cout << "Website: " << entry.website << " | Username: " << entry.username << " | Password: " << entry.password << std::endl;
        }
    }

    void savePasswordsToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const PasswordEntry& entry : passwordDatabase) {
                file << entry.website << "," << entry.username << "," << entry.password << "\n";
            }
            file.close();
            std::cout << "Passwords saved to " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not save passwords to file." << std::endl;
        }
    }

    void loadPasswordsFromFile(const std::string& filename) {
        passwordDatabase.clear(); // Clear existing passwords
        std::ifstream file(filename);
        if (file.is_open()) {
            PasswordEntry entry;
            std::string line;
            while (std::getline(file, line)) {
                size_t pos = line.find(",");
                if (pos != std::string::npos) {
                    entry.website = line.substr(0, pos);
                    line = line.substr(pos + 1);
                    pos = line.find(",");
                    if (pos != std::string::npos) {
                        entry.username = line.substr(0, pos);
                        entry.password = line.substr(pos + 1);
                        passwordDatabase.push_back(entry);
                    }
                }
            }
            file.close();
            std::cout << "Passwords loaded from " << filename << std::endl;
        } else {
            std::cerr << "Error: Could not load passwords from file." << std::endl;
        }
    }
};

int main() {
    PasswordManager passwordManager;
    std::string filename = "passwords.txt";

    while (true) {
        std::cout << "Password Manager Menu:\n";
        std::cout << "1. Add Password\n";
        std::cout << "2. View Passwords\n";
        std::cout << "3. Save Passwords to File\n";
        std::cout << "4. Load Passwords from File\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string website, username, password;
                std::cout << "Enter Website: ";
                std::cin >> website;
                std::cout << "Enter Username: ";
                std::cin >> username;
                std::cout << "Enter Password: ";
                std::cin >> password;
                passwordManager.addPassword(website, username, password);
                break;
            }
            case 2:
                passwordManager.viewPasswords();
                break;
            case 3:
                passwordManager.savePasswordsToFile(filename);
                break;
            case 4:
                passwordManager.loadPasswordsFromFile(filename);
                break;
            case 5:
                std::cout << "Exiting the Password Manager." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
