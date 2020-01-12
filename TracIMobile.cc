
#include "veins/modules/application/traci/TracIMobile.h"
#include<string.h>
#include<omnetpp.h>

using namespace omnetpp;


Define_Module(TracIMobile);



void TracIMobile::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    /*computingPower = Resource::computingPower;
    power = Resource::storage;
    typeofdata = Resource::type_of_data;*/
    EV << "HEY \n";
    genMsgSignal = new cMessage("\tStart of Simulation!!");
    EV << genMsgSignal <<"\n" ;

    scheduleAt(simTime().dbl() + uniform(10, 15), genMsgSignal);

}

void TracIMobile::generateMessage() {


    EV <<"\n"<< getName() << "node : Generating Message.\n";
    std::string message = "offloading from ";
    message.append(getName());

    populateWSM(newMsg);

    newMsg->setWsmData("4i");
    newMsg->setCreatedBy(getName());
    newMsg->setWorkload(uniform(5, 15));
    newMsg->setComputingPower(uniform(15, 20));
    newMsg->setStorage(uniform(10, 20));
    newMsg->setType_of_data(uniform('a', 'c'));

    newMsg->setGenTime(simTime());
    EV << "Hello World\n";
    EV << "Feedback size: "<< ((WaveShortMessage *) newMsg)->getWorkload()<<"\n";
    EV << "Message from: "<< ((WaveShortMessage *) newMsg)->getCreatedBy() <<"\n";
    EV << "Resource request\n Computing Power required: "<< ((WaveShortMessage *) newMsg)->getComputingPower() <<"\n";
    EV << "Storage space needed: "<< ((WaveShortMessage *) newMsg)->getStorage() <<"\n";
    EV << "a = Media File\nb = NEWS\nc = Text/document\n";
    EV << "Type of Data: "<< ((WaveShortMessage *) newMsg)->getType_of_data() <<"\n";


    scheduleAt(simTime().dbl() + uniform(34.50, 36.70), newMsg->dup());


}

//void TracIMobile::onWSM(WaveShortMessage* wsm) {
    //this rsu repeats the received traffic update in 2 seconds plus some random delay
    //wsm->setSenderAddress(myId);
    //sendDelayedDown(wsm->dup(), 2 + uniform(0.01,0.2));
//}

void TracIMobile::handleMessage(cMessage *msg) {
    if (msg == genMsgSignal)
    {
        EV << "\nInitial Message. Needs to be deleted!";
        delete msg;
        EV << "\n Initial message deleted. Time to start generating.";
        generateMessage();
    }
    else {
        if (WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg)){
            sendDelayedDown(wsm->dup(), 20);
            EV << "\nMessage Sent!!!" ;

        } else {
            BaseWaveApplLayer::handleLowerMsg(msg);
        }
    }

}
