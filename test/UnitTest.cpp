#include <iostream>

#include "gtest_lite.h"
#include "memtrace.h"

#include "../src/Circuit.h"
#include "../src/Pin.h"
#include "../src/Component.h"
#include "../src/Source.h"
#include "../src/Lamp.h"
#include "../src/Node.h"
#include "../src/Switch.h"
#include "../src/Gate.h"

#include "TestHelpFunctions.h"

int main() {
    std::string inputFile1Name = "C:\\Users\\palin\\VSCodeProjects\\Egyetem\\2.Felev\\Prog2NHF\\test\\TestMaterial_InputTest1.txt";
    std::string outputFileName = "TestMaterial_OutputTest.txt";
    std::string errorFileName = "Errors.txt";
    std::string nonExistentFileName = "IDONTEXIST.txt";
    std::string starSeperator = "**************************************************";
    std::string dashSeperator = "--------------------------------------------------";

    TEST(CIRCUIT, KonfigSikeres) {
        std::ofstream write;
        write.open(outputFileName, std::ostream::app);
        clearFileContent(outputFileName);

        Circuit circuit;
        circuit.setSourceFile(inputFile1Name);

        circuit.setSource(1, Signal(true));
        circuit.simulate(write);

        circuit.setSource(2, Signal(true));
        circuit.simulate(write);

        circuit.setSwitch(1, 5, true);
        circuit.setSource(3, Signal(true));
        circuit.simulate(write);
        
        write.close();
    } END;
}