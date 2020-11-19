#ifndef RANGERFUSION_H
#define RANGERFUSION_H

#include <vector>
#include "rangerfusioninterface.h"
#include "rangerinterface.h"

/**
@class RangerFusion
@brief RangerFusion extract data from a collection of Rangers and fuses the data. .
*/
class RangerFusion: public RangerFusionInterface
{
public:
    /**
    The Default constructor sets the cell centre to values within the #MAP_SIZE\n
    @sa RangerFusionInterface and @sa RangerInterface for more information
    */
  RangerFusion(std::vector<RangerInterface*> rangers);

  /**
  @struct Point
  @brief Can be used to store cartesian 2D co-ordinates\n
  @details The struct consists of following elements:\n
          - Position in reference to X axis(double)\n
          - Position in reference to X axis(double)\n
          */
  struct Point{
      double x ,y;
  };

  /**
   * @brief Accepts the container of cells.
   *
   * @param cells
   */
   void setCells(std::vector<Cell*> cells) ;

   /**
    * @brief Calls each ranger to generate data and combines range data with provided container of cells. Generates a 'fusion' of the data based on collision conditions as descibed in Assignment 2 specification
    *
    */
   void grabAndFuseData() ;

   /**
    * @brief Returns the raw data from any sensors in the ranger container within a vector of vectors
    * The raw data is updated every time a new fusion is requested. The raw data will match the preceeding fusion if it is called between fusions. If no fusion has occured the vector shall be empty.
    *
    * @return std::vector<std::vector<double>>  the outer elements of the vector related to the rangers, the inner elements of vector the respective range readings
    */
   std::vector<std::vector<double>> getRawRangeData() ;

   /**
    * @brief Returns the total scanning area possible with CONE based scanners supplied
    *
    * @return double Total area coverage
    */
   double getScanningArea() ;

   /**
    * @brief Returns sequence Number of Last fusion
    *
    * @return unsigned int Sequence Number of Fusion
    */
   unsigned int getSequenceNumber(void);

    private:
   /**
    * @brief Returns Last cartetsian coordinate each laser reached
    *
    * @return RangerFusion::Point
    */
   std::vector<Point>getLaserEndPoints(std::vector<double>data,RangerInterface* ranger);

   /**
    * @brief Returns cartetsian coordinates 2 corners of Sonar Cone other then the origin Points
    * @param double Maximum Distance Sonar Reached
    * @param A pointer to the ranger we are calculating the ponts for
    * @return RangerFusion::Point  Cartesian Coordinates of 2 corners of Cones
    */
   std::vector<Point>getSonarConePoints(double distance,RangerInterface* ranger);

   /**
    * @brief Iterates from one cartesian point to another and \n
    * supplies multiple points on a line drawn between those supplied Points
    * @param double X coordinate of Final point
    * @param double Y coordinate of Final point
    * @param double X coordinate of initial point
    * @param double Y coordinate of initial point
    * @return std::vector<RangerFusion::Point> Several Points on a line drawn
    */
   std::vector<Point> checkTroughLine(double ax, double ay,double bx,double by);

   /**
       * @brief Iterates through a all the cells and checks if line suppled intersects any of the cell \n
       * If it detects any intersection it looks at the supplies severity boolean flag .\n
       * If the flag is false, that indicates the we are looking if cells intersects in boundary conditions. where it will consider the cell is OCCUPIED\n
       * If the flag is true, that indicates that we are looking if cells intersects in inner area. where it will consider the cell is FREE\n
       * @param std::vector<Point> Points in one Line
       * @param bool Severity flag that indicates cell state if found in this points

*/
   void CheckCells(std::vector<Point>line, bool severity);

//member variables
  std::vector<std::vector<double>> data_; //!< This is to cater for getRawRangeData (which returns the raw data that was used for fusion))
  std::vector<RangerInterface*> rangers_; //!< A private copy of rangers @sa RangerInterface
  std::vector<Cell*> cells_; //!< A private copy of cells @sa Cell
  unsigned int sequenceNum_; //!< Sequence Number of Fusion

};

#endif // RANGERFUSION_H
