
#include "Circuit.h"


template<>
void Circuit::create<NOT>(size_t count, Queue<int>& nodeNumbers) {
    NOT* created = new NOT();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    for (size_t i = 0; i < count - 1; i++) {
        connectInPinWithNode(created->getInPinsBaseAdress() + i, *(copy.get()));
    }
    connectOutPinWithNode(created->getOutPinBaseAdress(), *(copy.get()));
    componentList.put(created);
}

template<>
void Circuit::create<Source>(Queue<int>& nodeNumbers) {
    Source* created = new Source();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    connectOutPinWithNode(created->getOutPinBaseAdress(), *(copy.get()));
    componentList.put(created);
    sourceList.put(created);
}
template<>
void Circuit::create<Lamp>(Queue<int>& nodeNumbers) {
    Lamp* created = new Lamp();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    connectInPinWithNode(created->getInPinsBaseAdress(), *(copy.get()));
    componentList.put(created);
    lampList.put(created);
}
template<>
void Circuit::create<Switch>(Queue<int>& nodeNumbers) {
    Switch* created = new Switch();
    created->setActiveQueue(&activeList);
    Queue<int> copy(nodeNumbers);
    connectInPinWithNode(created->getInPinsBaseAdress(), *(copy.get()));
    connectOutPinWithNode(created->getOutPinBaseAdress(), *(copy.get()));
    componentList.put(created);
    switchList.put(created);
}

std::ostream* Circuit::errorStream = &std::cerr;

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
        build();
    }
    catch (std::string errormsg) {
        printSeparatorLine(*errorStream, '*', 50);
        *errorStream << "SYNTAX ERROR" << std::endl;
        printSeparatorLine(*errorStream, '*', 50);
        *errorStream << errormsg;
        printSeparatorLine(*errorStream, '*', 50);
        reset();
        return;
    }
    configured = true;
}

void Circuit::build()
{
    if (!inputfile.is_open()) {
        throw std::string("Input file doesn't exist or can't be opened...");
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
    while (c != ':' || info.idx > info.line.length()) {
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
        throw std::string("Invalid component type: \"" + lineType + "\"!");
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
            throw std::string("Incorrect syntax at: \"()" + std::string(info.line.c_str() + info.idx) + "\" !");
        }
        nodeNumbers.put(new int(read));
        char c;
        if (!(s >> c)) {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + std::string(info.line.c_str() + info.idx) + "\" !");
        }
        if (c != ',' && c != ')') {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + std::string(info.line.c_str() + info.idx) + "\" !");
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
            throw std::string("Incorrect pin count for SOURCE type at line " + std::to_string(info.lineCount));
        break;
    case LAMP:
        if (count != 1)
            throw std::string("Incorrect pin count for LAMP type at line " + std::to_string(info.lineCount));
        break;
    case SWITCH:
        if (count != 2)
            throw std::string("Incorrect pin count for SWITCH type at line " + std::to_string(info.lineCount));
        break;
    case And:
        if (count <= 2)
            throw std::string("Incorrect pin count for AND type at line " + std::to_string(info.lineCount));
        break;
    case Or:
        if (count <= 2)
            throw std::string("Incorrect pin count for OR type at line " + std::to_string(info.lineCount));
        break;
    case Not:
        if (count != 2)
            throw std::string("Incorrect pin count for NOT type at line " + std::to_string(info.lineCount));
        break;
    case Xor:
        if (count <= 2)
            throw std::string("Incorrect pin count for XOR type at line " + std::to_string(info.lineCount));
        break;
    case Nand:
        if (count <= 2)
            throw std::string("Incorrect pin count for NAND type at line " + std::to_string(info.lineCount));
        break;
    case Nor:
        if (count <= 2)
            throw std::string("Incorrect pin count for NOR type at line " + std::to_string(info.lineCount));
        break;
    case Xnor:
        if (count <= 2)
            throw std::string("Incorrect pin count for XNOR type at line " + std::to_string(info.lineCount));
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

void Circuit::connectInPinWithNode(InPin* pin, size_t id)
{
    Queue<Node> copy(nodeList);
    bool found = false;
    while (!copy.isEmpty()) {
        Node* current = copy.get();
        if (current->getID() == id) {
            current->addOutPin(pin);
            found = true;
            break;
        }
    }
    if (!found) {
        Node* newNode = new Node(id);
        newNode->addOutPin(pin);
        newNode->setActiveQueue(&activeList);
        nodeList.put(newNode);
    }
}

void Circuit::connectOutPinWithNode(OutPin* pin, size_t id)
{
    Queue<Node> copy(nodeList);
    bool found = false;
    while (!copy.isEmpty()) {
        Node* current = copy.get();
        if (current->getID() == id) {
            pin->connectToPin(current->getInPin());
            found = true;
            break;
        }
    }
    if (!found) {
        Node* newNode = new Node(id);
        pin->connectToPin(newNode->getInPin());
        newNode->setActiveQueue(&activeList);
        nodeList.put(newNode);
    }
}

Circuit::Circuit() : simulated(false), configured(false), componentList(true), nodeList(true) {}

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
    if (inputfile.is_open()) {
        inputfile.close();
    }

    inputFileName = fileName;
    inputfile.open(inputFileName);

    if (!inputfile.is_open() && inputFileName != "") {
        *errorStream << "There is no file with name: " << fileName << std::endl;
    }
}

const std::string& Circuit::getSourceFileName() const
{
    return inputFileName;
}

void Circuit::simulate(std::ostream& os)
{
    if (!configured) {
        configure();
    }
    Queue<Source> temp(sourceList);
    while (!temp.isEmpty()) {
        activeList.put(temp.get());
    }

    while (!activeList.isEmpty()) {
        Component* current = activeList.get();
        current->executeFunction();
    }

    os << *this;
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
    printSeparatorLine(os, '*', 50);
    os << circuit.getSourceFileName() << std::endl;
    printSeparatorLine(os, '*', 50);
    circuit.printAllSourceStates(os);
    printSeparatorLine(os, '-', 50);
    circuit.printAllSwitchStates(os);
    printSeparatorLine(os, '-', 50);
    circuit.printAllLampStates(os);
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