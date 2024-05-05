#include "Circuit.h"

#include <ctime>


template<>
void Circuit::create<NOT>(size_t count, Queue<int>& nodeNumbers) {
    NOT* created = new NOT();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    for (size_t i = 0; i < count - 1; i++) {
        connectInPinWithNode(created->getInputPinByIndex(i), *(copy.get()), i);
    }
    connectOutPinWithNode(created, created->getOutputPinByIndex(0), *(copy.get()), 0);
    componentList.put(created);
    incomponents.put(created);
}

template<>
void Circuit::create<Source>(Queue<int>& nodeNumbers) {
    Source* created = new Source();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    connectOutPinWithNode(created, created->getOutputPinByIndex(0), *(copy.get()), 0);
    componentList.put(created);
    sourceList.put(created);
}
template<>
void Circuit::create<Lamp>(Queue<int>& nodeNumbers) {
    Lamp* created = new Lamp();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    connectInPinWithNode(created->getInputPinByIndex(0), *(copy.get()), 0);
    componentList.put(created);
    lampList.put(created);
    incomponents.put(created);
}
template<>
void Circuit::create<Switch>(Queue<int>& nodeNumbers) {
    Switch* created = new Switch();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    connectInPinWithNode(created->getInputPinByIndex(0), *(copy.get()), 0);
    connectOutPinWithNode(created, created->getOutputPinByIndex(0), *(copy.get()), 0);
    componentList.put(created);
    switchList.put(created);
    incomponents.put(created);
}

void Circuit::reset()
{
    componentList.clear();
    sourceList.clear();
    switchList.clear();
    lampList.clear();
    activeList.clear();

    if (inputfile.is_open())
        inputfile.close();
}

void Circuit::configure() {
    try {
        reset();
        build();
    }
    catch (std::string errormsg) {
        *errorStream << std::endl;
        printSeparatorLine(*errorStream, '=', 50);
        *errorStream << "SYNTAX ERROR" << std::endl;
        printSeparatorLine(*errorStream, '*', 50);
        *errorStream << errormsg;
        printSeparatorLine(*errorStream, '=', 50);
        *errorStream << std::endl;
        reset();
        return;
    }
    configured = true;
}

void Circuit::build()
{
    if (inputFileName == "")
        throw std::string("No file given...\n");
    if (!inputfile.is_open()) {
        inputfile.open(inputFileName);
    }
    if (!inputfile.is_open()) {
        throw std::string("Input file doesn't exist or can't be opened...\n");
    }
    inputfile.seekg(std::ios_base::beg);
    ContentInfo info;
    while (!inputfile.eof()) {
        std::getline(inputfile, info.line);
        if (!info.line.empty()) {
            info.idx = 0;
            buildLine(info);
        }
    }
}


void Circuit::buildLine(ContentInfo& info)
{
    checkLineType(info);
    char c = info.line[info.idx++];
    while (info.idx < info.line.length()) {
        if (c == '(') {
            buildComponent(info);
        }
        c = info.line[info.idx++];
    }
}

void Circuit::checkLineType(ContentInfo& info)
{
    const size_t totalType = 10;
    std::string lineType;
    std::string validTypes[totalType] = {
        "SOURCE", "LAMP", "SWITCH", "AND", "OR", "NOT", "XOR", "NAND", "NOR", "XNOR"
    };
    char c = info.line[info.idx++];
    while (c != ':' && info.idx < info.line.length()) {
        lineType += c;
        c = info.line[info.idx++];
    }

    bool valid = false;
    for (size_t i = 0; i < totalType; i++) {
        if (validTypes[i] == lineType) {
            valid = true;
            info.type = ComponentType(i + 1);
            break;
        }
    }

    if (!valid) {
        throw std::string("Invalid component type: \"" + lineType + "\"!\n");
    }
}

void Circuit::buildComponent(ContentInfo& info)
{
    Queue<int> nodeNumbers(true);
    getNodeNumbers(info, nodeNumbers);

    size_t count = nodeNumbers.size();
    checkNodeCount(info, count);

    createBasedOnType(info, count, nodeNumbers);
}

void Circuit::getNodeNumbers(ContentInfo& info, Queue<int>& nodeNumbers)
{
    int read;
    std::stringstream s(std::string(info.line.c_str() + info.idx));
    bool go = true;
    while (go) {
        if (!(s >> read)) {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + std::string(info.line.c_str() + info.idx) + "\" !\n");
        }
        nodeNumbers.put(new int(read));
        char c;
        if (!(s >> c)) {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + std::string(info.line.c_str() + info.idx) + "\" !\n");
        }
        if (c != ',' && c != ')') {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + std::string(info.line.c_str() + info.idx) + "\" !\n");
        }
        else if (c == ')') {
            while (info.line[info.idx] != ')')
                info.idx++;
            break;
        }
    }
}

void Circuit::checkNodeCount(ContentInfo& info, size_t count)
{
    switch (info.type)
    {
    case SOURCE:
        if (count != 1)
            throw std::string("Incorrect pin count for SOURCE type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case LAMP:
        if (count != 1)
            throw std::string("Incorrect pin count for LAMP type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case SWITCH:
        if (count != 2)
            throw std::string("Incorrect pin count for SWITCH type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case And:
        if (count <= 2)
            throw std::string("Incorrect pin count for AND type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case Or:
        if (count <= 2)
            throw std::string("Incorrect pin count for OR type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case Not:
        if (count != 2)
            throw std::string("Incorrect pin count for NOT type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case Xor:
        if (count <= 2)
            throw std::string("Incorrect pin count for XOR type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case Nand:
        if (count <= 2)
            throw std::string("Incorrect pin count for NAND type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case Nor:
        if (count <= 2)
            throw std::string("Incorrect pin count for NOR type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    case Xnor:
        if (count <= 2)
            throw std::string("Incorrect pin count for XNOR type at line " + std::to_string(info.lineCount)) + "\n";
        break;
    default:
        throw std::string("No found type error...");
        break;
    }
}

void Circuit::createBasedOnType(ContentInfo& info, size_t count, Queue<int>& nodeNumbers)
{
    switch (info.type)
    {
    case SOURCE:
        create<Source>(nodeNumbers);
        break;
    case LAMP:
        create<Lamp>(nodeNumbers);
        break;
    case SWITCH:
        create<Switch>(nodeNumbers);
        break;
    case And:
        create<AND>(count, nodeNumbers);
        break;
    case Or:
        create<OR>(count, nodeNumbers);
        break;
    case Not:
        create<NOT>(count, nodeNumbers);
        break;
    case Xor:
        create<XOR>(count, nodeNumbers);
        break;
    case Nand:
        create<NAND>(count, nodeNumbers);
        break;
    case Nor:
        create<NOR>(count, nodeNumbers);
        break;
    case Xnor:
        create<XNOR>(count, nodeNumbers);
        break;
    default:
        throw std::string("No found type error...");
        break;
    }
}

void Circuit::connectInPinWithNode(InputPin* pin, size_t id, size_t idx)
{
    Queue<Node> copy(nodeList);
    bool found = false;
    while (!copy.isEmpty()) {
        Node* current = copy.get();
        if (current->getID() == id) {
            current->addOutputPin(pin);
            pin->getComponent()->setInputNodeID(idx, id);
            found = true;
            break;
        }
    }
    if (!found) {
        Node* newNode = new Node(id);
        newNode->addOutputPin(pin);
        pin->getComponent()->setInputNodeID(idx, id);
        newNode->setActiveQueue(&activeList);
        nodeList.put(newNode);
        incomponents.put(newNode);
    }
}

void Circuit::connectOutPinWithNode(OutputComponent* component, OutputPin* pin, size_t id, size_t idx)
{
    Queue<Node> copy(nodeList);
    bool found = false;
    while (!copy.isEmpty()) {
        Node* current = copy.get();
        if (current->getID() == id) {
            pin->connectToPin(current->getInPin());
            component->setOutputNodeID(idx, id);
            found = true;
            break;
        }
    }
    if (!found) {
        Node* newNode = new Node(id);
        pin->connectToPin(newNode->getInPin());
        component->setOutputNodeID(idx, id);
        newNode->setActiveQueue(&activeList);
        nodeList.put(newNode);
        incomponents.put(newNode);
    }
}

Circuit::Circuit() : errorStream(&std::cerr), simulated(false), configured(false), componentList(true), nodeList(true) {}

Circuit::Circuit(const Circuit& source) : componentList(true)
{
    *this = source;
}

Circuit& Circuit::operator=(const Circuit& source)
{
    if (this != &source) {
        simulated = false;
        configured = false;
        reset();
        setSourceFile(source.inputFileName);
        configure();
    }
    return *this;
}

void Circuit::setErrorStream(std::ostream* os)
{
    errorStream = os;
}

void Circuit::setSourceFile(const std::string& fileName)
{
    std::string prev = inputFileName;

    if (inputfile.is_open()) {
        inputfile.close();
    }

    inputFileName = fileName;
    inputfile.open(inputFileName);

    if (!inputfile.is_open() && inputFileName != "") {
        inputFileName = prev;
        inputfile.open(prev);
        *errorStream << "There is no file with name: " << fileName << std::endl;
    }
    else {
        configured = false;
        simulated = false;
    }
}

const std::string& Circuit::getSourceFileName() const
{
    return inputFileName;
}

void Circuit::simulate(std::ostream& os)
{
    if (!configured)
        configure();

    if (configured) {
        for (size_t i = 0; i < incomponents.size(); i++) {
            InputComponent* current = incomponents.get();
            current->resetForSimulation();
            incomponents.put(current);
        }

        Queue<Source> temp(sourceList);
        while (!temp.isEmpty()) {
            activeList.put(temp.get());
        }

        bool wasShortCircuit = false;

        while (!activeList.isEmpty()) {
            Component* current = activeList.get();
            try {
                current->executeFunction();
            }
            catch (std::string str) {
                if (!wasShortCircuit) {
                    printSeparatorLine(os, '=', 50);
                    os << "ERROR DURING SIMULATION!" << std::endl;
                    printSeparatorLine(os, '=', 50);
                    std::time_t result = std::time(nullptr);
                    os << std::ctime(&result);
                    printSeparatorLine(os, '*', 50);
                    wasShortCircuit = true;
                }
                os << str << " at node ";
                dynamic_cast<OutputComponent*>(current)->printConnectedOutputNodes(os);
                os << "!" << std::endl;
            }
        }

        if (!wasShortCircuit)
            os << *this;
        else {
            printSeparatorLine(os, '=', 50);
            os << std::endl << std::endl;
        }
    }
}

void Circuit::setSource(size_t connectedNode, Signal newSignal)
{
    if (!configured) {
        configure();
    }
    Queue<Source> copy(sourceList);
    while (!copy.isEmpty()) {
        Source* current = copy.get();
        if (current->isConnectedToNodeOnOutput(connectedNode)) {
            current->setOutput(newSignal);
            return;
        }
    }
    *errorStream << "No source connected to node: " << connectedNode << "!" << std::endl;
}

void Circuit::printAllLampStates(std::ostream& os) const
{
    Queue<Lamp> copyList(lampList);
    while (!copyList.isEmpty()) {
        Lamp* current = copyList.get();
        os << *current << std::endl;
    }
}

void Circuit::printAllSourceStates(std::ostream& os) const
{
    Queue<Source> copyList(sourceList);
    while (!copyList.isEmpty()) {
        Source* current = copyList.get();
        os << *current << std::endl;
    }
}

void Circuit::setSwitch(size_t connectedNode1, size_t connectedNode2, bool closed)
{
    Queue<Switch> copy(switchList);
    while (!copy.isEmpty()) {
        Switch* current = copy.get();
        if (current->isConnectedToNodes(connectedNode1, connectedNode2)) {
            current->setState(closed);
            return;
        }
    }
    *errorStream << "No switch connected to nodes: " << connectedNode1 << " and " << connectedNode2 << "!" << std::endl;
}

void Circuit::printAllSwitchStates(std::ostream& os) const
{
    Queue<Switch> copyList(switchList);
    while (!copyList.isEmpty()) {
        Switch* current = copyList.get();
        os << *current << std::endl;
    }
}

Circuit::~Circuit()
{
    reset();
}

std::ostream& operator<<(std::ostream& os, const Circuit& circuit)
{
    size_t times = circuit.getSourceFileName().length();
    times = times < 75 ? 75 : times;
    printSeparatorLine(os, '=', times);
    os << circuit.getSourceFileName() << std::endl;
    printSeparatorLine(os, '*', times);
    std::time_t result = std::time(nullptr);
    os << std::ctime(&result);
    printSeparatorLine(os, '*', times);
    circuit.printAllSourceStates(os);
    printSeparatorLine(os, '-', times);
    circuit.printAllSwitchStates(os);
    printSeparatorLine(os, '-', times);
    circuit.printAllLampStates(os);
    printSeparatorLine(os, '=', times);
    os << std::endl << std::endl;
    return os;
}

void printSeparatorLine(std::ostream& os, char c, int times)
{
    for (int i = 0; i < times; i++) {
        os << c;
    }
    os << std::endl;
}