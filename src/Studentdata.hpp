//-- Studentdata; Where we do student database stuff
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>
#include <filesystem>

#include "Student.hpp"

#ifndef __NOTEMAN_STUDENTDATA_HPP__
#define __NOTEMAN_STUDENTDATA_HPP__

class Studentdata{
    /*!-- We use vector locations as ID. --!
     *
     * That means we just grow the size if we need 
     * an id larger than the size
     */
    public: //Vector operations
        std::vector<Student> data; // Our student data vector (A.K.A database in memory)
        //^ We might need to access the database directly in other files.

        void addstudent(unsigned int id){
            if(id >= data.size()) data.resize(id+1); // grow to id if the location does not exist
            else{};
        }

    public: //File operations
    /*          --DATA FORMAT--
    * student_id = name ; lastname \n
    * /t note_vector_location : note \n
    * ...
    * 
    * EXAMPLE:
    * 123=john;doe
    *   0:100
    *   1:90
    *   ...
    * 2341=alice;johnson
    *   0:79
    *   1:100
    *   ...
    */
        std::fstream database; // ""database""

        bool savedatabase(std::string file){

            std::filesystem::path f{file};
            if (!std::filesystem::exists(f)){ //create file if it doesnt exist
                std::ofstream mkfile {file}; /*Open and close file to create it*/
            }

            database.open(file, std::ios_base::app);
            if(database.is_open()){
                for (auto it = data.begin(); it != data.end(); ++it){ //search the entire data vector (with iterators)
                    if ( it -> getname() != "N/A"){ // Found a student by checking name, 
                                                     // By default student names are initilized to "N/A"

                        unsigned int it_distance = std::distance(data.begin(), it); //convert iterator to int
                        database << it_distance << '=' << it -> getname() << ';' << it -> getlastname() << '\n';

                        for(unsigned int i = 0; i < it -> notesize() ; i++){
                             //FILE FORMAT: /t note_vector_location : note /n
                            database << '\t' << i << ':' << it -> getnote(i) << '\n';  
                        }
                    }
                }
                database.close();
                return 1; //success!
            }
            else return 0; //Oh no! something went wrong
        }
        
        bool getdatabase(std::string file){ // load database into memory
            database.open(file, std::ios::in);
            
            if(database.is_open()){
                try{
                std::string line;
                unsigned int sid; // we can avoid out-of-scope by defining it out of the loop //SID means StudentID
                while(getline(database, line)){ //read each line
                    if(line[0] != '\t'){ //Found ID
                        auto idend = line.find('='); //location of '='
                        auto nameend = line.find(';'); //location of ';'
                        
                        auto eq = line.substr(0, idend);
                        sid = std::stoi(eq); //StudentID -> SID
                        addstudent(sid);
                    
                        data[sid].setname(line.substr(idend +1 , nameend - idend -1 )); // the second statement gets the length

                        data[sid].setlastname(line.substr(nameend +1 , line.back()));
                    }
                    else{ // Found data, cannot exist without ID,
                        auto vecend = line.find(':'); //location of ':'
                        
                        auto dubl = line.substr(0, vecend);
                        unsigned int vecloc = std::stoi(dubl);
                        auto ennd = line.substr(vecend +1, line.back());
                        int grade = std::stoi(ennd);

                        data[sid].setnote(grade, vecloc);
                    }
                } 
                }
            catch (const std::invalid_argument& ia) {
	            std::cerr << "Invalid argument: " << ia.what() << '\n';
            }
            return 1;
            }

            else return 0; // Oh no! something went wrong
        }
};
#endif // NOTEMAN_STUDENTDATA_HPP
