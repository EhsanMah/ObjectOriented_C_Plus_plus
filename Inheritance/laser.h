#ifndef LASER_H
#define LASER_H

#include "ranger.h"

/**
@class Laser
@brief Laser Shoots multiple Rangefinder rays within its field of view and returns distance readings.
@details The Laser works accordingly: \n
It shoots multiple number of laser within its field of view.\n
Number of Laser rays depends on field of view and Angular Resolution \n
Then it returns the distances of the nearest obstructions each Laser hits.\n*/
class Laser: public Ranger
{
public:
    /**
  Default constructor -  all sensor attributes set to a default values for Laser
  */
  Laser();

  ~Laser();

  /**
Member function sets Field of View
@param Desired Field of View
@return a boolean indicating if passed value is compatible with Laser.
*/
   bool setFieldOfView(unsigned int fov) ;

   /**
   Member function to genarate Laser Readings
   @brief This function generates random range readings as data  using supplied random number generator\n
   using normal distribution with mean of 4m and standard deviation of 5m
   @return dataset of range readings[m]
   */
   std::vector<double> generateData();

   /**
   Member function that can be used to query stored datasets of Laser
   @param Desired Sample Number
   @return a struct that consists of: \n
        - Sample Number\n
        - Dataset[m]
*/
   dataSequenceNum querySample(unsigned int &a);

private:
  std::vector<dataSequenceNum>storedLaserSamples;//!< stores sequence number stamped dataset
};

#endif // LASER_H
