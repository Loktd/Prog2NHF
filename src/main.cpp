#include <iostream>

#include "Circuit.h"
#include "Menu.h"

#include "../test/memtrace.h"
#ifdef CPORTA
#include "../test/gtest_lite.h"
#endif

#ifdef CPORTA
// Segédfüggvény, csak az error message-ek kihámozására kell
void ERROR_EXPECT_CHECK_STR(std::string& expected_error_message, std::istream& error_stream, size_t line_number) {
    std::string error_message;
    for (size_t i = 0; i < line_number; i++)
        std::getline(error_stream, error_message);

    EXPECT_STREQ(expected_error_message.c_str(), error_message.c_str());
    std::getline(error_stream, error_message);
}
#endif

int main() {
#ifdef CPORTA
    TEST(SANITY, KonfigAllitas) {
        Circuit circuit;
        std::stringstream error_stream;
        std::stringstream output;

        circuit.setErrorStream(error_stream);

        EXPECT_STREQ("", circuit.getSourceFileName().c_str());

        circuit.setSchematicFile("Gates.dat");
        EXPECT_STREQ("Gates.dat", circuit.getSourceFileName().c_str());

        circuit.setSchematicFile("Peripherals.dat");
        EXPECT_STREQ("Peripherals.dat", circuit.getSourceFileName().c_str());

        circuit.setSchematicFile("I_DONT_EXIST.dat");
        EXPECT_STREQ("", circuit.getSourceFileName().c_str());
        EXPECT_STRNE("", error_stream.str().c_str());
    }END;

    TEST(SANITY, Masolas) {
        Circuit circuit1;
        circuit1.setSchematicFile("Gates.dat");

        Circuit circuit2(circuit1);
        EXPECT_EQ(circuit1.getSourceFileName(), circuit2.getSourceFileName());

        circuit2.setSchematicFile("Peripherals.dat");
        EXPECT_NE(circuit1.getSourceFileName(), circuit2.getSourceFileName());

        circuit1 = circuit2;
        EXPECT_EQ(circuit1.getSourceFileName(), circuit2.getSourceFileName());
    }END;

    TEST(SANITY, ErrorAllitas) {
        Circuit circuit;
        std::stringstream error;
        std::stringstream output;

        circuit.setErrorStream(error);

        EXPECT_THROW(circuit.simulate(output), ConfigurationError);
        EXPECT_STREQ("", output.str().c_str());
        EXPECT_STRNE("", error.str().c_str());
    }END;

    TEST(COMPONENT_CHECK, Kapuk) {
        Circuit circuit;
        circuit.setSchematicFile("Gates.dat");

        std::stringstream error;
        circuit.setErrorStream(error);

        std::stringstream output;

        Signal SOURCE_1_SIGNALS[4] = { false, true, false, true };
        Signal SOURCE_2_SIGNALS[4] = { false, false, true, true };

        Signal GATE_AND_EXPECTED_VALUES[4] = { false, false, false, true };
        Signal GATE_OR_EXPECTED_VALUES[4] = { false, true, true, true };
        Signal GATE_XOR_EXPECTED_VALUES[4] = { false, true, true, false };
        Signal GATE_NAND_EXPECTED_VALUES[4] = { true, true, true, false };
        Signal GATE_NOR_EXPECTED_VALUES[4] = { true, false, false, false };
        Signal GATE_XNOR_EXPECTED_VALUES[4] = { true, false, false, true };
        Signal GATE_NOT_EXPECTED_VALUES[4] = { true, false, true, false };
        Signal GATE_WIRE_EXPECTED_VALUES[4] = { false, false, true, true };

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(1, SOURCE_1_SIGNALS[i]);
            circuit.setSource(2, SOURCE_2_SIGNALS[i]);
            circuit.simulate(output);

            EXPECT_EQ(GATE_AND_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(3).getValue());
            EXPECT_EQ(GATE_OR_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(4).getValue());
            EXPECT_EQ(GATE_XOR_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(5).getValue());
            EXPECT_EQ(GATE_NAND_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(6).getValue());
            EXPECT_EQ(GATE_NOR_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(7).getValue());
            EXPECT_EQ(GATE_XNOR_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(8).getValue());
            EXPECT_EQ(GATE_NOT_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(9).getValue());
            EXPECT_EQ(GATE_WIRE_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(10).getValue());
        }
    }END;

    TEST(COMPONENT_CHECK, Periferiak) {
        Circuit circuit;
        std::stringstream output;

        circuit.setSchematicFile("Peripherals.dat");

        Signal SOURCE_1_SIGNALS[] = { false, true, false, true };
        Signal SOURCE_4_SIGNALS[] = { true, true, true, true };

        bool SWITCH_1_2_STATES[] = { false, false, true, true };
        bool SWITCH_2_3_STATES[] = { false, true, false, true };
        bool SWITCH_4_5_STATES[] = { false, false, true, true };
        bool SWITCH_4_6_STATES[] = { false, true, false, true };

        Signal LAMP_3_EXPECTED_VALUES[] = { false, false, false, true };
        Signal LAMP_7_EXPECTED_VALUES[] = { false, false, false, true };

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(1, SOURCE_1_SIGNALS[i]);
            circuit.setSource(4, SOURCE_4_SIGNALS[i]);

            circuit.setSwitch(1, 2, SWITCH_1_2_STATES[i]);
            circuit.setSwitch(2, 3, SWITCH_2_3_STATES[i]);
            circuit.setSwitch(4, 5, SWITCH_4_5_STATES[i]);
            circuit.setSwitch(4, 6, SWITCH_4_6_STATES[i]);

            circuit.simulate(output);

            EXPECT_EQ(SWITCH_1_2_STATES[i], circuit.isSwitchClosed(1, 2));
            EXPECT_EQ(SWITCH_2_3_STATES[i], circuit.isSwitchClosed(2, 3));
            EXPECT_EQ(SWITCH_4_5_STATES[i], circuit.isSwitchClosed(4, 5));
            EXPECT_EQ(SWITCH_4_6_STATES[i], circuit.isSwitchClosed(4, 6));

            EXPECT_EQ(LAMP_3_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(3).getValue());
            EXPECT_EQ(LAMP_7_EXPECTED_VALUES[i].getValue(), circuit.getLampSignal(7).getValue());
        }
    }END;

    TEST(EXCEPTIONS, Konfiguracios_Kivetelek) {
        Circuit circuit;
        std::stringstream error_stream;
        std::stringstream output;

        circuit.setErrorStream(error_stream);
        circuit.setSchematicFile("I_DONT_EXIST.dat");

        EXPECT_THROW(circuit.simulate(output), ConfigurationError);
        EXPECT_THROW(circuit.setSource(0, Signal(true)), ConfigurationError);
        EXPECT_THROW(circuit.setSwitch(0, 0, true), ConfigurationError);
        EXPECT_THROW(circuit.getSourceSignal(0), ConfigurationError);
        EXPECT_THROW(circuit.isSwitchClosed(0, 0), ConfigurationError);
        EXPECT_THROW(circuit.getLampSignal(0), ConfigurationError);
    }END;

    TEST(EXCEPTIONS, Periferia_Kivetelek) {
        Circuit circuit;
        std::stringstream error_stream;
        std::stringstream output;

        circuit.setErrorStream(error_stream);
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

        circuit.setErrorStream(error);
        circuit.setSchematicFile("BadSyntax.dat");

        EXPECT_THROW(circuit.simulate(output), ConfigurationError);

        const size_t error_count = 6;
        std::string EXPECTED[error_count] = {
            "Invalid component type: \"sOUrCe\" at line 2!",
            "Incorrect syntax at: \"(1, 2, 3 (1, 2, 3) (1,2,3\" at line 5!",
            "Incorrect syntax at: \"(1,2,3\" at line 5!",
            "Incorrect pin count for NOT type at line 12!",
            "Incorrect syntax at: \"(3svs) (4err) (5) (6) (7) (8) (9)\" at line 15!",
            "Incorrect syntax at: \"(4err) (5) (6) (7) (8) (9)\" at line 15!",
        };

        for (size_t i = 0; i < error_count; i++) {
            ERROR_EXPECT_CHECK_STR(EXPECTED[i], error, 4);
        }
    }END;

    TEST(ERRORS, Szimulalatlan_Elemek) {
        Circuit circuit;
        std::stringstream output;
        std::stringstream error;

        circuit.setSchematicFile("Isolated.dat");
        circuit.setErrorStream(error);
        EXPECT_THROW(circuit.simulate(output), ConfigurationError);

        const size_t expected_count = 7;
        size_t EXPECTED[expected_count] = { 2, 3, 8, 9, 10, 11, 13 };
        for (size_t i = 0; i < expected_count; i++) {
            std::string expected_message = "Node " + size_tToString(EXPECTED[i]) + " is unsimulated (isolated or self-referential)...";
            ERROR_EXPECT_CHECK_STR(expected_message, error, 4);
        }
    }END;

    TEST(ERRORS, RovidZar) {
        Circuit circuit;
        std::stringstream output;
        std::stringstream error;

        circuit.setSchematicFile("ShortCircuit.dat");
        circuit.setErrorStream(error);

        circuit.setSwitch(1, 2, true);
        circuit.simulate(output);
        std::string expected_message = "Shortcircuit from looping back at node 1!";
        ERROR_EXPECT_CHECK_STR(expected_message, output, 4);

        Signal SOURCE_5_SIGNALS[2] = { Signal(true), Signal(false) };
        Signal SOURCE_6_SIGNALS[2] = { Signal(false), Signal(true) };
        size_t EXPECTED_IDS[2] = { 6, 5 };

        circuit.setSource(1, Signal(true));
        circuit.setSwitch(1, 2, false);
        for (size_t i = 0; i < 2; i++) {
            circuit.setSource(5, Signal(SOURCE_5_SIGNALS[i]));
            circuit.setSource(6, Signal(SOURCE_6_SIGNALS[i]));
            circuit.simulate(output);
            std::string expected = "Shortcircuit from looping back at node " + size_tToString(EXPECTED_IDS[i]) + "!";
            ERROR_EXPECT_CHECK_STR(expected, output, 4);
        }
    }END;

    TEST(COMLEX_CIRCUITS, Ot_Bemenet) {
        Circuit circuit;
        std::stringstream error;
        std::stringstream output;

        circuit.setSchematicFile("FiveToOne.dat");
        circuit.setErrorStream(error);

        bool EXPECTED_LAMP_STATE[5] = { true, true, true, true, false };

        for (size_t i = 0; i < 5; i++) {
            circuit.setSource(i + 1, Signal(true));
            circuit.simulate(output);
            EXPECT_EQ(EXPECTED_LAMP_STATE[i], circuit.getLampSignal(6).getValue());
        }
    }END;

    TEST(COMPLEX_CIRCUITS, Comparator) {
        Circuit circuit;
        std::stringstream error;
        std::stringstream output;

        circuit.setSchematicFile("Comparator.dat");
        circuit.setErrorStream(error);

        for (size_t i = 0; i < 16; i++) {
            circuit.setSource(1, Signal(i & 1));
            circuit.setSource(2, Signal(i & 2));
            circuit.setSource(3, Signal(i & 4));
            circuit.setSource(4, Signal(i & 8));

            for (size_t j = 0; j < 16; j++) {
                circuit.setSource(5, Signal(j & 1));
                circuit.setSource(6, Signal(j & 2));
                circuit.setSource(7, Signal(j & 4));
                circuit.setSource(8, Signal(j & 8));
                circuit.simulate(output);

                if (j != i) {
                    EXPECT_EQ(false, circuit.getLampSignal(13).getValue());
                }
                else {
                    EXPECT_EQ(true, circuit.getLampSignal(13).getValue());
                }
            }
        }
    }END;

    TEST(COMPLEX_CIRCUITS, Multiplexer) {
        Circuit circuit;
        std::stringstream error;
        std::stringstream output;

        circuit.setSchematicFile("Multiplexer.dat");
        circuit.setErrorStream(error);

        for (size_t i = 0; i < 16; i++) {
            circuit.setSource(1, Signal(i & 1));
            circuit.setSource(2, Signal(i & 2));
            circuit.setSource(3, Signal(i & 4));
            circuit.setSource(4, Signal(i & 8));

            for (size_t j = 0; j < 4; j++) {
                circuit.setSource(5, Signal(j & 1));
                circuit.setSource(6, Signal(j & 2));

                circuit.simulate(output);
                EXPECT_EQ(circuit.getSourceSignal(j + 1).getValue(), circuit.getLampSignal(15).getValue());
            }
        }
    }END;

    TEST(COMPLEX_CIRCUITS, Decoder) {
        Circuit circuit;
        std::stringstream error;
        std::stringstream output;

        circuit.setSchematicFile("Decoder.dat");
        circuit.setErrorStream(error);

        for (size_t i = 0; i < 4; i++) {
            circuit.setSource(1, Signal(i & 1));
            circuit.setSource(2, Signal(i & 2));
            circuit.simulate(output);

            for (size_t j = 0; j < 4; j++) {
                if (i == j)
                    EXPECT_EQ(true, circuit.getLampSignal(3 + j).getValue());
                else
                    EXPECT_EQ(false, circuit.getLampSignal(3 + j).getValue());
            }
        }
}END;
#endif
#ifndef CPORTA
    App application;
    while (application.keepRunning()) {
        application.display();
        application.handleInput();
    }
#endif
}