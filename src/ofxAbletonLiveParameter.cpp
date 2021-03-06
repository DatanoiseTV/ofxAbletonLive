#include "ofxAbletonLiveParameter.h"

ofxAbletonLiveParameter::~ofxAbletonLiveParameter()
{
    delete parameter;
}

ofxAbletonLiveParameter::ofxAbletonLiveParameter(ofParameter<float> *parameter, int track, int device, int index, ofxOscSender *sender)
{
    this->parameter = parameter;
    this->track = track;
    this->device = device;
    this->index = index;
    this->sender = sender;
    oscAddress = "/live/device";
    parameter->addListener(this, &ofxAbletonLiveParameter::parameterChanged);
}

void ofxAbletonLiveParameter::setValue(float value)
{
    parameter->set(value);
    ofxOscMessage msg;
    msg.setAddress(oscAddress);
    msg.addIntArg(track);
    msg.addIntArg(device);
    msg.addIntArg(index);
    msg.addFloatArg(value);
    sender->sendMessage(msg);
}

void ofxAbletonLiveParameter::parameterChanged(float & value)
{
    setValue(parameter->get());
}