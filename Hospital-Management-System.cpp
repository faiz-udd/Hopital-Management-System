//Library used for input output file
#include<iostream>
//library used for filing
#include<fstream>
//library to include system("clear"), pretty similar with iostream. input/output stream
#include<cstdio>
//used for string type of data types
#include<string>
//used for manupulation of console, like setw(), fillw() etc
#include<iomanip>

//Main functions are declared globaly
int chooseMain();
int main();
using namespace std;

//the password class
class Password {
	//string dataTypes, pass, x
	string pass;
	string x;
public:
//set password 
	void setPassword();
	//returns password to the system
	string getPassword();
	//verify the password, if matches with the previous one
	int verifyPassword();
	//make functions protected
	void passwordProtect();
};
//Password class member Functions definitions
void Password::setPassword() {
	cout << "Choose a password for your system:" << endl;
	cin >> pass;
}
string Password::getPassword() {
	return pass;
}
int Password::verifyPassword() {
	string x;
	cout << endl << "Enter the password:" << endl;
	cin >> x;
	if (x == pass)
		return 1;
	else
	return 0;
}
void Password::passwordProtect() {
	int verification = verifyPassword();
	if (verification == 1) {
		cout << endl << "Access Granted!" << endl;
	}
	else
	{ 
		do{
			cout << setw(40) << endl << " Incorrect password !! Access Denied!" << endl;
			cout << "TRY AGAIN" << endl;
			cin >> x;
		
		} while (x != getPassword());


	}
}

//Address class
class Address {
private:
	int house_no;
	int street_no;
	char sector [20];
	char city [20];
public:
//member Functions declarations
	void setData();
	void print();
};

//Member Fuctions declarations
void Address::setData() {
	cout << "Enter house number: ";
	cin >> house_no;
	cout << "Enter street number: ";
	cin >> street_no;
	cout << "Enter sector name: ";
	cin >> sector;
	cout << "Enter city name: ";
	cin >> city;	
}
void Address::print() {
	cout << "House number: " << house_no << endl;
	cout << "Street number: " << street_no << endl;
	cout << "Sector : " << sector << endl;
	cout << "city : " << city << endl;
}

//Person CLass

class Person {
protected://protected members of the class,
//data Members
	char name [20];
	char gender;
	unsigned int age;
	unsigned int ID;
	char mobile_no [20];

public:
//Member Functions
	void setName();
	void getName();
	void setID(unsigned int);
	unsigned int getID();
	
};
//Member Functions definitions
void Person::setName() {
	cout << "Enter name: ";
	cin >> name;
}
void Person::getName() {
	cout<< name;
}

void Person::setID(unsigned int id) {
	ID = id;
}
unsigned int Person::getID() {
	return ID;
}

//Patient CLass
class Patient :public Person {
protected:
//Protected Data members
	int bed_number;
	int ward_number;
	int floor_number;
	float drFess;
	float bedCharges;
	float medCharges;

public:
//public member Functions
	void setName();
	string getName();
	void setMobNo();
	void getMobNo();
	void setData();
	void print();
	void add_Patient(Patient);
	void showFile();
	void delete_Patient();
	void search_Patient();
	void modify();
	float operator+(Patient);
	void bill();

};
//Memeber Functions definitions
void Patient::setName() {
	cout << "Enter name: ";
	cin >> name;
}
string Patient::getName() {
	return name;
}
void Patient::setMobNo() {
	cout << "Enter Mobile number: ";
	cin >> mobile_no;
}
void Patient::getMobNo() {
	cout << mobile_no;
}

void Patient::setData() {
	Patient p;

	cout << "Enter the patient name :";
	cin >> name;
	cout << "Enter the patient gender (m/f) :";
	cin >> gender;
	//restrict the use to enter only f or m
	while (gender != 'm' && gender != 'f') {
		cout << "Enter correct gender (m/f): ";
		cin >> gender;
	}

	cout << "Enter the patient age :";
	cin >> age;
	cout << "Enter the patient ID :";
	cin >> ID;
	//objet of ifstream class  has been created, if stream is used for reading file.
	ifstream readFile;
	//open a file, with the name of patient.dat(dat is extension used for binary file.) file  opened in binary mode
	readFile.open("patient.dat", ios::binary);
	//set seekg() -->seekg is file pointer which point where to start reading in the file
	readFile.seekg(0);
	while (!readFile.eof()) {
		//start reading file
		readFile.read(reinterpret_cast<char*>(&p), sizeof(Patient));
//compare the id saved in the file, with the id of the new patient
		if (ID == p.ID) {
			cout << "This ID is already in use"<<endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
		
	}
	//close read mode of the file
	readFile.close();

	cout << "Enter the patient mobile number :";
	cin >> mobile_no;
	cout << "Enter the patient bed number :";
	cin >> bed_number;
	cout << "Enter the ward number :";
	cin >> ward_number;
	cout << "Enter the floor number :";
	cin >> floor_number;
	cout << endl << endl;
}
void Patient::print() {

	cout << "Name is ---> " << name << endl;
	cout << "Gender is ---> " << gender << endl;
	cout << "Age is ---> " << age << endl;
	cout << "Mobile number is ---> " << mobile_no << endl;
	cout << "ID is ---> " << ID << endl;
	cout << "Bed number is ---> " << bed_number << endl;
	cout << "Ward number is ---> " << ward_number << endl;
	cout << "floor number is ---> " << floor_number << endl << endl;
}
void Patient::add_Patient(Patient patient) {
	char ch;
	//ofstream class is used for writing in  file.
	//addpatient object of the ofstream(writing class) has been created
	ofstream addPatient;
	/*open the writing in the patient.dat file in "app" append mode, in append mode one data don't override the other
	basically what happens is append mode put the seekp() writing pointer to the end of the file, and writing start after that*/
	addPatient.open("patient.dat", ios::app |ios::binary);
	do {
		//set the Patient data
		patient.setData();
		//write the data of the patient to the binary file
		addPatient.write(reinterpret_cast<char*>(&patient), sizeof(Patient));
		cout << "Patient data added successfully" << endl << endl;
		cout << "Enter another person(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	//close the file
	addPatient.close();
}
void Patient::showFile() {
	Patient p{};
	char ch;
	unsigned int reqId;
	//totalPatients an object of ifstream class for reading the total number of patients written in the file
	ifstream totalPatients;
//open the file
	totalPatients.open("patient.dat", ios::binary);
	if (!totalPatients.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "***PATIENTS LIST***"<<endl;
		//until unless the file closes, print the name and id of the patients in the file
		while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {
			
			cout<<"ID: "<<p.ID<<"--> Name is : "<<p.name <<endl;
			
		}  
		//if all the patients have been read, end the loop and close the file
		  totalPatients.close();
	}
loop: {
	//if someone wants to check the details of the id, show all the details of the patient
	totalPatients.open("patient.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient)))
	{
		if (reqId == p.ID) {
			x++;
			p.print();
			break;
		}
	}
	//if the id is not amount the list of the pateints 
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	//close the file
	totalPatients.close();
	//check if the user want to check any other id
	cout << "Do you want to see other ID details(y/n): ";
	cin >> ch;
	//if the user want to check then go to the "loop" if not, break, and if enters something else show the the error
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n)";
			cin >> ch;

		}
	}
	
	}
}
void Patient::delete_Patient() {
	Patient p;
	unsigned int id;
	char ch;
	
	ifstream totalPatients;
	//show file list before deleting
	totalPatients.open("patient.dat", ios::binary);
	if (!totalPatients.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******PATIENTS LIST*******"  << endl<<endl;
		while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {

			cout << "ID: " << p.ID << "--> Name is : " << p.name << endl;

		}
		totalPatients.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Bill clearence
	p.bill();
	cout << "Did the patient pay total amount? (y/n): ";
	cin >> ch;

	if (ch == 'y') {
		//Deleting the object
		ifstream readFile;
		ofstream writeFile;
		readFile.open("patient.dat", ios::binary);
		if (!readFile.is_open()) {
			cout << "File not opening" << endl;
		}
		else {
			writeFile.open("temp.dat", ios::binary);
			readFile.seekg(0);
			while (readFile.read(reinterpret_cast<char*>(&p), sizeof(Patient)))
			{
				if (p.ID != id) {
					writeFile.write(reinterpret_cast<char*>(&p), sizeof(Patient));
				}

			}


		}
		writeFile.close();
		readFile.close();
		remove("patient.dat");
		rename("temp.dat", "patient.dat");
		cout << "The patient delete successfully" << endl<<endl;

		//showing the list after deleting
		totalPatients.open("patient.dat", ios::binary);
		if (!totalPatients.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******PATIENTS LIST*******" << endl<<endl;
			while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {

				cout << "ID: " << p.ID << "--> Name is : " << p.name << endl;

			}
			totalPatients.close();
		}

	}
	else
	{
		cout << "First clear the payment!" << endl<<endl;
	}
}
void Patient::search_Patient() {
	Patient p;
	char ch;
	ifstream patientslist;
	unsigned int reqId;
	
	
	do
	{
		int x = 0;
		cout << "Enter ID of the Patient you want to search" << endl;
		cin >> reqId;
		patientslist.open("patient.dat", ios::binary);
		if (!patientslist.is_open())
		{
			cout << "Error Occured while opening File" << endl;
		}
		else {
			patientslist.seekg(0);
			while (patientslist.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {

				if (reqId == p.ID) {
					x++;
					p.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			cout << "Do you want to search other ID (y/n): ";
			cin >> ch;
		}
		patientslist.close();
	} while (ch=='y');

	
}
void Patient::modify() {
	int position, x = 0;
	char ch,choise;
	unsigned int reqId,id;
	Patient p{};
	
	do{
	ifstream totalPatients;
	//show file list before modify
	totalPatients.open("patient.dat", ios::binary);
	if (!totalPatients.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******PATIENTS LIST*******" << endl << endl;
		while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {

			cout << "ID: " << p.ID << "--> Name is : " << p.name << endl;

		}
		totalPatients.close();
	}

	
	
		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("patient.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&p), sizeof(Patient));
			if (fs) {

				if (p.ID == id) {
					x = 1;
					p.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&p), sizeof(Patient));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalPatients.open("patient.dat", ios::binary);
		if (!totalPatients.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******PATIENTS LIST*******" << endl << endl;
			while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient))) {

				cout << "ID: " << p.ID << "--> Name is : " << p.name << endl;

			}
			totalPatients.close();
		}

		//see id details
	loop: {
		totalPatients.open("patient.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalPatients.read(reinterpret_cast<char*>(&p), sizeof(Patient)))
		{
			if (reqId == p.ID) {
				x++;
				p.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalPatients.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise=='y');
}

float Patient::operator+(Patient p) {
	float totalCharges;
	totalCharges = p.drFess + p.bedCharges + p.medCharges;
	return totalCharges;
}
void Patient::bill() {
	float totalBill;
	cout << "Enter the doctor fees: ";
	cin >> drFess;
	cout << "Enter the bed charges: ";
	cin >> bedCharges;
	cout << "Enter the medicines charges: ";
	cin >> medCharges;
	totalBill = drFess + bedCharges + medCharges;
	cout<<"Total charges is: "<< totalBill<<endl;
}
//class person publically inherited from the class person
class Employee :public Person {
protected:
	char profession [10];

public:
	void setProfession();
	void print();

};
//Doctor class inherited From the employee class
class Doctor :public Employee {
public:
	char specialization [20];

public:
//Functions Declarations
	void setName();
	string getName();
	void setSpec();
	void getSpec();
	void setMobNo();
	void getMobNo();
	void setData();
	void print();
	void add_Doctor(Doctor);
	void showFile();
	void delete_Doctor();
	void search_doctor();
	void modify();

};
//Functions definitions
void Doctor::setName() {
	cout << "Enter name: ";
	cin >> name;
}
string Doctor::getName() {
	return name;
}
void Doctor::setSpec() {
	cout << "Enter specialization: ";
	cin >> specialization;
}
void Doctor::getSpec() {
	cout << specialization;
}
void Doctor::setMobNo() {
	cout << "Enter Mobile number: ";
	cin >> mobile_no;
}
void Doctor::getMobNo() {
	cout << mobile_no;
}
//set all the Doctor Data
void Doctor::setData() {
	Doctor d;
	ifstream readFile;
	cout << "Enter the doctor name :";
	cin >> name;
	cout << "Enter the doctor gender :";
	cin >> gender;
	while (gender != 'm' && gender != 'f') {
		cout << "Enter correct gender (m/f): ";
		cin >> gender;
	}
	cout << "Enter the doctor specialization :";
	cin >> specialization;
	cout << "Enter the doctor age :";
	cin >> age;
	cout << "Enter the doctor ID :";
	cin >> ID;

	readFile.open("doctor.dat", ios::binary);
	readFile.seekg(0);
	while (!readFile.eof()) {
		readFile.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
		if (ID == d.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
		readFile.close();
	}

	cout << "Enter the doctor mobile number :";
	cin >> mobile_no;
	cout << endl << endl;
}
void Doctor::print() {
	cout << "Name is ---> " << name<<endl;
	cout << "Gender is ---> " << gender << endl;
	cout << "Specializatin is ---> " << specialization << endl;
	cout << "Age is ---> " << age << endl;
	cout << "ID is ---> " << ID << endl;
	cout << "Mobile number is ---> " << mobile_no << endl << endl;
}
void Doctor::add_Doctor(Doctor doctor) {
	char ch;
	ofstream addDoctor;
	addDoctor.open("doctor.dat", ios::app | ios::binary);
	do {
		doctor.setData();
		addDoctor.write(reinterpret_cast<char*>(&doctor), sizeof(Doctor));
		cout << "Doctor data added successfully" << endl << endl;
		cout << "Enter another person(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	addDoctor.close();
}
//show the list of all the doctors
void Doctor::showFile() {
		Doctor d;
		char ch;
		unsigned int reqId;
		ifstream totalDoctors;

		totalDoctors.open("doctor.dat", ios::binary);
		if (!totalDoctors.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "****DOCTORS LIST****" << endl;
			while (totalDoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {

				cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

			}
			totalDoctors.close();
		}
	loop: {
		totalDoctors.open("doctor.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalDoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor)))
		{
			if (reqId == d.ID) {
				x++;
				d.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalDoctors.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n): ";
				cin >> ch;
				goto loop;
			}
		
		}
		}
	
}
void Doctor::delete_Doctor() {
	Doctor d;
	unsigned int id;

	//showing list before deleting
	ifstream totalDoctors;
	totalDoctors.open("doctor.dat", ios::binary);
	if (!totalDoctors.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "***DOCTORS LIST***"<<endl;
		while (totalDoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totalDoctors.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;


	//deleting boject
	ifstream readFile;
	ofstream writeFile;
	readFile.open("doctor.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&d), sizeof(Doctor)))
		{
			if (d.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&d), sizeof(Doctor));
			}
		}
	}
	writeFile.close();
	readFile.close();
	remove("doctor.dat");
	rename("temp.dat", "doctor.dat");
	cout << "The doctor delete successfully" << endl;

	//showing list after deleting
	totalDoctors.open("doctor.dat", ios::binary);
	if (!totalDoctors.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "***DOCTORS LIST***" << endl;
		while (totalDoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totalDoctors.close();
	}

}
void Doctor::search_doctor() {
	Doctor doctor;
	char ch;
	ifstream DoctorsList;
	unsigned int reqId;
	
	do
	{
		int x = 0;
		cout << "Enter ID of the Doctor you want to search" << endl;
		cin >> reqId;


		DoctorsList.open("doctor.dat", ios::binary);
		if (!DoctorsList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (DoctorsList.read(reinterpret_cast<char*>(&doctor), sizeof(Doctor))) {

				if (reqId == doctor.ID) {
					x++;
					doctor.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			
			cout << "Do you want to search other ID (y/n): ";
			cin >> ch;
		}
		DoctorsList.close();
	} while (ch=='y');
	
}
void Doctor::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	Doctor d{};

	do{
	ifstream totaldoctors;
	//show file list before modify
	totaldoctors.open("doctor.dat", ios::binary);
	if (!totaldoctors.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******DOCTORS LIST*******" << endl << endl;
		while (totaldoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totaldoctors.close();
	}

	
	
		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("doctor.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
			if (fs) {

				if (d.ID == id) {
					x = 1;
					d.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&d), sizeof(Doctor));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totaldoctors.open("doctor.dat", ios::binary);
		if (!totaldoctors.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******DOCTORS LIST*******" << endl << endl;
			while (totaldoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor))) {

				cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

			}
			totaldoctors.close();
		}

		//see id details
	loop: {
		totaldoctors.open("doctor.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totaldoctors.read(reinterpret_cast<char*>(&d), sizeof(Doctor)))
		{
			if (reqId == d.ID) {
				x++;
				d.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totaldoctors.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}

//Nurse CLass, publically inherited From Employee
class Nurse :public Employee {
public:
	void setData();
	void print();
	void add_Nurse(Nurse);
	void showFile();
	void delete_Nurse();
	void search_Nurse();
	void modify();
};
void Nurse::setData() {
	Nurse n;

	cout << "Enter the nurse name :";
	cin >> name;
	cout << "Enter the nurse gender :";
	cin >> gender;
	while (gender != 'm' && gender != 'f') {
		cout << "Enter correct gender (m/f): ";
		cin >> gender;
	}
	cout << "Enter the nurse age :";
	cin >> age;
	cout << "Enter the nurse ID :";
	cin >> ID;


	ifstream readFile;
	readFile.open("nurse.dat", ios::binary);
	readFile.seekg(0);
	while (readFile.read(reinterpret_cast<char*>(&n), sizeof(Nurse))) {

		if (ID == n.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
	}
	cout << "Enter the nurse mobile number :";
	cin >> mobile_no;
	cout << endl << endl;
}
void Nurse::print() {
	cout << "Name is ---> " << name << endl;
	cout << "Gender is ---> " << gender << endl;
	cout << "Age is ---> " << age << endl;
	cout << "ID is ---> " << ID << endl;
	cout << "Mobile number is ---> " << mobile_no << endl<<endl;
}
void Nurse::add_Nurse(Nurse nurse) {
	char ch;
	ofstream addNurse;
	addNurse.open("nurse.dat", ios::app | ios::binary);
	do {
		nurse.setData();
		addNurse.write(reinterpret_cast<char*>(&nurse), sizeof(Nurse));
		cout << "Nurse data added successfully" << endl << endl;
		cout << "Enter another person(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	addNurse.close();
}
void Nurse::showFile() {
	Nurse n;
	unsigned int reqId;
	char ch;
	ifstream totalNurses;

	totalNurses.open("nurse.dat", ios::binary);
	if (!totalNurses.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "****NURSES LIST****" << endl;
		while (totalNurses.read(reinterpret_cast<char*>(&n), sizeof(Nurse))) {

			cout << "ID: " << n.ID << "--> Name is : " << n.name << endl;

		}
		totalNurses.close();
	}
loop: {
	totalNurses.open("nurse.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalNurses.read(reinterpret_cast<char*>(&n), sizeof(Nurse)))
	{
		if (reqId == n.ID) {
			x++;
			n.print();
			break;
		}
	}
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	totalNurses.close();

	cout << "Do you want to see other ID details(y/n)";
	cin >> ch;
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n)";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n)";
			cin >> ch;
			goto loop;
		}
		goto loop;
	}
	}
}
void Nurse::delete_Nurse() {
	Nurse n;
	unsigned int id;

	ifstream totalNurse;
	//show file list before deleting
	totalNurse.open("nurse.dat", ios::binary);
	if (!totalNurse.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******NURSES LIST*******" << endl;
		while (totalNurse.read(reinterpret_cast<char*>(&n), sizeof(Nurse))) {

			cout << "ID: " << n.ID << "--> Name is : " << n.name << endl;

		}
		totalNurse.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Deleting the object
	ifstream readFile;
	ofstream writeFile;
	readFile.open("nurse.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&n), sizeof(Nurse)))
		{
			if (n.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&n), sizeof(Nurse));
			}

		}


	}
	writeFile.close();
	readFile.close();
	remove("nurse.dat");
	rename("temp.dat", "nurse.dat");
	cout << "The nurse delete successfully" << endl;

	//showing the list after deleting
	totalNurse.open("nurse.dat", ios::binary);
	if (!totalNurse.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******NURSES LIST*******" << endl;
		while (totalNurse.read(reinterpret_cast<char*>(&n), sizeof(Nurse))) {

			cout << "ID: " << n.ID << "--> Name is : " << n.name << endl;

		}
		totalNurse.close();
	}
}
void Nurse::search_Nurse() {

	Nurse nurse;
	char ch;
	ifstream NursesList;
	unsigned int reqId;
	
	do
	{
		int x = 0;
		cout << "Enter ID of the Nurse you want to search" << endl;
		cin >> reqId;


		NursesList.open("nurse.dat", ios::binary);
		if (!NursesList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (NursesList.read(reinterpret_cast<char*>(&nurse), sizeof(Nurse))) {

				if (reqId == nurse.ID) {
					x++;
					nurse.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			
		}
		cout << "Do you want to search other ID (y/n): ";
		cin >> ch;
		NursesList.close();
	} while (ch=='y');
	
}
void Nurse::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	Nurse n{};

	do{
	ifstream totalNurses;
	//show file list before modify
	totalNurses.open("nurse.dat", ios::binary);
	if (!totalNurses.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******NURSES LIST*******" << endl << endl;
		while (totalNurses.read(reinterpret_cast<char*>(&n), sizeof(Nurse))) {

			cout << "ID: " << n.ID << "--> Name is : " << n.name << endl;

		}
		totalNurses.close();
	}

	
		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("nurse.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&n), sizeof(Nurse));
			if (fs) {

				if (n.ID == id) {
					x = 1;
					n.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&n), sizeof(Nurse));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalNurses.open("nurse.dat", ios::binary);
		if (!totalNurses.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******NURSES LIST*******" << endl << endl;
			while (totalNurses.read(reinterpret_cast<char*>(&n), sizeof(Nurse))) {

				cout << "ID: " << n.ID << "--> Name is : " << n.name << endl;

			}
			totalNurses.close();
		}

		//see id details
	loop: {
		totalNurses.open("nurse.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalNurses.read(reinterpret_cast<char*>(&n), sizeof(Nurse)))
		{
			if (reqId == n.ID) {
				x++;
				n.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalNurses.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}


class Ward_attendent :public Employee {
protected:

public:
	void setData();
	void print();
	void add_Ward_attendent(Ward_attendent);
	void showFile();
	void delete_Ward_attendent();
	void search_Ward_attendent();
	void modify();
};
void Ward_attendent::setData() {
	Ward_attendent w;

	cout << "Enter the Ward_attendent name :";
	cin >> name;
	cout << "Enter the Ward_attendent gender :";
	cin >> gender;
	while (gender != 'm' && gender != 'f') {
		cout << "Enter correct gender (m/f): ";
		cin >> gender;
	}
	cout << "Enter the Ward_attendent age :";
	cin >> age;
	cout << "Enter the Ward_attendent ID :";
	cin >> ID;

	ifstream readFile;
	readFile.open("ward_attendent.dat", ios::binary);
	readFile.seekg(0);
	while (readFile.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent))) {

		if (ID == w.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
	}
	cout << "Enter the Ward_attendent mobile number :";
	cin >> mobile_no;
	cout << endl << endl;
}
void Ward_attendent::print() {
	cout << "Name is ---> " << name << endl;
	cout << "Gender is ---> " << gender << endl;
	cout << "Age is ---> " << age << endl;
	cout << "ID is ---> " << ID << endl;
	cout << "Mobile number is ---> " << mobile_no << endl << endl;
}
void Ward_attendent::add_Ward_attendent(Ward_attendent ward_attendent) {
	char ch;
	ofstream addWard_attendent;
	addWard_attendent.open("ward_attendent.dat", ios::app | ios::binary);
	do {
		ward_attendent.setData();
		addWard_attendent.write(reinterpret_cast<char*>(&ward_attendent), sizeof(Ward_attendent));
		cout << "Ward_attendent data added successfully" << endl << endl;
		cout << "Enter another person(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	addWard_attendent.close();
}
void Ward_attendent::showFile() {
	Ward_attendent w;
	char ch;
	unsigned int reqId;
	ifstream totalWard_attendent;

	totalWard_attendent.open("ward_attendent.dat", ios::binary);
	if (!totalWard_attendent.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "*****WARD ATTENDENT LIST*****" << endl;
		while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent))) {

			cout << "ID: " << w.ID << "--> Name is : " << w.name << endl;

		}
		totalWard_attendent.close();
	}
loop: {
	totalWard_attendent.open("ward_attendent.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent)))
	{
		if (reqId == w.ID) {
			x++;
			w.print();
			break;
		}
	}
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	totalWard_attendent.close();

	cout << "Do you want to see other ID details(y/n): ";
	cin >> ch;
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			goto loop;
		}
		
	}
	}
}
void Ward_attendent::delete_Ward_attendent() {
	Ward_attendent w;
	unsigned int id;

	ifstream totalWard_attendent;
	//show file list before deleting
	totalWard_attendent.open("ward_attendent.dat", ios::binary);
	if (!totalWard_attendent)
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******WARD_ATTENDENT LIST*******" << endl;
		while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent))) {

			cout << "ID: " << w.ID << "--> Name is : " << w.name << endl;

		}
		totalWard_attendent.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Deleting the object
	ifstream readFile;
	ofstream writeFile;
	readFile.open("ward_attendent.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent)))
		{
			if (w.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&w), sizeof(Ward_attendent));
			}

		}

	}
	writeFile.close();
	readFile.close();
	remove("ward_attendent.dat");
	rename("temp.dat", "ward_attendent.dat");
	cout << "The ward_attendent delete successfully" << endl;

	//showing the list after deleting
	totalWard_attendent.open("ward_attendent.dat", ios::binary);
	if (!totalWard_attendent.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******WARD_ATTENDEND LIST*******" << endl;
		while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent))) {

			cout << "ID: " << w.ID << "--> Name is : " << w.name << endl;

		}
		totalWard_attendent.close();
	}
}
void Ward_attendent::search_Ward_attendent() {
	Ward_attendent wardAttendent;
	char ch;
	ifstream WardAttendentsList;
	unsigned int reqId;

	do
	{
		int x = 0;
		cout << "Enter ID of the ward Attendents you want to search" << endl;
		cin >> reqId;
		WardAttendentsList.open("ward_attendent.dat", ios::binary);
		if (!WardAttendentsList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (WardAttendentsList.read(reinterpret_cast<char*>(&wardAttendent), sizeof(Ward_attendent))) {

				if (reqId == wardAttendent.ID) {
					x++;
					wardAttendent.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}

		}
		cout << "Do you want to search other ID (y/n): ";
		cin >> ch;
		WardAttendentsList.close();
	} while (ch == 'y');
	
}
void Ward_attendent::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	Ward_attendent w{};

	do{
	ifstream totalWard_attendent;
	//show file list before modify
	totalWard_attendent.open("ward_attendent.dat", ios::binary);
	if (!totalWard_attendent.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******WARD ATTENDENTS LIST*******" << endl << endl;
		while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent))) {

			cout << "ID: " << w.ID << "--> Name is : " << w.name << endl;

		}
		totalWard_attendent.close();
	}
	
		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("ward_attendent.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent));
			if (fs) {

				if (w.ID == id) {
					x = 1;
					w.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&w), sizeof(Ward_attendent));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalWard_attendent.open("ward_attendent.dat", ios::binary);
		if (!totalWard_attendent.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******WARD ATTENDENTS LIST*******" << endl << endl;
			while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent))) {

				cout << "ID: " << w.ID << "--> Name is : " << w.name << endl;

			}
			totalWard_attendent.close();
		}

		//see id details
	loop: {
		totalWard_attendent.open("ward_attendent.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalWard_attendent.read(reinterpret_cast<char*>(&w), sizeof(Ward_attendent)))
		{
			if (reqId == w.ID) {
				x++;
				w.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalWard_attendent.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}


class Driver :public Employee {
protected:
	
	char licenseNo [20];
	char onDuty;
public:
	
	void setData();
	void print();
	void add_Driver(Driver);
	void showFile();
	void delete_Driver();
	void search_Driver();
	void modify();
};
void Driver::setData() {
	Driver d{};
	cout << "Enter the driver name :";
	cin >> name;
	cout << "Enter the driver gender :";
	cin >> gender;
	while (gender != 'm' && gender != 'f') {
		cout << "Enter correct gender (m/f): ";
		cin >> gender;
	}
	cout << "Enter the driver age :";
	cin >> age;
	cout << "Enter the driver ID :";
	cin >> ID;

	ifstream readFile;
	readFile.open("driver.dat", ios::binary);
	readFile.seekg(0);
	while (readFile.read(reinterpret_cast<char*>(&d), sizeof(Driver))) {

		if (ID == d.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
			break;
		}
	}
	cout << "Enter the driver mobile number :";
	cin >> mobile_no;
	cout << "Enter the driver license number :";
	cin >> licenseNo;
	cout <<endl << endl;
}
void Driver::print() {
	cout << "Name is ---> " << name << endl;
	cout << "Gender is ---> " << gender << endl;
	cout << "Age is ---> " << age << endl;
	cout << "ID is ---> " << ID << endl;
	cout << "Mobile number is ---> " << mobile_no << endl;
	cout << "License number is ---> " << licenseNo << endl << endl;
}
void Driver::add_Driver(Driver driver) {
	char ch;
	ofstream addDriver;
	addDriver.open("driver.dat", ios::app | ios::binary);
	do {
		driver.setData();
		addDriver.write(reinterpret_cast<char*>(&driver), sizeof(Driver));
		cout << "Driver data added successfully" << endl << endl;
		cout << "Enter another person(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	addDriver.close();
}
void Driver::showFile() {
	Driver d;
	char ch;
	unsigned int reqId;
	ifstream totalDriver;

	totalDriver.open("driver.dat", ios::binary);
	if (!totalDriver.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "*****DRIVERS LIST*****" << endl;
		while (totalDriver.read(reinterpret_cast<char*>(&d), sizeof(Driver))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totalDriver.close();
	}
loop: {
	totalDriver.open("driver.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalDriver.read(reinterpret_cast<char*>(&d), sizeof(Driver)))
	{
		if (reqId == d.ID) {
			x++;
			d.print();
			break;
		}
	}
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	totalDriver.close();
	cout << "Do you want to see other ID details(y/n): ";
	cin >> ch;
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			goto loop;
		}

	}
	}
}
void Driver::delete_Driver() {
	Driver d;
	unsigned int id;

	ifstream totalDrivers;
	//show file list before deleting
	totalDrivers.open("driver.dat", ios::binary);
	if (!totalDrivers.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******DRIVERS LIST*******" << endl;
		while (totalDrivers.read(reinterpret_cast<char*>(&d), sizeof(Driver))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totalDrivers.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Deleting the object
	ifstream readFile;
	ofstream writeFile;
	readFile.open("driver.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&d), sizeof(Driver)))
		{
			if (d.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&d), sizeof(Driver));
			}

		}

	}
	writeFile.close();
	readFile.close();
	remove("driver.dat");
	rename("temp.dat", "driver.dat");
	cout << "The driver delete successfully" << endl;

	//showing the list after deleting
	totalDrivers.open("driver.dat", ios::binary);
	if (!totalDrivers.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******DRIVERS LIST*******" << endl;
		while (totalDrivers.read(reinterpret_cast<char*>(&d), sizeof(Driver))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totalDrivers.close();
	}
}
void Driver::search_Driver() {
	Driver driver;
	char ch;
	ifstream driverList;
	unsigned int reqId;
	
	do
	{
		int x = 0;
		cout << "Enter ID of the Driver you want to search" << endl;
		cin >> reqId;

		driverList.open("driver.dat", ios::binary);
		if (!driverList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (driverList.read(reinterpret_cast<char*>(&driver), sizeof(Driver))) {

				if (reqId == driver.ID) {
					x++;
					driver.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			cout << "Do you want to search other ID (y/n): ";
			cin >> ch;
			
		}
		driverList.close();
	} while (ch=='y');
	
}
void Driver::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	Driver d{};

	do{
	//show file list before modify
	ifstream totalDrivers;
	totalDrivers.open("driver.dat", ios::binary);
	if (!totalDrivers.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******DRIVERS LIST*******" << endl << endl;
		while (totalDrivers.read(reinterpret_cast<char*>(&d), sizeof(Driver))) {

			cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

		}
		totalDrivers.close();
	}

		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("driver.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&d), sizeof(Driver));
			if (fs) {

				if (d.ID == id) {
					x = 1;
					d.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&d), sizeof(Driver));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalDrivers.open("driver.dat", ios::binary);
		if (!totalDrivers.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******DRIVERS LIST*******" << endl << endl;
			while (totalDrivers.read(reinterpret_cast<char*>(&d), sizeof(Driver))) {

				cout << "ID: " << d.ID << "--> Name is : " << d.name << endl;

			}
			totalDrivers.close();
		}

		//see id details
	loop: {
		totalDrivers.open("driver.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalDrivers.read(reinterpret_cast<char*>(&d), sizeof(Driver)))
		{
			if (reqId == d.ID) {
				x++;
				d.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalDrivers.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}


class ClassFour :public Employee {
protected:
	char workType [20];
public:
	void setData();
	void print();
	void add_ClassFour(ClassFour);
	void showFile();
	void delete_ClassFour();
	void search_ClassFour();
	void modify();
};
void ClassFour::setData() {
	ClassFour c;

	cout << "Enter the ClassFour name :";
	cin >> name;
	cout << "Enter the ClassFour gender :";
	cin >> gender;
	while (gender != 'm' && gender != 'f') {
		cout << "Enter correct gender (m/f): ";
		cin >> gender;
	}
	cout << "Enter the ClassFour age :";
	cin >> age;
	cout << "Enter the ClassFour ID: ";
	cin >> ID;

	ifstream readFile;
	readFile.open("classFour.dat", ios::binary);
	readFile.seekg(0);
	while (readFile.read(reinterpret_cast<char*>(&c), sizeof(ClassFour))) {

		if (ID == c.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
	}
	cout << "Enter the ClassFour mobile number: ";
	cin >> mobile_no;
	cout << "Enter the ClassFour work type: ";
	cin >> workType;
	cout << endl << endl;
}
void ClassFour::print() {
	cout << "Name is ---> " << name << endl;
	cout << "Gender is ---> " << gender << endl;
	cout << "Age is ---> " << age << endl;
	cout << "ID is ---> " << ID << endl;
	cout << "Mobile number is ---> " << mobile_no << endl;
	cout << "Work type is ---> " << workType << endl << endl;
}
void ClassFour::add_ClassFour(ClassFour classfour) {
	char ch;
	ofstream addClassFour;
	addClassFour.open("classFour.dat", ios::app | ios::binary);
	do {
		classfour.setData();
		addClassFour.write(reinterpret_cast<char*>(&classfour), sizeof(ClassFour));
		cout << "ClassFour data added successfully" << endl << endl;
		cout << "Enter another person(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	addClassFour.close();
}
void ClassFour::showFile() {
	ClassFour cf;
	char ch;
	unsigned int reqId;
	ifstream totalClassFour;

	totalClassFour.open("classFour.dat", ios::binary);
	if (!totalClassFour.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "*****CLASSFOURS LIST*****" << endl;
		while (totalClassFour.read(reinterpret_cast<char*>(&cf), sizeof(ClassFour))) {

			cout << "ID: " << cf.ID << "--> Name is : " << cf.name << endl;

		}
		totalClassFour.close();
	}
loop: {
	totalClassFour.open("classFour.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalClassFour.read(reinterpret_cast<char*>(&cf), sizeof(ClassFour)))
	{
		if (reqId == cf.ID) {
			x++;
			cf.print();
			break;
		}
	}
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	totalClassFour.close();
	cout << "Do you want to see other ID details(y/n): ";
	cin >> ch;
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			goto loop;
		}

	}
	}
}
void ClassFour::delete_ClassFour() {
	ClassFour c;
	unsigned int id;

	ifstream totalClassFour;
	//show file list before deleting
	totalClassFour.open("classFour.dat", ios::binary);
	if (!totalClassFour.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******CLASSFOURS LIST*******" << endl;
		while (totalClassFour.read(reinterpret_cast<char*>(&c), sizeof(ClassFour))) {

			cout << "ID: " << c.ID << "--> Name is : " << c.name << endl;

		}
		totalClassFour.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Deleting the object
	ifstream readFile;
	ofstream writeFile;
	readFile.open("classFour.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&c), sizeof(ClassFour)))
		{
			if (c.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&c), sizeof(ClassFour));
			}

		}

	}
	writeFile.close();
	readFile.close();
	remove("classFour.dat");
	rename("temp.dat", "classFour.dat");
	cout << "The classFour delete successfully" << endl<<endl;

	//showing the list after deleting
	totalClassFour.open("classFour.dat", ios::binary);
	if (!totalClassFour.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******CLASSFOURS LIST*******" << endl;
		while (totalClassFour.read(reinterpret_cast<char*>(&c), sizeof(ClassFour))) {

			cout << "ID: " << c.ID << "--> Name is : " << c.name << endl;

		}
		totalClassFour.close();
	}
}
void ClassFour::search_ClassFour() {
	ClassFour classFour;
	char ch;
	ifstream classFourList;
	unsigned int reqId;

	do
	{
		int x = 0;
		cout << "Enter ID of the ClassFour you want to search: " << endl;
		cin >> reqId;

		classFourList.open("classFour.dat", ios::binary);
		if (!classFourList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (classFourList.read(reinterpret_cast<char*>(&classFour), sizeof(ClassFour))) {

				if (reqId == classFour.ID) {
					x++;
					classFour.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			cout << "Do you want to search other ID (y/n): ";
			cin >> ch;

		}
		classFourList.close();
	} while (ch == 'y');
	
}
void ClassFour::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	ClassFour cf{};

	do{

	//show file list before modify
	ifstream totalClassFours;
	totalClassFours.open("classFour.dat", ios::binary);
	if (!totalClassFours.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******CLASSFOURS LIST*******" << endl << endl;
		while (totalClassFours.read(reinterpret_cast<char*>(&cf), sizeof(ClassFour))) {

			cout << "ID: " << cf.ID << "--> Name is : " << cf.name << endl;

		}
		totalClassFours.close();
	}

		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("classFour.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&cf), sizeof(ClassFour));
			if (fs) {

				if (cf.ID == id) {
					x = 1;
					cf.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&cf), sizeof(ClassFour));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalClassFours.open("classFour.dat", ios::binary);
		if (!totalClassFours.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******CLASSFOURS LIST*******" << endl << endl;
			while (totalClassFours.read(reinterpret_cast<char*>(&cf), sizeof(ClassFour))) {

				cout << "ID: " << cf.ID << "--> Name is : " << cf.name << endl;

			}
			totalClassFours.close();
		}

		//see id details
	loop: {
		totalClassFours.open("classFour.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalClassFours.read(reinterpret_cast<char*>(&cf), sizeof(ClassFour)))
		{
			if (reqId == cf.ID) {
				x++;
				cf.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalClassFours.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}

class Ambulance {
private:
	unsigned int ID;
	char model [10];
	char company [20];
	Driver driver;
	char ambulanceAvailable;
public:
	void setData();
	void print();
	void addAmbulance(Ambulance);
	void showFile();
	void deleteAmbulance();
	void searchAmbulance();
	void modify();
	void ambulanceService();
};
void Ambulance::setData() {
	Ambulance a;

	cout << "Enter ID of ambulance: ";
	cin >> ID;

	ifstream readFile;
	readFile.open("ambulance.dat", ios::binary);
	readFile.seekg(0);
	while (readFile.read(reinterpret_cast<char*>(&a), sizeof(Ambulance))) {

		if (ID == a.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
	}
	cout << "Enter model of ambulance: ";
	cin >> model;
	cout << "Enter company of ambulance: ";
	cin >> company;
	cout << "*******driver*******"<<endl;
     driver.setData();
}
void Ambulance::print() {
	cout << "ID of ambulance: " << ID << endl;
	cout << "Model of ambulance: "<<model<<endl;
	cout << "Company of ambulance: "<<company<<endl;
	cout << "**********Driver********"<<endl;
	driver.print();
}
void Ambulance::addAmbulance(Ambulance ambulance) {
	char ch;
	ofstream addAmbulance;
	addAmbulance.open("ambulance.dat", ios::app | ios::binary);
	do {
		ambulance.setData();
		addAmbulance.write(reinterpret_cast<char*>(&ambulance), sizeof(Ambulance));
		cout << "Ambulance data added successfully" << endl << endl;
		cout << "Enter another Data(y/n)? : " << endl;
		cin >> ch;
	} while (ch == 'y');
	addAmbulance.close();
}
void Ambulance::showFile() {
	Ambulance a;
	Driver driver;
	char ch;
	unsigned int reqId;
	ifstream totalAmbulance;

	totalAmbulance.open("ambulance.dat", ios::binary);
	if (!totalAmbulance.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "*****AMBULANCES LIST*****" << endl;
		while (totalAmbulance.read(reinterpret_cast<char*>(&a), sizeof(Ambulance))) {

			cout << "  ID is: " << a.ID<<endl;

		}
		totalAmbulance.close();
	}
loop: {
	totalAmbulance.open("ambulance.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalAmbulance.read(reinterpret_cast<char*>(&a), sizeof(Ambulance)))
	{
		if (reqId == a.ID) {
			x++;
			a.print();
			break;
		}
	}
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	totalAmbulance.close();
	cout << "Do you want to see other ID details(y/n): ";
	cin >> ch;
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			goto loop;
		}

	}
	}
}
void Ambulance::deleteAmbulance() {
	Ambulance a;
	unsigned int id;

	ifstream totalAmbulance;
	//show file list before deleting
	totalAmbulance.open("ambulance.dat", ios::binary);
	if (!totalAmbulance.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******AMBULANCE LIST*******" << endl;
		while (totalAmbulance.read(reinterpret_cast<char*>(&a), sizeof(Ambulance))) {

			cout << "ID is: " << a.ID << "--> Driver name is : "; driver.getName(); cout << endl;

		}
		totalAmbulance.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Deleting the object
	ifstream readFile;
	ofstream writeFile;
	readFile.open("ambulance.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&a), sizeof(Ambulance)))
		{
			if (a.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&a), sizeof(Ambulance));
			}

		}

	}
	writeFile.close();
	readFile.close();
	remove("ambulance.dat");
	rename("temp.dat", "ambulance.dat");
	cout << "The ambulance delete successfully" << endl << endl;

	//showing the list after deleting
	totalAmbulance.open("ambulance.dat", ios::binary);
	if (!totalAmbulance.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******AMBULANCE LIST*******" << endl<<endl;
		while (totalAmbulance.read(reinterpret_cast<char*>(&a), sizeof(Ambulance))) {

			cout << "ID is: " << a.ID << "--> Driver name is : "; driver.getName(); cout << endl;

		}
		totalAmbulance.close();
	}
}
void Ambulance::searchAmbulance() {
	Ambulance ambulance;
	char ch;
	ifstream ambulanceList;
	unsigned int reqId;
	
	do
	{
		int x = 0;
		cout << "Enter ID of the Ambulance you want to search" << endl;
		cin >> reqId;

		ambulanceList.open("ambulance.dat", ios::binary);
		if (!ambulanceList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (ambulanceList.read(reinterpret_cast<char*>(&ambulance), sizeof(Ambulance))) {

				if (reqId == ambulance.ID) {
					x++;
					ambulance.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			cout << "Do you want to search other ID (y/n): ";
			cin >> ch;
		}
		ambulanceList.close();
	} while (ch=='y');
	
}
void Ambulance::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	Ambulance a{};


	do{
	//show file list before modify
	ifstream totalAmbulances;
	totalAmbulances.open("ambulance.dat", ios::binary);
	if (!totalAmbulances.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******AMBULANCES LIST*******" << endl << endl;
		while (totalAmbulances.read(reinterpret_cast<char*>(&a), sizeof(Ambulance))) {

			cout << "ID: " << a.ID << endl;

		}
		totalAmbulances.close();
	}

		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("ambulance.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&a), sizeof(Ambulance));
			if (fs) {

				if (a.ID == id) {
					x = 1;
					a.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&a), sizeof(Ambulance));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalAmbulances.open("ambulance.dat", ios::binary);
		if (!totalAmbulances.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******AMBULANCES LIST*******" << endl << endl;
			while (totalAmbulances.read(reinterpret_cast<char*>(&a), sizeof(Ambulance))) {

				cout << "ID: " << a.ID <<endl;

			}
			totalAmbulances.close();
		}

		//see id details
	loop: {
		totalAmbulances.open("ambulance.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalAmbulances.read(reinterpret_cast<char*>(&a), sizeof(Ambulance)))
		{
			if (reqId == a.ID) {
				x++;
				a.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalAmbulances.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}
void Ambulance::ambulanceService(){
	Address add;
cout<<"Is Ambulance available(y/n): ";

	cin>>ambulanceAvailable;
	while(ambulanceAvailable!='y' && ambulanceAvailable !='n'){
		cout<<" Enter correct option!! (y/n): ";
		cin>>ambulanceAvailable;
	}
if(ambulanceAvailable=='n'){
	cout<<"Ambulance is not Available Right Now"<<endl;
}
else{
	cout<<"Please Enter Patient Pick/drop address"<<endl;
	add.setData();
	cout<<"Ambulance sended in this Address"<<endl<<endl;
	add.print();

}
}
class Appointment {
private:
	unsigned int ID;
	Doctor doctor;
	Patient patient;

public:
	void setData();
	void print();
	void addBooking(Appointment);
	void showFile();
	void deleteAppointment();
	void searchAppointment();
	void modify();
};
void Appointment::setData() {
	Appointment a;

	cout << "Enter appointment id: ";
	cin >> ID;

	ifstream readFile;
	readFile.open("appointment.dat", ios::binary);
	readFile.seekg(0);
	while (readFile.read(reinterpret_cast<char*>(&a), sizeof(Appointment))) {

		if (ID == a.ID) {
			cout << "This ID is already in use" << endl;
			cout << "Please enter correct ID: ";
			cin >> ID;
		}
	}
	cout << "******Patient******" << endl;
	patient.setName();
	patient.setMobNo();
	cout << endl << endl;
	cout << "******Doctor******"<<endl;
	doctor.setName();
	doctor.setSpec();
	doctor.setMobNo();
	cout << endl << endl;
}
void Appointment::print() {
	Doctor d;
	Patient p;
	cout << "*****APPOINTMENT NUMBER: "<<ID<<" ******"<<endl;
	cout << "******Patient******" << endl;
	cout << "Patient name: "; patient.getName() ;cout << endl;
	cout << "Patient mobile number: ";  patient.getMobNo(); cout <<endl<< endl;
	cout << "******Doctor******" << endl;
	cout << "Doctor name: "; doctor.getName(); cout << endl;
	cout << "Doctor specialization: "; doctor.getSpec(); cout << endl;
	cout << "Doctor mobile number: "; doctor.getMobNo();cout << endl << endl;

}
void Appointment::addBooking(Appointment appointment) {
	char ch;
	ofstream addBooking;
	addBooking.open("appointment.dat", ios::app | ios::binary);
	do {
		appointment.setData();
		addBooking.write(reinterpret_cast<char*>(&appointment), sizeof(Appointment));
		cout << "Appointment data added successfully" << endl << endl;
		cout << "Enter another Data(y/n)? : " << endl;
		cin >> ch;
		addBooking.close();
	} while (ch == 'y');
	
}
void Appointment::showFile() {
	Appointment a;
	char ch;
	unsigned int reqId;
	ifstream totalAppointment;

	totalAppointment.open("appointment.dat", ios::binary);
	if (!totalAppointment.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "*****APPOINTMENTS LIST*****" << endl;
		while (totalAppointment.read(reinterpret_cast<char*>(&a), sizeof(Appointment))) {

			cout << "  Appointment Number: " << a.ID<< endl;

		}
		totalAppointment.close();
	}
loop: {
	totalAppointment.open("appointment.dat", ios::binary);
	cout << "enter the id you want to check details: ";
	cin >> reqId;
	int x = 0;
	while (totalAppointment.read(reinterpret_cast<char*>(&a), sizeof(Appointment)))
	{
		if (reqId == a.ID) {
			x++;
			a.print();
			break;
		}
	}
	if (x == 0) {
		cout << "ID not found \n\n";
	}
	totalAppointment.close();
	cout << "Do you want to see other ID details(y/n): ";
	cin >> ch;
	switch (ch)
	{
	case 'y':
		goto loop;
		break;
	case 'n':
		break;
	default:
		cout << "Enter correct option (y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			goto loop;
		}

	}
	}
}
void Appointment::deleteAppointment() {
	Appointment a;
	//Patient patient;
	unsigned int id;

	ifstream totalAppointment;
	//show file list before deleting
	totalAppointment.open("appointment.dat", ios::binary);
	if (!totalAppointment.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******APPOINTMENTS LIST*******" << endl;
		while (totalAppointment.read(reinterpret_cast<char*>(&a), sizeof(Appointment))) {

			cout << "ID is: " << a.ID << "--> Patient name is : "; patient.getName(); cout << endl;

		}
		totalAppointment.close();
	}

	cout << "enter id you want to delete: ";
	cin >> id;

	//Deleting the object
	ifstream readFile;
	ofstream writeFile;
	readFile.open("appointment.dat", ios::binary);
	if (!readFile.is_open()) {
		cout << "File not opening" << endl;
	}
	else {
		writeFile.open("temp.dat", ios::binary);
		readFile.seekg(0);
		while (readFile.read(reinterpret_cast<char*>(&a), sizeof(Appointment)))
		{
			if (a.ID != id) {
				writeFile.write(reinterpret_cast<char*>(&a), sizeof(Appointment));
			}

		}

	}
	writeFile.close();
	readFile.close();
	remove("appointment.dat");
	rename("temp.dat", "appointment.dat");
	cout << "The appointment delete successfully" << endl << endl;

	//showing the list after deleting
	totalAppointment.open("appointment.dat", ios::binary);
	if (!totalAppointment.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******APPOINTMENTS LIST*******" << endl << endl;
		while (totalAppointment.read(reinterpret_cast<char*>(&a), sizeof(Appointment))) {

			cout << "ID is: " << a.ID << "--> Patient name is : "; patient.getName(); cout << endl;

		}
		totalAppointment.close();
	}
}
void Appointment::searchAppointment() {
	Appointment appointment;
	char ch;
	ifstream AppointmentList;
	unsigned int reqId;

	do
	{
		int x = 0;
		cout << "Enter ID of the Appointment you want to search" << endl;
		cin >> reqId;

		AppointmentList.open("appointment.dat", ios::binary);
		if (!AppointmentList.is_open())
		{
			cout << "Error Occured While Opening File" << endl;
		}
		else {
			while (AppointmentList.read(reinterpret_cast<char*>(&appointment), sizeof(Appointment))) {

				if (reqId == appointment.ID) {
					x++;
					appointment.print();
					break;
				}

			}if (x == 0) {
				cout << "ID not found \n\n";
			}
			cout << "Do you want to search other ID (y/n): ";
			cin >> ch;
		}
		AppointmentList.close();
	} while (ch == 'y');
	
}
void Appointment::modify() {
	int position, x = 0;
	char ch, choise;
	unsigned int reqId, id;
	Appointment a{};

	do{
	//show file list before modify
	ifstream totalAppointments;
	totalAppointments.open("appointment.dat", ios::binary);
	if (!totalAppointments.is_open())
	{
		cout << "File not opening" << endl;
	}
	else {
		cout << "******APPOINTMENTS LIST*******" << endl << endl;
		while (totalAppointments.read(reinterpret_cast<char*>(&a), sizeof(Appointment))) {

			cout << " ID: " << a.ID <<endl;

		}
		totalAppointments.close();
	}

		//modify the object on the basis of id
		cout << "Enetr the ID you want to update: ";
		cin >> id;
		fstream fs;
		fs.open("appointment.dat", ios::binary | ios::in | ios::out);
		fs.seekg(0);
		while (!fs.eof()) {
			position = fs.tellg();
			fs.read(reinterpret_cast<char*>(&a), sizeof(Appointment));
			if (fs) {

				if (a.ID == id) {
					x = 1;
					a.setData();
					fs.seekg(position);
					fs.write(reinterpret_cast<char*>(&a), sizeof(Appointment));
					break;
				}
			}
		}
		fs.close();
		if (x == 1)
			cout << "\nRecord successfully modified \n"<<endl;
		else
			cout << "\nRecord not found \n";

		//show file list after modify
		totalAppointments.open("appointment.dat", ios::binary);
		if (!totalAppointments.is_open())
		{
			cout << "File not opening" << endl;
		}
		else {
			cout << "******APPOINTMENTS LIST*******" << endl << endl;
			while (totalAppointments.read(reinterpret_cast<char*>(&a), sizeof(Appointment))) {

				cout << " ID: " << a.ID << endl;

			}
			totalAppointments.close();
		}

		//see id details
	loop: {
		totalAppointments.open("appointment.dat", ios::binary);
		cout << "enter the id you want to check details: ";
		cin >> reqId;
		int x = 0;
		while (totalAppointments.read(reinterpret_cast<char*>(&a), sizeof(Appointment)))
		{
			if (reqId == a.ID) {
				x++;
				a.print();
				break;
			}
		}
		if (x == 0) {
			cout << "ID not found \n\n";
		}
		totalAppointments.close();
		cout << "Do you want to see other ID details(y/n): ";
		cin >> ch;
		switch (ch)
		{
		case 'y':
			goto loop;
			break;
		case 'n':
			break;
		default:
			cout << "Enter correct option (y/n): ";
			cin >> ch;
			switch (ch)
			{
			case 'y':
				goto loop;
				break;
			case 'n':
				break;
			default:
				cout << "Enter correct option (y/n)";
				cin >> ch;

			}
		}
		}
	cout << "Do you want to update other data (y/n): ";
	cin >> choise;
	system("clear");
	} while (choise == 'y');
}

class Hospital {

	Patient patient;
	Doctor doctor;
	Nurse nurse;
	Ward_attendent ward_attendent;
	Driver driver;
	ClassFour classFour;
	Ambulance ambulance;
	Appointment appointment;


public:
	void PatientMenu();
	void DoctorMenu();
	void NurseMenu();
	void Ward_attendentMenu();
	void DriverMenu();
	void ClassFourMenu();
	void AmbulanceMenu();
	void AppointmentsMenu();
};
//Patient Main Menu Funciton
void Hospital::PatientMenu() {
	Patient p{};
	Address add;
	Ambulance ambulance;
	int c;
	char choice;
	do {
		cout << "*****WELLCOME TO PATIENTS MENU*****" << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Patient to list: " << endl;
		cout << "  2. See Patients List" << endl;
		cout << "  3. Search any Patient by ID Number" << endl;
		cout << "  4. Remove Patient from list" << endl;
		cout << "  5. Update any patient data in list" << endl;
		cout << "  6. Required Ambulance"<<endl;
		
		cin >> c;
		switch (c) {
		case 1:
			p.add_Patient(p);
			break;
		case 2:
			p.showFile();
			break;
		case 3:
			p.search_Patient();
			break;
		case 4:
			p.delete_Patient();
			break;
		case 5:
			p.modify();
			break;
			case 6:
			ambulance.ambulanceService();
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO PATIENTS MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();
	
}

//Doctor Menu Option
void Hospital::DoctorMenu() {
	Doctor d{};
	int c;
	char choice;
	do {
		cout << "*****WELLCOME TO DOCTOR MENU*****" << endl << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Doctor to list: " << endl;
		cout << "  2. See Doctor List" << endl;
		cout << "  3. Search any Doctor by ID Number" << endl;
		cout << "  4. Remove Doctor from list" << endl;
		cout << "  5. Update any Doctor data in list" << endl;


		cin >> c;
		switch (c) {
		case 1:
			d.add_Doctor(d);
			break;
		case 2:
			d.showFile();
			break;
		case 3:
			d.search_doctor();
			break;
		case 4:
			d.delete_Doctor();
			break;
		case 5:
			d.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO DOCTORS MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();

}
//Nurses Main Menu
void Hospital::NurseMenu() {
	Nurse n{};
	int c;
	char choice;
	do {
		cout << "*****WELLCOME TO NURSE MENU*****" << endl << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Nurse to list: " << endl;
		cout << "  2. See Nurse List" << endl;
		cout << "  3. Search any Nurse by ID Number" << endl;
		cout << "  4. Remove Nurse from list" << endl;
		cout << "  5. Update any Nurse data in list" << endl;


		cin >> c;
		switch (c) {
		case 1:
			n.add_Nurse(n);
			break;
		case 2:
			n.showFile();
			break;
		case 3:
			n.search_Nurse();
			break;
		case 4:
			n.delete_Nurse();
			break;
		case 5:
			n.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO NURSE MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
if(choice =='n')
	system("clear");
	main();

}
//wardAttendent Main Menu
void Hospital::Ward_attendentMenu() {
	Ward_attendent w{};
	int c;
	char choice;
	do {
		cout << "*****WELCOME TO WARD ATTENDENTS MENU*****" << endl << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Ward_attendent to list: " << endl;
		cout << "  2. See Ward_attendent List" << endl;
		cout << "  3. Search any Ward_attendent by ID Number" << endl;
		cout << "  4. Remove Ward_attendent from list" << endl;
		cout << "  5. Update any Ward_attendent data in list" << endl;


		cin >> c;
		switch (c) {
		case 1:
			w.add_Ward_attendent(w);
			break;
		case 2:
			w.showFile();
			break;
		case 3:
			w.search_Ward_attendent();
			break;
		case 4:
			w.delete_Ward_attendent();
			break;
		case 5:
			w.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO WARD ATTENDENTS MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();

}

//Driver MainMenu Function
void Hospital::DriverMenu() {
	Driver d{};
	int c;
	char choice;
	do {
		cout << "***** WELLCOME TO DRIVERS MENU *****" << endl << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Driver to list: " << endl;
		cout << "  2. See Driver List" << endl;
		cout << "  3. Search any Driver by ID Number" << endl;
		cout << "  4. Remove Driver from list" << endl;
		cout << "  5. Update any Driver data in list" << endl;



		cin >> c;
		switch (c) {
		case 1:
			d.add_Driver(d);
			break;
		case 2:
			d.showFile();
			break;
		case 3:
			d.search_Driver();
			break;
		case 4:
			d.delete_Driver();
			break;
		case 5:
			d.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO DRIVER MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();

}

//ClassFour MainMenu Function
void Hospital::ClassFourMenu() {
	ClassFour cf{};
	int c;
	char choice;
	do {
		cout << "***** WELLCOME TO CLASS FOUR MENU *****" << endl << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new ClassFour to list: " << endl;
		cout << "  2. See ClassFour List" << endl;
		cout << "  3. Search any ClassFour by ID Number" << endl;
		cout << "  4. Remove ClassFour from list" << endl;
		cout << "  5. Update any ClassFour data in list" << endl;


		cin >> c;
		switch (c) {
		case 1:
			cf.add_ClassFour(cf);
			break;
		case 2:
			cf.showFile();
			break;
		case 3:
			cf.search_ClassFour();
			break;
		case 4:
			cf.delete_ClassFour();
			break;
		case 5:
			cf.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO CLASSFOUR MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();

}

//Ambulance Menu Options
void Hospital::AmbulanceMenu() {
	Ambulance a{};
	int c;
	char choice;
	do {
		cout << "***** WELLCOME TO AMBULANCE MENU *****" << endl << endl;;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Ambulance to list: " << endl;
		cout << "  2. See Ambulance List" << endl;
		cout << "  3. Search any Ambulance by ID Number" << endl;
		cout << "  4. Remove Ambulance from list" << endl;
		cout << "  5. Update any Ambulance data in list" << endl;


		cin >> c;
		switch (c) {
		case 1:
			a.addAmbulance(a);
			break;
		case 2:
			a.showFile();
			break;
		case 3:
			a.searchAmbulance();
			break;
		case 4:
			a.deleteAmbulance();
			break;
		case 5:
			a.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO AMBULANCE MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();

}

//Appointment Menu
void Hospital:: AppointmentsMenu() {
	Appointment a{};
	int c;
	char choice;
	do {
		cout << "***** WELLCOME TO APPOINTMENT MENU *****" << endl << endl;
		cout << "  Select the options" << endl;
		cout << "  1. Add new Appointment to list: " << endl;
		cout << "  2. See Appointment List" << endl;
		cout << "  3. Search any Appointment by ID Number" << endl;
		cout << "  4. Remove Appointment from list" << endl;
		cout << "  5. Update any Appointment data in list" << endl;


		cin >> c;
		switch (c) {
		case 1:
			a.addBooking(a);
			break;
		case 2:
			a.showFile();
			break;
		case 3:
			a.searchAppointment();
			break;
		case 4:
			a.deleteAppointment();
			break;
		case 5:
			a.modify();
			break;
		default:
			cout << "Enter correct Menu Option" << endl;
			break;
		}
		cout << "***GO BACK TO APPOINTMENT MENU*** (y/n): ";
		cin >> choice;
		system("clear");
	} while (choice == 'y');
	if(choice =='n')
	system("clear");
	main();
}

int chooseMain()
{

	int choice2;
	cout << right << setw(40) << setfill(' ') << "\nMAIN MENU" << endl << endl << endl;
	cout << right << setw(80) << setfill('-') << "----------" << endl;
	cout << "			" << "  1. Patient Menu" << endl;
	cout << "			" << "  2. Doctor Menu" << endl;
	cout << "			" << "  3. Appointments Menu" << endl;
	cout << "			" << "  4. Nurse Menu" << endl;
	cout << "			" << "  5. ClassFour Menu" << endl;
	cout << "			" << "  6. Driver Menu " << endl;
	cout << "			" << "  7. Ward_Attendents Menu" << endl;
	cout << "			" << "  8. Ambulance Menu" << endl;
	cout << "			" << "  9. Exit" << endl << endl;
	cout << right << setw(80) << setfill('-') << "----------" << endl;

	cout << "\nEnter the number corresponding to your choice:" << endl;
	cin >> choice2;
	return choice2;
}

int main() {
	Hospital hospital{};
	Password A;
	char ch = 0;
	A.setPassword();
	system("clear");
	cout << endl;

		cout << right << setw(60) << setfill(' ') << "WELCOME TO HOSPITAL MANAGEMENT SYSTEM " << endl;
		cout << endl << endl;
		cout << right << setw(60) << setfill(' ') << "------------------------------------------------" << endl;
		cout << right << setw(40) << setfill(' ') << "1.Main Menu" << endl;
		cout << right << setw(35) << setfill(' ') << "2.Exit" << endl;
		cout << right << setw(60) << setfill(' ') << "------------------------------------------------" << endl << endl;
		cout << "Enter your choice:" << endl << endl;
		int choice1;
		cin >> choice1;

		if (choice1 == 1) {
			system("clear");
			int var = chooseMain();
			system("clear");

			switch (var) {
			case 1: {
				A.passwordProtect();
				system("clear");
				hospital.PatientMenu();
				break;
			}

			case 2: {
				A.passwordProtect();
				system("clear");
				hospital.DoctorMenu();
				break;

			}

			case 3: {
				A.passwordProtect();
				system("clear");
				hospital.AppointmentsMenu();
				break;
			}
			case 4: {
				A.passwordProtect();
				system("clear");
				hospital.NurseMenu();
				break;
			}
			case 5: {
				A.passwordProtect();
				system("clear");
				hospital.ClassFourMenu();
				break;
			}
			case 6: {
				A.passwordProtect();
				system("clear");
				hospital.DriverMenu();
				break;
			}
			case 7: {
				A.passwordProtect();
				system("clear");
				hospital.Ward_attendentMenu();
				break;
			}
			case 8: {
				A.passwordProtect();
				system("clear");
				hospital.AmbulanceMenu();
				break;
			}

			case 9:
			{
				return 0;
				break;
			}
			default:
				cout << "\nCome on!Enter a valid option." << endl;
			}

		}
		else if (choice1 == 2) {
           system("clear");
			exit(0);
			
		}
		else
			cout << "\nCome on!Enter a valid option." << endl;

	return 0;
}
