#include "ranger.h"
#include <iostream>

Ranger::Ranger()
    :angularReso_(0),fov_(0),offset_(0),
      minRange_(0.0),maxRange_(0.0),numOfSamples(0),model_("N/A"),sequenceNo(0)
{
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}
Ranger::~Ranger(){

}
unsigned int Ranger::getAngularResolution(){

    return angularReso_;
}

int Ranger::getAngularOffset(){

    return offset_;
}

unsigned int Ranger::getFieldOfView(){

    return  fov_;
}

double Ranger::getMaxRange(){

    return maxRange_;
}

double Ranger::getMinRange(){

    return minRange_;
}

ranger::SensingMethod Ranger::getSensingMethod(){

    return sensingType_;
}
std::string Ranger::getModel(){
    return model_;

}
unsigned int Ranger::getSequenceNo(void){
    return sequenceNo;
}
bool Ranger::setAngularResolution(unsigned int resolution){

    if(this->getSensingMethod()==ranger::POINT){
        if(resolution==10 || resolution==30){
            angularReso_=resolution;
            numOfSamples= (fov_/resolution)+1;
            return true;
        }else{
            return false;
        }
    }else{
        angularReso_=0;
        return true;
    }
}

bool Ranger::setAngularOffset(int offset){
bool validOffset=false;
if(offset>-180 && offset<180){
    offset_=offset;
    validOffset = true;
}
return validOffset;
}
