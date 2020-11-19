#include "sonar.h"
#include <iostream>
#define DEFAULT_SONAR_FOV 20;
#define SONAR_MIN_RANGE 0.2;
#define SONAR_MAX_RANGE 16.0;
#define DEFAULT_SONAR_NUM_OF_SAMPLES 1;
#define DEFAULT_SONAR_MODEL "SN-001";

Sonar::Sonar(){
    this->fov_ = DEFAULT_SONAR_FOV;
    this->maxRange_ = SONAR_MAX_RANGE;
    this->minRange_ = SONAR_MIN_RANGE;
    this->numOfSamples = DEFAULT_SONAR_NUM_OF_SAMPLES;
    this->sensingType_ =ranger::CONE;
    this->model_ = DEFAULT_SONAR_MODEL;
    this->sequenceNo=0;
}

Sonar::~Sonar(){

}
bool Sonar::setFieldOfView(unsigned int fov){
        fov_=fov;
        return true;
}

std::vector<double> Sonar::generateData(){
    double randii=0;
    this->sequenceNo++;
    dataSequenceNum newData;
    newData.sampleNo=this->sequenceNo;
    this->data_.resize(this->numOfSamples);
    this->data_.assign(this->numOfSamples,0.00);

    std::normal_distribution<double>distribution(4.0,5.0);
    for(unsigned int i=0; i<this->numOfSamples;i++){
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
      storedSonarSamples.push_back(newData);
    return this->data_;
}
Sonar::dataSequenceNum Sonar::querySample(unsigned int &a){

    return storedSonarSamples.at(a-1);
}
