//#define PRE_RELEASE

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

// Removes leading spaces/tabs
void trimLeft(std::string& s) {
    s.erase(0, s.find_first_not_of(" \t"));
}

int main() {
#ifdef PRE_RELEASE
    std::cout << "Running PRE-RELEASE version" << std::endl;
    const std::string fileName = "StudentData_Emails.txt";
#else
    std::cout << "Running STANDARD version" << std::endl;
    const std::string fileName = "StudentData.txt";
#endif

    std::vector<STUDENT_DATA> students;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error: could not open " << fileName << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        STUDENT_DATA student;
        std::getline(ss, student.lastName, ',');
#ifdef PRE_RELEASE
        std::getline(ss, student.firstName, ',');
        std::getline(ss, student.email);
        trimLeft(student.email);
#else
        std::getline(ss, student.firstName);
#endif
        trimLeft(student.firstName);

        students.push_back(student);
    }
    file.close();

#ifdef _DEBUG
    std::cout << "--- DEBUG: Loaded " << students.size() << " students ---" << std::endl;
    for (const STUDENT_DATA& s : students) {
        std::cout << s.firstName << " " << s.lastName;
#ifdef PRE_RELEASE
        std::cout << " - " << s.email;
#endif
        std::cout << std::endl;
    }
#endif

    return 1;
}