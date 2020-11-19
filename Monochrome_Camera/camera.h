#ifndef CAMERA_H
#define CAMERA_H
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <array>
#include <stdlib.h>
#include <chrono>
#include<random>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <unistd.h>

class Camera
{
public:
    Camera();
   ~Camera();
    struct dataTimeStamped{
    time_t time;
    unsigned int sampleNo;
      std::vector<std::vector<int>> data;
    } ;

    //Setters
    void setParam(char &c);
    bool setScaningTime(const unsigned int &t);
    void setImageSize(int r, int c);
    void storeData(dataTimeStamped &data);

private:
     void setModel(std::string &s);

    //Getters
public:

    std::string getModel(void);
    std::array<int,2> getImageSize(void);
    double getSamplingTime(void);

    std::vector<std::vector<int>> getData(void);
    dataTimeStamped querySample(unsigned int &a);
private:

    bool verifyData(int &a, int &b, char &c);
    std::vector<int> getFrame(void);

    //Variables:
public:
    int invalid_Flag = 1;
    volatile sig_atomic_t terminate;

    //Member Variables
private:

   std::vector <dataTimeStamped> dataCarrier;
   double minValue_, maxValue_ ;
   unsigned int samplingTime_ ;
   std::string model_;
   std::array<int,2> data_;
   unsigned int seed;
   std::default_random_engine generator;
};

#endif // CAMERA_H
