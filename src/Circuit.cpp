#include "Circuit.h"

#include <ctime>

// Template függvények
template<typename ComponentType>
void Circuit::create(Queue<size_t>& nodeNumbers) {
    size_t count = nodeNumbers.size();
    ComponentType* created = new ComponentType(count - 1);

    IOComponent* ptr = dynamic_cast<IOComponent*>(created);
    if (ptr == nullptr) {
        delete created;
        throw PointerConversionError("Trying to create non-IOComponent type...");
    }
    ptr->setActiveQueue(&activeList);

    Queue<size_t>::iterator it = nodeNumbers.begin();
    for (size_t i = 0; it != nodeNumbers.end() && i < count - 1; it++, i++) {
        size_t current = *(*it);
        connectInputPinWithNode(ptr->getInputPinByIndex(i), current, i);
    }
    size_t outID = *(*it);
    connectOutputPinWithNode(created, ptr->getOutputPinByIndex(0), outID, 0);

    componentList.put(created);
    inputComponentList.put(created);
}

template<>
void Circuit::create<NOT>(Queue<size_t>& nodeNumbers) {
    NOT* created = new NOT();
    created->setActiveQueue(&activeList);

    Queue<size_t>::iterator it = nodeNumbers.begin();
    size_t current = *(*it++);
    connectInputPinWithNode(created->getInputPinByIndex(0), current, 0);
    current = *(*it++);
    connectOutputPinWithNode(created, created->getOutputPinByIndex(0), current, 0);

    componentList.put(created);
    inputComponentList.put(created);
}

template<>
void Circuit::create<WIRE>(Queue<size_t>& nodeNumbers) {
    WIRE* created = new WIRE();
    created->setActiveQueue(&activeList);

    Queue<size_t>::iterator it = nodeNumbers.begin();
    size_t current = *(*it++);
    connectInputPinWithNode(created->getInputPinByIndex(0), current, 0);
    current = *(*it++);
    connectOutputPinWithNode(created, created->getOutputPinByIndex(0), current, 0);

    componentList.put(created);
    inputComponentList.put(created);
}

template<>
void Circuit::create<Source>(Queue<size_t>& nodeNumbers) {
    Source* created = new Source();
    created->setActiveQueue(&activeList);

    Queue<size_t>::iterator it = nodeNumbers.begin();
    size_t current = *(*it++);
    connectOutputPinWithNode(created, created->getOutputPinByIndex(0), current, 0);

    componentList.put(created);
    sourceList.put(created);
}

template<>
void Circuit::create<Lamp>(Queue<size_t>& nodeNumbers) {
    Lamp* created = new Lamp();
    created->setActiveQueue(&activeList);

    Queue<size_t>::iterator it = nodeNumbers.begin();
    size_t current = *(*it++);
    connectInputPinWithNode(created->getInputPinByIndex(0), current, 0);

    componentList.put(created);
    lampList.put(created);
    inputComponentList.put(created);
}

template<>
void Circuit::create<Switch>(Queue<size_t>& nodeNumbers) {
    Switch* created = new Switch();
    created->setActiveQueue(&activeList);

    Queue<size_t>::iterator it = nodeNumbers.begin();
    size_t current = *(*it++);
    connectInputPinWithNode(created->getInputPinByIndex(0), current, 0);
    current = *(*it++);
    connectOutputPinWithNode(created, created->getOutputPinByIndex(0), current, 0);

    componentList.put(created);
    switchList.put(created);
    inputComponentList.put(created);
}

// Belső tagfüggvények

void Circuit::reset()
{
    simulated = false;
    configured = false;

    componentList.clear();
    inputComponentList.clear();
    activeList.clear();

    sourceList.clear();
    switchList.clear();
    lampList.clear();
    nodeList.clear();

    if (inputfile.is_open())
        inputfile.close();
}

void Circuit::configure() {
    reset();

    try {
        build();
    }
    catch (FileAccessError& error) {
        printErrorMessage(*errorStream, "LOADING ERROR", error.exception_message());

        throw ConfigurationError("Unable to access schematics file during configuration...");
    }
    catch (UnsimulatedComponent& error) {
        printErrorMessage(*errorStream, "SEMANTIC ERROR", error.exception_message());

        reset();
        throw ConfigurationError("There was an unsimulated element during configuration...");
    }
    catch (SchematicsFileHasSyntaxError& error) {
        reset();
        throw ConfigurationError("Schematics file has a syntax error...");
    }
    catch (MessagedException& error) {
        printErrorMessage(*errorStream, "GENERAL EXCEPTION", error.exception_message());
        reset();

        throw ConfigurationError("There was an general error during configuration...");
    }
    catch (std::exception& error) {
        std::string message = "There was some form of non-unique error during configuration, most likely out_of_range.";
        printErrorMessage(*errorStream, "GENERAL ERROR", message);

        throw ConfigurationError("There was an unknown error during configuration...");
    }

    configured = true;
    simulated = false;
}

void Circuit::build()
{
    if (inputFilePath == "")
        throw FileAccessError("No file was given...");

    if (!inputfile.is_open()) {
        inputfile.open(inputFilePath);
        if (!inputfile.is_open()) {
            throw FileAccessError("Input file doesn't exist or can't be opened...");
        }
    }

    inputfile.seekg(std::ios_base::beg);
    LineContent line;

    while (!inputfile.eof()) {
        std::getline(inputfile, line.content);
        line.lineNumber++;

        if (!line.content.empty()) {
            line.idx = 0;
            line.type = INVALID;
            try {
                buildLine(line);
            }
            catch (CommentLine& exception) {
                continue;
            }
            catch (...) {
                throw;
            }
        }
    }
    if (line.wasSyntaxError) {
        throw SchematicsFileHasSyntaxError("File has incorrect syntax, can't be simulated...");
    }

    testForIsolatedComponent();
}

void Circuit::testForIsolatedComponent()
{
    for (Queue<Source>::iterator it = sourceList.begin(); it != sourceList.end(); it++) {
        activeList.put(*it);
    }

    while (!activeList.isEmpty()) {
        Component* current = activeList.get();
        try {
            current->executeFunction();
        }
        catch (ShortCircuit& error) {}
        current->setSimulated();
    }

    for (Queue<Component>::iterator it = componentList.begin(); it != componentList.end(); it++) {
        Component* current = *it;
        if (!current->simulated()) {
            Node* nptr = dynamic_cast<Node*>(current);
            if (nptr != nullptr) {
                throw UnsimulatedComponent("Node " + size_tToString(nptr->getID()) + " is unsimulated (isolated or self-referential)...");
            }
            else {
                std::stringstream message("Component connected to node(s): ");
                InputComponent* iptr = dynamic_cast<InputComponent*>(current);
                OutputComponent* optr = dynamic_cast<OutputComponent*>(current);
                if (iptr != nullptr) {
                    iptr->printConnectedInputNodes(message);
                    message << " ";
                }
                if (optr != nullptr) {
                    optr->printConnectedOutputNodes(message);
                    message << " ";
                }
                message << " is unsimulated (isolated or self-referential)...";
                std::string result;
                std::getline(message, result);
                throw UnsimulatedComponent(result);
            }
        }
    }

    for (Queue<InputComponent>::iterator it = inputComponentList.begin(); it != inputComponentList.end(); it++) {
        InputComponent* current = *it;
        current->resetForSimulation();
        current->resetSimulted();
    }
}


void Circuit::buildLine(LineContent& line)
{
    try {
        getLineType(line);
    }
    catch (NonExistentLineType& error) {
        printErrorMessage(*errorStream, "SYNTAX ERROR", error.exception_message());
        line.wasSyntaxError = true;
        return;
    }

    for (char c = line.content[line.idx++]; line.idx < line.content.length(); c = line.content[line.idx++]) {
        if (c == '(') {
            Queue<size_t> nodeNumbers(true);
            try {
                getNodeNumbers(line, nodeNumbers);
            }
            catch (IncorrectSyntax& error) {
                printErrorMessage(*errorStream, "SYNTAX ERROR", error.exception_message());
                line.wasSyntaxError = true;

                while (line.content[line.idx] != ')' && line.content[line.idx] != '\n') line.idx++;
                continue;
            }

            size_t count = nodeNumbers.size();
            try {
                checkNodeCount(line, count);
            }
            catch (IncorrectPinCount& error) {
                printErrorMessage(*errorStream, "SYNTAX ERROR", error.exception_message());
                line.wasSyntaxError = true;

                while (line.content[line.idx] != ')' && line.content[line.idx] != '\n') line.idx++;
                continue;
            }

            createBasedOnType(line, nodeNumbers);
        }
    }
}

void Circuit::getLineType(LineContent& line)
{
    const size_t totalTypeCount = 11;
    std::string validTypes[totalTypeCount] = {
        "SOURCE", "LAMP", "SWITCH", "AND", "OR", "NOT", "XOR", "NAND", "NOR", "XNOR", "WIRE"
    };

    std::string lineType;
    for (char c = line.content[line.idx++]; c != ':' && line.idx < line.content.length(); c = line.content[line.idx++]) {
        if (line.idx == 1 && c == '#') {
            throw CommentLine("Current line is a comment, and should be ignored...");
        }
        lineType += c;
    }

    bool valid = false;
    for (size_t i = 0; i < totalTypeCount; i++) {
        if (validTypes[i] == lineType) {
            valid = true;
            line.type = ComponentType(i + 1);
            break;
        }
    }

    if (!valid) {
        throw NonExistentLineType("Invalid component type: \"" + lineType + "\" at line " + size_tToString(line.lineNumber) + "!");
    }
}

void Circuit::getNodeNumbers(LineContent& line, Queue<size_t>& nodeNumbers)
{
    size_t read;
    char buff;
    std::stringstream stream(std::string(line.content.c_str() + line.idx));
    while (true) {
        if (!(stream >> read)) {
            throw IncorrectSyntax("Incorrect syntax at: \"(" + std::string(line.content.c_str() + line.idx) + "\"!");
        }
        nodeNumbers.put(new size_t(read));

        if (!(stream >> buff)) {
            throw IncorrectSyntax("Incorrect syntax at: \"(" + std::string(line.content.c_str() + line.idx) + "\"!");
        }

        if (buff != ',' && buff != ')') {
            throw IncorrectSyntax("Incorrect syntax at: \"(" + std::string(line.content.c_str() + line.idx) + "\"!");
        }
        else if (buff == ')') {
            while (line.content[line.idx] != ')') line.idx++;
            break;
        }
    }
}

void Circuit::checkNodeCount(LineContent& line, size_t count)
{
    switch (line.type)
    {
    case SOURCE:
        if (count != 1)
            throw IncorrectPinCount("Incorrect pin count for SOURCE type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case LAMP:
        if (count != 1)
            throw IncorrectPinCount("Incorrect pin count for LAMP type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case SWITCH:
        if (count != 2)
            throw IncorrectPinCount("Incorrect pin count for SWITCH type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_AND:
        if (count <= 2)
            throw IncorrectPinCount("Incorrect pin count for AND type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_OR:
        if (count <= 2)
            throw IncorrectPinCount("Incorrect pin count for OR type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_NOT:
        if (count != 2)
            throw IncorrectPinCount("Incorrect pin count for NOT type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_XOR:
        if (count <= 2)
            throw IncorrectPinCount("Incorrect pin count for XOR type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_NAND:
        if (count <= 2)
            throw IncorrectPinCount("Incorrect pin count for NAND type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_NOR:
        if (count <= 2)
            throw IncorrectPinCount("Incorrect pin count for NOR type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_XNOR:
        if (count <= 2)
            throw IncorrectPinCount("Incorrect pin count for XNOR type at line " + size_tToString(line.lineNumber) + "!");
        break;
    case GATE_WIRE:
        if (count != 2)
            throw IncorrectPinCount("Incorrect pin count for WIRE type line " + size_tToString(line.lineNumber) + "!");
        break;
    default:
        throw NonExistentLineType("Not found a type...");
        break;
    }
}

void Circuit::createBasedOnType(LineContent& info, Queue<size_t>& nodeNumbers)
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
    case GATE_AND:
        create<AND>(nodeNumbers);
        break;
    case GATE_OR:
        create<OR>(nodeNumbers);
        break;
    case GATE_NOT:
        create<NOT>(nodeNumbers);
        break;
    case GATE_XOR:
        create<XOR>(nodeNumbers);
        break;
    case GATE_NAND:
        create<NAND>(nodeNumbers);
        break;
    case GATE_NOR:
        create<NOR>(nodeNumbers);
        break;
    case GATE_XNOR:
        create<XNOR>(nodeNumbers);
        break;
    case GATE_WIRE:
        create<WIRE>(nodeNumbers);
        break;
    default:
        throw NonExistentLineType("Not found a type...");
        break;
    }
}

void Circuit::connectInputPinWithNode(InputPin* pin, size_t ID, size_t idx)
{
    for (Queue<Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
        Node* current = *it;
        if (current->getID() == ID) {
            current->addOutputPin(pin);
            pin->getComponent()->setInputNodeID(idx, ID);
            return;
        }
    }

    // Ha nem talált
    Node* newNode = new Node(ID);
    newNode->setActiveQueue(&activeList);
    componentList.put(newNode);
    inputComponentList.put(newNode);
    nodeList.put(newNode);

    newNode->addOutputPin(pin);
    pin->getComponent()->setInputNodeID(idx, ID);
}

void Circuit::connectOutputPinWithNode(OutputComponent* component, OutputPin* pin, size_t ID, size_t idx)
{
    for (Queue<Node>::iterator it = nodeList.begin(); it != nodeList.end(); it++) {
        Node* current = *it;
        if (current->getID() == ID) {
            pin->connectToPin(current->getInPin());
            component->setOutputNodeID(idx, ID);
            return;
        }
    }

    // Ha nem talált
    Node* newNode = new Node(ID);
    newNode->setActiveQueue(&activeList);
    componentList.put(newNode);
    inputComponentList.put(newNode);
    nodeList.put(newNode);

    pin->connectToPin(newNode->getInPin());
    component->setOutputNodeID(idx, ID);
}

void Circuit::printErrorMessage(std::ostream& os, const std::string& errorTypeName, const std::string& errorMessage)
{
    printSeparatorLine(os, '=', 50);
    os << errorTypeName << std::endl;
    printSeparatorLine(os, '*', 50);
    os << errorMessage << std::endl;
    printSeparatorLine(os, '=', 50);
}

// Publikus interfész kezdet

Circuit::Circuit() : errorStream(&std::cerr), componentList(true), configured(false), simulated(false) {}

Circuit::Circuit(const Circuit& source) : errorStream(source.errorStream), componentList(true), configured(false), simulated(false)
{
    *this = source;
}

Circuit& Circuit::operator=(const Circuit& source)
{
    if (this != &source) {
        errorStream = source.errorStream;

        reset();
        setSchematicFile(source.inputFilePath);
        configure();
    }
    return *this;
}

void Circuit::setErrorStream(std::ostream& os)
{
    errorStream = &os;
}

void Circuit::setSchematicFile(const std::string& path)
{
    std::string prev = inputFilePath;

    if (inputfile.is_open()) {
        inputfile.close();
    }

    inputFilePath = path;
    inputfile.open(inputFilePath);

    if (!inputfile.is_open() && inputFilePath != "") {
        inputFilePath = prev;
        inputfile.open(prev);

        std::string error_msg = "There is no file with name: " + path;
        printErrorMessage(*errorStream, "LOADING ERROR", error_msg);
    }
    else {
        configured = false;
        simulated = false;
    }
}

const std::string& Circuit::getSourceFileName() const
{
    return inputFilePath;
}

void Circuit::simulate(std::ostream& os)
{
    if (simulated) {
        os << *this;
        return;
    }

    if (!configured) {
        configure();
    }

    if (configured) {
        for (Queue<InputComponent>::iterator it = inputComponentList.begin(); it != inputComponentList.end(); it++) {
            InputComponent* current = *it;
            current->resetForSimulation();
        }

        for (Queue<Source>::iterator it = sourceList.begin(); it != sourceList.end(); it++) {
            activeList.put(*it);
        }

        bool wasShortCircuit = false;

        while (!activeList.isEmpty()) {
            Component* current = activeList.get();
            try {
                current->executeFunction();
            }
            catch (ShortCircuit& err) {
                wasShortCircuit = true;

                std::string error_message;
                error_message += err.exception_message();
                Node* ptr = dynamic_cast<Node*>(err.getResimulated());
                if (ptr != nullptr)
                    error_message += " at node " + size_tToString(ptr->getID()) + "!";

                printErrorMessage(os, "SHORTCIRCUIT!", error_message);
            }
        }

        if (!wasShortCircuit) {
            os << *this;
            simulated = true;
        }
    }
}

void Circuit::setSource(size_t connectedNode, Signal newSignal)
{
    if (!configured) {
        configure();
    }
    for (Queue<Source>::iterator it = sourceList.begin(); it != sourceList.end(); it++) {
        Source* current = *it;
        if (current->isConnectedToNodeOnOutput(connectedNode)) {
            current->setOutput(newSignal);
            simulated = false;
            return;
        }
    }
    throw MatchingComponentNotFound(("No source connected to node: " + size_tToString(connectedNode) + "!"));
}

void Circuit::setSwitch(size_t connectedNode1, size_t connectedNode2, bool closed)
{
    if (!configured) {
        configure();
    }
    for (Queue<Switch>::iterator it = switchList.begin(); it != switchList.end(); it++) {
        Switch* current = *it;
        if (current->isConnectedToNodes(connectedNode1, connectedNode2)) {
            current->setState(closed);
            simulated = false;
            return;
        }
    }
    throw MatchingComponentNotFound("No switch connected to nodes: " + size_tToString(connectedNode1) + " and " + size_tToString(connectedNode2) + "!");
}

Signal Circuit::getSourceSignal(size_t connectedNode)
{
    if (!configured) {
        configure();
    }
    for (Queue<Source>::iterator it = sourceList.begin(); it != sourceList.end(); it++) {
        Source* current = *it;
        if (current->isConnectedToNodeOnOutput(connectedNode)) {
            return current->getOutput();
        }
    }
    throw MatchingComponentNotFound("No source connected to node: " + size_tToString(connectedNode) + "!");
}

bool Circuit::isSwitchClosed(size_t connectedNode1, size_t connectedNode2)
{
    if (!configured) {
        configure();
    }
    for (Queue<Switch>::iterator it = switchList.begin(); it != switchList.end(); it++) {
        Switch* current = *it;
        if (current->isConnectedToNodes(connectedNode1, connectedNode2)) {
            return current->getState();
        }
    }
    throw MatchingComponentNotFound("No switch connected to nodes: " + size_tToString(connectedNode1) + " and " + size_tToString(connectedNode2) + "!");
}

Signal Circuit::getLampSignal(size_t connectedNode)
{
    if (!configured) {
        configure();
    }
    for (Queue<Lamp>::iterator it = lampList.begin(); it != lampList.end(); it++) {
        Lamp* current = *it;
        if (current->isConnectedToNodeOnInput(connectedNode)) {
            return current->getState();
        }
    }
    throw MatchingComponentNotFound("No lamp connected to node: " + size_tToString(connectedNode) + "!");
}

void Circuit::printAllSourceStates(std::ostream& os) const
{
    printQueue(sourceList, os);
}

void Circuit::printAllSwitchStates(std::ostream& os) const
{
    printQueue(switchList, os);
}

void Circuit::printAllLampStates(std::ostream& os) const
{
    printQueue(lampList, os);
}

Circuit::~Circuit()
{
    reset();
}

// Publikus interface vége


// Globális függvények

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

std::string size_tToString(size_t converted) {
    if (converted == 0) {
        return std::string("0");
    }

    std::string result;
    while (converted > 0) {
        size_t digit = converted % 10;
        converted /= 10;
        result = (static_cast<char>('0' + digit)) + result;
    }
    return result;
}