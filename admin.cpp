#include <bits/stdc++.h>

using namespace std;

void showExistingUsers()
{
    ifstream filereader{ "database/users.txt" };
    string line;
    vector<string> username;
    vector<string> clinicName;

    while (filereader)
    {
        // get line of string "user1,pass,clinic_A"
        getline(filereader, line);

        // to store an element separated by a comma in the string
        string element;
        stringstream ss(line);

        if (ss.good())
        {
            // get username of staff
            getline(ss, element, ',');
            username.push_back(element);

            // skip next element (password)
            getline(ss, element, ',');

            // get clinic name assigned to staff
            getline(ss, element, ',');
            clinicName.push_back(element);
        }
        else
        {
            cerr << "something went wrong while reading the file" << endl;
        }
    }

    // to handle bug that appends an extra line to the vector arrays
    username.pop_back();
    clinicName.pop_back();

    // to print the staffs and corresponding clinics
    cout << "\n[existing users]" << endl;
    for (int i = 0; i < username.size(); i++)
    {
        cout << "Name: " << username[i] << " Clinic: " << clinicName[i] << endl;
    }
}

int registerUser(string username, string password, string clinicPostfix)
{
    ifstream filereader{"database/users.txt"};
    string line;
    string element;

    // first check if username already exists,
    // if it does exists, send error message, and exit method
    while (filereader)
    {
        getline(filereader, line);
        element = line.substr(0, line.find(","));

        if (username == element)
        {
            cout << "username is already taken." << endl;
            return 0;
        }
    }

    filereader.close();

    // else if it does not exist, write username and clinic assigned to database
    filereader.open("database/users.txt");
    ofstream filewriter;
    filewriter.open("database/temp.txt", ofstream::out);

    bool firstLine = true;
    getline(filereader, line);

    // rewrite contents of users.txt into temp.txt
    while (filereader)
    {
        // to handle pesky bug for the first line
        if (firstLine)
        {
            filewriter << line;
            firstLine = false;
            getline(filereader, line);
        }
        else
        {
            cout << line << endl;
            filewriter << "\n"
                       << line;
            getline(filereader, line);
        }
    }

    // append newly registered user details to temp.txt
    string newLine = "\n" + username + "," + password + "," + "clinic_" + clinicPostfix;
    filewriter << newLine;

    filereader.close();
    filewriter.close();

    string fileLocation = "database/users.txt";
    // delete original file
    remove(fileLocation.c_str());
    // rename temporary file
    string fileName = "database/users.txt";
    rename("database/temp.txt", fileName.c_str());
}

void deleteUser(string username)
{
    // rewrite contents of users.txt
    // but when username matches, skip that line
    ifstream filereader { "database/users.txt" };
    ofstream filewriter;
    filewriter.open("database/temp.txt", ofstream::out);
    string line;

    bool firstLine = true;
    getline(filereader, line);
    bool found = false;

    // rewrite contents of users.txt into temp.txt
    while (filereader)
    {
        if (username == line.substr(0, line.find(',')))
        {
            // do nothing, skip that line
            getline(filereader, line);
            found = true;
        }
        else
        {
            // to handle pesky bug for the first line
            if (firstLine)
            {
                filewriter << line;
                firstLine = false;
                getline(filereader, line);
            }
            else
            {
                cout << line << endl;
                filewriter << "\n" << line;
                getline(filereader, line);
            }
        }
    }

    filereader.close();
    filewriter.close();

    string fileLocation = "database/users.txt";
    // delete original file
    remove(fileLocation.c_str());
    // rename temporary file
    string fileName = "database/users.txt";
    rename("database/temp.txt", fileName.c_str());

    if (found)
    {
        cout << "user deletion success" << endl;
    }
    else
    {
        cout << "user not found, deletion cancelled." << endl;
    }
}

int main()
{

    while (true)
    {
        cout << "\n\n\n\n\n\n\n\n\n\nhello admin, what would you like to do?" << endl;
        cout << "1. register new user \n2. delete user \n3. exit program" << endl;

        showExistingUsers();

        int choice;
        cin >> choice;

        string username;
        string clinicLetter;
        string password;

        switch (choice)
        {
        case 1:
            cout << "[User Account Creation]" << endl;

            cout << "enter username:" << endl;
            cin >> username;

            cout << "enter user password" << endl;
            cin >> password;

            cout << "enter clinic postfix/letter" << endl;
            cin >> clinicLetter;

            registerUser(username, password, clinicLetter);
            break;

        case 2:
            cout << "[User Account Deletion]" << endl;
            cout << "enter username to delete" << endl;
            cin >> username;
            deleteUser(username);
            break;

        case 3:
            return 0;
            break;

        default:
            cout << "invalid input, please try again." << endl;
            break;
        }
    }
}
