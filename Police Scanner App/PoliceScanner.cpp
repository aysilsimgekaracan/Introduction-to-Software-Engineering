#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype> // for toupper()
#include <algorithm> // for transform()

#if _WIN32 || _WIN64 
        #include "windows.h"
    #else 
        #include <unistd.h>
#endif

using namespace std;

void clear() {
    #if _WIN32 || _WIN64 
        system("cls");
    #else 
        system("clear");
    #endif
}

struct Criminal {
    string name, age, location, crime, detail;
};

vector<Criminal> criminalsList;

void setAllCriminals() { // Get all criminals from the data file and save it to the varible criminalsList 
    ifstream DBFile;

    DBFile.open("CriminalData.txt");

    string delimiter = ",";
    vector<string> v_criminal;

    // Read from the file with using delimeter

    string criminal_info; 
    while ( getline (DBFile, criminal_info) )
    {
        v_criminal.clear();

        size_t last = 0;
        size_t next = 0; 

        while ((next = criminal_info.find(delimiter, last)) != string::npos) {
            v_criminal.push_back(criminal_info.substr(last, next-last));
            last = next + 1; 
        } 
        
        v_criminal.push_back(criminal_info.substr(last));

        Criminal criminal { v_criminal[0], v_criminal[1], v_criminal[2], v_criminal[3], v_criminal[4] };

        criminalsList.push_back(criminal);

    }

}

// Make a string upper case
string toUpperStr(string str) { 
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    return str;
}

class Police {
    public:

        void getAllCriminals() { // Show all criminals' names
            for (int i = 0; i < criminalsList.size(); i++) {
                cout << i+1 << ". " << criminalsList[i].name << endl;
            }
        }
    
        void getCriminal() { // Choose a criminal to see detailed info
            getAllCriminals();
            int option;
            cout << "Which criminal you want to choose : ";
            cin >> option;

            getCriminalDetails(option - 1);
        }

        virtual void setNewCriminal() {cout << "Police Class";}

        virtual int showOptions() { // This func shows all options that this class can use
            int option = -1;

            while ((option != 1) && (option != 2) && (option != 3)) {
            cout << "[1] GET ALL CRIMINALS" << endl;
            cout << "[2] GET A CRIMINAL" << endl;
            cout << "[3] SEARCH BY LOCATION" << endl;

            cin >> option;
            }

            return option;
        }

        void searchbyLocation() { // User can search Criminals by location
            string input_location;
            int count = 0;

            cout << "SEARCH A LOCATION: ";
            cin >> input_location;

            for (int i = 0; i < criminalsList.size(); i++) {
                if (criminalsList[i].location == toUpperStr(input_location)) {
                    count += 1;
                    cout << "\t\t\t" << count << endl;
                    getCriminalDetails(i);
                    cout << "\n\n";
                }
            }

            cout << "\t\t" << count << " Criminal Found." << endl;

        }

    private:
    
    void getCriminalDetails(int opt) { // Prints all details of chosen Criminal
        cout << "\tNAME: " << criminalsList[opt].name << endl;
        cout << "\tAGE: " << criminalsList[opt].age << endl;
        cout << "\tLOCATION: " << criminalsList[opt].location << endl;
        cout << "\tCRIME: " << criminalsList[opt].crime << endl;
        cout << "\tDETAIL: " << criminalsList[opt].detail << endl;
    }
};

class AuthorizedPolice : public Police {
    public:
        
        void setNewCriminal(){ // Create a new Criminal
            Criminal newCriminal;

            cin.clear();
            cin.ignore();

            cout << "\t\tADD NEW CRIMINAL" << endl;
            cout << "NAME: ";
            getline(cin, newCriminal.name);
            
            cout << "AGE: ";
            getline(cin, newCriminal.age);

            cout << "LOCATION: ";
            getline(cin, newCriminal.location);

            cout << "CRIME: ";
            getline(cin, newCriminal.crime);

            cout << "DETAIL: ";
            getline(cin, newCriminal.detail);

            saveNewCriminal(upperCaseCriminal(newCriminal));

        }

        int showOptions() {
            int option = -1;

            while (option != 1 && option != 2 && option != 3 && option != 4) {
            cout << "[1] GET ALL CRIMINALS" << endl;
            cout << "[2] GET A CRIMINAL" << endl;
            cout << "[3] SEARCH BY LOCATION" << endl;
            cout << "[4] ADD A NEW CRIMINAL" << endl;

            cin >> option;
            }

            return option;
        }

    private:
        void saveNewCriminal(Criminal newCriminal) { // Save the criminal to the DB file
            criminalsList.push_back(newCriminal);

            ofstream DBFile("CriminalData.txt", ios::app);

            DBFile << newCriminal.name << "," << newCriminal.age << "," << newCriminal.location << "," << newCriminal.crime << "," << newCriminal.detail << endl;
        }

        Criminal upperCaseCriminal(Criminal criminal) { // Saves all data in upper case.
            Criminal newCriminal;
            newCriminal.name = toUpperStr(criminal.name);
            newCriminal.age = toUpperStr(criminal.age);
            newCriminal.location = toUpperStr(criminal.location);
            newCriminal.crime = toUpperStr(criminal.crime);
            newCriminal.detail = toUpperStr(criminal.detail);

            return newCriminal;
        }
};

int main() {
    clear();
    setAllCriminals();

    cout << "------------------------------------------------------------------" << endl;
    cout << "       P O L I C E     S C A N N E R      A P P                   " << endl;
    cout << "------------------------------------------------------------------" << endl;

    Police *ptrPolice;

    int policeType;
    bool policeIsValid = false; // User should choose opt 1 or 2 to be valid
    bool isOver = false; // This will set to true if user decides to stop the programme

    string passcode = "12345"; // Passcode for Authorized Police
    

    while (!policeIsValid) {
        cout << "[1]. POLICE" << endl;
        cout << "[2]. AUTHORIZED POLICE" << endl;
        cin >> policeType;

        if (policeType == 2) {
            string input_passcode;

            cout << "PASSCODE: ";
            cin >> input_passcode;

            if (passcode == input_passcode) {
                policeIsValid = true;
                ptrPolice = new AuthorizedPolice;
            }
        } 
        
        if (policeType == 1) {
            policeIsValid = true;
            ptrPolice = new Police;
        }        
    }

    while(!isOver) {
    string choice;
    int option = ptrPolice->showOptions();

    switch (option) {
        case 1:
            ptrPolice->getAllCriminals();
            break;
        case 2:
            ptrPolice->getCriminal();
            break;
        case 3:
            ptrPolice->searchbyLocation();
            break;
        case 4:
            ptrPolice->setNewCriminal();
            break;
    }

    cout << "DO YOU WANT TO CONTINUE? ([yes]||[no]): ";
    cin >> choice;

    if (choice == "no" || choice == "NO" ) {
        isOver = true;
    }

    clear();

    }

}
