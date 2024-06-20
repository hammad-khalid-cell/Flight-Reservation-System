#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
public:
    virtual void addFlight() const = 0;
    virtual void removeFlight() const = 0;
};
class Flight
{
protected:
    string flightNumber;
    string departure;
    string destination;
    float price;

public:
    Flight(const string &flightNumber, const string &departure, const string &destination, float price)
        : flightNumber(flightNumber), departure(departure), destination(destination), price(price) {}

    virtual void display() const
    {
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Departure: " << departure << endl;
        cout << "Destination: " << destination << endl;
        cout << "Price: " << price << " USD" << endl;
    }

    virtual void writeToFile(string filename) const
    {
        ofstream outFile(filename, ios::app); // Open file in append mode
        if (outFile.is_open())
        {
            outFile << flightNumber << " " << departure << " " << destination << " " << price << endl;
            outFile.close();
        }
        else
        {
            cout << "Unable to open file for writing." << endl;
        }
    }

    const string &getFlightNumber() const
    {
        return flightNumber;
    }

    float getPrice() const
    {
        return price;
    }
};
class Admin : public User
{
public:
    void addFlight() const override
    {
        string flightNumber, departure, destination;
        float price;
        char choice;

        do
        {
            cout << "Enter flight number: ";
            cin >> flightNumber;
            cout << "Enter departure city: ";
            cin >> departure;
            cout << "Enter destination city: ";
            cin >> destination;
            cout << "Enter price: ";
            cin >> price;

            Flight newFlight(flightNumber, departure, destination, price);
            newFlight.writeToFile("flights.txt");

            cout << "Flight added successfully!" << endl;

            cout << "Do you want to add another flight? (y/n): ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
    }

    void removeFlight() const override
    {
        string flightNumberToRemove;
        cout << "Enter flight number to remove: ";
        cin >> flightNumberToRemove;

        ifstream adminFile("flights.txt");
        ofstream tempFile("temp.txt", ios::out);
        if (adminFile.is_open() && tempFile.is_open())
        {
            string flightNumber, departure, destination;
            float price;
            bool found = false;
            while (adminFile >> flightNumber >> departure >> destination >> price)
            {
                if (flightNumber != flightNumberToRemove)
                {
                    tempFile << flightNumber << " " << departure << " " << destination << " " << price << endl;
                }
                else
                {
                    found = true;
                }
            }
            adminFile.close();
            tempFile.close();
            remove("flights.txt");
            rename("temp.txt", "flights.txt");
            if (found)
            {
                cout << "Flight " << flightNumberToRemove << " removed successfully." << endl;
            }
            else
            {
                cout << "Flight " << flightNumberToRemove << " not found." << endl;
            }
        }
        else
        {
            cout << "Unable to open file for reading or writing." << endl;
        }
    }
};

class Buyer : public User
{
public:
    void addFlight() const override
    {
        string flightnum;
        cout << "Enter the code of the flight you want to book " << endl;
        cin >> flightnum;
        ifstream buyerFile("flights.txt");
        if (buyerFile.is_open())
        {
            string flightNumber, departure, destination;
            float price;
            while (buyerFile >> flightNumber >> departure >> destination >> price)
            {
                if (flightnum == flightNumber)
                {

                    Flight newFlight(flightNumber, departure, destination, price);
                    newFlight.writeToFile("bookedFlight.txt");

                    cout << "Flight booked successfully!" << endl;
                }
            }
            buyerFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }
    }
    void showAllFlights()
    {
        ifstream buyerFile("bookedFlight.txt");
        if (buyerFile.is_open())
        {
            string flightNumber, departure, destination;
            float price;
            while (buyerFile >> flightNumber >> departure >> destination >> price)
            {
                cout << "Flight Number: " << flightNumber << endl;
                cout << "Departure: " << departure << endl;
                cout << "Destination: " << destination << endl;
                cout << "Price: " << price << " USD" << endl;
                cout << endl;
            }
            buyerFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }
    }

    void removeFlight() const override
    {
        string flightNumberToRemove;
        cout << "Enter flight number to remove: ";
        cin >> flightNumberToRemove;

        ifstream buyerFile("bookedFlight.txt");
        ofstream tempFile("temp.txt", ios::out);
        if (buyerFile.is_open() && tempFile.is_open())
        {
            string flightNumber, departure, destination;
            float price;
            bool found = false;
            while (buyerFile >> flightNumber >> departure >> destination >> price)
            {
                if (flightNumber != flightNumberToRemove)
                {
                    tempFile << flightNumber << " " << departure << " " << destination << " " << price << endl;
                }
                else
                {
                    found = true;
                }
            }
            buyerFile.close();
            tempFile.close();
            remove("bookedFlight.txt");
            rename("temp.txt", "bookedFlight.txt");
            if (found)
            {
                cout << "Flight " << flightNumberToRemove << " removed successfully." << endl;
            }
            else
            {
                cout << "Flight " << flightNumberToRemove << " not found." << endl;
            }
        }
        else
        {
            cout << "Unable to open file for reading or writing." << endl;
        }
    }
    void printFinalSlip() const
    {
        ifstream buyerFile("bookedFlight.txt");
        if (buyerFile.is_open())
        {
            string flightNumber, departure, destination;
            float price;
            float totalCost = 0;

            cout << "-----------------------------" << endl;
            cout << "       Final Flight Slip     " << endl;
            cout << "-----------------------------" << endl;

            while (buyerFile >> flightNumber >> departure >> destination >> price)
            {
                cout << "Flight Number: " << flightNumber << endl;
                cout << "Departure: " << departure << endl;
                cout << "Destination: " << destination << endl;
                cout << "Price: " << price << " USD" << endl;
                cout << "-----------------------------" << endl;
                totalCost += price;
            }

            cout << "Total Cost: " << totalCost << " USD" << endl;
            cout << "-----------------------------" << endl;

            buyerFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }
    }
};



int main()
{
    User *user = nullptr;
    int option;
     Buyer user1;

    do
    {
        cout << "\n\t\t\t========       BOOKME           ========" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t|                MAIN MENU                 |" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t============================================" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t|            1 ==>  ADMINISTRATOR          |" << endl;
        cout << "\t\t\t|            2 ==>  BUYER                  |" << endl;
        cout << "\t\t\t|            3 ==>  EXIT                   |" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t============================================" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t|             Select your Option           |" << endl;
        cout << "\t\t\t|                                          |" << endl;
        cout << "\t\t\t============================================" << endl;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            string username, password;
            cout << "\t\t\t      ADMINISTRATOR LOGIN      " << endl;
            cout << "\t\t\tEnter your username: ";
            cin >> username;
            cout << "\t\t\tEnter your password: ";
            cin >> password;

            if (username == "hammad" && password == "hammad") 
            {
                cout << "<========== Login successfully =========>" << endl;
                user = new Admin();
                int adminOption;
                do
                {
                    cout << "\n\t\t\t========= ADMIN MENU =========" << endl;
                    cout << "\t\t\t1. Add Flight" << endl;
                    cout << "\t\t\t2. Remove Flight" << endl;
                    cout << "\t\t\t3. Back to Main Menu" << endl;
                    cout << "\t\t\t================================" << endl;
                    cout << "\t\t\tSelect your option: ";
                    cin >> adminOption;

                    switch (adminOption)
                    {
                    case 1:
                        user->addFlight();
                        break;
                    case 2:
                        user->removeFlight();
                        break;
                    case 3:
                        delete user;
                        user = nullptr;
                        break;
                    default:
                        cout << "Invalid option, please try again." << endl;
                    }
                } while (adminOption != 3);
            }
            else
            {
                cout << "Invalid username or password." << endl;
            }
            break;
        }
        case 2:
        {
            user = new Buyer();
            int buyerOption;
            do
            {
                cout << "\n\t\t\t========= BUYER MENU =========" << endl;
                cout << "\t\t\t1. View All Available Flights" << endl;
                cout << "\t\t\t2. Book Flight" << endl;
                cout << "\t\t\t3. View Booked Flights" << endl;
                cout << "\t\t\t4. Remove Booked Flight" << endl;
                cout << "\t\t\t5. Print Final Slip" << endl;
                cout << "\t\t\t6. Back to Main Menu" << endl;
                cout << "\t\t\t================================" << endl;
                cout << "\t\t\tSelect your option: ";
                cin >> buyerOption;

                switch (buyerOption)
                {
                case 1:
                {
                    ifstream flightFile("flights.txt");
                    if (flightFile.is_open())
                    {
                        string flightNumber, departure, destination;
                        float price;
                        while (flightFile >> flightNumber >> departure >> destination >> price)
                        {
                            cout << "Flight Number: " << flightNumber << endl;
                            cout << "Departure: " << departure << endl;
                            cout << "Destination: " << destination << endl;
                            cout << "Price: " << price << " USD" << endl;
                            cout << "------------------------------------" << endl;
                        }
                        flightFile.close();
                    }
                    else
                    {
                        cout << "Unable to open file for reading." << endl;
                    }
                    break;
                }
                case 2:
                    user->addFlight();
                    break;
                case 3:
                      
                    // static_cast<Buyer *>(user)->showAllFlights();
                   
                    user1.showAllFlights();
                    break;
                case 4:
                    user->removeFlight();
                    break;
                case 5:
                    // static_cast<Buyer *>(user)->printFinalSlip();
                    user1.printFinalSlip();
                    break;
                case 6:
                    delete user;
                    user = nullptr;
                    break;
                default:
                    cout << "Invalid option, please try again." << endl;
                }
            } while (buyerOption != 6);
            break;
        }
        case 3:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid option, please try again." << endl;
        }

    } while (option != 3);

    return 0;
}


