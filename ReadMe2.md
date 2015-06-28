_Deze readme dient voor het overzicht geven van de inhoud van deze ZIP._
_De readme is in Markdown formaat geschreven._
_De namen in bold stellen de makers voor, oftewel een dubbele underscore aan het begin en einde van de naam._

Project Air Support - Sint Dronard
==================================
Deze ZIP bevat alleen de laatste versie van de broncode voor het aansturen van de PIXHawk.
Eerdere versies en deelprojecten zijn niet inbegrepen.
De deelprojecten waren er om kennis te maken met nieuwe libraries.
Met alle kennis die we hiermee hebben opgedaan, hebben we de uiteindelijke broncode geschreven.
In de broncode zijn deze deelprojecten dus verwoven.

Het compileren van de broncode gebeurt doormiddel van een Makefile.
Deze gebruikt gcc als compiler.
In een terminal moet de Makefile aangeroepen worden met `make`.
Dit zal alles gaan compileren en builden.
Een uitvoerbaar bestand genaamd "Run_Dronard" zal worden gemaakt.
Vervolgens kan `make clean` worden aanroepen om alle .o bestanden te verwijderen.
Dit is nodig als er opnieuw moet worden gecompileerd.
Als een .o bestand al bestaat zal het compileren worden overgeslagen.
Alle commands moeten worden uitgevoerd op de Raspberry Pi 2 (die draait op Raspbian OS).
Het uitvoeren van "Run_Dronard" word gedaan met het command `./Run_Dronard`.

De WiringPi libraries en X11 libraries moeten zijn geïnstalleerd!

## 1. Broncode map - Dronard_v0.13
In deze map staan twee deelmappen:

* UI_Functions - _Bevatten codes voor de user interface_
* Dronard - _Bevat de rest van de codes_

De volgende bestanden staan in de broncode map:

* main.c - _De main waarin alles wordt aangeroepen_
* main.h - _De header van de main_
* Makefile - _De Makefile voor het compileren van alles_

De main.c bestaat uit 4 threads, inclusief the main thread.
Deze worden parallel uitgevoerd op de Raspberry Pi 2 met 4 CPU's:

* PThreads algemeen - __Martijn__
* ROS thread - __Geen bijdragen__
* User interface thread - __David__
* Ultrasoon thread - __Mike, Susan en Arlene__
* Main thread - __David, Martijn__

De main.h is door __David__ gecodeerd.
De Makefile is ook door __David__ gecodeerd.

## 1.1 Dronard map
In deze map staat één deelmap:

* MAVLink - _Library map van MAVLink_

De volgende bestanden staan in de Dronard map:

* MAVLinkFunctions.c - _Functies die MAVLink gebruiken_ __David__
* MAVLinkFunctions.h - _De header van MAVLinkFunctions.c_ __David__
* Ultrasoon.c - _Functies voor het uitlezen van de ultrasoon en transmitter detectie_ __Titus, Mike, Susan en Arlene__
* Ultrasoon.h - _De header van Ultrasoon.c_ __Martijn__
* USBFunctions.c - _Functies voor het uitlezen/versturen van data over de USB poort van de Raspberry Pi_ __David__
* USBFunctions.h - _De header van USBFunctions.c_ __David__
* px4_custom_mode - _De header voor Pixhawk modes_ __Martijn__ (zie bestand)

### 1.1.1 MAVLink map
In deze map staan alle bestanden van MAVLink. Deze zijn niet zelf geschreven en komen van GitHub.

## 1.2 UI_Functions map
De volgende bestanden staan in de UI_Functions map:

* UI_Functions.c - _Functies voor het creëren van een user interface_ __David__
* UI_Functions.h - _De header van UI_Functions.c_ __David__

De user interface moet nog verder ontwikkeld worden.
Het verversen van het scherm gebeurt alleen bij veranderingen aan het "window" zelf, bijvoorbeeld de grootte.
Het verversen met de een framesnelheid moet nog gecodeerd worden.
Er is ook een knop aanwezig met een rode rand, deze sluit het programma af.

# Overig
Alle andere bijdrages, zoals aan het verslag en hardware worden in het verslag beschreven.


