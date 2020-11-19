#ifndef SONAR_H
#define SONAR_H

#include "ranger.h"

/**
@class Sonar
@brief Sonar Shoots one broad sonar that covers its field of view and returns maximum distance it reached.
@details The Sonar works accordingly: \n
It shoots a broad cone shaped sonar wave that covers field of view completely.\n
Then it returns the maximum distance the sonar reaches.\n*/
class Sonar: public Ranger
{
public:
    /**
  Default constructor -  all sensor attributes set to a default values for Sonar
  */
  Sonar();
  ~Sonar();

  /**
Member function sets Field of View
@param Desired Field of View
@return a boolean indicating if passed value is compatible with Sonar.
*/
  bool setFieldOfView(unsigned int fov) ;

  /**
  Member function to generate range reading for Sonar
  @brief This function generates random range readings as data  using supplied random number generator\n
  using normal distribution with mean of 4m and standard deviation of 5m
  @return dataset of range reading of Sonar[m]
  */
  std::vector<double> generateData();

  /**
  Member function that can be used to query stored data of Sonar
  @param Desired Sample Number
  @return a struct that consists of: \n
       - Sample Number\n
       - Dataset[m]
*/
  dataSequenceNum querySample(unsigned int &a);

private:
  std::vector<dataSequenceNum>storedSonarSamples;//!< stores sequence number stamped data
};

#endif // SONAR_H
