#include <iostream>

#ifdef CPORTA
#include "gtest_lite.h"
#endif

#include "memtrace.h"

#include "../src/Circuit.h"
#include "../src/Pin.h"
#include "../src/Component.h"
#include "../src/Peripherals.h"
#include "../src/Gate.h"

#include "Menu.h"

int main() {
#ifdef CPORTA
    std::string inputFile1Name = "C:\\Users\\palin\\VSCodeProjects\\Egyetem\\2.Felev\\Prog2NHF\\test\\TestMaterial_InputTest1.txt";
    std::string outputFileName = "TestMaterial_OutputTest.txt";
    std::string errorFileName = "Errors.txt";
    std::string nonExistentFileName = "IDONTEXIST.txt";
    std::string starSeperator = "**************************************************";
    std::string dashSeperator = "--------------------------------------------------";

    TEST(CIRCUIT, KonfigSikeres) {
        std::ofstream write;
        write.open(outputFileName, std::ostream::app);

        Circuit circuit;
        circuit.setSourceFile(inputFile1Name);

        circuit.simulate(write);

        circuit.setSource(1, Signal(true));
        circuit.setSource(5, Signal(true));
        circuit.simulate(write);

        circuit.setSource(2, Signal(true));
        circuit.setSource(6, Signal(true));
        circuit.simulate(write);

        circuit.simulate(write);

        write.close();
    } END;
#else
    App application;
    while (application.keepRunning()) {
        application.display();
        application.handleInput();
    }
#endif
}