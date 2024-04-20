class Circuit
!!!128002.cpp!!!	reset() : void
    componentList.clear();
    sourceList.clear();
    switchList.clear();
    lampList.clear();
    activeList.clear();

    if (inputfile.is_open())
        inputfile.close();
!!!128130.cpp!!!	configure() : void
    try {
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
!!!128258.cpp!!!	build() : void
    if (inputFileName == "")
        return;
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
!!!128514.cpp!!!	buildLine(inout info : Circuit::ContentInfo) : void
    checkLineType(info);
    char c = info.line[info.idx++];
    while (info.idx < info.line.length()) {
        if (c == '(') {
            buildComponent(info);
        }
        c = info.line[info.idx++];
    }
!!!128642.cpp!!!	checkLineType(inout info : Circuit::ContentInfo) : void
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
!!!128770.cpp!!!	buildComponent(inout info : Circuit::ContentInfo) : void
    Queue<int> nodeNumbers(true);
    getNodeNumbers(info, nodeNumbers);

    size_t count = nodeNumbers.size();
    checkNodeCount(info, count);

    createBasedOnType(info, count, nodeNumbers);
!!!128898.cpp!!!	getNodeNumbers(inout info : Circuit::ContentInfo, inout nodeNumbers : Queue<int>) : void
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
!!!129026.cpp!!!	checkNodeCount(inout info : Circuit::ContentInfo, in count : size_t) : void
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
!!!129154.cpp!!!	createBasedOnType(inout info : Circuit::ContentInfo, in count : size_t, inout nodeNumbers : Queue<int>) : void
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
!!!129282.cpp!!!	create(in count : size_t, inout nodeNumbers : Queue<int>) : void
  T* created = new T(count - 1);
  ((Component*)created)->setActiveQueue(&activeList);
  Queue<int> copy(nodeNumbers);
  for (size_t i = 0; i < count - 1; i++) {
    connectInPinWithNode(((InPin_Component*)created)->getInPinsBaseAdress() + i, *(copy.get()), i);
  }
  connectOutPinWithNode(created, ((OutPin_Component*)created)->getOutPinBaseAdress(), *(copy.get()), 0);
  componentList.put(created);
  incomponents.put(created);
!!!129538.cpp!!!	connectInPinWithNode(inout pin : InPin, in id : size_t, in idx : size_t) : void
    Queue<Node> copy(nodeList);
    bool found = false;
    while (!copy.isEmpty()) {
        Node* current = copy.get();
        if (current->getID() == id) {
            current->addOutPin(pin);
            pin->getComponent()->setInNodeID(idx, id);
            found = true;
            break;
        }
    }
    if (!found) {
        Node* newNode = new Node(id);
        newNode->addOutPin(pin);
        pin->getComponent()->setInNodeID(idx, id);
        newNode->setActiveQueue(&activeList);
        nodeList.put(newNode);
        incomponents.put(newNode);
    }
!!!129666.cpp!!!	connectOutPinWithNode(inout component : OutPin_Component, inout pin : OutPin, in id : size_t, in idx : size_t) : void
    Queue<Node> copy(nodeList);
    bool found = false;
    while (!copy.isEmpty()) {
        Node* current = copy.get();
        if (current->getID() == id) {
            pin->connectToPin(current->getInPin());
            component->setOutNodeID(idx, id);
            found = true;
            break;
        }
    }
    if (!found) {
        Node* newNode = new Node(id);
        pin->connectToPin(newNode->getInPin());
        component->setOutNodeID(idx, id);
        newNode->setActiveQueue(&activeList);
        nodeList.put(newNode);
        incomponents.put(newNode);
    }
!!!129922.cpp!!!	Circuit(in source : Circuit)
    *this = source;
!!!130050.cpp!!!	operator =(in source : Circuit) : Circuit
    if (this != &source) {
        simulated = false;
        configured = false;
        reset();
        setSourceFile(source.inputFileName);
        configure();
    }
    return *this;
!!!130178.cpp!!!	setErrorStream(inout os : std::ostream) : void
    errorStream = os;
!!!130306.cpp!!!	setSourceFile(in fileName : std::string) : void
    if (inputfile.is_open()) {
        inputfile.close();
    }

    inputFileName = fileName;
    inputfile.open(inputFileName);

    if (!inputfile.is_open() && inputFileName != "") {
        *errorStream << "There is no file with name: " << fileName << std::endl;
    }
!!!130434.cpp!!!	getSourceFileName() : std::string
    return inputFileName;
!!!130562.cpp!!!	simulate(inout os : std::ostream) : void
    if (!configured)
        configure();

    for (size_t i = 0; i < incomponents.size(); i++) {
        InPin_Component* current = incomponents.get();
        current->resetForSimulation();
        incomponents.put(current);
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
!!!130690.cpp!!!	setSource(in connectedNode : size_t, in newSignal : Signal) : void
    if (!configured) {
        configure();
    }
    Queue<Source> copy(sourceList);
    while (!copy.isEmpty()) {
        Source* current = copy.get();
        if (current->connectedToNodeOut(connectedNode)) {
            current->setOutput(newSignal);
            return;
        }
    }
    *errorStream << "No source connected to node: " << connectedNode << " !" << std::endl;
!!!131458.cpp!!!	printAllSourceStates(inout os : std::ostream) : void
    Queue<Source> copyList(sourceList);
    while (!copyList.isEmpty()) {
        Source* current = copyList.get();
        os << *current << std::endl;
    }
!!!131586.cpp!!!	setSwitch(in connectedNode1 : size_t, in connectedNode2 : size_t, in closed : bool) : void
    Queue<Switch> copy(switchList);
    while (!copy.isEmpty()) {
        Switch* current = copy.get();
        if (current->connectedToNodes(connectedNode1, connectedNode2)) {
            current->setState(closed);
            return;
        }
    }
    *errorStream << "No switch connected to nodes: " << connectedNode1 << " and " << connectedNode2 << " !" << std::endl;
!!!132354.cpp!!!	printAllSwitchStates(inout os : std::ostream) : void
    Queue<Switch> copyList(switchList);
    while (!copyList.isEmpty()) {
        Switch* current = copyList.get();
        os << *current << std::endl;
    }
!!!132866.cpp!!!	printAllLampStates(inout os : std::ostream) : void
    Queue<Lamp> copyList(lampList);
    while (!copyList.isEmpty()) {
        Lamp* current = copyList.get();
        os << *current << std::endl;
    }
!!!132994.cpp!!!	~Circuit()
    reset();
