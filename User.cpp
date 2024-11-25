#include "User.h"
#include "Booking.h"

void User::viewHistory(bool isPassenger) {
  ifstream file("bookings.csv");
  string line;

  string idStr, statusStr, pickupStr, dropoffStr, typeStr, fareStr,
      passengerIdStr, driverIdStr, bookedAtStr, startedAtStr, completedAtStr;
  Booking booking;

  if (file) {
    while (getline(file, line)) {
      string *fields[11] = {&idStr,          &statusStr,     &pickupStr,
                            &dropoffStr,     &typeStr,       &fareStr,
                            &passengerIdStr, &bookedAtStr,   &driverIdStr,
                            &startedAtStr,   &completedAtStr};
      getFields(line, fields, 11);

      if ((!isPassenger && stoi(driverIdStr) == id) ||
          (isPassenger && stoi(passengerIdStr) == id)) {
        booking.load(stoi(idStr), statusStr, pickupStr[0], dropoffStr[0],
                     typeStr, stoi(fareStr), stoi(passengerIdStr), bookedAtStr,
                     stoi(driverIdStr), startedAtStr, completedAtStr);
        booking.display(isPassenger);
      }
    }

    file.close();
  }
}