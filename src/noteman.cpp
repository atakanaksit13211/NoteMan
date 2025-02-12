#include <iostream>
#include <vector>

//-- user headers --{{{
#include "Student.hpp"
#include "Log.hpp"
#include "Studentdata.hpp"
//}}}


    std::string name;
    std::string lastname;
    int grade;
    unsigned int id;
    Studentdata student; // Our student "database"

void enternotes(){
    std::cout << "Enter student ID: ";
    std::cin >> id;
    student.addstudent(id);
    
    std::cout << "Enter student name: ";
    std::cin >> name;
    student.data[id].setname(name);


    std::cout << "Enter student lastname: ";
    std::cin >> lastname;
    student.data[id].setlastname(lastname);
    
    std::cout << "Enter notes seperated by spaces. Type | to end: ";
    for(unsigned int a = 0; std::cin >> grade; a++){
    student.data[id].setnote(grade, a);
    }
    student.savedatabase("test.txt");
}

int main(){

    Log log;
    /* AVAILABLE LOG LEVELS:
     *   log.LogLevelInfo
     *   log.LogLevelWarn
     *   log.LogLevelError */
    
    /* AVAILABLE LOG FUNCTIONS:
     *   log.Error("Error"); 
     *   log.Warn("foo");
     *   log.Info("bar"); */
    log.ChangeLogLvl(log.LogLevelInfo);

    std::cout << "Enter operation ((A)dd, (L)ist): ";
    char operation;
    std::cin >> operation;

    if (operation == 'A') enternotes();

    if (operation == 'L'){
    student.getdatabase("test.txt");

    for (auto it = student.data.begin(); it != student.data.end(); ++it){ //search the entire data vector
        if ( it -> getname() != "N/A"){
            unsigned int it_distance = std::distance(student.data.begin(), it);
            std::cout << "ID: " << it_distance << "\nName: " << it -> getname() << "\nSurname: " << it -> getlastname();

            std::cout << "\nThe notes are:\n";
            for(unsigned int i = 0; i < it -> notesize() ; i++){
            std::cout << i+1 << "th exam: " << it -> getnote(i) << '\n';
            }
        }
    }
    }
}


