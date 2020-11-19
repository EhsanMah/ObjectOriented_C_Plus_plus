#ifndef RANGER_H
#define RANGER_H
#include <chrono>
#include<random>
#include <cstdio>
#include <ctime>
#include "rangerinterface.h"
/**
@class Ranger
@brief Ranger will be used as an abstract class for different type of rangefinder sensor classes .
@details this class consists of basic features of a rangefinder sensor which includes:\n
Orientation Offset, Field of View, Angular Resolution, Number of Samples, Sensing Type, Data\n
classes inherited from this class can conduct computations by adding functions for the features that are exclusiveto them\n*/
class Ranger: public RangerInterface
{

public:
    /**
    The Default constructor sets all the attributes to zero. Inherited Child classes are suppose to configure these Parameters\n
    Besides it initiates a seed and a random number generator which can be used by child classes to generate data .\n
    @note NOTE: All the member variables should be set to default values in child classes
    */
  Ranger();

  ~Ranger();

  /**
  @struct dataSequenceNum
  @brief This struct can be used to keep store datasets and keep track of every sample and its sequence number.\n
  @details The struct consists of following elements:\n
          - Sample Number(unsigned int)\n
          - Dataset of the sample (A vector of double)\n
          */
  struct dataSequenceNum{
      unsigned int sampleNo;
      std::vector<double> data;
      } ;

  /**
  Member function to get Angular Resolution of the ranger
  @return Angular Resolution of Ranger [Degree]
  */
unsigned int getAngularResolution(void);

/**
Member function to get angle of offset from the Y axis
@return Angle Offset of Ranger [Degree]
*/
int getAngularOffset(void);

/**
Member function to get angle of Field of View of Ranger.
@return Field of View of Ranger [Degree]
*/
unsigned int getFieldOfView(void);

/**
Member function to get value possible Maximum Range of Sensor
@return Maximum Range of Ranger [m]
*/
double getMaxRange(void);

/**
Member function to get value possible Minimum Range of Sensor
@return Minimum Range of Ranger [m]
*/
double getMinRange(void);

/**
Member function to get specific Sensing Type of the ranger
@return Sensing Type of Ranger [POINT / CONE]
*/
ranger::SensingMethod getSensingMethod(void);

/**
Member function to get specific Model name of the Ranger
@return Model Name of Ranger
*/
std::string getModel(void);

/**
Member function to get sequence Number of generated data set.
@return Sequence Number of Dataset
*/
unsigned int getSequenceNo(void);

/**
Member function sets Angular Resolution
@param Desired Angular Resolution
@return a boolean indicating if Passed Angular Resolution is supported by the sensor.
*/
bool setAngularResolution(unsigned int resolution);

/**
Member function sets Angle of offset of Ranger from Y axis
@param desired Angle of Offset[Degree]
@return a boolean indicating if the given offset is compatible with the sensor.
*/
bool setAngularOffset(int offset);

/**
Pure Virtual function sets Field of View
@param Desired Field of View
@return a boolean indicating if passed value is correct.
*/
virtual bool setFieldOfView(unsigned int fov)=0 ;

/**
Pure Virtual function generates data
@brief This function should be implimented in the inherited child class to generate data\n
 using seeded random number generator supplied from ranger class.
@return dataset of range readings[m]
*/
virtual std::vector<double> generateData()=0;

/**
Pure Virtual function that can be used to query stored datasets
@param Desired Sample Number
@return a struct that consists of: \n
        - Sample Number\n
        - Dataset[m]
*/
virtual dataSequenceNum querySample(unsigned int &a)=0;

//Protected member variables only accesible to this class and
// inherited classes
protected:

unsigned int angularReso_,fov_;//!< Angular Resolution and Field of View of Ranger
int offset_;//!< Angular Offset of Ranger
double minRange_,maxRange_;//!< Minimum and Maximum Range Capacity of the Sensor
unsigned int numOfSamples;//!< Number of sensor reading extracted in Samples
unsigned int seed;//!< seed for Random Number generator
std::default_random_engine generator;//!< Random Number generator to supply random sensor readings
ranger::SensingMethod sensingType_;//!< Specific Sensing Type of the Ranger
std::vector<double> data_;//!< Container to store data for each execution
std::string model_;//!< Model Name of the Ranger
unsigned int sequenceNo;//!< Sequence Number of generated data

  //See rangerinterface.h for more information
};

#endif // RANGER_H
