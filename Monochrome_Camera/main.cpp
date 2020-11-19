#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "camera.h"


int main(){

   Camera camera;
   char ans;
   char proceed;
    unsigned int sampNo,sampleNum;
   camera.terminate = 0;
       while (camera.invalid_Flag ==1) {
           std::cout<< "==============================================================="<<std::endl;
           std::cout<< "Sensor: Monochrome Camera" <<'\n'<<"Model: CCD-MN0"<< '\n'<< "Output Data type: Image"<< '\n';
           std::cout<< "==============================================================="<< '\n'<<std::endl;

           std::cout << "Please Select required Sampling Time(a/b/c):" << '\n'<< "a) 20 MiliSeconds       b)100 Milliseconds       c)200 Milliseconds"<< '\n'<<std::endl;
           std::cin>>ans;
          camera.setParam(ans);
          if(camera.invalid_Flag==1){
           std::cout<<"!!!!!!! invalid input !!!!!!"<<'\n'<<"default Parameters set"<<std::endl;
          }
                std::cout<< "Please Confirm the Camera Specs [Y/N] :"<< '\n' << '\n';
                std::cout<< "==============================================================="<<std::endl;
                std::cout<< "Model: " << camera.getModel() << '\n';
                std::cout << "Sampling Time (Milliseconds) : " << camera.getSamplingTime()<< '\n';
                std::cout << "Image Size [Row X Column]: " << camera.getImageSize().at(0) << "X"<< camera.getImageSize().at(1)<< '\n';
                std::cout<< "==============================================================="<<std::endl;
                std::cin>> proceed;


            if(proceed == 'Y' || proceed == 'y'){

                    std::cout<< "Initialising the Monochrome Camera......" << '\n'<< "Acquiring data..." <<std::endl;


                      std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();

                      double elapsed_time = 0 ;

                       sampleNum = 1;
                        while (elapsed_time<5000){

                            std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
                             elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - time).count();

                        Camera::dataTimeStamped frameContainer;

                        frameContainer.time = elapsed_time;
                       std::cout<<'\n'<<'\n'<<"Elasped Time:"<< frameContainer.time << " (milliSeconds)"<<std::endl;

                       frameContainer.sampleNo=sampleNum;
                       std::cout<< "Sample No # "<< frameContainer.sampleNo<< '\n'<< std::endl;
                       frameContainer.data = camera.getData();

                       for ( const std::vector<int> &v : frameContainer.data )
                       {
                           std::cout<< std::endl;
                          for ( int x : v ) {
                              std::cout << std::setw(3)<< x << ' ';}
                       }

                       std::cout<<'\n'<<std::endl;
                        camera.storeData(frameContainer);
                        sampleNum++;
                        }

////////// This is the piece of code to query data with sequence number //////////////
//                        std::cout<< "==============================================================="<<std::endl;
//                        std::cout<< "Please Enter desired sample number you want to query : ";
//                        std::cin>>sampNo;
//                        Camera::dataTimeStamped sample =camera.querySample(sampNo);
//                        std::cout<<"sample No : " << sample.sampleNo <<std::endl;
//                        std::cout<< "Time : "<< sample.time<<std::endl;
//                        for ( const std::vector<int> &v : sample.data )
//                        {
//                            std::cout<< std::endl;
//                           for ( int x : v ) {
//                               std::cout << std::setw(3)<< x << ' ';}
//                        }

                    camera.invalid_Flag = 1;
                }

            else{
            camera.invalid_Flag = 1;
            }
            if(camera.terminate==1){
                break;
            }
    }

            return 0;
}
