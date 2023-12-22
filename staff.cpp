#include <bits/stdc++.h>

using namespace std;

bool login(string username, string password, string &clinicPostfix)
{
    // onto checking matches in database
    ifstream filereader{"database/users.txt"};

    if (!filereader)
    {
        cerr << "error. could not open file for reading." << endl;
        return false;
    }

    while (filereader)
    {
        string line;
        getline(filereader, line);

        // to store each element separated by comma in the csv line
        string element;

        // string vector to store csv values
        vector<string> v;
        stringstream ss(line);

        while (ss.good())
        {
            // get first element (username)
            getline(ss, element, ',');
            if (username == element)
            {
                // if username matches, then check password.
                // get next element (password)
                getline(ss, element, ',');
                if (password == element)
                {
                    // if password matches, change value at memory address of clinicPrefix
                    getline(ss, clinicPostfix, ',');
                    // get postfix value
                    clinicPostfix = clinicPostfix.substr(clinicPostfix.find("_") + 1);
                    return true;
                }
            }
            else
            {
                break;
            }
        }
    }
    cout << "wrong username or password" << endl;
    return false;
}

int dashboard(string username, string clinicPostfix)
{

    while (true)
    {
        // dashboard wants to know which txt file you want to modify,
        // hence parameters should be username and clinic number
        cout << "\n\nHELLO " << username << "! what would you like to do?" << endl;
        cout << "YOU ARE IN CLINIC " + clinicPostfix << endl;

        // now to open specific clinic database with ifstream
        string fileLocation = "database/clinic_" + clinicPostfix + ".txt";
        ifstream filereader{fileLocation};
        ofstream filewriter;

        // to handle errors if file cannot be opened.
        if (!filereader)
        {
            cerr << "file could not be opened." << endl;
        }

        // returns true if .txt file is empty
        bool empty = filereader.peek() == ifstream::traits_type::eof();

        while (empty)
        {
            cout << "there is currently no one in queue." << endl;
            filereader.close();
            // let thread sleep for 5 seconds before checking txt file again.
            this_thread::sleep_for(std::chrono::seconds(5));
            filereader.open(fileLocation);
            empty = filereader.peek() == ifstream::traits_type::eof();
        }

        // if queue is not empty, display latest queue and present staff options.
        string queueNumber;
        getline(filereader, queueNumber);
        cout << "current queue number is " << queueNumber << endl;
        filereader.close();

        cout << "1. announce queue \n2. next queue \n3. logout" << endl;
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "(broadcast) queue number " << queueNumber << ". Please proceed to Clinic " << clinicPostfix << endl;
            break;

        // delete first line in a given clinic queue.
        case 2:
        {
            filereader.open(fileLocation);
            // opens file in write mode
            filewriter.open("database/temp.txt", ofstream::out);
            string line;


            // to skip/read first line
            getline(filereader, line);
            // to start reading from 2nd line
            getline(filereader, line);

            bool firstLine = true;
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
                    filewriter << "\n" << line;
                    getline(filereader, line);
                }
            }

            // close filereader and filewriter
            filereader.close();
            filewriter.close();

            // delete original file
            remove(fileLocation.c_str());
            // rename temporary file
            string fileName = "database/clinic_" + clinicPostfix + ".txt";
            rename("database/temp.txt", fileName.c_str());
            break;
        }

        case 3:
            return 0;
        default:
            cout << "invalid input, please try again." << endl;
            break;
        }
    }
    return 0;
}

int main()
{

    while (true)
    {
        // main menu
        cout << "what would you like to do?" << endl;
        cout << "1. LOGIN \n2. exit program" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            string username;
            string password;
            string clinicPrefix;

            cout << "enter username" << endl;
            cin >> username;
            cout << "enter password" << endl;
            cin >> password;

            if (login(username, password, clinicPrefix))
            {
                cout << "LOGIN SUCCESS" << endl;

                // onto dashboard
                dashboard(username, clinicPrefix);
            }
        }
        else
        {
            return 0;
        }
    }
}
