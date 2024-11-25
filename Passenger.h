#pragma once

#include "Booking.h"
#include "User.h"
#include <unistd.h>

const int MAX_TRIES = 8; // LATER: change value

class Passenger : public User {
public:
  Passenger() {}

  Passenger(int id, int day, int month, int year, string firstName,
            string lastName, string phoneNum, string password)
      : User(id, day, month, year, firstName, lastName, phoneNum, password) {}

  void appendToFile() {
    ofstream file("passengers.csv", ios::app);
    file << id << "," << day << "," << month << "," << year << "," << firstName
         << "," << lastName << "," << phoneNum << "," << password << "\n";
    file.close();
  }

  int displayMenu() {
    int opt = 0;

    do {
      cout << endl << "1) Book a ride" << endl;
      cout << "2) View history" << endl;
      cout << "3) View profile" << endl;
      cout << "4) Update profile" << endl;
      cout << "5) Logout" << endl;
      cin >> opt;
    } while (opt > 5 || opt < 1);

    return opt;
  }

  void viewProfile() override {
    this->User::viewProfile();
    // LATER: more data?
  }

  void updateProfile(bool isPassenger) override {
    istringstream ss;

    this->User::updateProfile(isPassenger);
    ifstream file("passengers.csv");

    ofstream file2("passengers2.csv");
    file2.close();
    file2.open("passengers2.csv", ios::app);

    string line, idStr;
    while (getline(file, line)) {
      ss.clear();
      ss.str(line);
      getline(ss, idStr, ',');

      if (stoi(idStr) == id)
        line = to_string(id) + "," + to_string(day) + "," + to_string(month) +
               "," + to_string(year) + "," + firstName + "," + lastName + "," +
               phoneNum + "," + password;

      file2 << line << "\n";
    }

    file.close();
    file2.close();

    remove("passengers.csv");
    rename("passengers2.csv", "passengers.csv");
  }

  void bookARide() {
    system("cls");
    char pickup, dropoff;

    do {
      cout << endl
           << "Enter pickup location (enter any location from A to Z): ";
      cin >> pickup;

      cout << "Enter dropoff location (make sure not to use the same location "
              "as pickup): ";
      cin >> dropoff;

      pickup = toupper(pickup);
      dropoff = toupper(dropoff);
    } while (pickup < 'A' || pickup > 'Z' || dropoff < 'A' || dropoff > 'Z' ||
             pickup == dropoff);

    cout << endl
         << "Enter a number to select the type of vehicle that you want to "
            "book: "
         << endl;
    string type = typesMenu(false);

    int newId = getLastId("bookings.csv") + 1;
    Booking booking(newId, pickup, dropoff, type, this);
    booking.appendToFile();

    // wait for X seconds OR until a driver accepts a ride
    int tries = 0;
    bool found = false;

    cout << endl
         << "Checking every five seconds if any driver accepted the ride...";

    // LATER: check if user cancels the search; in that case update status to
    // unavailable
    while (tries < MAX_TRIES && !found) {
      cout << endl << "Wait... ";
      for (int i = 1; i <= 5; i++) {
        cout << i << " ";
        sleep(1000);
      }

      found = booking.checkStatus("accepted", "started");

      if (!found)
        tries++;
      else
        found = true;
    }

    if (found) {
      cout << endl << "Ride found!" << endl;

      booking.getFromFile();
      booking.display(true);

      int tries2 = 0;
      bool started = false;

      while (tries2 < MAX_TRIES && !started) {

        cout << endl << "Wait... ";
        for (int i = 1; i <= 5; i++) {
          cout << i << " ";
          sleep(1000);
        }
        cout << endl;

        started = booking.checkStatus("started", "");

        if (!started)
          tries2++;
        else {
          cout << endl << "Ride started" << endl;
          for (int i = 0; i < booking.getAvgDistance() + 5; i++) {
            cout << endl << "Wait... " << i;
            sleep(1000);
          }
          cout << endl;

          bool completed = booking.checkStatus("completed", "");
          if (completed) {
            cout << endl << "Ride completed!" << endl;

            int rating;

            do {
              cout << endl << "Enter rating out of 5: " << endl;
              cin >> rating;
            } while (rating > 5 || rating < 0);

            addRating(booking.getDriverId(), rating);
            cout << endl << "Thank you";
          }
        }
      }

      if (!found) {
        updateBooking(booking, "unavailable", -1, "-", "-");
        // LATER: check that if ctrl+c is pressed then the line above can be
        // made to run or not
        cout << endl
             << endl
             << "Your ride was not started by the driver" << endl
             << "Please try again later" << endl;
      } else {
      }
    } else {
      updateBooking(booking, "unavailable", -1, "-", "-");
      // LATER: check that if ctrl+c is pressed then the line above can be made
      // to run or not
      cout << endl
           << endl
           << "Your ride was not accepted by any driver" << endl
           << "Please try again later" << endl;
    }
  }

  void displayToUser() {
    cout << endl << "Passenger ID: " << id << endl;
    cout << "Passenger Name: " << firstName << " " << lastName << endl;
    cout << "Passenger Phone Number: " << phoneNum << endl;
  }

  void setId(int id) { this->id = id; }

  void getFromFile() {
    istringstream ss;

    ifstream file("passengers.csv");
    string idStr, dayStr, monthStr, yearStr, firstNameStr, lastNameStr,
        phoneNumStr;
    string line;
    string *fields[7] = {&idStr,        &dayStr,      &monthStr,   &yearStr,
                         &firstNameStr, &lastNameStr, &phoneNumStr};
    bool found = false;

    while (getline(file, line)) {
      ss.clear();
      ss.str(line);
      getFields(line, fields, 7);

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
    }

    file.close();
  }
};