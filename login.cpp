        #include <bits/stdc++.h>
     
        using namespace std;
        int main()
        {
                string username;
                string password;

                cout << "enter username" << endl;
                cin >> username;
                cout << "enter password" << endl;
                cin >> password; 

                // onto checking matches in database
                ifstream filereader { "users.txt" };

                if (!filereader)
                {
                    cerr << "error. could not open file for reading." << endl;
                    return 0;
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
                           cout << "LOGIN SUCCESS" << endl;
                           return 0;
                        }
                        break;
                    }
                }
                cout << "wrong username or password" << endl;
        }