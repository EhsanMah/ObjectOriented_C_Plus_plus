#include "rangerfusion.h"
#include <cmath>
#include <math.h>
#include <iostream>
#include<chrono>
#include <thread>

RangerFusion::RangerFusion(std::vector<RangerInterface*> rangers){
rangers_=rangers;
data_.reserve(rangers.size());
data_.assign(rangers.size(),{0});
cells_.reserve(5);
cells_.assign(5,0);
for (unsigned int i=0; i< 5; i++){
          Cell* cell = new Cell;
          cell->setSide(0.5);

          cells_.at(i)=cell;

  }
sequenceNum_=0;
}

void RangerFusion::setCells(std::vector<Cell*> cells) {

    cells_=cells;
}

std::vector<std::vector<double>> RangerFusion::getRawRangeData(){

    for(unsigned int i =0;i<rangers_.size();i++){
        data_.at(i).clear();
        data_.at(i)=rangers_.at(i)->generateData();
    }

    return data_;
}

double RangerFusion::getScanningArea(){
    double area=0.00;
    for(unsigned int i =0;i<rangers_.size();i++){
        if(rangers_.at(i)->getSensingMethod()==ranger::CONE){
            for(auto s : data_.at(i)){
                double base= 2*(s*tan((rangers_.at(i)->getFieldOfView()/2)*M_PI/180));
                area+=(0.5*base*s);
            }
        }else{

        }
    }
    return area;
}

unsigned int RangerFusion::getSequenceNumber(void){
    return  sequenceNum_;
}
std::vector<RangerFusion::Point>RangerFusion::getLaserEndPoints(std::vector<double>data,RangerInterface* ranger){
    std::vector<RangerFusion::Point> endPoints;
    endPoints.reserve(data.size());
    endPoints.assign(data.size(),{0,0});
    for(unsigned int l=0;l<data.size();l++){

        double x=data.at(l)*cos(l*(ranger->getAngularResolution()*M_PI/180));
        double y  =data.at(l)*sin(l*(ranger->getAngularResolution()*M_PI/180));
        if(x>0&&x<0.10){
            x=0;
        }
        if(y>0&&y<0.10){
            y=0;
        }
        endPoints.at(l)={x,y};
    }
    return endPoints;
}

std::vector<RangerFusion::Point>RangerFusion::getSonarConePoints(double distance,RangerInterface* ranger){
    std::vector<RangerFusion::Point> conePoints;
    conePoints.reserve(2);
    conePoints.assign(2,{0,0});
    Point rightSide,leftSide;
    double halfFOV= ranger->getFieldOfView()/2;

    rightSide.x=distance*sin((90-ranger->getAngularOffset()-halfFOV)*M_PI/180);
    rightSide.y=distance*cos(((90-halfFOV)-ranger->getAngularOffset())*M_PI/180);
    if(rightSide.x>0&&rightSide.x<0.10){
        rightSide.x=0;
    }
    if(rightSide.y>0&&rightSide.y<0.10){
        leftSide.y=0;
    }
    conePoints.at(0)=rightSide;

    leftSide.x=distance*sin((90-ranger->getAngularOffset()+halfFOV)*M_PI/180);
    leftSide.y=distance*cos((90-ranger->getAngularOffset()+halfFOV)*M_PI/180);

    if(leftSide.x>0&&leftSide.x<0.10){
        leftSide.x=0;
    }
    if(leftSide.y>0&&leftSide.y<0.10){
        leftSide.y=0;
    }
    conePoints.at(1)=leftSide;

    return conePoints;
}

std::vector<RangerFusion::Point> RangerFusion::checkTroughLine(double ax, double ay, double bx, double by){
    std::vector<Point>linePoint;

    double distance =pow( pow((bx-ax),2)+pow((by-ay),2),0.5);
    double theta = atan(((by-ay)/(bx-ax)));

    for(double d=0;d<distance;d+=0.1){
        ax+=(d*cos(theta));
        ay+=(d*sin(theta));
        if(ax>0&&ax<0.10){
            ax=0;
        }
        if(ay>0&& ay<0.10){
            ay=0;
        }
     linePoint.push_back({ax,ay});

    }
    return linePoint;
}

void RangerFusion::CheckCells(std::vector<Point>line,bool severity){
    double centreX,centreY;

    for(unsigned int c=0;c<cells_.size();c++){

        cells_.at(c)->getCentre(centreX,centreY);
        double length = cells_.at(c)->getSide();

    for(auto data: line){

           if((data.x>=centreX-(length/2)) &&
                 (data.x<=centreX+(length/2)) &&
                 (data.y<=centreY+(length/2)) &&
                 (data.y>=centreY-(length/2)) ){

               if(cells_.at(c)->getState()!=cell::OCCUPIED){

                   if(severity==0){
                       cells_.at(c)->setState(cell::OCCUPIED);

                   }else{
                       cells_.at(c)->setState(cell::FREE);
                   }
               }
           }
         }
    }
}

void RangerFusion::grabAndFuseData(){

    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    sequenceNum_++;
    for(auto &c:cells_){
        c->setState(cell::UNKNOWN);
    }

    getRawRangeData();

    std::vector<Point> laserPoints,sonarPoints,rightConeArm,leftConeArm ;
    for(unsigned int r=0;r<rangers_.size();r++){
        if(rangers_.at(r)->getSensingMethod()==ranger::POINT){

            laserPoints=getLaserEndPoints(data_.at(r),rangers_.at(r));
            CheckCells(laserPoints,0);

            for(auto x:laserPoints){
                std::vector<Point>lines=checkTroughLine(x.x,x.y,0.00,0.00);
                lines.erase(lines.begin());
                CheckCells(lines,1);
            }
        }else{
            for(auto dist:data_.at(r)){

            sonarPoints=getSonarConePoints(dist,rangers_.at(r));
            CheckCells(checkTroughLine(sonarPoints.at(0).x,sonarPoints.at(0).y,sonarPoints.at(1).x,sonarPoints.at(1).y),0);

            rightConeArm=checkTroughLine(sonarPoints.at(0).x,sonarPoints.at(0).y,0.00,0.00);
            rightConeArm.erase(rightConeArm.begin());

            leftConeArm =checkTroughLine(sonarPoints.at(1).x,sonarPoints.at(1).y,0.00,0.00);
            leftConeArm.erase(leftConeArm.begin());

            for(unsigned int a=0;a<rightConeArm.size();a++){

             CheckCells(checkTroughLine(leftConeArm.at(a).x,leftConeArm.at(a).y,
                                            rightConeArm.at(a).x,rightConeArm.at(a).y),1);
            }
          }
        }
    }
}
