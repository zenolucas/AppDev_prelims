        #include <bits/stdc++.h>

        using namespace std;

        bool login(string username, string password)
        {
                // onto checking matches in database
                ifstream filereader { "users.txt" };

                if (!filereader)
                {
                    cerr << "error. could not open file for reading." << endl;
                    return false;
                }

                while (filereader)
                {
                    string line;
                    getline(filereader, line);

                    // check if username exists in the database
                    int delimiterIndex = line.find(",");
                    if (line.substr(0, delimiterIndex) == username)
                    {
                        // check if password matches
                        if (line.substr(delimiterIndex + 2) == password)
                        {
                           return true;
                        }
                        break;
                    }
                }
                cout << "wrong username or password" << endl;
                return false;
        }

        int dashboard(string username)
        {
            cout << "HELLO " << username << "! what would you like to do?" << endl;
            cout << "1. option 1 \n2. option 2 \n3. logout" << endl;
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                break;
            
            case 2:
                break;
            
            case 3:
                return 0;
            default:
                break;
            }
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

                    cout << "enter username" << endl;
                    cin >> username;
                    cout << "enter password" << endl;
                    cin >> password; 

                    if (login(username, password))
                    {
                        cout << "LOGIN SUCCESS" << endl; 

                        // onto dashboard
                        dashboard(username);
                    }
                }
                else 
                {
                        return 0;
                }
            }
        }