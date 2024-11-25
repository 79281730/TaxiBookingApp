#include "Booking.h"
#include "Driver.h"
#include "Passenger.h"

Booking::Booking(int id, char pickupLocation, char dropoffLocation, string type,
                 Passenger *passenger) {
  this->id = id;
  this->pickupLocation = pickupLocation;
  this->dropoffLocation = dropoffLocation;
  this->type = type;
  this->passenger = passenger;
  this->passengerId = passenger->getId();
  this->fare = getFarePerKM(type) * abs(dropoffLocation - pickupLocation);
  bookedAt = getCurrentTime();
}

void Booking::appendToFile() {
  ofstream file("bookings.csv", ios::app);
  file << id << "," << status << "," << pickupLocation << "," << dropoffLocation
       << "," << type << "," << fare << "," << passengerId << "," << bookedAt
       << "," << driverId << "," << completedAt << "\n";
  file.close();
}

void Booking::display(bool fromPassenger) {
  cout << endl << "Booking ID: " << id;

  if (fromPassenger) {
    if (driverId != -1) {
      Driver driver;
      driver.setId(driverId);
      driver.getFromFile();
      driver.displayToUser();
    }
  } else {
    if (passengerId != -1) {
      Passenger p;
      p.setId(passengerId);
      p.getFromFile();
      p.displayToUser();
    }
  }
  cout << "Status: " << status;
  cout << endl << "Fare: Rs. " << fare;
  cout << endl << "Pickup Location: " << pickupLocation;
  cout << endl << "Dropoff Location: " << dropoffLocation;
  cout << endl << "Average Distance: " << avgDistance << " km";
  cout << endl << "Vehicle Type: " << type;
  cout << endl << "Booked at: " << bookedAt << endl;
}