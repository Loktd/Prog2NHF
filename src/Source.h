#ifndef SOURCE_H_
#define SOURCE_H_

#include "OutputComponent.h"
#include <iostream>
#include "../test/memtrace.h"


class Source : public OutputComponent {
public:
    /**
     * @brief Létrehoz egy forrást.
     *
     */
    Source();

    /**
     * @brief Végrehajtja a forrás funkcióját, azaz kiküldi a jelet a kimenetén.
     *
     */
    virtual void executeFunction();

    /**
     * @brief Beállítja a forrás kimeneti jelét.
     *
     * @param signal Az új jel.
     */
    void setOutput(const Signal& signal);

    /**
     * @brief Visszaadja a forrás kimeneti jelét.
     *
     * @return A forrás jele.
     */
    Signal getOutput() const;

    /**
     * @brief Megfordítja a kimeneti jel értékét.
     *
     */
    void flipOutput();

    /**
     * @brief Virtuális destruktor öröklés miatt.
     *
     */
    virtual ~Source() {}
};

/**
 * @brief Kiírja a forrás állapotát  a kimeneti streamre.
 *
 * @param os A kimeneti stream.
 * @param x A forrás, amit ki kell írni.
 * @return A kimeneti stream-re referencia, a láncolás miatt.
 */
std::ostream& operator<<(std::ostream& os, const Source& x);


#endif // SOURCE_H_