#include <bits/stdc++.h>
using namespace std;

class MenuItem
{
public:
    string name;
    double price;
};

class Order
{
public:
    string ordername;
    int Quantity;
};

class customerdetails
{
public:
    string Name;
    string MobNo;
};

customerdetails inputdetails()
{
    customerdetails details;
    cout << "Enter the name of custmer: ";
    cin.ignore();
    getline(cin, details.Name);
    cout << "Enter the Mobile Number of the customer: ";
    getline(cin, details.MobNo);
    return details;
}

void DisplauMenu(const vector<MenuItem> &Menu)
{
    cout << "Menu:\n";
    for (int i = 0; i < Menu.size(); i++)
    {
        cout << i + 1 << "." << Menu[i].name << " - Rs" << Menu[i].price << endl;
    }
}

vector<Order> takeorders(const vector<MenuItem> &menu)
{
    vector<Order> orders;
    char addmore;

    do
    {
        DisplauMenu(menu);
        int choice;
        cout << "Enter the number of item: ";
        cin >> choice;
        choice--;
        if (choice >= 0 && choice < menu.size())
        {
            Order order;
            int x;
            cout << "Enter the " << choice << " order: ";
            cin >> x;
            cout << endl;
            order.ordername = menu[x - 1].name;
            cout << "Enter the quantity: ";
            cin >> order.Quantity;
            orders.push_back(order);

            cout << "Add more item to the order? (y/n): ";
            cin >> addmore;
        }
        else
        {
            cout << "Invalid choice. Please select a valid item from the menu.\n";
        }
    } while (addmore == 'y' || addmore == 'Y');
    return orders;
}

double calculatetotalbil(const vector<Order> &orders, const vector<MenuItem> &menu)
{
    double totalamount = 0.0;
    for (const Order &order : orders)
    {
        for (const MenuItem &item : menu)
        {
            if (order.ordername == item.name)
            {
                totalamount += order.Quantity * item.price;
                break;
            }
        }
    }
    return totalamount;
}

int getandupdatebillnumber()
{
    ifstream inFile("bill_number.txt");
    int billnumber = 1;
    if (inFile.is_open())
    {
        inFile >> billnumber;
        inFile.close();

        billnumber++;

        ofstream outFile("bill_number.txt");
        if (outFile.is_open())
        {
            outFile << billnumber;
            outFile.close();
        }
    }
    return billnumber;
}

void savetofile(const vector<Order> &orders, const vector<MenuItem> &menu, double totalamount, int billnumber)
{
    ofstream outFile("bill.txt");

    if (outFile.is_open())
    {
        outFile << "          HUNGRY MAKS                 " << endl;
        outFile << " RGIPT Campus, Raibareli Sultanpur \n Road, Mubarkpur Mukhatiya, Uttar \n          Pradesh, India\n       Contact No: 9569691588\n";
        outFile << "      website:www.hungrymaks.com\n";
        time_t currentTime = time(nullptr);
        string currentTimestr = ctime(&currentTime);
        outFile << "       " << currentTimestr << endl;
        outFile << "           Quick Bill\n           Bill No: " << billnumber << endl;
        outFile << "--------------------------------------" << endl;
        outFile << "Quick Bill                 User SAIF01" << endl;
        outFile << "Pay Mode:PhonePe                      " << endl;
        outFile << "--------------------------------------" << endl;
        for (const Order &order : orders)
        {
            for (const MenuItem &item : menu)
            {
                if (order.ordername == item.name)
                {
                    outFile <<  "  Item      Qty     Rate        Total"<<endl;
                    outFile << "  "<<item.name << "       " << order.Quantity << "      " << item.price << "        " << order.Quantity*item.price<< endl;
                    break;
                }
            }
            outFile<<"--------------------------------------"<<endl;
            outFile << "Total Qty: " << order.Quantity << "     Total Amount: Rs" << totalamount << endl;
        }
        
                outFile << "                  Grand Total: Rs" << totalamount << endl;

                outFile << "--------------------------------------" << endl;

                customerdetails customer = inputdetails();
                outFile << "Customer " << customer.Name << "(" << customer.MobNo << ")" << endl;
                outFile << "--------------------------------------" << endl;
                outFile << "Paid Amount: Rs " << totalamount << endl;
                outFile << "      Thank you for your order.       " << endl;
                outFile << "      Powered by TMBill v6.1.55       " << endl;
            
        
        outFile.close();
    }
}
int main()
{
    vector<MenuItem> menu = {
        {"Burger", 5.99},
        {"Pizza", 8.99},
        {"Pasta", 7.99},
        {"Salad", 4.99},
        {"Soda", 1.99}};

    while (true)
    {
        cout << "1.Take Order" << endl;
        cout << "2.Save To File" << endl;
        cout << "3.exit" << endl;

        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            vector<Order> orders = takeorders(menu);
            double totalamount = calculatetotalbil(orders, menu);
            int billnumber = getandupdatebillnumber();
            savetofile(orders, menu, totalamount, billnumber);
            break;
        }

        case 2:
        {
            cout << "save to file....." << endl;
            break;
        }

        case 3:
        {
            cout << "Thank you." << endl;
            return 0;
            break;
        }
        default:
            cout << "Invalid Choice, Please try again." << endl;
            break;
        }
    }

    return 0;
}
