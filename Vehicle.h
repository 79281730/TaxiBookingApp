#pragma once
#include <iostream>
#include <string>

using namespace std;

class Vehicle {
  friend class Driver;

  string type = "", make = "", model = "", trimLevel = "", plateNum = "",
         color = "";
  int yearOfManufacture = 0;

public:
  Vehicle() {}

  Vehicle(string type, int yearOfManufacture, string make, string model,
          string trimLevel, string plateNum, string color) {
    this->type = type;
    this->yearOfManufacture = yearOfManufacture;
    this->make = make;
    this->model = model;
    this->trimLevel = trimLevel;
    this->plateNum = plateNum;
    this->color = color;
  }

  void viewData() {
    cout << endl << "Vehicle Data: " << endl;
    cout << "Name: " << yearOfManufacture << " " << make << " " << model << " "
         << trimLevel << endl;
    cout << "Type: " << type << endl;
    cout << "Color: " << color << endl;
    cout << "Plate Number: " << plateNum << endl;
  }

  void setDetails(string type, int yearOfManufacture, string model, string make,
                  string trimLevel, string plateNum, string color) {
    this->type = type;
    this->yearOfManufacture = yearOfManufacture;
    this->model = model;
    this->make = make;
    this->trimLevel = trimLevel;
    this->plateNum = plateNum;
    this->color = color;
  }
};