
#include <veins/modules/application/traci/TracITower.h>

#include<string.h>
#include<omnetpp.h>


using namespace omnetpp;


Define_Module(TracITower);



void TracITower::initialize(int stage) {

    BaseWaveApplLayer::initialize(stage);


}

void TracITower::onWSM(WaveShortMessage* wsm)
{

    EV<<"\n"<<wsm->getSenderAddress()<<"\n";
    if((strcmp(((WaveShortMessage *) wsm)->getWsmData(), "4i")==0))
    {
       EV<<"\ntest\n";
       wsm->setTowerData(1);
       sendDown(wsm->dup());

       EV << "\nMessage sent!!";

    }


    else
    {
        EV<<"\nMESSAGE IGNORED by TOWER!!";
    }

}



