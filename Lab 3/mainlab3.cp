#include "cmath"
#include <iostream>
#include <limits>
#include <string>
using namespace std;
int qty = 0; //изначальный размер массива
double InputProve(double var);
int InputProve(int var);
class wheel{
public:
  int status;//повреждено/неповреждено 1/0
  double current_mileage;
  int check_status();//ПЕРЕДЕЛАТЬ!
  wheel(){status=0;current_mileage=0;};
  wheel(double mileage)
 {
   status=check_status();
 }
  virtual void output()
{
  cout<<"status: "<<status<<endl;
  if (status==1)
  {
    cout<<"damaged"<<endl;
  }
  else{cout<< "not damaged"<<endl;}
}
};
class engine
{
public:
  double engIntake; //потребление двигателя литров/км l/km
  double engPow; //мощность двигателя HP horsepower
 inline double calculateIntake() {return fabs(pow(engPow, 1 / 3) + sqrt(engPow) - 6.25);}
 engine(){engIntake=0;engPow=0;};
 engine(double power)
 {
   cin>>power;
   engPow=power;
   engIntake=calculateIntake();
 }
 virtual void output()
{
  cout<<"engine power: "<<engPow<<endl;
  cout<<"engine intake: "<<engIntake<<endl;
}
};
class fuel_system
{
public:
  double TankCapacity; //обЪём бака литры l
  double current_fuel; //текущий обЪём топлива литры l;
  //double calculate_cur_fuel() {};//расчёт текущего обЪёма топлива
  fuel_system(){TankCapacity=0;current_fuel=0;};
  fuel_system(double capacity)
 {
   cin>>capacity;;
   TankCapacity=capacity;
 }
 virtual void output()
{
  cout<<"fuel capacity: "<<TankCapacity<<endl;
  //cout<<"current fuel: "<<current_fuel<<endl;
}
};
class vehicle : public engine, fuel_system {
private:
  double speed;        //скорость км/ч km/h
  int Nwheels;
public:///////////////////////////////////////////////////////
  double mileage; //пробег km
  string name;
  double Time; //время пути hour
  /*inline double calculateSpeed() {
    return fabs(sqrt(engPow) * (70 / Nwheels - 2.5));//сделать функцией от мощности статуса колёс и оставшегося топлива
  };*/
  wheel wheel_obj;
  vehicle() {
    name="ADDVEHICLE";
    mileage=0;
    wheel wheel_obj;
  }
  vehicle(string vehicle_name,int wheels) 
  {
    mileage = 0;
    cout << "\nName of the car: ";
    cin >> vehicle_name;
    setName(vehicle_name);
    cout << "Number of wheels: ";
    wheels = InputProve(wheels);
    while ((wheels < 2) || (wheels == 5) || (wheels == 7)) {
      cout << "Uncorrect number of wheels! try again:" << endl;
      cin >> wheels;
    }
    setNwheels(wheels);
    wheel_obj=wheel(mileage);
  }
  void setName(string vehicle_name) {name = vehicle_name;}
  void setNwheels(int wheels){Nwheels = wheels;}
  ~vehicle() { cout << "Destruction of " << name << endl;} 
  void output();
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
      int Nwheels = 0;
      vehicle cars(vehicle_name, Nwheels);
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
          //adres[i].Time = adres[i].calculateRaceTime(trackLen);
          adres[i].mileage = trackLen;
          //adres[i].NRefuel = adres[i].calculateRefuel(trackLen);
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
      if ((results[i].Time - results[j].Time < 0) /*&&
          (results[i].NRefuel - results[i].NRefuel <= 0)*/) {
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
    //results[i].time_display();
    //cout << "Refuel times: " << int(ceil(results[i].NRefuel)) << endl;
  }
  delete[] results;
}
void vehicle::output() {
  cout << "Number of wheels: " << Nwheels << ";\n"
       << "power of engine: " << engPow << " HP;\n"
       << "speed: " << speed << " km/h;\n"
       << "Engine intake: " << engIntake << " l/100km;\n"
       << "mileage: " << mileage << " km;" << endl;
       cout << "Wheel status: " << wheel_obj.status;
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
/*void vehicle ::time_display() {
  double t = this->Time;
  int hours = static_cast<int>(t);
  double cur_time = (t - hours) * 60;
  int minutes = static_cast<int>((cur_time));
  int seconds = static_cast<int>((cur_time - minutes) * 60);
  cout << "TIME: " << hours << ":" << minutes << ":" << seconds << endl;
}*/
int wheel :: check_status()
{
  int random=rand()%100;
  int wear_probability = current_mileage/1000;
  if (random<=wear_probability)
  {
    return 1;//повреждено
  }
  else
  {
    return 0;//неповреждено
  }
}