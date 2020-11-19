#include "camera.h"
#include <thread>


const double DEFAULT_SAMPLING_TIME = 100;
const double DEFAULT_MAX_DISTANCE = 255.0;
const double DEFAULT_MIN_DISTANCE = 0.0;
const std::string DEFAULT_MODEL = "CCD-MNO";
//Constructor
Camera::Camera()
    :minValue_(DEFAULT_MIN_DISTANCE),maxValue_(DEFAULT_MAX_DISTANCE),samplingTime_(DEFAULT_SAMPLING_TIME)
    ,model_(DEFAULT_MODEL ),data_{5,4}
{

    seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);

}

//Destructor
Camera::~Camera(){

}

//Sets Sampling time
bool Camera::setScaningTime(const unsigned int &t ){
bool valid=0;
    if(t==20){
    samplingTime_ = 20;

  setImageSize(2,2);
    }
    else if(t==200) {
        samplingTime_ = 200;
        setImageSize(10,4);
    }
    else{
        samplingTime_ = 100;
        setImageSize(5,4);
    }


return valid;
}

//Sets dimensions of image matrix
void Camera::setImageSize(int r, int c){

    data_ ={r,c};

}


//Gets first row of the Image Matrix with random number generatior
std::vector<int> Camera::getFrame(void){
    dataCarrier.reserve(5000/samplingTime_);
    dataCarrier.assign(5000/samplingTime_,{0,0,{{0,0}}});
std::vector<int> first_row;

std::uniform_real_distribution<> value_distribution(minValue_,maxValue_);


    first_row.reserve(data_.at(1));
    first_row.assign(data_.at(1),0);
        for ( double i = 0 ; i<data_.at(1) ; i++) {
            auto num = value_distribution(generator);
            first_row.at(i) = ((int)num);
        }

    return first_row;
}


//Gets a image frame for each samples
std::vector<std::vector<int>> Camera::getData(void){

    std::vector<std::vector<int>> vec;
    vec.reserve(data_.at(0));
    vec.assign(data_.at(0),{0,0});

    std::vector<int> v =getFrame();
    vec.at(0)=v;

   for(int i=1; i<data_.at(0) ; i++ ){
    std::vector<int> vs;
    std::vector<int>ve = vec.at(i-1);
    vs.reserve(data_.at(1));
    vs.assign(data_.at(1),0);
    for(int j =0; j<data_.at(1);j++){
        double s = ve.at(j)/2;
        vs.at(j) = s;
    }
    vec.at(i) = vs;
   }
    std::this_thread::sleep_for(std::chrono::milliseconds( samplingTime_));

    return vec;

    }

// gets the camera model
std::string Camera::getModel(){
    return model_;
}

//gets Sampling Time
double Camera::getSamplingTime(){

    return samplingTime_;
}

//gets image dimensions from user input
std::array<int,2> Camera::getImageSize(void){
    return data_;
}

// Verifies if combination of image size and Sampling rate is correct from user input
bool Camera::verifyData(int &a, int &b, char &c){
    bool correctParam = 0;
    if((a==2 && b==2 && c=='a') || (a==5 && b==4 && c=='b')|| (a==10 && b==4 && c=='c')){
        correctParam =1;
    }

    return correctParam;
}

// takes the user input set parameters from user input
void Camera::setParam( char &c){

invalid_Flag=0;

        if(c == 'c'){
        setScaningTime(200);

        } else if (c=='a'){
        setScaningTime(20);

        }else if(c == 'b'){

            setScaningTime(100);
         }else{
          invalid_Flag=1;
           setScaningTime(100);

        }



}

void Camera::storeData(dataTimeStamped &data){

    unsigned int index=0;
    dataTimeStamped as;

                for (unsigned int ptr = 0; ptr < dataCarrier.size(); ptr++) {
                    as = dataCarrier.at(ptr);

                    if(as.sampleNo==0){

                        index= ptr;
                        break;
                    }
                }
           dataCarrier.at(index)= data;
}

Camera::dataTimeStamped Camera::querySample(unsigned int &a){

    return dataCarrier.at(a-1);
}
