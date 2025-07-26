#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <stdexcept>


using namespace std;

class Person {
protected:
    string ID, Name, Address, BGroup, Disease;

public:
    Person() : ID(""), Name(""), Address(""), BGroup(""), Disease("") {}

    void setID(string id) {
        ID = id;
    }

    void setName(string name) {
        Name = name;
    }

    void setAddress(string address) {
        Address = address;
    }

    void setBGroup(string group) {
        BGroup = group;
    }

    void setDisease(string dis) {
        Disease = dis;
    }

    string getID() const {
        return ID;
    }

    string getName() const {
        return Name;
    }

    string getAddress() const {
        return Address;
    }

    string getBGroup() const {
        return BGroup;
    }

    string getDisease() const {
        return Disease;
    }
};

class Doctor : public Person {
private:
    string specialization;

public:
    Doctor() : specialization("") {}

    void setSpecialization(string spec) {
        specialization = spec;
    }

    string getSpecialization() const {
        return specialization;
    }

    void displayInfo() const {
        cout << "\tDoctor Name: " << getName() << endl;
        cout << "\tSpecialization: " << getSpecialization() << endl;
    }
};

class Hospital : public Person {
private:
    Doctor doctor;

public:
    void setDoctor(const Doctor& doc) {
        doctor = doc;
    }

    Doctor getDoctor() const {
        return doctor;
    }

    void displayInfo() const {
        cout << "\tID: " << getID() << endl;
        cout << "\tName: " << getName() << endl;
        cout << "\tAddress: " << getAddress() << endl;
        cout << "\tBlood Group: " << getBGroup() << endl;
        cout << "\tDisease: " << getDisease() << endl;
        cout << "\tDoctor: ";
        getDoctor().displayInfo();
    }
};

class FileHandler {
public:
    static bool isIDUnique(const string& fileName, const string& id) {
        ifstream infile(fileName);
        if (!infile.is_open()) {
            ofstream outfile(fileName);
            if (!outfile.is_open()) {
                throw runtime_error("Error: File Can't Open!");
            }
            outfile.close();
            return true; // New file, ID is unique
        } else {
            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                string existingID;
                ss >> existingID;
                if (id == existingID) {
                    return false;
                }
            }
        }
        infile.close();
        return true;
    }

    static void writeToFile(const string& fileName, const string& data) {
        ofstream outfile(fileName, ios::app);
        if (!outfile.is_open()) {
            throw runtime_error("Error: File Can't Open!");
        } else {
            outfile << data << endl;
        }
        outfile.close();
    }

    static void readFromFile(const string& fileName, const string& patientID) {
        ifstream infile(fileName);
        if (!infile.is_open()) {
            throw runtime_error("Error: File Can't Open!");
        } else {
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss(line);
                string id, name, address, bgroup, disease, docName, specialization;
                ss >> id >> name >> address >> bgroup >> disease >> docName >> specialization;
                if (patientID == id) {
                    found = true;
                    cout << "\tPatient Found:" << endl;
                    cout << "\tID: " << id << endl;
                    cout << "\tName: " << name << endl;
                    cout << "\tAddress: " << address << endl;
                    cout << "\tBlood Group: " << bgroup << endl;
                    cout << "\tDisease: " << disease << endl;
                    cout << "\tDoctor Name: " << docName << endl;
                    cout << "\tDoctor Specialization: " << specialization << endl;
                    break;  // Exit the loop once the patient is found
                }
            }
            if (!found) {
                cout << "\tPatient Not Found!" << endl;
            }
        }
        infile.close();
    }

    static void readAllFromFile(const string& fileName) {
        ifstream infile(fileName);
        if (!infile.is_open()) {
            throw runtime_error("Error: File Can't Open!");
        } else {
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss(line);
                string id, name, address, bgroup, disease, docName, specialization;
                ss >> id >> name >> address >> bgroup >> disease >> docName >> specialization;
                found = true;
                cout << "\tID: " << id << endl;
                cout << "\tName: " << name << endl;
                cout << "\tAddress: " << address << endl;
                cout << "\tBlood Group: " << bgroup << endl;
                cout << "\tDisease: " << disease << endl;
                cout << "\tDoctor Name: " << docName << endl;
                cout << "\tDoctor Specialization: " << specialization << endl;
                cout << "\t-----------------------------------------" << endl;
            }
            if (!found) {
                cout << "\tNo Patients Found!" << endl;
            }
        }
        infile.close();
    }

    static void removeFromFile(const string& fileName, const string& patientID) {
        ifstream infile(fileName);
        ofstream outfile("temp.txt");
        if (!infile.is_open() || !outfile.is_open()) {
            throw runtime_error("Error: File Can't Open!");
        } else {
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss(line);
                string id;
                ss >> id;
                if (patientID == id) {
                    found = true;
                    cout << "\tPatient Discharged!" << endl;
                } else {
                    outfile << line << endl;
                }
            }
            if (!found) {
                cout << "\tPatient Not Found!" << endl;
            }
        }
        infile.close();
        outfile.close();
        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());
    }

    static int countPatients(const string& fileName) {
        ifstream infile(fileName);
        if (!infile.is_open()) {
            throw runtime_error("Error: File Can't Open!");
        } else {
            int count = 0;
            string line;
            while (getline(infile, line)) {
                count++;
            }
            infile.close();
            return count;
        }
    }
};

void admit(Hospital &patient, Doctor &doctor) {
    system("cls");
    string id, name, address, group, disease, docName, specialization;

    cout << "\tEnter ID Of Patient: ";
    cin >> id;

    if (!FileHandler::isIDUnique("patient.txt", id)) {
        cout << "\tID already exists. Please enter a unique ID." << endl;
        Sleep(3000);
        return;
    }

    patient.setID(id);

    cout << "\tEnter Name Of Patient: ";
    cin >> name;
    patient.setName(name);
    cout << "\tEnter Address Of Patient: ";
    cin >> address;
    patient.setAddress(address);
    cin.ignore();
    cout << "\tEnter Blood Group Of Patient: ";
    cin >> group;
    patient.setBGroup(group);
    cout << "\tEnter Disease Of Patient: ";
    cin >> disease;
    patient.setDisease(disease);

    cout << "\tEnter Name Of Doctor: ";
    cin >> docName;
    doctor.setName(docName);
    cin.ignore();
    cout << "\tEnter Doctor's Specialization: ";
    cin >> specialization;
    doctor.setSpecialization(specialization);
    patient.setDoctor(doctor);

    try {
        string data = patient.getID() + "\t" + patient.getName() + "\t" + patient.getAddress() + "\t" + patient.getBGroup() + "\t" + patient.getDisease() + "\t" +
                      patient.getDoctor().getName() + "\t" + patient.getDoctor().getSpecialization();
        FileHandler::writeToFile("patient.txt", data);
        cout << "\tPatient Admitted!" << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    Sleep(3000);
}

void discharge() {
    system("cls");
    string id;

    cout << "\tEnter ID of Patient: ";
    cin >> id;

    try {
        FileHandler::removeFromFile("patient.txt", id);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    Sleep(3000);
}

void update() {
    system("cls");
    string id;

    cout << "\tEnter ID of Patient to Update: ";
    cin >> id;

    try {
        ifstream infile("patient.txt");
        ofstream outfile("temp.txt");
        if (!infile.is_open() || !outfile.is_open()) {
            throw runtime_error("Error: File Can't Open!");
        } else {
            string line;
            bool found = false;
            while (getline(infile, line)) {
                stringstream ss(line);
                string patientID, name, address, bgroup, disease, docName, specialization;
                ss >> patientID >> name >> address >> bgroup >> disease >> docName >> specialization;
                if (id == patientID) {
                    found = true;
                    bool updateMenu = true;
                    while (updateMenu) {
                        system("cls");
                        int choice;
                        cout << "\tWhat would you like to update?" << endl;
                        cout << "\t|-----------------------------------------|" << endl;
                        cout << "\t|1. Name                                  |" << endl;
                        cout << "\t|2. Address                               |" << endl;
                        cout << "\t|3. Blood Group                           |" << endl;
                        cout << "\t|4. Disease                               |" << endl;
                        cout << "\t|5. Doctor Name                           |" << endl;
                        cout << "\t|6. Doctor Specialization                 |" << endl;
                        cout << "\t|7. Exit                                  |" << endl;
                        cout << "\t|-----------------------------------------|" << endl;
                        cout << "\tEnter choice: ";
                        cin >> choice;
                        string newValue;

                        switch (choice) {
                            case 1:
                                cout << "\tEnter New Name Of Patient: ";
                                cin >> newValue;
                                name = newValue;
                                break;
                            case 2:
                                cout << "\tEnter New Address of Patient: ";
                                cin >> newValue;
                                address = newValue;
                                break;
                            case 3:
                                cout << "\tEnter New Blood Group Of Patient: ";
                                cin >> newValue;
                                bgroup = newValue;
                                break;
                            case 4:
                                cout << "\tEnter New Disease Of Patient: ";
                                cin >> newValue;
                                disease = newValue;
                                break;
                            case 5:
                                cout << "\tEnter New Doctor Name: ";
                                cin >> newValue;
                                docName = newValue;
                                break;
                            case 6:
                                cout << "\tEnter New Specialization of Doctor: ";
                                cin >> newValue;
                                specialization = newValue;
                                break;
                            case 7:
                                updateMenu = false;
                                break;
                            default:
                                cout << "\tInvalid Choice! Please enter a valid option." << endl;
                                Sleep(2000);
                        }

                        if (updateMenu) {
                            // Update the patient's line with the new values
                            line = patientID + "\t" + name + "\t" + address + "\t" + bgroup + "\t" + disease + "\t" + docName + "\t" + specialization;
                            cout << "\tPatient Record Updated!" << endl;
                            Sleep(2000);
                        }
                    }
                }
                outfile << line << endl;
            }
            if (!found) {
                cout << "\tPatient Not Found!" << endl;
            }
        }
        infile.close();
        outfile.close();
        remove("patient.txt");
        rename("temp.txt", "patient.txt");
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    Sleep(3000);
}

void displayPatientDetails() {
    system("cls");
    string id;
    cout << "\tEnter ID of Patient: ";
    cin >> id;

    try {
        FileHandler::readFromFile("patient.txt", id);
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    Sleep(3000);
}
void displayAllPatients() {
    system("cls");

    try {
        FileHandler::readAllFromFile("patient.txt");
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    Sleep(3000);
}

void countPatients() {
    system("cls");

    try {
        int patientCount = FileHandler::countPatients("patient.txt");
        cout << "\tNumber of existing patients: " << patientCount << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    Sleep(3000);
}

int main() {
    Hospital patient;
    Doctor doctor;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;

        cout << "\t\tPatient Management System" << endl;
        cout << "\t-----------------------------------------" << endl;
        cout << "\t| 1. Admit Patient                       |" << endl;
        cout << "\t| 2. Discharge Patient                   |" << endl;
        cout << "\t| 3. Update Patient Record               |" << endl;
        cout << "\t| 4. Display Patient Details             |" << endl;
        cout << "\t| 5. Display All Patients                |" << endl;
        cout << "\t| 6. Number of Existing Patients         |" << endl;
        cout << "\t| 7. Exit                                |" << endl;
        cout << "\t-----------------------------------------" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        switch (val) {
            case 1:
                cout << "\tPlease admit a patient..." << endl;
                Sleep(2000);
                admit(patient, doctor);
                break;
            case 2:
                cout << "\tPlease discharge the patient..." << endl;
                Sleep(2000);
                discharge();
                break;
            case 3:
                cout << "\tPlease update the patient details..." << endl;
                Sleep(2000);
                update();
                break;
            case 4:
                cout << "\tPlease enter patient ID to display details..." << endl;
                Sleep(2000);
                displayPatientDetails();
                break;
            case 5:
                cout << "\tDisplaying all patients..." << endl;
                Sleep(4000);
                displayAllPatients();
                break;
            case 6:
                cout << "\tChecking number of existing patients..." << endl;
                Sleep(2000);
                countPatients();
                break;
            case 7:
                system("cls");
                exit = true;
                cout << "\t\tGood Luck!" << endl;
                Sleep(2000);
                break;
            default:
                cout << "\tInvalid Choice! Please enter a valid option." << endl;
                Sleep(2000);
        }
    }
    return 0;
}