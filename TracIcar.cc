#include <veins/modules/application/traci/TracIcar.h>


#include<string.h>
#include<omnetpp.h>

using namespace omnetpp;


Define_Module(TracIcar);

double multiHop;


void TracIcar::initialize(int stage) {

    BaseWaveApplLayer::initialize(stage);

    populateWSM(newCar);



    newCar->setCar_computing(uniform(15, 20));
    newCar->setCar_storage(uniform(10, 20));
    newCar->setCar_data_type(uniform('a', 'c'));


}

void TracIcar::onWSM(WaveShortMessage* wsm)
{
//
   if(wsm->hopcount == 0)
   {
   wsm->hopcount = wsm->hopcount + 1;
   sendDelayedDown(wsm->dup(), uniform(1,3));
//   msgQueue.insert(wsm);
   newCar->setInMsgTime(simTime());
   EV << "Message from RSU or Mobile device!!\n";
   std::cout << "\n"<< wsm->getSenderAddress();
   EV << "Server processed " << ((WaveShortMessage *) wsm)->getCreatedBy();
   EV << "\n Workload of the message: " << wsm->getWorkload() << "\n";
   EV << "Resource request\n Computing Power required: "<< ((WaveShortMessage *) wsm)->getComputingPower() <<"\n";
   EV << "Storage space needed: "<< ((WaveShortMessage *) wsm)->getStorage() <<"\n";
   EV << "Type of Data: "<< ((WaveShortMessage *) wsm)->getType_of_data() <<"\n";
   EV << "Car's computing power being offered: "<<newCar->getCar_computing() <<"\n";
   EV << "Car's storage being offered: "<<newCar->getCar_storage() <<"\n";
   EV << "Car's data being offered: "<<newCar->getCar_data_type() <<"\n";

   EV << "In coming resource request message time: "<< newCar->getInMsgTime() <<"\n";
   EV << "\nHop count is: "<<wsm->hopcount <<"\n";

   if(((WaveShortMessage *) wsm)->getComputingPower() != 0 && ((WaveShortMessage *) wsm)->getStorage() != 0 && ((WaveShortMessage *) wsm)->getType_of_data() != '\0')
   {

       newCar->b1 = 0;
       newCar->b2 = 0;
       newCar->b3 = 0;

       newCar -> setCar_Data(0);

       if((newCar->getCar_computing() >= ((WaveShortMessage *) wsm)->getComputingPower()))
       {
           newCar->b1 =  newCar->b1 + 1;
           if((newCar->getCar_storage() >= ((WaveShortMessage *) wsm)->getStorage()))
           {
               newCar->b2 =  newCar->b2 + 1;
               if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
               {
                   newCar->b3 =  newCar->b3 + 1;
                   newCar->setCar_Data(newCar->getCar_Data() + 10);
                   EV<<"Request Hit!\n";
                   wsm->hopcount = wsm->hopcount + 1;
                   EV << "\nHop count is: "<<wsm->hopcount <<"\n";
                   newCar->setWsmData("5i");
                   sendDelayedDown(newCar->dup(), uniform(1, 3));
                   EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                   EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
               }
               else
               {
                   EV<<"Request Hit!\n";
                   newCar->setWsmData("5i");
                   wsm->hopcount = wsm->hopcount + 1;
                   EV << "\nHop count is: "<<wsm->hopcount <<"\n";
                   sendDelayedDown(newCar->dup(), uniform(1, 3));
                   EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
               }
           }
           else if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
           {
               newCar->b3 =  newCar->b3 + 1;
               newCar->setCar_Data(newCar->getCar_Data() + 10);
               EV<<"Request Hit!\n";
               newCar->setWsmData("5i");
               wsm->hopcount = wsm->hopcount + 1;
               EV << "\nHop count is: "<<wsm->hopcount <<"\n";
               sendDelayedDown(newCar->dup(), uniform(1, 3));
               EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
               EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
           }
           else
           {
               EV<<"Request Hit!\n";
               newCar->setWsmData("5i");
               wsm->hopcount = wsm->hopcount + 1;
               EV << "\nHop count is: "<<wsm->hopcount <<"\n";
               sendDelayedDown(newCar->dup(), uniform(1, 3));
               EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
           }


       }
       else if((newCar->getCar_storage() >= ((WaveShortMessage *) wsm)->getStorage()))
       {
           newCar->b2 =  newCar->b2 + 1;

               if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
               {
                   newCar->b3 =  newCar->b3 + 1;
                   newCar->setCar_Data(newCar->getCar_Data() + 10);
                   EV<<"Request Hit!\n";
                   newCar->setWsmData("5i");
                   wsm->hopcount = wsm->hopcount + 1;
                   EV << "\nHop count is: "<<wsm->hopcount <<"\n";
                   sendDelayedDown(newCar->dup(), uniform(1, 3));
                   EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                   EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
               }
               else
               {
                   EV<<"Request Hit!\n";
                   newCar->setWsmData("5i");
                   wsm->hopcount = wsm->hopcount + 1;
                   EV << "\nHop count is: "<<wsm->hopcount <<"\n";
                   sendDelayedDown(newCar->dup(), uniform(1, 3));
                   EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
               }

       }
       else if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
              {
                   newCar->b3 =  newCar->b3 + 1;
                   newCar->setCar_Data(newCar->getCar_Data() + 10);
                   EV<<"Request Hit!\n";
                   newCar->setWsmData("5i");
                   wsm->hopcount = wsm->hopcount + 1;
                   EV << "\nHop count is: "<<wsm->hopcount <<"\n";
                   sendDelayedDown(newCar->dup(), uniform(1, 3));
                   EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                   EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
              }


       else
       {
           EV<<"Request Miss!\n";
           newCar->setWsmData("6i");
           wsm->hopcount = wsm->hopcount + 1;
           EV << "\nHop count is: "<<wsm->hopcount <<"\n";
           sendDelayedDown(newCar->dup(), uniform(2, 3));
           EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;

       }
   }
   }

   else if(wsm->hopcount == 1)
   {
       EV <<"Testing!!\n";
       newCar->setInMsgTime(simTime());
          EV << "Message from Other car (multihop implemented)!!\n";
          std::cout << "\n"<< wsm->getSenderAddress();
          EV << "Server processed " << ((WaveShortMessage *) wsm)->getCreatedBy();
          EV << "\n Workload of the message: " << wsm->getWorkload() << "\n";
          EV << "Resource request\n Computing Power required: "<< ((WaveShortMessage *) wsm)->getComputingPower() <<"\n";
          EV << "Storage space needed: "<< ((WaveShortMessage *) wsm)->getStorage() <<"\n";
          EV << "Type of Data: "<< ((WaveShortMessage *) wsm)->getType_of_data() <<"\n";
          EV << "Car's computing power being offered: "<<newCar->getCar_computing() <<"\n";
          EV << "Car's storage being offered: "<<newCar->getCar_storage() <<"\n";
          EV << "Car's data being offered: "<<newCar->getCar_data_type() <<"\n";

          EV << "In coming resource request message time: "<< newCar->getInMsgTime() <<"\n";

          EV << "\nHop count is: "<<wsm->hopcount <<"\n";

          if(((WaveShortMessage *) wsm)->getComputingPower() != 0 && ((WaveShortMessage *) wsm)->getStorage() != 0 && ((WaveShortMessage *) wsm)->getType_of_data() != '\0')
          {

              newCar->b1 = 0;
              newCar->b2 = 0;
              newCar->b3 = 0;

              newCar -> setCar_Data(0);

              if((newCar->getCar_computing() >= ((WaveShortMessage *) wsm)->getComputingPower()))
              {
                  newCar->b1 =  newCar->b1 + 1;
                  if((newCar->getCar_storage() >= ((WaveShortMessage *) wsm)->getStorage()))
                  {
                      newCar->b2 =  newCar->b2 + 1;
                      if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
                      {
                          newCar->b3 =  newCar->b3 + 1;
                          newCar->setCar_Data(newCar->getCar_Data() + 10);
                          EV<<"Request Hit!\n";
                          newCar->hopcount = newCar->hopcount + 2;
                          EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                          newCar->setWsmData("5i");
                          sendDelayedDown(newCar->dup(), uniform(1, 3));
                          EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                          EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
                      }
                      else
                      {
                          EV<<"Request Hit!\n";
                          newCar->setWsmData("5i");
                          newCar->hopcount = newCar->hopcount + 2;
                          EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                          sendDelayedDown(newCar->dup(), uniform(1, 3));
                          EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                      }
                  }
                  else if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
                  {
                      newCar->b3 =  newCar->b3 + 1;
                      newCar->setCar_Data(newCar->getCar_Data() + 10);
                      EV<<"Request Hit!\n";
                      newCar->hopcount = newCar->hopcount + 2;
                      EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                      newCar->setWsmData("5i");
                      sendDelayedDown(newCar->dup(), uniform(1, 3));
                      EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                      EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
                  }
                  else
                  {
                      EV<<"Request Hit!\n";
                      newCar->hopcount = newCar->hopcount + 2;
                      EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                      newCar->setWsmData("5i");
                      sendDelayedDown(newCar->dup(), uniform(1, 3));
                      EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                  }


              }
              else if((newCar->getCar_storage() >= ((WaveShortMessage *) wsm)->getStorage()))
              {
                  newCar->b2 =  newCar->b2 + 1;

                      if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
                      {
                          newCar->b3 =  newCar->b3 + 1;
                          newCar->setCar_Data(newCar->getCar_Data() + 10);
                          EV<<"Request Hit!\n";
                          newCar->hopcount = newCar->hopcount + 2;
                          EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                          newCar->setWsmData("5i");
                          sendDelayedDown(newCar->dup(), uniform(1, 3));
                          EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                          EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
                      }
                      else
                      {
                          EV<<"Request Hit!\n";
                          newCar->hopcount = newCar->hopcount + 2;
                          EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                          newCar->setWsmData("5i");
                          sendDelayedDown(newCar->dup(), uniform(1, 3));
                          EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                      }

              }
              else if((newCar->getCar_data_type() == ((WaveShortMessage *) wsm)->getType_of_data()))
                     {
                          newCar->b3 =  newCar->b3 + 1;
                          newCar->setCar_Data(newCar->getCar_Data() + 10);
                          EV<<"Request Hit!\n";
                          newCar->hopcount = newCar->hopcount + 2;
                          EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                          newCar->setWsmData("5i");
                          sendDelayedDown(newCar->dup(), uniform(1, 3));
                          EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;
                          EV<<"\nValue of Car Data: "<<newCar->getCar_Data();
                     }


              else
              {
                  EV<<"Request Miss!\n";
                  newCar->hopcount = newCar->hopcount + 2;
                  EV << "\nHop count is: "<<newCar->hopcount <<"\n";
                  newCar->setWsmData("6i");
                  sendDelayedDown(newCar->dup(), uniform(2, 3));
                  EV<<"\nValue of b: "<<newCar->b1 + newCar->b2 + newCar->b3;

              }
          }

   }
   else if(wsm->hopcount == 2)
   {
       multiHop = 0.4000;
       wsm->setInMsgTime(wsm->getInMsgTime() + multiHop);
       EV <<"Delay in first hop: "<<wsm->getInMsgTime() <<"\n";
       sendDelayedDown(wsm->dup(), uniform(1,3));
       EV <<"\nMESSAGE REDIRECTED!!\n";
   }

}
