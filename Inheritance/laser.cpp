#include "laser.h"
#include <iostream>
#define DEFAULT_ANGULAR_RESO 10;
#define DEFAULT_FOV 180;
#define MIN_RANGE 0.2;
#define MAX_RANGE 8.0;
#define DEFAULT_NUM_OF_SAMPLES 19;
#define DEFAULT_LASER_MODEL "SICK-XL";

Laser::Laser()
{
    this->angularReso_ = DEFAULT_ANGULAR_RESO;
    this->fov_ = DEFAULT_FOV;
    this->maxRange_ = MAX_RANGE;
    this->minRange_ = MIN_RANGE;
    this->numOfSamples = DEFAULT_NUM_OF_SAMPLES;
    this->sensingType_=ranger::POINT;
    this->model_ = DEFAULT_LASER_MODEL;
    this->sequenceNo=0;
}

Laser::~Laser(){

}


bool Laser::setFieldOfView(unsigned int fov){
    bool validFOV=false;
    if(fov==180){
        fov_ =fov;
        validFOV=true;
    }

    return validFOV;
}

std::vector<double> Laser::generateData(){
    double randii=0;
    this->sequenceNo++;
    dataSequenceNum newData;
    newData.sampleNo=this->sequenceNo;

    this->numOfSamples=(this->fov_/this->angularReso_)+1;
    this->data_.resize(numOfSamples);
    this->data_.assign(numOfSamples,0.00);

    std::normal_distribution<double>distribution(4.0,5.0);

    for(unsigned int i=0; i<numOfSamples;i++){
              randii = distribution(generator);
             if(randii<minRange_){
              this->data_.at(i)=minRange_;
             }
            else if(randii>maxRange_){
                this->data_.at(i)=maxRange_;
               }else{
                 this->data_.at(i)=randii;
             }
       }
    newData.data=this->data_;
    storedLaserSamples.push_back(newData);
    return this->data_;
}

Laser::dataSequenceNum Laser::querySample(unsigned int &a){

    return storedLaserSamples.at(a-1);
}
