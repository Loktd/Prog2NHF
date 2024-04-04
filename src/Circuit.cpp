
#include "Circuit.h"

std::ostream* Circuit::errorStream = &std::cerr;

void Circuit::nullifyPointers()
{
    componentList = nullptr;
    sourceList = nullptr;
    switchList = nullptr;
    lampList = nullptr;

    activeList = nullptr;
}

void Circuit::allocateMemory()
{
    componentList = new Queue<Component>(true);
    sourceList = new Queue<Source>(false);
    switchList = new Queue<Switch>(false);
    lampList = new Queue<Lamp>(false);

    activeList = new Queue<Component>(false);
}

void Circuit::deleteMemory()
{
    delete componentList;
    delete sourceList;
    delete switchList;
    delete lampList;

    delete activeList;

    if (inputfile.is_open())
        inputfile.close();
}

Circuit::Circuit() : outputValid(false)
{
    nullifyPointers();
    allocateMemory();
}

Circuit::Circuit(const Circuit& source)
{
    nullifyPointers();
    *this = source;
}

Circuit& Circuit::operator=(const Circuit& source)
{
    if (this != &source) {
        outputValid = false;
        setInputFile(source.inputFileName);
        configure();
    }
    return *this;
}

void Circuit::setInputFile(const std::string& fileName)
{
    if (inputfile.is_open()) {
        inputfile.close();
    }

    inputFileName = fileName;
    inputfile.open(inputFileName);

    if (!inputfile.is_open() && inputFileName != "") {
        *errorStream << "There is no file with name: " << fileName << std::endl;
    }
}

const std::string& Circuit::getInputFileName() const
{
    return inputFileName;
}

void Circuit::configure()
{
    deleteMemory();
    allocateMemory();
}

void Circuit::setErrorStream(std::ostream* os)
{
    errorStream = os;
}

void Circuit::simulate()
{
    Queue<Source> temp(sourceList);
    while (!temp.isEmpty()) {
        activeList->put(temp.get());
    }

    while (!activeList->isEmpty()) {
        Component* current = activeList->get();
        current->executeFunction();
    }
}

void Circuit::printLampStates(std::ostream& os) const
{
    Queue<Lamp> copyList(lampList);
    while (!copyList.isEmpty()) {
        Lamp* current = copyList.get();
        os << *current << std::endl;
    }
}

void Circuit::printSourceStates(std::ostream& os) const
{
    Queue<Source> copyList(sourceList);
    while (!copyList.isEmpty()) {
        Source* current = copyList.get();
        os << *current << std::endl;
    }
}

void Circuit::printSwitchStates(std::ostream& os) const
{
    Queue<Switch> copyList(switchList);
    while (!copyList.isEmpty()) {
        Switch* current = copyList.get();
        os << *current << std::endl;
    }
}

Circuit::~Circuit()
{
    deleteMemory();
}

std::ostream& operator<<(std::ostream& os, const Circuit& circuit)
{
    printSeparatorLine(os, '*', 50);
    os << circuit.getInputFileName() << std::endl;
    printSeparatorLine(os, '*', 50);
    circuit.printSourceStates(os);
    printSeparatorLine(os, '-', 50);
    circuit.printSwitchStates(os);
    printSeparatorLine(os, '-', 50);
    circuit.printLampStates(os);
    printSeparatorLine(os, '*', 50);
    return os;
}

void printSeparatorLine(std::ostream& os, char c, int times)
{
    for (int i = 0; i < times; i++) {
        os << c;
    }
    os << std::endl;
}
