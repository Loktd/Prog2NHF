
#include "Circuit.h"

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
        *errorStream << "SYNTAX ERROR";
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
    inputfile.seekg(std::ios_base::beg);
    ContentInfo info;
    while (!inputfile.eof()) {
        std::getline(inputfile, info.line);
        if (!info.line.empty()) {
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
    checkNodeCount(info, nodeNumbers);

}

void Circuit::getNodeNumbers(ContentInfo& info, Queue<int>& nodeNumbers)
{
    int read;
    std::stringstream s(info.line);
    bool go = true;
    while (go) {
        if (!(s >> read)) {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + info.line + "\" !");
        }
        nodeNumbers.put(new int(read));
        char c;
        if (!(s >> c)) {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + info.line + "\" !");
        }
        if (c != ',' && c != ')') {
            nodeNumbers.clear();
            throw std::string("Incorrect syntax at: \"(" + info.line + "\" !");
        }
        else if (c == ')') {
            while (info.line[info.idx] != ')')
                info.idx++;
        }
    }
}

void Circuit::checkNodeCount(ContentInfo& info, Queue<int>& nodeNumbers)
{
    Queue<int> copyList(nodeNumbers);
    size_t count = 0;
    while (!copyList.isEmpty()) {
        count++;
        copyList.get();
    }
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
    case AND:
        if (count <= 2)
            throw std::string("Incorrect pin count for AND type at line " + std::to_string(info.lineCount));
        break;
    case OR:
        if (count <= 2)
            throw std::string("Incorrect pin count for OR type at line " + std::to_string(info.lineCount));
        break;
    case NOT:
        if (count != 2)
            throw std::string("Incorrect pin count for NOT type at line " + std::to_string(info.lineCount));
        break;
    case XOR:
        if (count <= 2)
            throw std::string("Incorrect pin count for XOR type at line " + std::to_string(info.lineCount));
        break;
    case NAND:
        if (count <= 2)
            throw std::string("Incorrect pin count for NAND type at line " + std::to_string(info.lineCount));
        break;
    case NOR:
        if (count <= 2)
            throw std::string("Incorrect pin count for NOR type at line " + std::to_string(info.lineCount));
        break;
    case XNOR:
        if (count <= 2)
            throw std::string("Incorrect pin count for XNOR type at line " + std::to_string(info.lineCount));
        break;
    default:
        throw std::string("No found type error...");
        break;
    }
}

Circuit::Circuit() : simulated(false), configured(false), componentList(true) {}

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