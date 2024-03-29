
#include "Circuit.h"
#include "Component.h"
#include "Source.h"
#include "Switch.h"
#include "Lamp.h"

void Circuit::reset() {
}

Circuit::Circuit(const std::ostream & outStream){
}

Circuit::Circuit(const Circuit & source){
}

void Circuit::setOutputStream(const std::ostream & os) {
}

void Circuit::configure(const std::string & fileName) {
}

void Circuit::simulate() {
}

void Circuit::flipSource(int connectedNode) {
}

void Circuit::flipSwitch(int connectedNode1, int connectedNode2) {
}

void Circuit::readLampStates() const {
}

void Circuit::readSourceStates() const {
}

void Circuit::readSwitchStates() const {
}

Circuit::~Circuit(){
}

