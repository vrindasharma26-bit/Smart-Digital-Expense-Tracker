#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdio>
using namespace std;

string currentUser;

// Expense Structure
struct Expense
{
    string username;
    double amount;
    string category;
    string date;
    string description;
};

// Input Helper
void clearInput()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

    cout << "Registration Successful!\n";
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
            currentUser = username;
            file.close();
            cout << "\nLogin Successful!\n";
            return true;
        }
    }

    file.close();
    cout << "Invalid Username or Password!\n";
    return false;
}

// Add Daily Expense
void addExpense()
{
    Expense e;

    e.username = currentUser;

    cout << "\nEnter Expense Amount: ";
    cin >> e.amount;

    if (cin.fail() || e.amount <= 0)
    {
        cout << "Invalid Amount!\n";
        cin.clear();
        clearInput();
        return;
    }

    cout << "\nSelect Category:\n";
    cout << "1. Food\n2. Travel\n3. Shopping\n";
    cout << "4. Education\n5. Other\n";

    int choice;
    cout << "Enter Choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1: e.category = "Food"; break;
        case 2: e.category = "Travel"; break;
        case 3: e.category = "Shopping"; break;
        case 4: e.category = "Education"; break;
        case 5: e.category = "Other"; break;

        default:
            cout << "Invalid Category!\n";
            return;
    }

    cout << "Enter Date (DD-MM-YYYY): ";
    cin >> e.date;

    cout << "Enter Description: ";
    clearInput();
    getline(cin, e.description);

    if (e.description.find('|') != string::npos)
    {
        cout << "Please do not use | in description.\n";
        return;
    }

    ofstream file("expenses.txt", ios::app);

    file << e.username << "|"
         << e.amount << "|"
         << e.category << "|"
         << e.date << "|"
         << e.description << endl;

    file.close();

    cout << "\nExpense Added Successfully!\n";
}

// Read Expense Record
bool readExpense(ifstream &file, Expense &e)
{
    string amount;

    if (!getline(file, e.username, '|'))
        return false;

    if (!getline(file, amount, '|'))
        return false;

    if (!getline(file, e.category, '|'))
        return false;

    if (!getline(file, e.date, '|'))
        return false;

    if (!getline(file, e.description))
        return false;

    try
    {
        e.amount = stod(amount);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

// View Expense History
void viewExpenseHistory()
{
    ifstream file("expenses.txt");
    Expense e;
    int count = 0;

    cout << "\n========== EXPENSE HISTORY ==========\n";

    while (readExpense(file, e))
    {
        if (e.username == currentUser)
        {
            count++;

            cout << "\nExpense No: " << count;
            cout << "\nDate: " << e.date;
            cout << "\nAmount: Rs. " << e.amount;
            cout << "\nCategory: " << e.category;
            cout << "\nDescription: " << e.description;
            cout << "\n------------------------------------\n";
        }
    }

    file.close();

    if (count == 0)
        cout << "No Expenses Found!\n";
}

// Category-wise Expense
void categoryExpense()
{
    string categories[5] =
    {"Food", "Travel", "Shopping", "Education", "Other"};

    double total[5] = {0};

    ifstream file("expenses.txt");
    Expense e;

    while (readExpense(file, e))
    {
        if (e.username == currentUser)
        {
            for (int i = 0; i < 5; i++)
            {
                if (e.category == categories[i])
                    total[i] += e.amount;
            }
        }
    }

    file.close();

    cout << "\n===== CATEGORY-WISE EXPENSE =====\n";

    for (int i = 0; i < 5; i++)
    {
        cout << categories[i] << ": Rs. "
             << total[i] << endl;
    }
}

// Monthly Total
double monthlyTotal(string month)
{
    ifstream file("expenses.txt");
    Expense e;
    double total = 0;

    while (readExpense(file, e))
    {
        if (e.username == currentUser &&
            e.date.length() >= 10 &&
            e.date.substr(3, 7) == month)
        {
            total += e.amount;
        }
    }

    file.close();
    return total;
}

// Monthly Expense Report
void monthlyReport()
{
    string month;

    cout << "\nEnter Month (MM-YYYY): ";
    cin >> month;

    double total = monthlyTotal(month);

    cout << "\n===== MONTHLY EXPENSE REPORT =====\n";
    cout << "Month: " << month << endl;
    cout << "Total Expense: Rs. " << total << endl;
}

// Set Monthly Budget
void setBudget()
{
    string month;
    double budget;

    cout << "\nEnter Month (MM-YYYY): ";
    cin >> month;

    cout << "Enter Monthly Budget: ";
    cin >> budget;

    if (cin.fail() || budget <= 0)
    {
        cout << "Invalid Budget!\n";
        cin.clear();
        clearInput();
        return;
    }

    ifstream input("budgets.txt");
    ofstream output("temp.txt");

    string user, oldMonth;
    double oldBudget;

    while (input >> user >> oldMonth >> oldBudget)
    {
        if (user != currentUser || oldMonth != month)
        {
            output << user << " "
                   << oldMonth << " "
                   << oldBudget << endl;
        }
    }

    input.close();

    output << currentUser << " "
           << month << " "
           << budget << endl;

    output.close();

    remove("budgets.txt");
    rename("temp.txt", "budgets.txt");

    cout << "Budget Saved Successfully!\n";
}

// Get Monthly Budget
double getBudget(string month)
{
    ifstream file("budgets.txt");

    string user, m;
    double budget;

    while (file >> user >> m >> budget)
    {
        if (user == currentUser && m == month)
        {
            file.close();
            return budget;
        }
    }

    file.close();
    return 0;
}

// Budget Warning
void budgetWarning()
{
    string month;

    cout << "\nEnter Month (MM-YYYY): ";
    cin >> month;

    double budget = getBudget(month);
    double spent = monthlyTotal(month);

    if (budget == 0)
    {
        cout << "Please set your budget first!\n";
        return;
    }

    cout << "\nMonthly Budget: Rs. " << budget;
    cout << "\nTotal Spent: Rs. " << spent;

    if (spent > budget)
        cout << "\nWarning! Budget Exceeded!\n";
    else if (spent >= budget * 0.8)
        cout << "\nAlert! You have used 80% of your budget.\n";
    else
        cout << "\nYou are within your budget.\n";
}

// Expense Prediction
void expensePrediction()
{
    string month;
    int daysPassed, totalDays;

    cout << "\nEnter Month (MM-YYYY): ";
    cin >> month;

    cout << "Enter Days Passed: ";
    cin >> daysPassed;

    cout << "Enter Total Days in Month: ";
    cin >> totalDays;

    if (cin.fail() || totalDays < 28 ||
        totalDays > 31 || daysPassed < 1 ||
        daysPassed > totalDays)
    {
        cout << "Invalid Day Information!\n";
        cin.clear();
        clearInput();
        return;
    }

    double spent = monthlyTotal(month);

    double prediction =
        (spent / daysPassed) * totalDays;

    cout << "\n===== EXPENSE PREDICTION =====\n";
    cout << "Current Spending: Rs. " << spent;
    cout << "\nPredicted Monthly Spending: Rs. "
         << prediction << endl;

    double budget = getBudget(month);

    if (budget > 0 && prediction > budget)
        cout << "Warning! Budget May Be Exceeded.\n";
    else
        cout << "Budget Prediction is Within Limit.\n";
}

// Search Expense
void searchExpense()
{
    string keyword;
    bool found = false;

    cout << "\nEnter Category or Date to Search: ";
    cin >> keyword;

    ifstream file("expenses.txt");
    Expense e;

    while (readExpense(file, e))
    {
        if (e.username == currentUser &&
            (e.category == keyword || e.date == keyword))
        {
            cout << "\nAmount: Rs. " << e.amount;
            cout << "\nCategory: " << e.category;
            cout << "\nDate: " << e.date;
            cout << "\nDescription: " << e.description;
            cout << "\n----------------------\n";

            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "Expense Not Found!\n";
}

// Delete Expense
void deleteExpense()
{
    ifstream file("expenses.txt");
    ofstream temp("temp.txt");

    Expense e;
    int count = 0, number;

    while (readExpense(file, e))
    {
        if (e.username == currentUser)
        {
            count++;

            cout << "\n" << count << ". "
                 << e.date << " | "
                 << e.category << " | Rs. "
                 << e.amount << " | "
                 << e.description << endl;
        }
    }

    file.close();

    if (count == 0)
    {
        temp.close();
        remove("temp.txt");
        cout << "No Expenses Available!\n";
        return;
    }

    cout << "\nEnter Expense Number to Delete: ";
    cin >> number;

    if (cin.fail() || number < 1 || number > count)
    {
        cin.clear();
        clearInput();
        temp.close();
        remove("temp.txt");
        cout << "Invalid Expense Number!\n";
        return;
    }

    ifstream input("expenses.txt");
    count = 0;

    while (readExpense(input, e))
    {
        if (e.username == currentUser)
        {
            count++;

            if (count == number)
                continue;
        }

        temp << e.username << "|"
             << e.amount << "|"
             << e.category << "|"
             << e.date << "|"
             << e.description << endl;
    }

    input.close();
    temp.close();

    remove("expenses.txt");
    rename("temp.txt", "expenses.txt");

    cout << "Expense Deleted Successfully!\n";
}

// Main Expense Menu
void expenseMenu()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "       EXPENSE TRACKER MENU\n";
        cout << "====================================\n";

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

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: addExpense(); break;
            case 2: viewExpenseHistory(); break;
            case 3: categoryExpense(); break;
            case 4: monthlyReport(); break;
            case 5: setBudget(); break;
            case 6: budgetWarning(); break;
            case 7: expensePrediction(); break;
            case 8: searchExpense(); break;
            case 9: deleteExpense(); break;
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
        cout << "   SMART DIGITAL EXPENSE TRACKER\n";
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
                    expenseMenu();
                break;

            case 3:
                cout << "Thank You for Using Expense Tracker!\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}
