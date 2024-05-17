#ifndef INPUTPIN_H_
#define INPUTPIN_H_

#include "Pin.h"
#include "InputComponent.h"
#include "Exceptions.hpp"

class InputComponent;


class InputPin : public Pin {
    /**
     * @brief Az áramköri elem, melynek része a bemeneti pin.
     *
     */
    InputComponent* component;
    /**
     * @brief Tárolja, hogy készen áll a pin feldolgozásra.
     *
     */
    bool ready;
public:
    /**
     * @brief Létrehoz egy bemeneti pin-t, komponensét NULL-ra állítva.
     *
     * @param baseSignal Az alapjel, ha van megadva.
     */
    InputPin(Signal baseSignal = Signal(false));

    /**
     * @brief Egy áramköri elemhez köti a bemeneti pin-t, így tud majd neki üzenni.
     *
     * @param component Az áramköri elem, amihez kötjük.
     */
    void connenctToComponent(InputComponent* connected);

    /**
     * @brief Visszaadja a pointerét arra az elemre, amihez kapcsolódik.
     *
     * @return Az elem, aminek része.
     */
    InputComponent* getComponent() const;

    /**
     * @brief Visszaadja, hogy készen áll-e kiértékelésre a bemeneti pin, azaz erről a pinről már meg van-e a helyes bemenet.
     *
     * @return true = ha készenáll.
     * @return false = ha még nem áll készen
     */
    bool isReady();

    /**
     * @brief Jelzi az áramköri elem felé, hogy ezen a lábán rendelkezésre áll a jel.
     *
     * @exception NonExistentConnection = Nincs kapcsolt InputComponent eleme.
     */
    void setReady();

    /**
     * @brief Reseteli a készenlétet, azaz a pin-nek beállítja, hogy még nem áll készen adat feldolgozásra.
     *
     */
    void resetReady();

    /**
     * @brief Virtuális a destruktor az öröklés miatt.
     *
     */
    virtual ~InputPin();
};


#endif // INPUTPIN_H_