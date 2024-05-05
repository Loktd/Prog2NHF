#ifndef _CIRCUIT_H
#define _CIRCUIT_H


#include "Signal.h"
#include "Pin.h"
#include "Component.h"
#include "Queue.h"
#include "Gate.h"
#include "Peripherals.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>


class Circuit {
  // Belső adatok

  /**
   * @brief A hiba stream, ahova ki írjuk az esetleges hibákat (pointer, nem referencia, mert változtatható).
   *
   */
  std::ostream* errorStream;
  /**
   * @brief A felhasznált bemeneti file helye.
   *
   */
  std::string inputFilePath;
  /**
   * @brief A bemeneti file, ahonnan olvassuk felkonfiguráláskor.
   *
   */
  std::ifstream inputfile;

  /**
   * @brief Összes áramkör elem listája, felszabadításkor ezen keresztül biztosítja, hogy minden memóriát töröl, ami nem csomópont.
   *
   */
  Queue<Component> componentList;
  /**
   * @brief A bemeneti pin-el rendelkező pin-ek listája. Reseteléshez kell, ezen keresztül tudjuk az összes bemeneti pin-jeit resetelni.
   *
   */
  Queue<InputComponent> inputComponentList;
  /**
   * @brief Az aktív FIFO, amiből szimuláció során kiértékejük elemeket. (Azért kell itt, mert be kell az elemekre állítani az aktív FIFO-t)
   *
   */
  Queue<Component> activeList;
  /**
   * @brief A jelforrások listája, kiolvasáshoz és beállításhoz.
   *
   */
  Queue<Source> sourceList;
  /**
   * @brief A kapcsolók listája, kiolvasáshoz és beállításhoz.
   *
   */
  Queue<Switch> switchList;
  /**
   * @brief A lámpák listája, kiolvasáshoz.
   *
   */
  Queue<Lamp> lampList;
  /**
   * @brief A csomópontok listája, melyeken keresztül kapcsolódnak az egyes áramköri elemek. Ez birtokos, azaz a csomópontok felszabadításáért ez felel.
   *
   */
  Queue<Node> nodeList;

  /**
   * @brief Ez a változó jelzi, hogy fel van-e konfigurálva az áramkör. (Ha igen, akkor nem konfigurál újra feleslegesen.)
   *
   */
  bool configured;
  /**
   * @brief Ez jelzi, hogy le lett-e szimulálva az áramkör. (Ha igen, akkor nem szimuláljuk újra feleslegesen.)
   *
   */
  bool simulated;

  // Belső adatszerkezetek és függvények a konfiguráláshoz

  /**
   * @brief A konfigurálás során meg kell állapítania hogy milyen típusú elemet hozunk létre a sorban, ennek az információnak a tárolására van ez az enum.
   *
   */
  enum ComponentType {
    INVALID = 0, SOURCE = 1, LAMP = 2, SWITCH = 3,
    GATE_AND = 4, GATE_OR = 5, GATE_NOT = 6, GATE_XOR = 7, GATE_NAND = 8, GATE_NOR = 9, GATE_XNOR = 10
  };

  /**
   * @brief Ez a struktúra tartalmazza a fő információkat a forrás file feldolgozásakor, a rövidebb paraméterlista miatt született meg főleg.
   *
   */
  struct LineContent {
    /**
     * @brief Hanyadik sornál tartunk.
     */
    size_t lineNumber;
    /**
     * @brief A jelenleg olvasott sor.
     */
    std::string content;
    /**
     * @brief Hanyadik karakternél tart a beolvasás.
     */
    size_t idx;
    /**
     * @brief Milyen típusú a sor.
     */
    ComponentType type;
    /**
     * @brief Egy szimpla default konstruktor a könnyebb használatért.
     */
    LineContent() : lineNumber(0), content(""), idx(0), type(INVALID) {}
  };

  /**
   * @brief Felkonfigurálja az áramkört a forrás file alapján, ha hiba van, akkor jelzi a hiba stream-re.
   *
   */
  void configure();
  /**
   * @brief Törli az eddig tartalmazott áramkört, azaz kezdeti, üres állapotba hozza magát. (Forrás file-t is bezárja.)
   *
   */
  void reset();
  /**
   * @brief A feldolgozást vezérlő fő függvény, mely megnyitja a file-t, beolvas minden sort, és ezeket feldolgozza.
   *
   * @exception NoFileGiven = ha nem adtunk neki vagy nem létező file-t adtunk meg.
   */
  void build();
  /**
   * @brief Tesztel szimulálás során elérhetetlen elemek után, ha talál dob egy kivételt.
   *
   * @exception UnsimulatedComponent = ha talált nem szimulált elemet
   */
  void testForIsolatedComponent();
  /**
   * @brief Egy konkrét sor feldolgozásához szükséges folyamatokat végzi el.
   *
   * @param line A feldolgozandó sor-hoz tartozó információkat tároló struktúra.
   */
  void buildLine(LineContent& line);
  /**
   * @brief Kiszedi a sorból, hogy milyen típusú elemeket hozunk benne létre.
   *
   * @param line A feldolgozandó sor-hoz tartozó információkat tároló struktúra.
   */
  void getLineType(LineContent& line);
  /**
   * @brief Kiolvassa a létrehozott áramköri elem pin-jeihez megadott csomóponti ID-kat.
   *
   * @param line A feldolgozandó sor-hoz tartozó információkat tároló struktúra.
   * @param nodeNumbers A lista, ahol akarjuk ezeket tárolni.
   */
  void getNodeNumbers(LineContent& line, Queue<size_t>& nodeNumbers);
  /**
   * @brief Ellenőrzi, hogy az adott áramköri elemhez helyes-e a megadott pin-ek száma.
   *
   * @param line A feldolgozandó sor-hoz tartozó információkat tároló struktúra.
   * @param count A pin-ek száma, amit kiolvastunk.
   */
  void checkNodeCount(LineContent& line, size_t count);
  /**
   * @brief A sor típusa alapján kiválasztja, hogy hogyan hozza létre az adott elemet.
   *
   * @param line A feldolgozandó sor-hoz tartozó információkat tároló struktúra.
   * @param nodeNumbers A lista, ami tárolja az összekötendő csomópontok ID-jait.
   */
  void createBasedOnType(LineContent& line, Queue<size_t>& nodeNumbers);

  /**
   * @brief Létrehozza a konkrét specifikus áramköri elemet a megadott típus alapján és összeköti a megfelelő csomópontokkal.
   *
   * @tparam ComponentType Az áramköri elem típusa.
   * @param nodeNumbers A lista, ami tárolja az összekötendő csomópontok ID-jait.
   */
  template<typename ComponentType>
  void create(Queue<size_t>& nodeNumbers);
  /**
   * @brief Összeköt egy bemeneti pin-t egy csomóponttal. (Ha nem létezik, akkor létrehozza a csomópontot.)
   *
   * @param pin A bemenet pin-amivel kötünk.
   * @param ID A csomópont ID-ja.
   * @param idx Az indexe a bemeneti pin-nek, ID beállításhoz.
   */
  void connectInputPinWithNode(InputPin* pin, size_t ID, size_t idx);
  /**
   * @brief Összeköt egy kimeneti pin-t egy csomóponttal. (Ha nem létezik, akkor létrehozza a csomópontot.)
   *
   * @param component Az áramköri elem, amihez a kimeneti pin tartozik.
   * @param pin A pin, amit akarunk összekötni.
   * @param ID A csomópont ID-ja, amire akarjuk kötni.
   * @param idx Az indexe a kimeneti pin-nek, ID beállításhoz.
   */
  void connectOutputPinWithNode(OutputComponent* component, OutputPin* pin, size_t ID, size_t idx);

public:
  /**
   * @brief Létrehoz egy üres áramkört, amit fel tudunk konfigurálni.
   *
   */
  Circuit();
  /**
   * @brief Másolással hoz létre egy áramkört egy másikból.
   * @attention Feltételezzük, hogy nem változott a forrás file-ja a másoltnak! (Ezt lehet még meg kell fixálni...)
   *
   * @param source A másolt áramköri elem.
   */
  Circuit(const Circuit& source);
  /**
   * @brief Átmásol egy áramkört egy másikba.
   * @attention Feltételezzük, hogy nem változott a forrás file-ja a másoltnak! (Ezt lehet még meg kell fixálni...)
   *
   * @param source Ahonnan másolunk.
   * @return Circuit& A láncolás miatt kell csak magára referenciát visszaadnunk.
   */
  Circuit& operator=(const Circuit& source);

  /**
   * @brief Beállítja az hiba stream-et, ami lehet vagy std::cerr vagy file vagy bármilyen ostream objektum.
   *
   * @param os Ahová fogja kijelezni a hibaüzeneteket.
   */
  void setErrorStream(std::ostream* os);
  /**
   * @brief Beállítja forrás file-t. (Nem konfigurálja fel!)
   *
   * @param path A forrás file helye.
   */
  void setSchematicFile(const std::string& path);
  /**
   * @brief Visszaadja a forrás file nevét (esetlegesen a helyével, ha úgy lett megadva).
   *
   * @return const std::string& A forrás file neve.
   */
  const std::string& getSourceFileName() const;

  /**
   * @brief Leszimulálja az áramkört, és az eredményeket kiírja a megadott kimeneti stream-re.
   *
   * @param os A kimeneti stream, ahová írjuk.
   */
  void simulate(std::ostream& os);

  /**
   * @brief Beállítja egy forrás jelszintjét a megadott értékre, amennyiben létezik. (Ha nem, akkor hiba stream-re jelzi ezt.)
   *
   * @param connectedNode A csomópont, amihez a forrás kapcsolódik.
   * @param newSignal A beállítani kívánt jelszint.
   */
  void setSource(size_t connectedNode, Signal newSignal);
  /**
   * @brief Beállítja egy kapcsoló állapotát, amennyiben létezik. (Ha nem, akkor hiba stream-re jelzi ezt.)
   *
   * @param connectedNode1 Az egyik csomópont, amihez kapcsolódik a kapcsoló.
   * @param connectedNode2 A másik csomópont, amihez kapcsolódik a kapcsoló.
   * @param closed Az új állapota. (true = zárt, false = nyitott)
   */
  void setSwitch(size_t connectedNode1, size_t connectedNode2, bool closed);

  /**
   * @brief Visszaadja egy megadott csomópontra csatlakozó forrás által kiadott jelszintet.
   *
   * @param connectedNode A csomópont, amihez kapcsolódik a forrás.
   * @return Signal A jelszint, amit kiad a forrás.
   *
   * @exception MatchingComponentNotFound = ha nincs az adott csomóponthoz kapcsolódó forrás.
   */
  Signal getSourceSignal(size_t connectedNode);

  /**
   * @brief Visszaadja két megadott csomóponra csatlakozó kapcsoló állapotát.
   *
   * @param connectedNode1 Az egyik csomópont, amire kell csatlakoznia.
   * @param connectedNode2 A másik csomópont, amire kell csatlakoznia.
   * @return true = zárt a kapcsoló ;
   * @return false = nyitott a kapcsolóá
   *
   * @exception MatchingComponentNotFound = ha nincs az adott csomópontokhoz kapcsolódó kapcsoló.
   */
  bool isSwitchClosed(size_t connectedNode1, size_t connectedNode2);

  /**
   * @brief Visszaadja egy megadott csomópontra csatlakozó lámpa állapotát, azaz a tárolt állapotát.
   *
   * @param connectedNode A csomópont, amihez kapcsolódik a lámpa.
   * @return Signal A jelszint, amivel a lámpa rendelkezik.
   */
  Signal getLampSignal(size_t connectedNode);

  /**
   * @brief Kiírja egy kimeneti stream-re az összes forrás jeleit.
   *
   * @param os A kimeneti stream.
   */
  void printAllSourceStates(std::ostream& os) const;
  /**
   * @brief Kiírja egy kimeneti stream-re az összes kapcsoló státuszát.
   *
   * @param os A kimeneti stream.
   */
  void printAllSwitchStates(std::ostream& os) const;
  /**
   * @brief Kiírja egy kimeneti stream-re az összes lámpa állapotát.
   *
   * @param os A kimeneti stream.
   */
  void printAllLampStates(std::ostream& os) const;

  /**
   * @brief Törli az objektumot, minden memóriával együtt, illetve bezárja a használt forrás file-t.
   *
   */
  ~Circuit();
};

/**
 * @brief Kiírja a kimeneti stream-re az áramkör összes periféria elemének (forrás, kapcsoló, lámpa) állapotát, illetve a forrás file nevét és a kiolvasás idejét is.
 *
 * @param os A kimeneti stream, ahova írunk.
 * @param circuit Az áramkör amit kiírunk.
 * @return std::ostream& Referencia a kimeneti stream-re a láncoláshoz.
 */
std::ostream& operator<<(std::ostream& os, const Circuit& circuit);

/**
 * @brief Kiír egy elválasztóvonalat egy kimeneti stream-re.
 *
 * @param os A kimeneti stream.
 * @param c A karakter amiből épül az elválasztóvonal.
 * @param times Ailyen hosszú az elválasztóvonal.
 */
void printSeparatorLine(std::ostream& os, char c, int times);

/**
 * @brief String-é konvertál egy unsigned intigert.
 *
 * @param converted A konvertálandó szám.
 * @return std::string A szám, string-ként reprezentálva.
 */
std::string size_tToString(size_t converted);
#endif
