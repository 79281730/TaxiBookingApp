#pragma once
#include "Functions.h"

using namespace std;

class Passenger;

class Booking {
  int id = -1;
  string status = "available"; // available, not accepted, arriving, arrived, in
                               // progress, completed, cancelled
  char pickupLocation = '-', dropoffLocation = '-';
  string type = "";
  int fare = 0;
  int avgDistance = 0;
  Passenger *passenger;
  int passengerId = -1;
  int driverId = -1;
  string bookedAt = "-";
  string startedAt = "-";
  string completedAt = "-";

  const int fare_per_km = 25;

public:
  Booking() {}
  Booking(int id) : id(id) {}
  Booking(int id, char pickupLocation, char dropoffLocation, string type,
          Passenger *passenger);

  // constructor for loading an already stored booking
  void load(int id, string status, char pickupLocation, char dropoffLocation,
            string type, int fare, int passengerId, string bookedAt,
            int driverId, string startedAt, string completedAt) {
    this->id = id;
    this->status = status;
    this->pickupLocation = pickupLocation;
    this->dropoffLocation = dropoffLocation;
    avgDistance = abs(dropoffLocation - pickupLocation);
    this->type = type;
    this->fare = fare;
    this->passengerId = passengerId;
    this->bookedAt = bookedAt;
    this->driverId = driverId;
    this->startedAt = startedAt;
    this->completedAt = completedAt;
  }

  friend void updateBooking(Booking &booking, string newStatus, int newDriverId,
                            string newStartedAt, string newCompletedAt);

  bool checkStatus(string givenStatus, string givenStatus2) {
    istringstream ss;
    ifstream file("bookings.csv");
    string idStr, statusStr, pickupStr, dropoffStr, driverIdStr;

    string line;
    bool found = false;

    while (getline(file, line)) {
      ss.clear();
      ss.str(line);
      getline(ss, idStr, ',');

      if (stoi(idStr) == id) {
        getline(ss, statusStr, ',');
        getline(ss, pickupStr, ',');
        getline(ss, dropoffStr, ',');

        pickupLocation = pickupStr[0];
        dropoffLocation = dropoffStr[0];
        avgDistance = abs(pickupLocation - dropoffLocation);

        if (statusStr == givenStatus || statusStr == givenStatus2) {
          for (int i = 0; i < 5; i++)
            getline(ss, driverIdStr, ',');

          driverId = stoi(driverIdStr);
          found = true;
        }
      }
    }

    file.close();
    return found;
  }

  void appendToFile();

  void completeRide() { completedAt = getCurrentTime(); }

  void getFromFile() {
    istringstream ss;
    ifstream file("bookings.csv");
    string idStr, statusStr, pickupLocationStr, dropoffLocationStr, typeStr,
        fareStr, passengerIdStr, bookedAtStr, driverIdStr, startedAtStr,
        completedAtStr;
    string line;
    bool found = false;

    string *fields[11] = {
        &idStr,       &statusStr,    &pickupLocationStr, &dropoffLocationStr,
        &typeStr,     &fareStr,      &passengerIdStr,    &bookedAtStr,
        &driverIdStr, &startedAtStr, &completedAtStr};
    while (getline(file, line)) {
      ss.clear();
      ss.str(line);
      getFields(line, fields, 11);
      // getline(ss, idStr, ',');

      if (stoi(idStr) == id) {
        found = true;
        break;
      }
    }

    if (found) {
      status = statusStr;
      pickupLocation = pickupLocationStr[0];
      dropoffLocation = dropoffLocationStr[0];
      type = typeStr;
      fare = stoi(fareStr);
      passengerId = stoi(passengerIdStr);
      bookedAt = bookedAtStr;
      driverId = stoi(driverIdStr);
      startedAt = startedAtStr;
      completedAt = completedAtStr;
    }

    file.close();
  }

  void display(bool);

  string getCompletedAt() { return completedAt; }
  int getAvgDistance() { return avgDistance; }
  int getDriverId() { return driverId; }
};

inline void updateBooking(Booking &booking, string newStatus, int newDriverId,
                          string newStartedAt, string newCompletedAt) {
  istringstream ss;
  ifstream file("bookings.csv");
  ofstream file2("bookings2.csv");
  file2.close();
  file2.open("bookings2.csv", ios::app);
  // string idStr, statusStr, pickupLocationStr, dropoffLocationStr, typeStr,
  // fareStr, passengerIdStr, bookedAtStr, driverIdStr, completedAtStr;

  // string *fields[10] = {&idStr, &statusStr, &pickupLocationStr,
  // &dropoffLocationStr, &typeStr, &fareStr, &passengerIdStr, &bookedAtStr,
  // &driverIdStr, &completedAtStr};

  string line, idStr;
  while (getline(file, line)) {
    ss.clear();
    ss.str(line);
    getline(ss, idStr, ',');

    if (stoi(idStr) == booking.id)
      line = to_string(booking.id) + "," + newStatus + "," +
             booking.pickupLocation + "," + booking.dropoffLocation + "," +
             booking.type + "," + to_string(booking.fare) + "," +
             to_string(booking.passengerId) + "," + booking.bookedAt + "," +
             to_string(newDriverId) + "," + newCompletedAt;

    file2 << line << "\n";
  }

  file.close();
  file2.close();

  remove("bookings.csv");
  rename("bookings2.csv", "bookings.csv");
}
