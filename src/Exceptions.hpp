#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>
#include "../test/memtrace.h"


class InputComponent;

/**
 * @brief Üzenetet hordozó kivételek ősosztálya.
 *
 */
class MessagedException : public std::exception {
    /**
     * @brief A hordozott üzenet.
     *
     */
    std::string message;
public:
    /**
     * @brief Konstruktor, átadható üzenettel.
     *
     * @param msg Az átadott üzenet.
     */
    MessagedException(const std::string& msg) : message(msg) {}
    /**
     * @brief Az üzenete adja vissza, amit tárol.
     *
     * @return std::string Az üzenet.
     */
    std::string exception_message() {
        return std::string(message.c_str());
    }
};


// "Periféria"-szintű kivételek
/**
 * @brief Jelolvasás és állítás során dobja az áramkör, ha nincs a megfelelő csomópontokra kapcsolódó elem. Ezt dobhatja a felhasználó felé.
 *
 */
class MatchingComponentNotFound : public MessagedException {
public:
    MatchingComponentNotFound(const std::string& msg) : MessagedException(msg) {}
};
/**
 * @brief Konfiguráció soránt történt hiba, ezt dobhatja a felhasználó felé.
 *
 */
class ConfigurationError : public MessagedException {
public:
    ConfigurationError(const std::string msg) : MessagedException(msg) {}
};


// "Belső" kivételek
/**
 * @brief Kimeneti vagy bemeneti pin a szükséges kapcsolat hiánya esetén dobja.
 *
 */
class NonExistentConnection : public MessagedException {
public:
    NonExistentConnection(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Rövidzár esetén dobja egy kimeneti pin. El van tárolva, hogy melyik áramköri elemet próbált újraszimulálni.
 *
 */
class ShortCircuit : public MessagedException {
    InputComponent* resimulated;
public:
    ShortCircuit(const std::string& msg, InputComponent* resimmed) : MessagedException(msg), resimulated(resimmed) {}
    InputComponent* getResimulated() { return resimulated; }
};

/**
 * @brief A file-hoz nem tudott hozzáférni a program (nem létezik, stb.)
 *
 */
class FileAccessError : public MessagedException {
public:
    FileAccessError(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Az áramkör felkonfigurálásakor nem elfogadott sortípust tartalmaz a konfigurációs file.
 *
 */
class NonExistentLineType : public MessagedException {
public:
    NonExistentLineType(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief A sor komment, csak ennek jelzésére van. Lekezelése = ignorálás és kövi sorra váltás.
 *
 */
class CommentLine : public MessagedException {
public:
    CommentLine(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Hibás szintaxisa a konfigurációs file-nak valahol.
 *
 */
class IncorrectSyntax : public MessagedException {
public:
    IncorrectSyntax(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Hibás számú csomópont mennyiséget adott meg a konfigurációs file-ban egy áramköri elemhez.
 *
 */
class IncorrectPinCount : public MessagedException {
public:
    IncorrectPinCount(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Nem Node-ot dobott a rövidzár (elméletileg nem kéne ilyet dobnia).
 *
 */
class PointerConversionError : public MessagedException {
public:
    PointerConversionError(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Szimulálatlan elem van az áramkörben, valahol szakadás van benne.
 *
 */
class UnsimulatedComponent : public MessagedException {
public:
    UnsimulatedComponent(const std::string& msg) : MessagedException(msg) {}
};

/**
 * @brief Szintaktikai error jelzésének továbbítására szolgál.
 *
 */
class SchematicsFileHasSyntaxError : public MessagedException {
public:
    SchematicsFileHasSyntaxError(const std::string msg) : MessagedException(msg) {}
};

#endif // EXCEPTIONS_H_