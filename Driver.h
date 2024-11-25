#pragma once
#include "Booking.h"
#include "User.h"
#include "Vehicle.h"

class Driver : public User {
  int sumOfRatings = 0, ratedBy = 0;
  Vehicle vehicle;
  string nic = "";

public:
  Driver() {}

  Driver(int id, int day, int month, int year, string firstName,
         string lastName, string phoneNum, string password, string nic,
         Vehicle vehicle)
      : User(id, day, month, year, firstName, lastName, phoneNum, password),
        sumOfRatings(0), ratedBy(0), nic(nic), vehicle(vehicle) {}

  void appendToFile() {
    ofstream file("drivers.csv", ios::app);
    file << id << "," << day << "," << month << "," << year << "," << firstName
         << "," << lastName << "," << phoneNum << "," << password << "," << nic
         << "," << vehicle.type << "," << vehicle.yearOfManufacture << ","
         << vehicle.make << "," << vehicle.model << "," << vehicle.trimLevel
         << "," << vehicle.plateNum << "," << vehicle.color << ","
         << sumOfRatings << "," << ratedBy << "\n";
    file.close();
  }

  int displayMenu() {
    int opt = 0;

    do {
      cout << endl << "1) View available rides" << endl;
      cout << "2) View history" << endl;
      cout << "3) View profile" << endl;
      cout << "4) Update profile" << endl;
      cout << "5) Logout" << endl;
      cin >> opt;
    } while (opt > 5 || opt < 1);

    // if (opt == 3)
    //     viewProfile();

    return opt;
  }

  void viewProfile() override {
    this->User::viewProfile();
    cout << "NIC: " << nic << endl;
    cout << "Average Rating: " << getRating() << endl;
    cout << "Rated by: " << ratedBy << " passengers" << endl;
    vehicle.viewData();
    // LATER: more data?
  }

  void updateProfile(bool isPassenger) override {
    istringstream ss;

    this->User::updateProfile(isPassenger);

    string nic2;
    string type2, make2, model2, trimLevel2, plateNum2, color2;
    int yearOfManufacture2;

    askNIC(true, nic2);
    askVehicle(true, type2, yearOfManufacture2, make2, model2, trimLevel2,
               plateNum2, color2);

    if (nic2 != "-1" && nic != "-")
      nic = nic2;

    if (type2 != "-")
      vehicle.type = type2;

    if (yearOfManufacture2 != -1)
      vehicle.yearOfManufacture = yearOfManufacture2;

    if (make2 != "-")
      vehicle.make = make2;

    if (model2 != "-")
      vehicle.model = model2;

    if (trimLevel2 != "-")
      vehicle.trimLevel = trimLevel2;

    if (plateNum2 != "-")
      vehicle.plateNum = plateNum2;

    if (color2 != "-")
      vehicle.color = color2;

    ifstream file("drivers.csv");

    ofstream file2("drivers2.csv");
    file2.close();
    file2.open("drivers2.csv", ios::app);

    string line, idStr;
    while (getline(file, line)) {
      ss.clear();
      ss.str(line);
      getline(ss, idStr, ',');

      if (stoi(idStr) == id)
        line = to_string(id) + "," + to_string(day) + "," + to_string(month) +
               "," + to_string(year) + "," + firstName + "," + lastName + "," +
               phoneNum + "," + password + "," + nic + "," + vehicle.type +
               "," + to_string(vehicle.yearOfManufacture) + "," + vehicle.make +
               "," + vehicle.model + "," + vehicle.trimLevel + "," +
               vehicle.plateNum + "," + vehicle.color + "," +
               to_string(sumOfRatings) + "," + to_string(ratedBy);

      file2 << line << "\n";
    }

    file.close();
    file2.close();

    remove("drivers.csv");
    rename("drivers2.csv", "drivers.csv");
  }

  void viewAvailableRidesAndAskId(int &acceptedId, Booking &booking,
                                  bool &found) {
    system("cls");
    istringstream ss;

    ifstream file("bookings.csv");
    string line;

    string idStr, statusStr, pickupStr, dropoffStr, typeStr, fareStr,
        passengerIdStr, driverIdStr, bookedAtStr, startedAtStr, completedAtStr;
    string *fields[11] = {&idStr,          &statusStr,     &pickupStr,
                          &dropoffStr,     &typeStr,       &fareStr,
                          &passengerIdStr, &bookedAtStr,   &driverIdStr,
                          &startedAtStr,   &completedAtStr};

    acceptedId = -1;
    found = false;

    if (file) {
      while (getline(file, line)) {
        getFields(line, fields, 11);

        if (statusStr == "available" && (this->vehicle).type == typeStr) {
          booking.load(stoi(idStr), statusStr, pickupStr[0], dropoffStr[0],
                       typeStr, stoi(fareStr), stoi(passengerIdStr),
                       bookedAtStr, stoi(driverIdStr), startedAtStr,
                       completedAtStr);
          booking.display(false);
        }
      }
    }

    cout << endl << "Enter a booking ID to accept it (enter -1 to cancel): ";
    cin >> acceptedId;

    if (acceptedId < 0)
      acceptedId = -1;

    else // if acceptedId >= 0
    {
      ifstream file("bookings.csv");
      string line, idStr, statusStr;

      while (getline(file, line)) {
        ss.clear();
        ss.str(line);
        getline(ss, idStr, ',');
        getline(ss, statusStr, ',');

        if (stoi(idStr) == acceptedId && statusStr == "available")
          found = true;
      }
    }

    file.close();
  }

  void setId(int id) { this->id = id; }

  float getRating() {
    return (ratedBy == 0) ? 0 : (float)sumOfRatings / (float)ratedBy;
  }

  void getFromFile() {
    istringstream ss;
    ifstream file("drivers.csv");
    string idStr, dayStr, monthStr, yearStr, firstNameStr, lastNameStr,
        phoneNumStr, passwordStr;
    string typeStr, yearOfManufactureStr, modelStr, makeStr, trimLevelStr,
        plateNumStr, colorStr;
    string nicStr;
    string line;
    string *fields[16] = {&idStr,
                          &dayStr,
                          &monthStr,
                          &yearStr,
                          &firstNameStr,
                          &lastNameStr,
                          &phoneNumStr,
                          &passwordStr,
                          &nicStr,
                          &typeStr,
                          &yearOfManufactureStr,
                          &makeStr,
                          &modelStr,
                          &trimLevelStr,
                          &plateNumStr,
                          &colorStr};
    bool found = false;

    while (getline(file, line)) {
      ss.clear();
      ss.str(line);
      getFields(line, fields, 16);

      if (stoi(idStr) == id) {
        found = true;
        break;
      }
    }

    if (found) {
      this->id = stoi(idStr);
      this->day = stoi(dayStr);
      this->month = stoi(monthStr);
      this->year = stoi(yearStr);
      this->firstName = firstNameStr;
      this->lastName = lastNameStr;
      this->phoneNum = phoneNumStr;
      this->password = passwordStr;
      this->nic = nicStr;
      vehicle.setDetails(typeStr, stoi(yearOfManufactureStr), modelStr, makeStr,
                         trimLevelStr, plateNumStr, colorStr);
    }

    file.close();
  }

  void displayToUser() {
    cout << endl << "Driver ID: " << id << endl;
    cout << "Driver Name: " << firstName << " " << lastName << endl;
    cout << "Driver Rating: " << getRating() << "/5" << endl;
    cout << "Driver Rated By: " << ratedBy << " passengers" << endl;
    cout << "Driver Phone Number: " << phoneNum << endl;
    cout << "Driver NIC: " << nic << endl;
  }
};
