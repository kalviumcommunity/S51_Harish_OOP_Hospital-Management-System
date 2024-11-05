#include <iostream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 10;
const int MAX_DOCTORS = 5;
const int MAX_ROOMS = 5;

class Patient {
private:
    string name;
    int id;
    string diagnosis;
    static int totalPatients;

public:
    Patient() : name(""), id(0), diagnosis("") {}
    Patient(string n, int i, string d) : name(n), id(i), diagnosis(d) {
        totalPatients++;
    }
    ~Patient() {
        totalPatients--;
        cout << "Destructor called for patient " << name << endl;
    }
    
    string getName() const { return name; }
    int getId() const { return id; }
    string getDiagnosis() const { return diagnosis; }
    void setDiagnosis(string d) { diagnosis = d; }

    static void displayTotalPatients() {
        cout << "Total Patients: " << totalPatients << endl;
    }

    void display() const {
        cout << "Patient ID: " << id << ", Name: " << name << ", Diagnosis: " << diagnosis << endl;
    }
    
    void display(string info) const {
        if (info == "name") {
            cout << "Patient Name: " << name << endl;
        } else {
            display();
        }
    }
};

int Patient::totalPatients = 0;

class Doctor {
protected:
    string name;
    int id;
    string specialty;
    static int totalDoctors;

public:
    Doctor() : name(""), id(0), specialty("") {}
    Doctor(string n, int i, string s) : name(n), id(i), specialty(s) {
        totalDoctors++;
    }
    virtual ~Doctor() {
        totalDoctors--;
        cout << "Destructor called for doctor " << name << endl;
    }

    string getName() const { return name; }
    int getId() const { return id; }
    string getSpecialty() const { return specialty; }

    virtual void display() const = 0;

    static void displayTotalDoctors() {
        cout << "Total Doctors: " << totalDoctors << endl;
    }
};

int Doctor::totalDoctors = 0;

class SpecialistDoctor : public Doctor {
private:
    string subSpecialty;

public:
    SpecialistDoctor(string n, int i, string s, string ss) : Doctor(n, i, s), subSpecialty(ss) {}

    void display() const override {
        cout << "Specialist Doctor ID: " << id << ", Name: " << name << ", Specialty: " << specialty
             << ", Sub-Specialty: " << subSpecialty << endl;
    }
};

class SeniorDoctor : public SpecialistDoctor {
private:
    int experienceYears;

public:
    SeniorDoctor(string n, int i, string s, string ss, int years) 
        : SpecialistDoctor(n, i, s, ss), experienceYears(years) {}

    void display() const override {
        cout << "Senior Doctor ID: " << getId() << ", Name: " << getName() << ", Specialty: " << getSpecialty()
             << ", Experience: " << experienceYears << " years" << endl;
    }
};

// DiagnosisManager class handles diagnosis setting for patients
class DiagnosisManager {
public:
    static void diagnosePatient(Patient &p, const Doctor &d, string diagnosis) {
        p.setDiagnosis(diagnosis);
        cout << "Doctor " << d.getName() << " diagnosed Patient " << p.getName() << " with " << diagnosis << endl;
    }
};

class Room {
private:
    int roomNumber;
    bool isOccupied;
    Patient *currentPatient;

public:
    Room() : roomNumber(0), isOccupied(false), currentPatient(nullptr) {}
    Room(int num) : roomNumber(num), isOccupied(false), currentPatient(nullptr) {}

    ~Room() {
        cout << "Destructor called for room " << roomNumber << endl;
    }

    void admitPatient(Patient &p) {
        if (!isOccupied) {
            currentPatient = &p;
            isOccupied = true;
            cout << "Patient " << p.getName() << " admitted to room " << roomNumber << endl;
        } else {
            cout << "Room " << roomNumber << " is already occupied." << endl;
        }
    }

    void dischargePatient() {
        if (isOccupied) {
            cout << "Patient " << currentPatient->getName() << " discharged from room " << roomNumber << endl;
            currentPatient = nullptr;
            isOccupied = false;
        } else {
            cout << "Room " << roomNumber << " is already empty." << endl;
        }
    }

    void display() const {
        cout << "Room Number: " << roomNumber << ", Occupied: " << (isOccupied ? "Yes" : "No") << endl;
        if (isOccupied) {
            cout << "Current Patient: " << currentPatient->getName() << endl;
        }
    }
};

int main() {
    Patient p1("John Doe", 101, "Flu");

    cout << "Full Patient Display:" << endl;
    p1.display();

    cout << "\nPartial Patient Display (name only):" << endl;
    p1.display("name");

    Room r1(101);
    r1.admitPatient(p1);
    r1.display();

    SpecialistDoctor sd1("Dr. Specialist", 301, "Cardiology", "Pediatrics");
    DiagnosisManager::diagnosePatient(p1, sd1, "Cold");
    sd1.display();

    SeniorDoctor sr1("Dr. Senior", 401, "Cardiology", "Pediatrics", 20);
    sr1.display();

    Patient::displayTotalPatients();
    Doctor::displayTotalDoctors();

    return 0;
}
