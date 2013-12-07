//Steven Crespo
//Tarea utilizando Linked List

//Notar que si el input file tiene newlines al final esto puede causar que la funcion
//initialize() no trabaje correctamente e ingrese estudiantes sin nombres, lo ideal
//es editar los estudiantes atravez del programa y no habrir Students.txt

/*
Instrucciones:
main usando la clase pero con elementos de tipo estudiantes.
El estudiante tiene como instancias: Nombre, numero de estudiante, direccion postal, edad, promedio
Debes tener la funcion de: 
1. eliminar estudiante
2. busqueda de estudiante por numero de estudiante
*/

#include<iostream>
#include<string>
#include<fstream>
#include"LinkedList.h"
#include<cstdlib>
#include<iomanip>

using namespace std;

struct student{
	string name;
	int ID;
	int age;
	float gpa;	
	string address;
};

void initialize( ifstream&, LinkedList<student>& ); //initializes the list with the content of Students.txt input file
ostream& operator << ( ostream&, student& );
istream& operator >> ( istream&, student& );
bool operator == ( student , student ); 
bool menu(); //obviously...a menu
void fileUpdater(ofstream&, LinkedList<student>&); //updates output file according to list's content

int main(){
	ifstream in;
	ofstream out;
	LinkedList <student> list;
	student stdt;
	int input;

	initialize(in, list);

	while (menu()){
		while(true){
			while(cout << "Option: _\b" && !(cin >> input)){//Only accepts integers
				cin.clear(); 
				while(cin.get() != '\n'){}
				cout << "Invalid option\n";
			}
			//After accepting an int value, if it satisfies this if statement it will break the infinite loop, meaning 
			//it will pass through as valid input
			if(input > 0 && input < 6)
				break;
			else
				cout << "Invalid option\n";
			
		}
		system("cls");	

		switch (input){
		case 1:
			//Display all students
			list.first(stdt);
			cout << stdt << endl;
			system("pause");
			cout << endl;
			while(list.getNext(stdt) && !list.isEmpty()){
				cout << stdt << endl;
				system("pause");
				cout << endl;
			}
			cout << "RETURNING TO MENU, ";
			system("pause");
			system("cls");
			break;
		case 2:
			//Find student using ID number
			cout << "Enter ID of the student you want to FIND: (No symbols or spaces)" << endl;
			cout << endl << "____________\b\b\b\b\b\b\b\b\b\b\b\b";
			cin >> stdt.ID;
			if(list.retrieve(stdt)){
				cout << endl << "MATCH FOUND!" << endl;
				cout << endl << stdt << endl;
			}
			else
				cout << endl << "NOT FOUND" << endl << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			//Delete student
			cout << "Enter ID of the student you want to DELETE: (No symbols or spaces)" << endl;
			cout << endl << "____________\b\b\b\b\b\b\b\b\b\b\b\b";
			cin >> stdt.ID;
			if(list.retrieve(stdt)){
				cout << endl << stdt << endl;
				cout << "Student was DELETED!" << endl << endl;
				list.remove(stdt);
				fileUpdater(out, list);
			}
			else
				cout << endl << "ERROR: No student with that ID was found!" << endl << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			//Add student
			cout << "Enter information for the student you want to ADD:" << endl << endl;
			cin >> stdt;
			list.insert(stdt);
			fileUpdater(out, list);
			cout << endl << "Student was ADDED!" << endl << endl;
			system("pause");
			system("cls");
			break;
		case 5:
			//Exit program
			in.close();
			return 0;
		}
	}
}
void initialize( ifstream& file, LinkedList<student> & list ){
	student temp;
	string line;

	file.open("Students.txt");
	if (file.fail()){
		cout << "Error: failed to open file." << endl;
		exit(1);
	}

	getline(file, line);
	while (file.ignore() && getline(file, line)){
		temp.name = line;
		file >> temp.ID;
		file >> temp.age;
		file >> temp.gpa;
		file.ignore();
		getline(file, temp.address);
		list.insert(temp);
	}
}

ostream& operator << ( ostream& file, student& s ){
	file.setf(ios::fixed);
	file << "Name: " << s.name << endl
		 << "ID: " << s.ID << endl
		 << "Age: " << s.age << endl
		 << "Gpa: " << setprecision(2) << s.gpa << endl
		 << "Address: " << s.address << endl;
	return file;
}

istream& operator >> ( istream& file, student& s){
	cout << "Name: ";
	cin.ignore();
	getline(file, s.name);
	cout << "ID: ";
	file >> s.ID;
	cout << "Age: ";
	file >> s.age;
	cout << "Gpa: ";
	file >> s.gpa;
	cout << "Address: ";
	file.ignore();
	getline(file, s.address);
	return file;
}

bool operator == ( student a, student b ){
	if (a.ID == b.ID)
		return true;
	else 
		return false;
}

bool menu(){
	cout << "~ Students added/deleted will be updated in Students.txt ~" << endl << endl
		 << "\t   MENU: " << endl
		 << "---------------------------" << endl
		 << "1. Display ALL students" << endl
		 << "2. SEARCH by student number" << endl
		 << "3. DELETE student from list" << endl
		 << "4. ADD student to list" << endl
		 << "5. EXIT" << endl
		 << "---------------------------" << endl;
	return true;
}

void fileUpdater(ofstream& file, LinkedList<student>& list){
	student temp;
	file.open("Students.txt");
	file << "Instructions: Do NOT erase this line and leave a blank line between every student's info."
	 	 << endl << endl;
	list.first(temp);
	file.setf(ios::fixed);
	file << temp.name << endl
		 << temp.ID << endl
		 << temp.age << endl
		 << setprecision(2) << temp.gpa << endl
		 << temp.address << endl << endl;
	while(list.getNext(temp) && !list.isEmpty()){
		file << temp.name << endl
	 		 << temp.ID << endl
			 << temp.age << endl
			 << setprecision(2) << temp.gpa << endl
			 << temp.address << endl << endl;
	}
	file.close();
}