#include "cmath"
#include <iostream>
#include <limits>
#include <string>
using namespace std;
int qty = 0; //изначальный размер массива
double InputProve(double var);
int InputProve(int var);
class vehicle {
private:
  double TankCapacity; //обЪём бака литры l
  double speed; //скорость км/ч km/h
  double engIntake; //потребление двигателя литров/км l/km
  double engPow; //мощность двигателя HP horsepower
  int Nwheels;

public:///////////////////////////////////////////////////////
  double mileage; //пробег km
  double NRefuel; //количесвто дозаправок
  string name;
  double Time; //время пути hour
  inline double calculateSpeed() {
    return fabs(sqrt(engPow) * ((70 / double(Nwheels)) - 2.5));
  }
  inline double calculateIntake() {
    return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);
  }
  double calculateRefuel(double raceLength) {
    double Nrefuel=(raceLength * (engIntake / 100)) / TankCapacity;
    if(Nrefuel>1)
      return ceil(Nrefuel);
    else
     return floor(Nrefuel);
  };
  inline double calculateRaceTime(double raceLength) {
    return (raceLength / speed);
  };
  vehicle() {
    name="ADDVEHICLE";
    mileage = Time= NRefuel= 0;
  }
  vehicle(string vehicle_name, double tank, double power, int wheels) {
    mileage = Time = NRefuel = 0;
    cout << "\nName of the car: ";
    cin>>vehicle_name;
    setName(vehicle_name);
    cout << "Number of wheels: ";
    wheels = InputProve(wheels);
    while ((wheels < 2) || (wheels == 5) || (wheels == 7)) {
      cout << "Uncorrect number of wheels! try again:" << endl;
      wheels = InputProve(wheels);
    }
    setNwheels(wheels);
    cout << "Power of the engine (HP): "; // horse power
    power = InputProve(power);
    setEnginePower(power);
    cout << "Tank capacity (l): ";
    tank = InputProve(tank);
    setTankCapacity(tank);
    speed = calculateSpeed();
    engIntake = calculateIntake();
    cout << "\nCar added successfully!" << endl;
  }
  void setTankCapacity(double tank) {TankCapacity = tank;}
  void setEnginePower(double power) {engPow = power;}
  void setName(string vehicle_name) {name = vehicle_name;}
  void setNwheels(int wheels){Nwheels = wheels;}
  ~vehicle() { cout << "Destruction of " << name << endl; }
  void output();
  void time_display();
};
int menu(int &flag);
void clean(int var = 1);
void create_vehicle(vehicle *&adres, int &qty, vehicle cars);
vehicle *RatingResults(vehicle *&adres, int qty);
void outputResults(vehicle *&adres, int qty);
/////////////////////////////////MAIN/////////////////////////
int main() {
  clean();
  vehicle *adres = nullptr;
  double trackLen = 0;
  int flag = 1;
  int rez = 0;
  while (flag == 1) {
    int choice = 10;
    choice = menu(rez);
    if ((choice > 5) || (choice < 0)) {
      cout << "\nError, try another number!\n";
    }
    switch (choice) {
    case (0): {
      cout << "Are you sure you want to exit?\n1-yes\n0-go back\n";
      int exit = 2;
      exit = InputProve(exit);
      if (exit == 1) {
        flag = 0;
        break;
      } else {
        clean();
      }
      break;
    }
      delete[] adres;
      break;
    case (1): {
      clean();
      string vehicle_name = "";
      double tank = 0;
      double power = 0;
      int Nwheels = 0;
      vehicle cars(vehicle_name, tank, power, Nwheels);
      clean();
      create_vehicle(adres, qty, cars);
      rez = 0;
      break;
    }
    case (2): {
      clean();
      for (int i = 0; i < qty; i++) {
        cout << adres[i].name << endl;
        adres[i].output();
      }
      break;
    }
    case (3): {
      clean();
      cout << "Enter the length of the track (km): ";
      trackLen = InputProve(trackLen);
      rez = 0;
      break;
    }
    case (4): {
      clean();
      if (trackLen == 0) {
        cout << "You haven't entered the length of the track!\n";
        rez = 0;
        break;
      } else {
        for (int i = 0; i < qty; i++) {
          adres[i].Time = adres[i].calculateRaceTime(trackLen);
          adres[i].mileage = trackLen;
          adres[i].NRefuel = adres[i].calculateRefuel(trackLen);
        }
      }
      break;
    }
    case (5): {
      clean();
      outputResults(*&adres, qty);
      break;
    }
    default:
      clean();
      break;
    }
  }

  return 0;
}

void clean(int var) {
  for (int i = 0; i < 3; i = i + 1) {
    cout << "\n";
  }
}
int menu(int &rez) {
  cout << "\nInter a number to choose action:\n";
  cout << "0 for exit\n";
  cout << "1 for adding Vehicle\n";
  cout << "2 for output information about Vehicle\n";
  cout << "3 to enter length of the track\n";
  cout << "4 for route calculation\n"; //расчет прохождения трассы
  if (rez == 1)
    cout << "5 for results of last race\n";
  int choice = 0;
  choice = InputProve(choice);
  if (choice == 4) {
    rez = 1;
  }
  return choice;
}
void create_vehicle(vehicle *&adres, int &qty, vehicle cars) {
  vehicle *tempArray;
  if (adres != nullptr) {
    tempArray = new vehicle[qty + 1];
    for (int i = 0; i < qty; i++) {
      tempArray[i] = adres[i];
    }
    delete[] adres;
  } else {
    tempArray = new vehicle[1];
  }
  tempArray[qty] = cars;
  adres = tempArray;
  qty++;
}

vehicle *RatingResults(vehicle *&adres, int qty) {
  vehicle *results = new vehicle[qty];
  vehicle *rez_copy = new vehicle[1];
  for (int i = 0; i < qty; i++) {
    results[i] = adres[i];
  }
  for (int i = 0; i < qty; i++) {
    for (int j = 0; j < qty; j++) {
      if ((results[i].Time - results[j].Time < 0) &&
          (results[i].NRefuel - results[i].NRefuel <= 0)) {
        rez_copy[0] = results[i];
        results[i] = results[j];
        results[j] = rez_copy[0];
      }
    }
  }
  delete[] rez_copy;
  return results;
}
void outputResults(vehicle *&adres, int qty) {
  vehicle *results = RatingResults(adres, qty);
  for (int i = 0; i < qty; i++) {
    cout << results[i].name << endl;
    results[i].time_display();
    cout << "Refuel times: " << int(ceil(results[i].NRefuel)) << endl;
  }
  delete[] results;
}
void vehicle::output() {
  cout << "Number of wheels: " << Nwheels << ";\n"
       << "power of engine: " << engPow << " HP;\n"
       << "speed: " << speed << " km/h;\n"
       << "Engine intake: " << engIntake << " l/100km;\n"
       << "mileage: " << mileage << " km;" << endl;
}
double InputProve(double var) {
  cin >> var;
  if (cin.fail() || var <= 0) {
    while (!(cin >> var) || var <= 0) {
      cout << "Uncorrect, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}
int InputProve(int var) {
  cin >> var;
  if (cin.fail() || var < 0) {
    while (!(cin >> var) || var < 0) {
      cout << "Uncorrect, try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  return var;
}
void vehicle ::time_display() {
  double t = this->Time;
  int hours = static_cast<int>(t);
  double cur_time = (t - hours) * 60;
  int minutes = static_cast<int>((cur_time));
  int seconds = static_cast<int>((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}