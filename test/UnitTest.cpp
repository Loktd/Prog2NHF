#include <iostream>

#include "../src/Circuit.h"
#include "Menu.h"

#include "memtrace.h"
#include "gtest_lite.h"

int main() {
    TEST(SANITY, ForrasAllitas) {
        Circuit circuit;
        std::stringstream error_stream;
        circuit.setErrorStream(&error_stream);

        EXPECT_STREQ("", circuit.getSourceFileName().c_str());

        circuit.setSchematicFile("Gates.dat");
        EXPECT_STREQ("Gates.dat", circuit.getSourceFileName().c_str());

        circuit.setSchematicFile("Peripherals.dat");
        EXPECT_STREQ("Peripherals.dat", circuit.getSourceFileName().c_str());

        circuit.setSchematicFile("IDontExist.dat");
        EXPECT_STREQ("Peripherals.dat", circuit.getSourceFileName().c_str());
        EXPECT_STRNE("", error_stream.str().c_str());
    }END;

    TEST(SANITY, ErrorAllitas) {
        Circuit circuit;

        std::stringstream error;
        circuit.setErrorStream(&error);
        std::stringstream output;

        circuit.simulate(output);
        EXPECT_STREQ("", output.str().c_str());

        std::string expectedError[5] = {
            "==================================================",
            "LOADING ERROR",
            "**************************************************",
            "No file was given...",
            "=================================================="
        };
        std::string line;
        for (size_t i = 0; i < 5; i++) {
            std::getline(error, line);
            EXPECT_STREQ(expectedError[i].c_str(), line.c_str());
        }


    }END;

    TEST(SANITY, Masolas) {
        Circuit circuit1;
        std::stringstream output1;
        std::stringstream output2;

        circuit1.setSchematicFile("Gates.dat");

        Circuit circuit2(circuit1);
        EXPECT_EQ(circuit1.getSourceFileName(), circuit2.getSourceFileName());

        circuit1.simulate(output1);
        circuit2.simulate(output2);
        EXPECT_STREQ(output1.str().c_str(), output2.str().c_str());

        output2.str("");
        circuit2.setSchematicFile("Peripherals.dat");
        circuit2.simulate(output2);
        EXPECT_STRNE(output1.str().c_str(), output2.str().c_str());

        output1.str("");
        circuit1 = circuit2;
        circuit1.simulate(output1);
        EXPECT_STREQ(output2.str().c_str(), output1.str().c_str());
    }END;

    TEST(COMPONENT_CHECK, Kapuk) {
        Circuit circuit;
        circuit.setSchematicFile("Gates.dat");

        std::stringstream error;
        circuit.setErrorStream(&error);

        std::stringstream output;

        bool SOURCE_1_SIGNALS[4] = { false, true, false, true };
        bool SOURCE_2_SIGNALS[4] = { false, false, true, true };

        bool GATE_AND_EXPECTED_VALUES[4] = { false, false, false, true };
        bool GATE_OR_EXPECTED_VALUES[4] = { false, true, true, true };
        bool GATE_XOR_EXPECTED_VALUES[4] = { false, true, true, false };
        bool GATE_NAND_EXPECTED_VALUES[4] = { true, true, true, false };
        bool GATE_NOR_EXPECTED_VALUES[4] = { true, false, false, false };
        bool GATE_XNOR_EXPECTED_VALUES[4] = { true, false, false, true };
        bool GATE_NOT_EXPECTED_VALUES[4] = { true, false, true, false };

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(1, Signal(SOURCE_1_SIGNALS[i]));
            circuit.setSource(2, Signal(SOURCE_2_SIGNALS[i]));
            circuit.simulate(output);

            EXPECT_EQ(GATE_AND_EXPECTED_VALUES[i], circuit.getLampSignal(3).getValue());
            EXPECT_EQ(GATE_OR_EXPECTED_VALUES[i], circuit.getLampSignal(4).getValue());
            EXPECT_EQ(GATE_XOR_EXPECTED_VALUES[i], circuit.getLampSignal(5).getValue());
            EXPECT_EQ(GATE_NAND_EXPECTED_VALUES[i], circuit.getLampSignal(6).getValue());
            EXPECT_EQ(GATE_NOR_EXPECTED_VALUES[i], circuit.getLampSignal(7).getValue());
            EXPECT_EQ(GATE_XNOR_EXPECTED_VALUES[i], circuit.getLampSignal(8).getValue());
            EXPECT_EQ(GATE_NOT_EXPECTED_VALUES[i], circuit.getLampSignal(9).getValue());
        }
    }END;

    TEST(COMPONENT_CHECK, Periferiak) {
        Circuit circuit;
        std::stringstream output;
        circuit.setSchematicFile("Peripherals.dat");

        bool SOURCE_1_SIGNALS[] = { true, true, true, false };
        bool SOURCE_4_SIGNALS[] = { true, true, true, true };

        bool SWITCH_1_2_STATES[] = { false, false, true, true };
        bool SWITCH_1_3_STATES[] = { false, true, false, true };
        bool SWITCH_4_5_STATES[] = { false, false, true, true };
        bool SWITCH_4_6_STATES[] = { false, true, false, true };

        bool LAMP_2_EXPECTED_VALUES[] = { false, false, true, false };
        bool LAMP_3_EXPECTED_VALUES[] = { false, true, false, false };
        bool LAMP_7_EXPECTED_VALUES[] = { false, false, false, true };

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(1, Signal(SOURCE_1_SIGNALS[i]));
            circuit.setSource(4, Signal(SOURCE_4_SIGNALS[i]));

            circuit.setSwitch(1, 2, SWITCH_1_2_STATES[i]);
            circuit.setSwitch(1, 3, SWITCH_1_3_STATES[i]);
            circuit.setSwitch(4, 5, SWITCH_4_5_STATES[i]);
            circuit.setSwitch(4, 6, SWITCH_4_6_STATES[i]);

            circuit.simulate(output);

            EXPECT_EQ(SWITCH_1_2_STATES[i], circuit.isSwitchClosed(1, 2));
            EXPECT_EQ(SWITCH_1_3_STATES[i], circuit.isSwitchClosed(1, 3));
            EXPECT_EQ(SWITCH_4_5_STATES[i], circuit.isSwitchClosed(4, 5));
            EXPECT_EQ(SWITCH_4_6_STATES[i], circuit.isSwitchClosed(4, 6));

            EXPECT_EQ(LAMP_2_EXPECTED_VALUES[i], circuit.getLampSignal(2).getValue());
            EXPECT_EQ(LAMP_3_EXPECTED_VALUES[i], circuit.getLampSignal(3).getValue());
            EXPECT_EQ(LAMP_7_EXPECTED_VALUES[i], circuit.getLampSignal(7).getValue());
        }
    }END;

    TEST(COMPONENT_CHECK, Periferia_Kivetelek) {
        Circuit circuit;
        std::stringstream output;
        circuit.setSchematicFile("Peripherals.dat");

        EXPECT_THROW(circuit.setSource(0, Signal(true)), MatchingComponentNotFound);
        EXPECT_THROW(circuit.setSwitch(0, 0, true), MatchingComponentNotFound);
        EXPECT_THROW(circuit.getSourceSignal(0), MatchingComponentNotFound);
        EXPECT_THROW(circuit.isSwitchClosed(0, 0), MatchingComponentNotFound);
        EXPECT_THROW(circuit.getLampSignal(0), MatchingComponentNotFound);
    }END;

    TEST(ERRORS, Helytelen_Szintaxis) {
        Circuit circuit;
        std::stringstream output;
        std::stringstream error;
        circuit.setErrorStream(&error);

        std::string FILENAMES[4] = {
            "BadSyntax1.dat",
            "BadSyntax2.dat",
            "BadSyntax3.dat",
            "BadSyntax4.dat"
        };
        std::string EXPECTED[4] = {
            "Invalid component type: \"SOUrC\" at line 1!",
            "Incorrect syntax at: \"(1, 2, 3\"!",
            "Incorrect pin count for NOT type at line 9!",
            "Incorrect syntax at: \"(3svs) (4) (5) (6) (7) (8) (9)\"!",
        };

        for (size_t i = 0; i < 4; i++) {
            error.str("");
            output.str("");
            circuit.setSchematicFile(FILENAMES[i]);
            circuit.simulate(output);

            std::string errorMessage;
            for (size_t i = 0; i < 4; i++)
                std::getline(error, errorMessage);

            EXPECT_STREQ(EXPECTED[i].c_str(), errorMessage.c_str());
        }
    }END;

    TEST(ERRORS, Onhivatkozo_Elem) {
        Circuit circuit;
        circuit.setSchematicFile("SelfRef.dat");
        std::stringstream output;
        std::stringstream error;
        circuit.setErrorStream(&error);
        circuit.simulate(output);

        std::string EXPECTED = "Node 2 is unsimulated (isolated or self-referential)...";

        std::string line;
        for (size_t i = 0; i < 4; i++)
            std::getline(error, line);
        EXPECT_STREQ(EXPECTED.c_str(), line.c_str());
    }END;

    TEST(ERRORS, Elszigetelt_Elem) {
        Circuit circuit;
        circuit.setSchematicFile("Isolated.dat");
        std::stringstream output;
        std::stringstream error;
        circuit.setErrorStream(&error);
        circuit.simulate(output);

        std::string EXPECTED = "Node 8 is unsimulated (isolated or self-referential)...";
        std::string line;
        for (size_t i = 0; i < 4; i++)
            std::getline(error, line);
        EXPECT_STREQ(EXPECTED.c_str(), line.c_str());
    }END;

    TEST(ERRORS, RovidZar) {
        Circuit circuit;
        circuit.setSchematicFile("ShortCircuit.dat");
        std::stringstream output;
        std::stringstream error;
        circuit.setErrorStream(&error);
        circuit.simulate(output);

        std::string EXPECTED = "ERROR: Shortcircuit from looping back at node 1!";
        std::string line;
        for (size_t i = 0; i < 4; i++)
            std::getline(error, line);
        EXPECT_STREQ(EXPECTED.c_str(), line.c_str());
    }END;

    TEST(COMLEX_CIRCUITS, Ot_Bemenet) {
        Circuit circuit;
        circuit.setSchematicFile("FiveToOne.dat");
        std::stringstream error;
        circuit.setErrorStream(&error);
        std::stringstream output;

        bool EXPECTED_LAMP_STATE[5] = { true, true, true, true, false };

        for (size_t i = 0; i < 5; i++) {
            circuit.setSource(i + 1, Signal(true));
            circuit.simulate(output);
            EXPECT_EQ(EXPECTED_LAMP_STATE[i], circuit.getLampSignal(6).getValue());
        }
    }END;

    TEST(COMPLEX_CIRCUITS, Comparator) {
        Circuit circuit;
        circuit.setSchematicFile("Comparator.dat");
        std::stringstream error;
        circuit.setErrorStream(&error);
        std::stringstream output;

        // 13-al vetjük össze az összes többi értéket
        circuit.setSource(1, Signal(true));
        circuit.setSource(2, Signal(false));
        circuit.setSource(3, Signal(true));
        circuit.setSource(4, Signal(true));

        for (size_t i = 0; i < 16; i++) {
            circuit.setSource(5, Signal(i & 1));
            circuit.setSource(6, Signal(i & 2));
            circuit.setSource(7, Signal(i & 4));
            circuit.setSource(8, Signal(i & 8));

            circuit.simulate(output);

            if (i != 13) {
                EXPECT_EQ(false, circuit.getLampSignal(13).getValue());
            }
            else {
                EXPECT_EQ(true, circuit.getLampSignal(13).getValue());
            }
        }
    }END;

    TEST(COMPLEX_CIRCUITS, Multiplexer) {
        Circuit circuit;
        circuit.setSchematicFile("Multiplexer.dat");
        std::stringstream error;
        circuit.setErrorStream(&error);
        std::stringstream output;

        bool GIVEN_SIGNALS[4] = { true, false, false, true };

        for (size_t i = 0; i < 4; i++)
            circuit.setSource(i + 1, Signal(GIVEN_SIGNALS[i]));

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(5, Signal(i & 1));
            circuit.setSource(6, Signal(i & 2));

            circuit.simulate(output);

            EXPECT_EQ(GIVEN_SIGNALS[i], circuit.getLampSignal(15).getValue());
        }
    }END;

    TEST(COMPLEX_CIRCUITS, Decoder) {
        Circuit circuit;
        circuit.setSchematicFile("Decoder.dat");
        std::stringstream error;
        circuit.setErrorStream(&error);
        std::stringstream output;

        bool SOURCE_1_SIGNALS[4] = { false, true, false, true };
        bool SOURCE_2_SIGNALS[4] = { false, false, true, true };

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(1, Signal(SOURCE_1_SIGNALS[i]));
            circuit.setSource(2, Signal(SOURCE_2_SIGNALS[i]));

            circuit.simulate(output);
            for (size_t j = 0; j < 4; j++) {
                if (i == j)
                    EXPECT_EQ(true, circuit.getLampSignal(3 + j).getValue());
                else
                    EXPECT_EQ(false, circuit.getLampSignal(3 + j).getValue());
            }
        }
    }END;

#ifndef CPORTA
    App application;
    while (application.keepRunning()) {
        application.display();
        application.handleInput();
    }
#endif
}