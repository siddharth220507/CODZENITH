#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <limits>


struct Student {
    std::string name;
    double marks;
};


double getValidatedDouble(const std::string& prompt, double minVal = 0.0, double maxVal = 100.0) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minVal && value <= maxVal) {
                 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "\033[31m[Error] Marks must be between " << minVal << " and " << maxVal << ". Please try again.\033[0m\n";
            }
        } else {
            std::cout << "\033[31m[Error] Invalid input. Please enter a valid number.\033[0m\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
        }
    }
}


int getValidatedInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minVal && value <= maxVal) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            } else {
                std::cout << "\033[31m[Error] Choice must be between " << minVal << " and " << maxVal << ".\033[0m\n";
            }
        } else {
            std::cout << "\033[31m[Error] Invalid input. Please enter a whole number.\033[0m\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}


std::string getValidatedString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        
       
        size_t first = value.find_first_not_of(" \t");
        if (first == std::string::npos) {
            std::cout << "\033[31m[Error] Input cannot be empty. Please enter a name.\033[0m\n";
            continue;
        }
        size_t last = value.find_last_not_of(" \t");
        return value.substr(first, (last - first + 1));
    }
}


void inputStudents(std::vector<Student>& students) {
    std::cout << "\n============================================\n";
    std::cout << "          ADD NEW STUDENT MARKS             \n";
    std::cout << "============================================\n";
    
    int count = getValidatedInt("Enter the number of students to add: ", 1, 1000);
    
    for (int i = 0; i < count; ++i) {
        std::cout << "\n--- Student #" << (students.size() + 1) << " ---\n";
        std::string name = getValidatedString("Enter student name: ");
        double marks = getValidatedDouble("Enter student marks (0 - 100): ");
        
        students.push_back({name, marks});
    }
    
    std::cout << "\n\033[32m[Success] " << count << " student(s) added successfully!\033[0m\n";
}


void displayStudents(const std::vector<Student>& students) {
    std::cout << "\n============================================\n";
    std::cout << "            STUDENT MARKS RECORD            \n";
    std::cout << "============================================\n";
    
    if (students.empty()) {
        std::cout << "\033[33mNo student marks registered yet. Please add data first!\033[0m\n";
        return;
    }
    
    
    std::cout << std::left << std::setw(8) << "S.No." 
              << std::setw(25) << "Student Name" 
              << std::right << std::setw(10) << "Marks" << "\n";
    std::cout << "--------------------------------------------\n";
    
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << std::left << std::setw(8) << (i + 1)
                  << std::setw(25) << students[i].name
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << students[i].marks << "\n";
    }
    std::cout << "--------------------------------------------\n";
    std::cout << "Total Students: " << students.size() << "\n";
}


void analyzeMarks(const std::vector<Student>& students) {
    std::cout << "\n============================================\n";
    std::cout << "             MARKS ANALYSIS                 \n";
    std::cout << "============================================\n";
    
    if (students.empty()) {
        std::cout << "\033[33mNo student marks registered yet. Please add data first!\033[0m\n";
        return;
    }
    
    double sum = 0;
    double highest = students[0].marks;
    double lowest = students[0].marks;
    
    std::vector<std::string> highestPerformers = {students[0].name};
    std::vector<std::string> lowestPerformers = {students[0].name};
    
    for (size_t i = 0; i < students.size(); ++i) {
        double currentMarks = students[i].marks;
        sum += currentMarks;
        
        if (i > 0) {
            
            if (currentMarks > highest) {
                highest = currentMarks;
                highestPerformers.clear();
                highestPerformers.push_back(students[i].name);
            } else if (currentMarks == highest) {
                highestPerformers.push_back(students[i].name);
            }
            
           
            if (currentMarks < lowest) {
                lowest = currentMarks;
                lowestPerformers.clear();
                lowestPerformers.push_back(students[i].name);
            } else if (currentMarks == lowest) {
                lowestPerformers.push_back(students[i].name);
            }
        }
    }
    
    double average = sum / students.size();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(20) << "Average Marks:" << std::right << std::setw(8) << average << "\n";
    
    std::cout << std::left << std::setw(20) << "Highest Marks:" << std::right << std::setw(8) << highest << " (";
    for (size_t i = 0; i < highestPerformers.size(); ++i) {
        std::cout << highestPerformers[i] << (i + 1 < highestPerformers.size() ? ", " : "");
    }
    std::cout << ")\n";
    
    std::cout << std::left << std::setw(20) << "Lowest Marks:" << std::right << std::setw(8) << lowest << " (";
    for (size_t i = 0; i < lowestPerformers.size(); ++i) {
        std::cout << lowestPerformers[i] << (i + 1 < lowestPerformers.size() ? ", " : "");
    }
    std::cout << ")\n";
    std::cout << "============================================\n";
}


void showMenu() {
    std::cout << "\n\033[36m============================================\n";
    std::cout << "        STUDENT MARKS ANALYZER MENU         \n";
    std::cout << "============================================\033[0m\n";
    std::cout << "1. Add Student Marks\n";
    std::cout << "2. View Student Records\n";
    std::cout << "3. Calculate & Display Analysis\n";
    std::cout << "4. Reset / Clear Database\n";
    std::cout << "5. Exit Program\n";
    std::cout << "--------------------------------------------\n";
}

int main() {
    std::vector<Student> students;
    bool running = true;
    
    
    std::cout << "\033[32mWelcome to the Student Marks Analyzer System!\033[0m\n";
    
    while (running) {
        showMenu();
        int choice = getValidatedInt("Enter your choice (1-5): ", 1, 5);
        
        switch (choice) {
            case 1:
                inputStudents(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                analyzeMarks(students);
                break;
            case 4: {
                std::cout << "\n\033[31m[Warning] Are you sure you want to clear all data? (1 = Yes, 2 = No):\033[0m ";
                int confirm = getValidatedInt("", 1, 2);
                if (confirm == 1) {
                    students.clear();
                    std::cout << "\033[32m[Success] Database has been reset.\033[0m\n";
                } else {
                    std::cout << "Action cancelled.\n";
                }
                break;
            }
            case 5:
                std::cout << "\nThank you for using Student Marks Analyzer. Goodbye!\n";
                running = false;
                break;
        }
    }
    return 0;
}
