#include <stdio.h>
#include <iostream>
#include "laser.h"
#include "sonar.h"
#include "cell.h"
#include "rangerfusion.h"
#include "rangerinterface.h"
#include <signal.h>


void printCellStates(std::vector<Cell*>cellset){
    std::cout<<"Cells: ";

    for(auto c:cellset){
        std::cout<<c->getState()<<"  ";

    }
    std::cout<<std::endl;
}
int main(){

    char rep;
    unsigned int  offset1,offset2, offset3, num_of_Cells;
    unsigned int angle= 0;

     Sonar *sonar1= new Sonar;
     Laser *laser= new Laser;
     Sonar *sonar2= new Sonar;
     sig_atomic_t terminate =0;

     std::vector<RangerInterface*>rangersHolder = {laser,sonar1,sonar2};
     RangerFusion Fuse(rangersHolder);
     std::vector<Cell*>cellHolder;
     std::cout<<"====================================================="<<"\n"<<std::endl;
     std::cout<<"This Fusion Includes 1 Laser RangeFinder Scanner"<< "\n"
             <<"Sensors Specifications ar following:"<<"\n"<< "\n"<<std::endl;
     std::cout<<"====================================================="<<"\n"<<std::endl;
     std::cout<<"\n \n"<<"====================================================="<<std::endl;
     std::cout<<"Laser RangeFinder Scanner :"<<"\n"<<std::endl;
     std::cout<<"MODEL :"<< laser->getModel()<<std::endl;
     std::cout<<"FIELD OF VIEW :"<< laser->getFieldOfView()<<std::endl;
     std::cout<<"MAX DISTANCE :"<< laser->getMaxRange()<<std::endl;
     std::cout<<"MIN DISTANCE :"<< laser->getMinRange()<<std::endl;
     std::cout<<"====================================================="<<"\n"<<std::endl;

     std::cout<<"\n"<<"====================================================="<<std::endl;
     std::cout<<"Sonar 1 :"<<"\n"<<std::endl;
     std::cout<<"MODEL :"<< sonar1->getModel()<<std::endl;
     std::cout<<"FIELD OF VIEW :"<< sonar1->getFieldOfView()<<std::endl;
     std::cout<<"MAX DISTANCE :"<< sonar1->getMaxRange()<<std::endl;
     std::cout<<"MIN DISTANCE :"<< sonar1->getMinRange()<<std::endl;
     std::cout<<"====================================================="<<"\n"<<std::endl;

     std::cout<<"\n"<<"====================================================="<<std::endl;
     std::cout<<"Sonar 2 :"<<"\n"<<std::endl;
     std::cout<<"MODEL :"<< sonar2->getModel()<<std::endl;
     std::cout<<"FIELD OF VIEW :"<< sonar2->getFieldOfView()<<std::endl;
     std::cout<<"MAX DISTANCE :"<< sonar2->getMaxRange()<<std::endl;
     std::cout<<"MIN DISTANCE :"<< sonar2->getMinRange()<<std::endl;
     std::cout<<"====================================================="<<"\n"<<std::endl;

      std::cout<<"Do you want to configure " <<
      "Angular Resolution of the Laser RangeFinder? [Y/N]"<<"\n"<<std::endl;
      std::cin>>rep;
      if(rep=='Y'||rep=='y'){
       std::cout<< "Please enter new Angular Resolution for Laser :";
       std::cin>>angle;
      }else{

      }
      std::cout<< "set offset for all the Rangers:"<<"\n";
      std::cout<< "Laser RangeFinder: ";
      std::cin>>offset1;
      std::cout<< "Sonar1 :";
      std::cin>>offset2;
      std::cout<< "Sonar2 :";
      std::cin>>offset3;
      laser->setAngularResolution(angle);
      laser->setAngularOffset(offset1);
      sonar1->setAngularOffset(offset2);
      sonar2->setAngularOffset(offset3);

      std::cout<<"how many cells you want to generate?"<< "\n";
      std::cin>> num_of_Cells;

      cellHolder.resize(num_of_Cells);
      cellHolder.assign(num_of_Cells,nullptr);
      for (unsigned int i=0; i< num_of_Cells; i++){
                Cell* cell = new Cell;
                cell->setSide(0.5);
                cellHolder.at(i)=cell;
        }


    printCellStates(cellHolder);

   while(terminate ==0){
              Fuse.setCells(cellHolder);
              Fuse.grabAndFuseData();
              std::cout<<"***************************************"<<std::endl;
              std::cout<<"Sample No: "<<Fuse.getSequenceNumber()<<std::endl;
              std::cout<<"printing cell states after Fusing."<<std::endl;
              printCellStates(cellHolder);

              std::cout<<"Total area covered by sonar: "<< Fuse.getScanningArea()<<std::endl;
              std::cout<<"****************************************"<<"\n"<<std::endl;
              std::cout<<"\n"<<std::endl;
  }


std::cout<<std::endl;

    return  0;
}
