# L06 - Komponenttester (del II)

## Dagordning
* Utveckling av befintliga stubklasser så att befintliga komponenttester fungerar.
* Implementering av testfallen enligt kommenterade instruktioner i [logic_test.cpp](../../library/test/logic/logic_test.cpp).
* Tillägg av ytterligare komponenttester för att täcka fler scenarion i systemlogiken.

## Mål med lektionen
* Förstå hur systemlogiken i [logic.cpp](../../library/source/logic/logic.cpp) fungerar genom att analysera implementationen.
* Kunna vidareutveckla stubklasser för att möjliggöra kontroll av hårdvarubeteende i tester.
* Förstå hur stubklasser används för att simulera hårdvaruinteraktioner (GPIO-tillstånd, timeouts med mera).
* Kunna skriva komponenttester som verifierar komplex logik med flera hårdvarukomponenter.
* **Huvudmål**: Utveckla stubklasserna så att testfallen i [logic_test.cpp](../../library/test/logic/logic_test.cpp) kan implementeras och går igenom, samt lägga till ytterligare tester för att täcka fler scenarion.

## Förutsättningar
* Genomgång av L05 där de första revisionerna av stubklasserna implementerades.
* Bekantskap med Google Test-ramverket.
* Förståelse för interface-baserad design i C++.
* Alla stubklasser är implementerade och [logic_test.cpp](../../library/test/logic/logic_test.cpp) kompilerar.

## Instruktioner

### Analysera systemlogiken
* Öppna och studera [logic.cpp](../../library/source/logic/logic.cpp) för att förstå:
  * Hur knapptryckningar hanteras via `handleButtonEvent()`.
  * Hur debounce-timern används för att undvika flera avläsningar av samma knapptryck.
  * Hur toggle-timern styr LED-blinkningar.
  * Hur temperaturtimern och temperaturknappen används för att läsa och skriva ut temperaturen.
  * Hur EEPROM används för att spara och återställa toggle-timer-tillståndet vid uppstart.

* Identifiera vilka stub-metoder som behövs för att kunna:
  * Simulera knapptryckningar genom att sätta GPIO-tillstånd.
  * Simulera timer-timeouts.
  * Kontrollera LED-tillstånd.
  * Verifiera EEPROM-skrivningar och läsningar.
  * Kontrollera att rätt temperatur läses och skrivs ut via serial.

### Vidareutveckla stubklasser
* Stubklasserna för GPIO och EEPROM är redan kompletta. De stubklasser som behöver vidareutvecklas är:
  * [driver::timer::Stub](../../library/include/driver/timer/stub.h)
    - Lägg till en metod för att simulera timeout: `setTimedOut(bool)`.
  * [driver::tempsensor::Stub](../../library/include/driver/tempsensor/stub.h)
    - Lägg till metod för att sätta temperaturen: `setTemperature(int16_t)`.

* Tips: Stubklasserna behöver inte simulera verklig hårdvara exakt, utan endast tillhandahålla 
  den funktionalitet som krävs för att testa systemlogiken.

### Demonstration
* Följ med under demonstrationen där toggle-testet implementeras.
* Notera hur stubklasserna används för att:
  * Simulera knapptryckningar genom att sätta GPIO-tillstånd.
  * Simulera timer-timeouts med `setTimedOut()`.
  * Verifiera LED-tillstånd och timer-status.
* Se hur testfallen struktureras för att verifiera komplexa scenarion steg för steg.

### Implementera testfall
* Öppna [logic_test.cpp](../../library/test/logic/logic_test.cpp) och implementera de återstående testfallen enligt kommentarerna:
  * **TEST(Logic, ToggleHandling)** - Implementeras under demonstration.

  * **TEST(Logic, TempHandling)** - Testa temperaturhantering:
    - Sätt temperaturen till 25 °C via stub-implementationen.
    - Tryck på toggle-knappen och verifiera att temperaturen inte skrivs ut.
    - Tryck på temperaturknappen och verifiera att temperaturen skrivs ut.
    - Simulera temperaturtimerns timeout och verifiera att temperaturen skrivs ut igen.

  * **TEST(Logic, Eeprom)** - Testa EEPROM-hantering:
    - Case 1: Skapa systemlogik utan toggle-state i EEPROM, verifiera att toggle-timern är avstängd
    - Case 2: Sätt toggle-state i EEPROM, skapa ny systemlogik, verifiera att toggle-timern aktiveras vid uppstart.

### Köra tester
Navigera till testmappen och kör följande kommandon:

```bash
cd library/test
make
```

Målet är att de implementerade testerna ska gå igenom. Om något test misslyckas, analysera felmeddelandet och justera antingen stub-implementationen eller testfallet.

### Felsökning och buggfixar
* Om tester indikerar att buggar förekommer i systemlogiken eller stub-implementationerna:
  * Analysera testresultatet noggrant för att identifiera rotorsaken.
  * Avgör om felet ligger i testfallet, stub-implementationen eller logik-implementationen.
  * Åtgärda buggen och kör testerna igen för att verifiera att problemet är löst.

### Lägg till ytterligare tester
* När de kommenterade testfallen fungerar, lägg till egna tester för att täcka fler scenarion:
  * Testa flerknapptryckningar i olika kombinationer.
  * Testa edge cases, exempelvis för att testa vad som händer om temperatursensorn returnerar orealistiska värden.
  * Testa vad som händer om flera timers får timeout samtidigt.
  * Verifiera felhantering när hårdvara inte är initialiserad korrekt.

## Utvärdering
* Vilka delar av systemlogiken var svårast att testa?
* Hur behövde stubklasserna modifieras för att möjliggöra testning?
* Hittades några buggar under testningen? Hur gick felsökningen till?
* Vilka fördelar ger det att kunna kontrollera hårdvarubeteende via stubklasser?
* Hur skiljer sig komponenttester från unittester i komplexitet och omfattning?
* Vilka lärdomar tar ni med er om testbarhet och design?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Slutförande av komponenttester för systemlogiken.
