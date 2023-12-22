// Header that defines the standard input/output stream objects
#include <iostream>
// Input/output stream class to operate on files.
#include <fstream>

using namespace std;

void queueClinic(string clinicPostfix)
{
    
    // READ txt file for corresponding clinic
    string fileLocation = "database/clinic_" + clinicPostfix + ".txt";
    // ifstream filereader{fileLocation};
    ifstream filereader;
    filereader.open(fileLocation);

    // to handle errors if file cannot be opened.
    if (!filereader)
    {
        cerr << "file could not be opened." << endl;
    }

    // first check if file is empty
    if (filereader.peek() == std::ifstream::traits_type::eof())
    {
        // if txt file is empty, generate first queue number (e.g. AQ0001)
        string queueNumber = clinicPostfix + "Q0001";

        // write first queue number to the txt file
        ofstream filewriter{fileLocation};
        filewriter << queueNumber;
        filewriter.close();

        cout << "your queue number is " << queueNumber << endl;
    }
    else
    {
        // get last line
        string line;
        while (filereader)
        {
            getline(filereader, line);
        }

        // extract last integer from last line/queue
        int lastDigits;
        int delimiterIndex = line.find("Q");
        string stringDigits = line.substr(delimiterIndex + 1);
        // convert string queueNumber to int
        lastDigits = stoi(stringDigits);
        // increment queueNumber
        lastDigits++;

        // convert int queueNumber to string queueNumber (e.g. 3 becomes AQ0003)
        stringDigits = to_string(lastDigits);
        string queueNumber = "";
        while (stringDigits.length() != 4)
        {
            stringDigits = "0" + stringDigits;
        }
        queueNumber = clinicPostfix + "Q" + stringDigits;

        // write queueNumber to txt file
        ofstream filewriter{fileLocation, ios::app};

        // handle errors when opening txt file
        if (!filewriter)
        {
            // Print an error and exit
            cerr << "Uh oh, database could not be opened for writing!\n";
        }

        if (filereader.is_open())
        {
            filewriter << "\n"
                       << queueNumber;
        }

        cout << "your queue number is " << queueNumber << endl;
    }
}

int main()
{

    while (true)
    {
        cout << "\nwhich clinic would you like to go?" << endl;
        cout << "1. Clinic A \n2. Clinic B \n3. Clinic C \n4. Clinic D \n5. Clinic E" << endl;
        cout << "\n\n\n-1 to exit program \n"
             << endl;
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:

            queueClinic("A");
            break;

        case 2:
            queueClinic("B");
            break;

        case 3:
            queueClinic("C");
            break;

        case 4:
            queueClinic("D");
            break;

        case 5:
            queueClinic("E");
            break;

        case -1:
            return 0;

        default:
            cout << "incorrect input, please try again.";
            break;
        }
    }
} // end of main()