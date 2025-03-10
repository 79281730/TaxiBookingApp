#pragma once
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
using namespace std;

// time_t now = time(NULL);
// tm *timePtr = localtime(&now);
static time_t now = time(NULL);
static tm *timePtr = localtime(&now);
const int current_year = 1900 + timePtr->tm_year; // tm_year is relative to 1900

inline bool doesPhoneNumOrNicExist(string str, bool isItPhoneNum,
                                   string fileName) {
  ifstream file_in(fileName);
  istringstream ss;
  bool phoneNumOrNicExists = false;

  if (file_in) {
    string line, thisStr;

    int skip = isItPhoneNum ? 6 : 8;

    while (getline(file_in, line)) {
      ss.clear();
      ss.str(line);

      for (int i = 0; i < skip; i++) {
        getline(ss, thisStr, ',');
      }

      getline(ss, thisStr, ',');

      if (thisStr == str) {
        phoneNumOrNicExists = true;
        break;
      }
    }
  }

  file_in.close();
  return phoneNumOrNicExists;
}

inline int countOccurrences(string str, char ch) {
  int occurrences = 0;

  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ch)
      occurrences++;
  }

  return occurrences;
}

inline bool containsComma(string str) {
  return countOccurrences(str, ',') >= 1;
}

inline bool isValidName(string name) {
  bool valid = name.length() >= 1 && name.length() <= 30;

  if (!valid)
    return valid;

  for (int i = 0; i < name.length(); i++) {
    // includes comma check
    if (!isalnum(name[i])) {
      valid = false;
      return valid;
    }
  }

  return valid;
}

inline bool isPhoneNumValid(string phoneNum) {
  bool valid = phoneNum.length() == 11;

  if (!valid)
    return false;

  if (phoneNum[0] != '0' || phoneNum[1] != '3') {
    valid = false;
    return valid;
  }

  for (int i = 0; i < phoneNum.length(); i++) {
    // includes comma check
    if (!isdigit(phoneNum[i])) {
      valid = false;
      break;
    }
  }

  return valid;
}

inline bool isValidNIC(string nic) {
  bool valid = nic.length() == 13;

  if (!valid)
    return valid;

  if (nic[0] != '4') {
    valid = false;
    return valid;
  }

  for (int i = 0; i < nic.length(); i++) {
    if (!isdigit(nic[i])) {
      // includes comma check
      valid = false;
      return valid;
    }
  }

  return valid;
}

inline bool isValidPlateNum(string plateNum) {
  // AA-111
  // AAA-1111
  regex plateNumRegex("[A-Z]{2,3}-[0-9]{3,4}");
  return regex_match(plateNum, plateNumRegex);
}

inline int menu1() {
  int opt;

  do {
    cout << endl << "Enter a number for one of the following commands:" << endl;
    cout << "1) Signup" << endl;
    cout << "2) Login" << endl;
    cout << "3) Exit" << endl;
    cin >> opt;
  } while (opt != 1 && opt != 2 && opt != 3);

  return opt;
}

inline int menu2() {
  int opt = 0;

  do {
    cout << endl << "1) As passenger" << endl;
    cout << "2) As driver" << endl;
    cout << "3) Go back" << endl;
    cin >> opt;
  } while (opt != 1 && opt != 2 && opt != 3);

  return opt;
}

inline string typesMenu(bool editing) {
  int opt = 0;

  do {
    cout << "1) Uber Auto [Rickshaw] [3 passengers]" << endl;
    cout << "2) Uber Moto [Bike] [1 passenger]" << endl;
    cout << "3) UberX [A private ride at an everyday price] [4 passengers]"
         << endl;
    cout << "4) UberXL [Affordable rides for groups up to 6] [6 passengers]"
         << endl;
    cout << "5) Uber Black [Premium rides in luxury cars]" << endl;
    cin >> opt;
    if (editing && opt == -1)
      return "-";
  } while (opt < 1 || opt > 5);

  if (opt == 1)
    return "Uber Auto";
  else if (opt == 2)
    return "Uber Moto";
  else if (opt == 3)
    return "UberX";
  else if (opt == 4)
    return "UberXL";
  else
    return "Uber Black";
}

inline int getLastId(string fileName) {
  ifstream file_in(fileName);
  istringstream ss;

  string returnId = "0";

  if (file_in) {
    string line, thisIdStr;

    while (getline(file_in, line)) {
      ss.clear();
      ss.str(line);

      getline(ss, thisIdStr, ',');
      returnId = thisIdStr;
    }
  }

  file_in.close();
  return stoi(returnId);
}

inline string getCurrentTime() {
  time_t current_time;
  current_time = time(NULL);
  string time = ctime(&current_time);
  time[time.length() - 1] = ' ';
  return time;
}

inline void getFields(string line, string **fields, int num_fields) {
  istringstream ss;

  ss.clear();
  ss.str(line);

  for (int i = 0; i < num_fields; i++)
    getline(ss, *(fields[i]), ',');
}

inline int getFarePerKM(string type) {
  if (type == "Uber Auto")
    return 25;
  else if (type == "Uber Moto")
    return 28;
  else if (type == "UberX")
    return 35;
  else if (type == "UberXL")
    return 45;
  else if (type == "Uber Black")
    return 50;
  else
    return 0;
}

inline int getAge(int day, int month, int year) {
  struct tm dob = {0};

  dob.tm_mday = day;
  dob.tm_mon = month - 1;    // tm_mon is from 0-11
  dob.tm_year = year - 1900; // tm_year is relative to 1900

  time_t then = mktime(&dob);
  time_t now = time(NULL);               //
  const int seconds_per_year = 31536000; // approx

  double seconds = difftime(now, then);
  return seconds / seconds_per_year;
}

inline void addRating(int id, int rating) {
  istringstream ss;
  ifstream file("drivers.csv");
  ofstream file2("drivers2.csv");
  file2.close();
  file2.open("drivers2.csv", ios::app);
  string line;
  string idStr, dayStr, monthStr, yearStr, firstNameStr, lastNameStr,
      phoneNumStr, passwordStr;
  string typeStr, yearOfManufactureStr, modelStr, makeStr, trimLevelStr,
      plateNumStr, colorStr;
  string nicStr, sumOfRatingsStr, ratedByStr;
  string *fields[18] = {&idStr,
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
                        &colorStr,
                        &sumOfRatingsStr,
                        &ratedByStr};

  while (getline(file, line)) {
    ss.clear();
    ss.str(line);
    getFields(line, fields, 18);

    if (stoi(idStr) == id)
      line = idStr + "," + dayStr + "," + monthStr + "," + yearStr + "," +
             firstNameStr + "," + lastNameStr + "," + phoneNumStr + "," +
             passwordStr + "," + nicStr + "," + typeStr + "," +
             yearOfManufactureStr + "," + makeStr + "," + modelStr + "," +
             trimLevelStr + "," + plateNumStr + "," + colorStr + "," +
             to_string(stoi(sumOfRatingsStr) + rating) + "," +
             to_string(stoi(ratedByStr) + 1);

    file2 << line << "\n";
  }

  file.close();
  file2.close();

  remove("drivers.csv");
  rename("drivers2.csv", "drivers.csv");
}