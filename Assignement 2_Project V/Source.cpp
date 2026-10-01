#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students;

    std::ifstream file("StudentData.txt");
    if (!file.is_open()) {
        std::cout << "Error: could not open StudentData.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        STUDENT_DATA student;
        std::getline(ss, student.lastName, ',');
        std::getline(ss, student.firstName);
        student.firstName.erase(0, student.firstName.find_first_not_of(" \t"));
        students.push_back(student);
    }
    file.close();

    #ifdef _DEBUG
        std::cout << "--- DEBUG: Loaded " << students.size() << " students ---" << std::endl;
        for (const STUDENT_DATA& s : students) {
            std::cout << s.firstName << " " << s.lastName << std::endl;
        }
    #endif

    return 1;
}