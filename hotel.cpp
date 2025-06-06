#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

class hotel {
    int room_no;
    char name[30];
    char address[50];
    char phone[15];

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
    void bill(int);
};

// ------------------ MAIN MENU ------------------

void hotel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        system("cls");
        cout << "\n\t\t\t\t*";
        cout << "\n\t\t\t\t   HOTEL MANAGEMENT  ";
        cout << "\n\t\t\t\t     * MAIN MENU *";
        cout << "\n\t\t\t\t*";
        cout << "\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Records";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: cout << "\nExiting..."; break;
            default:
                cout << "\n\n\t\t\tWrong choice.....!!!";
                cin.ignore();
                cin.get();
        }
    }
}

// ------------------ ADD RECORD ------------------

void hotel::add() {
    system("cls");
    int r, flag;
    ofstream fout("Record.dat", ios::app | ios::binary);

    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Total number of Rooms - 50";
    cout << "\n Ordinary Rooms: 1 - 30";
    cout << "\n Luxury Rooms: 31 - 45";
    cout << "\n Royal Rooms: 46 - 50";
    cout << "\n Enter Room number you want to stay in: ";
    cin >> r;

    flag = check(r);
    if (flag) {
        cout << "\n Sorry..!!! Room is already booked";
    } else {
        room_no = r;
        cout << " Name: ";
        cin >> ws;
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone Number: ";
        cin >> phone;

        fout.write((char*)this, sizeof(hotel));
        cout << "\n Room is booked...!!!";
    }

    fout.close();
    cout << "\n Press Enter to continue.....!!";
    cin.ignore();
    cin.get();
}

// ------------------ DISPLAY A PARTICULAR RECORD ------------------

void hotel::display() {
    system("cls");
    ifstream fin("Record.dat", ios::in | ios::binary);
    int r, flag = 0;

    cout << "\n Enter Room number: ";
    cin >> r;

    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n Room number: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone number: " << phone;
            flag = 1;
            break;
        }
    }

    if (!flag)
        cout << "\n Sorry Room number not found or vacant....!!";

    fin.close();
    cout << "\n\n Press Enter to continue....!!";
    cin.ignore();
    cin.get();
}

// ------------------ SHOW ALL ROOMS ------------------

void hotel::rooms() {
    system("cls");
    ifstream fin("Record.dat", ios::in | ios::binary);
    cout << "\n\t\t\t    List Of Rooms Allotted";
    cout << "\n\t\t\t    ----------------------";
    cout << "\n\n Room No.\tName\t\tAddress\t\t\tPhone Number";

    while (fin.read((char*)this, sizeof(hotel))) {
        cout << "\n " << room_no << "\t\t" << name << "\t\t" << address << "\t\t" << phone;
    }

    fin.close();
    cout << "\n\n Press Enter to continue.....!!";
    cin.ignore();
    cin.get();
}

// ------------------ EDIT RECORD ------------------

void hotel::edit() {
    system("cls");
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ---------";
    cout << "\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n 3. Bill Of Customer";
    cout << "\n Enter your choice: ";
    cin >> choice;
    cout << "\n Enter Room number: ";
    cin >> r;

    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        case 3: bill(r); break;
        default: cout << "\n Wrong Choice.....!!";
    }

    cout << "\n Press Enter to continue....!!!";
    cin.ignore();
    cin.get();
}

// ------------------ CHECK IF ROOM EXISTS ------------------

int hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::in | ios::binary);
    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

// ------------------ MODIFY RECORD ------------------

void hotel::modify(int r) {
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n Name: ";
            cin >> ws;
            cin.getline(name, 30);
            cout << " Address: ";
            cin.getline(address, 50);
            cout << " Phone number: ";
            cin >> phone;

            file.seekp(-sizeof(hotel), ios::cur);
            file.write((char*)this, sizeof(hotel));
            cout << "\n Record modified successfully!";
            flag = 1;
            break;
        }
    }

    if (!flag)
        cout << "\n Sorry Room number not found or vacant...!!";
    file.close();
}

// ------------------ DELETE RECORD ------------------

void hotel::delete_rec(int r) {
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in | ios::binary);
    ofstream fout("Temp.dat", ios::out | ios::binary);

    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone number: " << phone;
            cout << "\n\n Do you want to delete this record (y/n)? ";
            cin >> ch;

            if (ch == 'n' || ch == 'N')
                fout.write((char*)this, sizeof(hotel));

            flag = 1;
        } else {
            fout.write((char*)this, sizeof(hotel));
        }
    }

    fin.close();
    fout.close();

    if (!flag)
        cout << "\n Sorry room number not found or vacant...!!";
    else {
        remove("Record.dat");
        rename("Temp.dat", "Record.dat");
        cout << "\n Record deleted successfully!";
    }
}

// ------------------ BILL FUNCTION ------------------

void hotel::bill(int r) {
    ifstream fin("Record.dat", ios::in | ios::binary);
    int found = 0;

    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            found = 1;
            cout << "\n Room No: " << room_no;
            cout << "\n Customer Name: " << name;

            if (room_no >= 1 && room_no <= 30)
                cout << "\n Your Bill = Rs. 2000";
            else if (room_no >= 31 && room_no <= 45)
                cout << "\n Your Bill = Rs. 5000";
            else if (room_no >= 46 && room_no <= 50)
                cout << "\n Your Bill = Rs. 7000";
            else
                cout << "\n Invalid Room Range!";
            break;
        }
    }

    if (!found)
        cout << "\n Room number not found!";

    fin.close();
}

// ------------------ MAIN FUNCTION ------------------

int main() {
    hotel h;
    h.main_menu();
    return 0;
}
