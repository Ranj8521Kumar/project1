#include <bits/stdc++.h>
#include<windows.h>
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

class totalinfo{
    public:
    double totalamount;
    int totalQuantity;

};

customerdetails inputdetails()
{
    customerdetails details;
    cout << "Enter the name of custmer: ";
    std::cin.ignore();
    getline(std::cin, details.Name);
    cout << "Enter the Mobile Number of the customer: ";
    getline(std::cin, details.MobNo);
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
        std::cin >> choice;
        choice--;
        if (choice >= 0 && choice < menu.size())
        {
            Order order;
            int x;
            cout << "Enter the " << choice << " order: ";
            std::cin >> x;
            cout << endl;
            order.ordername = menu[x - 1].name;
            cout << "Enter the quantity: ";
           std::cin >> order.Quantity;
            orders.push_back(order);

            cout << "Add more item to the order? (y/n): ";
            std::cin >> addmore;
        }
        else
        {
            cout << "Invalid choice. Please select a valid item from the menu.\n";
        }
    } while (addmore == 'y' || addmore == 'Y');
    return orders;
}

totalinfo calculatetotal(const vector<Order>& orders, const vector<MenuItem>& menu){
    totalinfo info;
    info.totalamount=0.00;
    info.totalQuantity=0;

    for(const Order& order: orders){
        for(const MenuItem& item: menu){
            if(order.ordername==item.name){
                info.totalamount+=order.Quantity*item.price;
                info.totalQuantity+=order.Quantity;
                break;
            }
        }
    }
    return info;
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

void clearbillnumberfile(const string& filename){
    ofstream outfile(filename, std::ios::trunc);

    if(outfile.is_open()){
        outfile<<"";
        outfile.close();
        cout<<"Previous Bill numbers are cleared."<<endl;
    }
}

void clearbills(const string& filename){
    ofstream Outfile(filename, std::ios::trunc);

    if(Outfile.is_open()){
        Outfile<<"";
        cout<<"Cleared "<<filename<<endl;
    }
}


void savetofile(const vector<Order> &orders, const vector<MenuItem> &menu, totalinfo &totalinfo, int billnumber, const string& filename)
{
    int number=billnumber-1;
    customerdetails customer = inputdetails();
    ofstream outFile(filename, std::ios::app);
    if (outFile.is_open())
    {
        outFile << "          HUNGRY MAKS                 " << endl;
        outFile << " RGIPT Campus, Raibareli Sultanpur \n Road, Mubarkpur Mukhatiya, Uttar \n          Pradesh, India\n       Contact No: 9569691588\n";
        outFile << "      website:www.hungrymaks.com\n";
        time_t currentTime = time(nullptr);
        string currentTimestr = ctime(&currentTime);
        outFile << "       " << currentTimestr << endl;
        outFile << "           Quick Bill\n           Bill No: " << number << endl;
        outFile << "--------------------------------------" << endl;
        outFile << "Quick Bill                 User SAIF01" << endl;
        outFile << "Pay Mode:PhonePe                      " << endl;
        outFile << "--------------------------------------" << endl;
        outFile <<  "  Item      Qty     Rate        Total"<<endl;
        for (const Order &order : orders)
        {
            for (const MenuItem &item : menu)
            {
                if (order.ordername == item.name)
                {
                    
                    outFile << "  "<<item.name << "       " << order.Quantity << "      " << item.price << "        " << order.Quantity*item.price<< endl;
                    break;
                }
            }
        }
                outFile<<"--------------------------------------"<<endl;
                outFile << "Total Qty: " << totalinfo.totalQuantity << "     Total Amount: Rs" << totalinfo.totalamount << endl;
        
                outFile << "                  Grand Total: Rs" << totalinfo.totalamount << endl;

                outFile << "--------------------------------------" << endl;

                
                outFile << "Customer " << customer.Name << "(" << customer.MobNo << ")" << endl;
                outFile << "--------------------------------------" << endl;
                outFile << "Paid Amount: Rs " << totalinfo.totalamount << endl;
                outFile << "      Thank you for your order.       " << endl;
                outFile << "      Powered by TMBill v6.1.55       " << endl;
                outFile<<"----------------------------------------"<<endl;
                outFile<<"----------------------------------------"<<endl;
                outFile<<endl<<endl;

        
        outFile.close();
    }


    ofstream OUTFile("bill.txt");
    if (OUTFile.is_open())
    {
        OUTFile << "          HUNGRY MAKS                 " << endl;
        OUTFile << " RGIPT Campus, Raibareli Sultanpur \n Road, Mubarkpur Mukhatiya, Uttar \n          Pradesh, India\n       Contact No: 9569691588\n";
        OUTFile << "      website:www.hungrymaks.com\n";
        time_t currentTime = time(nullptr);
        string currentTimestr = ctime(&currentTime);
        OUTFile << "       " << currentTimestr << endl;
        OUTFile << "           Quick Bill\n           Bill No: " << number << endl;
        OUTFile << "--------------------------------------" << endl;
        OUTFile << "Quick Bill                 User SAIF01" << endl;
        OUTFile << "Pay Mode:PhonePe                      " << endl;
        OUTFile << "--------------------------------------" << endl;
        OUTFile <<  "  Item      Qty     Rate        Total"<<endl;
        for (const Order &order : orders)
        {
            for (const MenuItem &item : menu)
            {
                if (order.ordername == item.name)
                {
                    
                    OUTFile << "  "<<item.name << "       " << order.Quantity << "      " << item.price << "        " << order.Quantity*item.price<< endl;
                    break;
                }
            }
        }
                OUTFile<<"--------------------------------------"<<endl;
                OUTFile << "Total Qty: " << totalinfo.totalQuantity << "     Total Amount: Rs" << totalinfo.totalamount << endl;
        
                OUTFile << "                  Grand Total: Rs" << totalinfo.totalamount << endl;

                outFile << "--------------------------------------" << endl;

                
                OUTFile << "Customer " << customer.Name << "(" << customer.MobNo << ")" << endl;
                OUTFile << "--------------------------------------" << endl;
                OUTFile << "Paid Amount: Rs " << totalinfo.totalamount << endl;
                OUTFile << "      Thank you for your order.       " << endl;
                OUTFile << "      Powered by TMBill v6.1.55       " << endl;
                OUTFile<<"----------------------------------------"<<endl;
                OUTFile<<"----------------------------------------"<<endl;
                OUTFile<<endl<<endl;

        
        OUTFile.close();
    }
}

void displaymenuitem(const MenuItem& item){
    cout<<item.name<<"  :  Rs"<<item.price<<endl;
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
        cout<<"Item List:"<<endl;
        for (int i = 0; i < menu.size(); i++)
        {
            cout<<"  "<<i+1<<".";
            displaymenuitem(menu[i]);
        }
        
        cout << "2.Save To File" << endl;
        cout<<"3.Clear Previous Bill numbers"<<endl;
        cout<<"4.Clear Previous Bill history"<<endl;
        cout << "5.exit" << endl;

        cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            vector<Order> orders = takeorders(menu);
            totalinfo totalInfo=calculatetotal(orders,menu);
            int billnumber = getandupdatebillnumber();
            string filename="BILL_"+to_string(billnumber-1)+".txt";
            savetofile(orders, menu, totalInfo, billnumber, filename);
            break;
        }

        case 2:
        {
            cout << "save to file....." << endl;
            break;
        }

        case 3: {
            string Filename="bill_number.txt";
            clearbillnumberfile(Filename);
            break;
        }

        case 4:{
            cout<<"Enter the Bill Number to clear(e.g., 1, 2, 3, ...): ";
            int billNumber;
            std::cin>>billNumber;
            string fileName="BILL_"+to_string(billNumber)+".txt";
            clearbills(fileName);
            break;
        }

        case 5:
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
