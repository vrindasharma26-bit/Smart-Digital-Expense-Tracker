#include <iostream>
using namespace std;

int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "   SMART DIGITAL EXPENSE TRACKER\n";
        cout << "====================================\n";

        cout << "1. User Registration\n";
        cout << "2. Login\n";
        cout << "3. Add Daily Expense\n";
        cout << "4. View Expense History\n";
        cout << "5. Category-wise Expense\n";
        cout << "6. Monthly Expense Report\n";
        cout << "7. Set Monthly Budget\n";
        cout << "8. Budget Warning\n";
        cout << "9. Expense Prediction\n";
        cout << "10. Search Expense\n";
        cout << "11. Delete Expense\n";
        cout << "12. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "User Registration Selected\n";
                break;

            case 2:
                cout << "Login Selected\n";
                break;

            case 3:
                cout << "Add Daily Expense Selected\n";
                break;

            case 4:
                cout << "View Expense History Selected\n";
                break;

            case 5:
                cout << "Category-wise Expense Selected\n";
                break;

            case 6:
                cout << "Monthly Report Selected\n";
                break;

            case 7:
                cout << "Set Monthly Budget Selected\n";
                break;

            case 8:
                cout << "Budget Warning Selected\n";
                break;

            case 9:
                cout << "Expense Prediction Selected\n";
                break;

            case 10:
                cout << "Search Expense Selected\n";
                break;

            case 11:
                cout << "Delete Expense Selected\n";
                break;

            case 12:
                cout << "Thank You for Using Expense Tracker!\n";
                break;

            default:
                cout << "Invalid Choice! Try Again.\n";
        }

    } while(choice != 12);

    return 0;
}
