#pragma once

#include "Questions.h"
#include <iostream>
#include <string>

using namespace std;

class User {
protected:
  int id = -1, day = 0, month = 0, year = 0;
  string firstName = "", lastName = "", phoneNum = "", password = "";

public:
  User() {}

  User(int id, int day, int month, int year, string firstName, string lastName,
       string phoneNum, string password)
      : id(id), day(day), month(month), year(year), firstName(firstName),
        lastName(lastName), phoneNum(phoneNum), password(password) {}

  virtual void viewProfile() {
    system("cls");
    cout << endl << "ID: " << id << endl;
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Date of Birth (D/M/Y): " << day << "/" << month << "/" << year
         << endl;
    cout << "Phone Number: " << phoneNum << endl;
  }

  virtual void updateProfile(bool isPassenger) {
    cout << endl
         << "If you do not want to update a field then enter -1 in it" << endl;

    string firstName2, lastName2, password2;
    int day2, month2, year2;
    string phoneNum2;
    int age;

    askName(firstName2, true, true);
    askName(lastName2, false, true);
    askPassword(password2, password, true);

    do {
      askDate(1, day2, 1, 31, true);
      askDate(2, month2, 1, 12, true);
      askDate(3, year2, current_year - 120, current_year, true);

      if (day2 == -1)
        day2 = day;
      if (month2 == -1)
        month2 = month;
      if (year2 == -1)
        year2 = year;

      if (!isPassenger) {
        age = getAge(day2, month2, year2);
        if (age < 18)
          cerr << endl << "Error: driver must be at least 18 years old" << endl;
      }
    } while (!isPassenger && age < 18);

    askPhoneNum(phoneNum2, isPassenger, true);

    if (firstName2 != "-")
      firstName = firstName2;
    if (lastName2 != "-")
      lastName = lastName2;
    if (password2 != "-")
      password = password2;
    if (phoneNum2 != "-" && phoneNum2 != "-1")
      phoneNum = phoneNum2;
    if (day2 != -1)
      day = day2;
    if (month2 != -1)
      month = month2;
    if (year2 != -1)
      year = year2;
  }

  void viewHistory(bool);

  int getId() { return id; }
};
