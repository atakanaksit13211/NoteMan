//-- Student class: has student name, grade etc.

#include <vector> // apparently std libs are protected
#include <string>

#ifndef __NOTEMAN_STUDENT_HPP__
#define __NOTEMAN_STUDENT_HPP__

class Student{
    public:
        int getnote(int exam){return note[exam];}
        void setnote(int grade, unsigned int location){
            if(location >= note.size()) note.resize(location+1); // grow size if the location does not exist
            note.at(location) = grade; // set grade for that location
        }

        unsigned int notesize(){return note.size();}

        std::string getname() {return student;}
        void setname(std::string name){student = name;}


        std::string getlastname() {return lastname;}
        void setlastname(std::string surname){lastname = surname;}
    private:
        std::string student{"N/A"};
        std::string lastname;
    public: 
        std::vector<int> note; // we need the vector in studentdata
};
#endif // NOTEMAN_STUDENT_HPP
