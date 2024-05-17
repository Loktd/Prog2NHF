#ifndef OUTPUTPIN_H_
#define OUTPUTPIN_H_

#include "Pin.h"
#include "InputPin.h"
#include "Component.h"
#include "Exceptions.h"

class InputPin;
class OutputComponent;


class OutputPin : public Pin {
    /**
     * @brief A bemeneti pin, amihez van kapcsolva.
     *
     */
    InputPin* connectedTo;
public:
    /**
     * @brief Létrhoz egy kimeneti pin-t, kapcsolt bemeneti pin-jét NULL-ra állítva.
     *
     * @param baseSignal Az alapjel, ha van megadva.
     */
    OutputPin(Signal baseSignal = Signal(false));

    /**
     * @brief Összekapcsolja egy bemeneti pin-nel.
     *
     * @param pin A kapcsolni kívánt pin.
     */
    void connectToPin(InputPin* pin);

    /**
     * @brief Jelet küld a kapcsolt bemeneti pin-nek.
     *
     * @exception NonExistentConnection = Nincs kapcsolt bemeneti pin.
     * @exception ShortCircuit = Már aktivált bemeneti pin-nek üzen.
     */
    void sendSignal() const;

    /**
     * @brief Virtuális destruktor az öröklés miatt.
     *
     */
    virtual ~OutputPin();
};

#endif // OUTPUTPIN_H_