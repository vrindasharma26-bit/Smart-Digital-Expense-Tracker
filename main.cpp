#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// User Registration
void registerUser()
{
    string username, password, u, p;

    cout << "\nEnter Username: ";
    cin >> username;

    ifstream check("users.txt");

    while (check >> u >> p)
    {
        if (u == username)
        {
            cout << "Username already exists!\n";
            check.close();
            return;
        }
    }
    check.close();

    cout << "Enter Password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "\nRegistration Successful!\n";
}

// User Login
bool loginUser()
{
    string username, password, u, p;

    cout << "\nEnter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    ifstream file("users.txt");

    while (file >> u >> p)
    {
        if (u == username && p == password)
        {
            file.close();
            cout << "\nLogin Successful!\n";
            return true;
        }
    }

    file.close();
    cout << "\nInvalid Username or Password!\n";
    return false;
}

// Main Expense Menu
void expenseMenu()
{
    int choice;

    do
    {
        cout << "\n===== EXPENSE TRACKER =====\n";
        cout << "1. Add Daily Expense\n";
        cout << "2. View Expense History\n";
        cout << "3. Category-wise Expense\n";
        cout << "4. Monthly Expense Report\n";
        cout << "5. Set Monthly Budget\n";
        cout << "6. Budget Warning\n";
        cout << "7. Expense Prediction\n";
        cout << "8. Search Expense\n";
        cout << "9. Delete Expense\n";
        cout << "10. Logout\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Add Expense Module Coming Soon!\n";
                break;

            case 2:
                cout << "Expense History Module Coming Soon!\n";
                break;

            case 3:
                cout << "Category Module Coming Soon!\n";
                break;

            case 4:
                cout << "Monthly Report Module Coming Soon!\n";
                break;

            case 5:
                cout << "Budget Setting Module Coming Soon!\n";
                break;

            case 6:
                cout << "Budget Warning Module Coming Soon!\n";
                break;

            case 7:
                cout << "Expense Prediction Module Coming Soon!\n";
                break;

            case 8:
                cout << "Search Module Coming Soon!\n";
                break;

            case 9:
                cout << "Delete Expense Module Coming Soon!\n";
                break;

            case 10:
                cout << "Logged Out Successfully!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 10);
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "  SMART DIGITAL EXPENSE TRACKER\n";
        cout << "====================================\n";

        cout << "1. User Registration\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                if (loginUser())
                {
                    expenseMenu();
                }
                break;

            case 3:
                cout << "Thank You!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}
