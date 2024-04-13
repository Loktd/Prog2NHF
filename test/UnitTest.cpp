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
    std::string inputFile1Name = "TestMaterial_InputTest1.txt";
    std::string outputFileName = "TestMaterial_OutputTest.txt";
    std::string errorFileName = "Errors.txt";
    std::string nonExistentFileName = "IDONTEXIST.txt";
    std::string starSeperator = "**************************************************";
    std::string dashSeperator = "--------------------------------------------------";

    std::ofstream errorFile;
    errorFile.open(errorFileName);
    Circuit::setErrorStream(&errorFile);

    TEST(CIRCUIT, KonstruktorDestruktorUres) {
        Circuit circuit;
        EXPECT_EQ("", circuit.getSourceFileName());
    } END;

    TEST(CIRCUIT, MasoloKonstruktorUres) {
        Circuit circuit;
        Circuit circuit2(circuit);
    } END;

    TEST(CIRCUIT, EgyenlosegOperatorUres) {
        Circuit circuit;
        Circuit circuit2;
        circuit2 = circuit;
    } END;

    TEST(CIRCUIT, BementiFileBeallitas) {
        Circuit circuit;

        circuit.setSourceFile(inputFile1Name);
        EXPECT_EQ(inputFile1Name, circuit.getSourceFileName());

        clearFileContent(errorFileName);
        std::ifstream errorFileIn;
        errorFileIn.open(errorFileName);
        std::string line;

        circuit.setSourceFile(nonExistentFileName);
        std::getline(errorFileIn, line);
        EXPECT_EQ("There is no file with name: " + nonExistentFileName, line);

        errorFileIn.close();
    } END;

    TEST(CIRCUIT, KiirasUres) {
        Circuit circuit;

        clearFileContent(outputFileName);

        std::ofstream write;
        write.open(outputFileName, std::ostream::app);
        write << circuit;
        write.close();

        std::ifstream read;
        read.open(outputFileName);
        std::string line;

        std::getline(read, line);
        EXPECT_EQ(starSeperator, line);
        std::getline(read, line);
        EXPECT_EQ(inputFile1Name, line);
        std::getline(read, line);
        EXPECT_EQ(starSeperator, line);
        std::getline(read, line);
        EXPECT_EQ(dashSeperator, line);
        std::getline(read, line);
        EXPECT_EQ(dashSeperator, line);
        std::getline(read, line);
        EXPECT_EQ(starSeperator, line.c_str());
    } END;

    errorFile.close();
}