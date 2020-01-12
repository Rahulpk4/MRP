
#include <veins/modules/application/traci/TracIRSU.h>

#include<string.h>
#include<omnetpp.h>
#include<vector>
#include<algorithm>


using namespace omnetpp;


Define_Module(TracIRSU);

std::vector< double > arr;
std::vector< int > arr1;
std::vector< int > arr2;
std::vector< double > arr3;
std::vector< double > arr4;
std::vector< double > arr5;
std::vector< double > arr6;
std::vector< double > arr7;
std::vector< double > arr8;
int duplicate;
double throughput;

double Load;
double MaxIntRatio;
double sub_throughput;
double Delay;
double MinDelay;



void TracIRSU::initialize(int stage) {

    BaseWaveApplLayer::initialize(stage);

}

void TracIRSU::onWSM(WaveShortMessage* wsm)
{

    duplicate = 0;

//    arr2.push_back(((WaveShortMessage *) wsm)->getSenderAddress());
    for (int i = 0; i < arr.size(); i++) {
        if (wsm->getSenderAddress() == arr1.at(i))
        {
            duplicate = 1;
        }
        else
        {
            continue;
        }
    }


    if((duplicate == 0 || wsm->getTowerData() == 1) && strcmp(((WaveShortMessage *) wsm)->getWsmData(), "6i")!=0)
    {

    EV <<"\nTower Data: "<< wsm->getTowerData()<<"\n";
    oneHop = 0.500000;


    if(strcmp(((WaveShortMessage *) wsm)->getWsmData(), "5i")==0 && (wsm->getTowerData()!= 1)){
        EV <<"\n In message time of vehicle: "<<wsm->getInMsgTime()<<"\n";
       ((WaveShortMessage *) wsm)->connTime = simTime() - (((WaveShortMessage *) wsm)->getInMsgTime() + oneHop);
       ((WaveShortMessage *) wsm)->intRatio = ((::omnetpp::simtime_t)15.0 / ((WaveShortMessage *) wsm)->connTime);
    }
    if(strcmp(((WaveShortMessage *) wsm)->getWsmData(), "5i")==0 && (wsm->getTowerData()!= 1))
    {

       wsm -> decVar = 1;
       EV << "\nSender's address: "<<((WaveShortMessage *) wsm)->getSenderAddress() <<"\n";
       EV <<"\nVehicle's computing power: "<<((WaveShortMessage *) wsm)->getCar_computing() <<"\n";
       EV <<"\nVehicle's storage: "<<((WaveShortMessage *) wsm)->getCar_storage() <<"\n";
       EV <<"\nVehicle's type of data: "<<((WaveShortMessage *) wsm)->getCar_data_type() <<"\n";
       EV << "And the car data: "<<wsm -> getCar_Data() <<"\n";
       EV << "\nWave short message data of the address "<< wsm->getSenderAddress()<<" is: ";
       EV<< wsm->getWsmData() <<"\n";
       EV << "Server processed " << ((WaveShortMessage *) wsm)->getCreatedBy();
       EV << "\nWorkload of the message: " << wsm->getWorkload() << "\n";
       EV << "Resource request\nComputing Power required: "<< ((WaveShortMessage *) wsm)->getComputingPower() <<"\n";
       EV << "Storage space needed: "<< ((WaveShortMessage *) wsm)->getStorage() <<"\n";
       EV << "Type of Data: "<< ((WaveShortMessage *) wsm)->getType_of_data() <<"\n";
       EV << "Total time delay taken by vehicle with ID: "<<((WaveShortMessage *) wsm)->getSenderAddress()<<" is equal to: "
          <<  ((WaveShortMessage *) wsm)->connTime<<"\n";
       EV << "Decision variable for the vehicle (x): "<<wsm -> decVar <<"\n";
       EV << "Single hop delay: "<<oneHop << "\n";
       EV << "How many resources can the vehicle provide (b): "<<wsm -> b1 + wsm -> b2 + wsm -> b3 <<"\n";
//       EV << "Time delay for this vehicle (t): "<<((WaveShortMessage *) wsm)->connTime;

       arr.push_back(((WaveShortMessage *) wsm)->intRatio);
       arr1.push_back(((WaveShortMessage *) wsm)->getSenderAddress());
       arr6.push_back(wsm->b1);
       arr7.push_back(wsm->b2);
       arr8.push_back(wsm->b3);

       throughput = ((wsm -> intRatio) * (wsm -> decVar) * (((wsm ->getCar_computing()) * (wsm -> b1)) + ((wsm -> getCar_storage()) * (wsm -> b2)) + ((wsm -> getCar_Data()) * (wsm -> b3))) + ((wsm -> decVar) * (wsm ->connTime))).dbl();

     //  ((WaveShortMessage *) wsm)->getSenderAddress()<<": "<<
       arr3.push_back(throughput);

       Load = ((wsm -> decVar) * (((wsm ->getCar_computing()) * (wsm -> b1)) + ((wsm -> getCar_storage()) * (wsm -> b2)) + ((wsm -> getCar_Data()) * (wsm -> b3))));

       arr4.push_back(Load);

//       (wsm -> intRatio) *

       Delay = ((wsm -> decVar) * (wsm ->connTime)).dbl();
       arr5.push_back(Delay);

       std::cout<<"\n*********************************************************\n";

       for (int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0; i < arr.size(), j < arr1.size(), k < arr3.size(), l < arr6.size(), m < arr7.size(), n < arr8.size(); i++, j++, k++, l++, m++, n++) {
           std::cout<<"\nThe Intermittancy ratio of this vehicle: "<< arr.at(i) << ' ' <<"\n";
           std::cout<<"\nThe Delay in communication of this vehicle: "<< arr5.at(i) << " "<<"\n";
           std::cout<<"\nSender Address: " << arr1.at(j) <<"\n";
           std::cout<<"\nThe total throughput of Car: "<< arr3.at(j) <<"\n";
           std::cout<< "\n"<<arr6.at(l)<<"\t "<<arr7.at(m)<<"\t "<<arr8.at(n);
           std::cout<<"\n*********************************************************";
       }


       MinDelay = *std::min_element(arr5.begin(), arr5.end());
       std::cout<<"\nMinimum delay till now: "<<MinDelay;

       MaxIntRatio = *std::max_element(arr.begin(), arr.end());
       std::cout<<"\nMaximum intermittancy ratio till now: "<<MaxIntRatio;

       for (int i = 0; i < arr4.size(); i++)
       {
           arr4.at(i) = (MaxIntRatio * (arr4.at(i))) + MinDelay;
       }


       sub_throughput = *std::max_element(arr4.begin(), arr4.end());

       for (int i = 0; i < arr4.size(); i++)
       {
           arr4.at(i) = ((arr4.at(i))/MaxIntRatio) - MinDelay;
       }

       std::cout<< "\nSub-Optimal Throughput from all Request hits till now: "<<sub_throughput<<"\n";
    }


       sendDelayedDown(wsm->dup(), uniform(1, 2));

       EV << "\nMessage sent!!";

    }

    else if(duplicate == 1 || strcmp(((WaveShortMessage *) wsm)->getWsmData(), "6i")==0)
    {
        EV <<"Message ignored by RSU!!\n";
    }


}

//


