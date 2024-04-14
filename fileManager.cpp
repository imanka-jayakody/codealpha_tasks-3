#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

void listDirectory(const string& dirPath) {
    cout << "Contents of directory " << dirPath << ":\n";
    DIR *directory;
    struct dirent *entry;
    directory = opendir(dirPath.c_str());
    if (directory != nullptr) {
        while ((entry = readdir(directory)) != nullptr) {
            cout << entry->d_name << "\n";
        }
        closedir(directory);
    } else {
        cout << "Error: Unable to open directory " << dirPath << "\n";
    }
}

void viewFile(const string& filePath) {
    ifstream file(filePath);
    if (file.is_open()) {
        cout << "Contents of file " << filePath << ":\n";
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open file " << filePath << "\n";
    }
}

void createDirectory(const string& dirPath) {
    if (mkdir(dirPath.c_str()) == 0) {
        cout << "Directory created: " << dirPath << "\n";
    } else {
        cout << "Failed to create directory " << dirPath << "\n";
    }
}

void copyFile(const string& source, const string& destination) {
    ifstream src(source, ios::binary);
    ofstream dest(destination, ios::binary);
    dest << src.rdbuf();
    src.close();
    dest.close();
    cout << "File copied from " << source << " to " << destination << "\n";
}

void moveFile(const string& source, const string& destination) {
    if (rename(source.c_str(), destination.c_str()) == 0) {
        cout << "File moved from " << source << " to " << destination << "\n";
    } else {
        cout << "Error: Failed to move file\n";
    }
}

void deleteFile(const string& filePath) {
    if (remove(filePath.c_str()) == 0) {
        cout << "File deleted: " << filePath << "\n";
    } else {
        cout << "Failed to delete file " << filePath << "\n";
    }
}

int main() {
    char choice;
    string currentPath = "./";

    do {
        cout << "\nCurrent directory: " << currentPath << "\n";
        cout << "Options:\n";
        cout << "1. List contents\n";
        cout << "2. View file\n";
        cout << "3. Create directory\n";
        cout << "4. Copy file\n";
        cout << "5. Move file\n";
        cout << "6. Delete file\n";
        cout << "7. Change directory\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                listDirectory(currentPath);
                break;
            case '2': {
                string filename;
                cout << "Enter filename: ";
                cin >> filename;
                viewFile(currentPath + filename);
                break;
            }
            case '3': {
                string dirname;
                cout << "Enter directory name: ";
                cin >> dirname;
                createDirectory(currentPath + dirname);
                break;
            }
            case '4': {
                string source, destination;
                cout << "Enter source file path: ";
                cin >> source;
                cout << "Enter destination file path: ";
                cin >> destination;
                copyFile(currentPath + source, destination);
                break;
            }
            case '5': {
                string source, destination;
                cout << "Enter source file path: ";
                cin >> source;
                cout << "Enter destination file path: ";
                cin >> destination;
                moveFile(currentPath + source, currentPath + destination);
                break;
            }
            case '6': {
                string filename;
                cout << "Enter filename to delete: ";
                cin >> filename;
                deleteFile(currentPath + filename);
                break;
            }
            case '7': {
                string newDir;
                cout << "Enter directory name: ";
                cin >> newDir;
                currentPath += newDir + "/";
                break;
            }
            case '8':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != '8');

    return 0;
}
