Met hierin een korte uitleg van de samenhang van de inhoud van de ZIP, zodat we weten
wat jullie meegestuurd hebben. Vertel per (sub)map:

* Wat de inhoud is (bijv. STM-camera-code)
* Waar deze voor dient
* Welke tools er gebruikt zijn (IDE, compilersettings etc.)
* Wie wat heeft bijgedragen aan dit onderdeel.

_Deze readme dient voor het overzicht geven van de inhoud van deze ZIP_
_De readme is in Markdown formaat geschreven_

Project Air Support - Sint Dronard
==================================
Deze ZIP bevat alleen de laatste versie van de broncode voor het aansturen van de PIXHawk.
Eerdere versies en deelprojecten zijn niet inbegrepen.
De deelprojecten waren er om kennis te maken met nieuwe libraries.
Alle kennis die we hiermee hebben opgedaan hebben we de uiteindelijke broncode geschreven.
In de broncode zijn deze deelprojecten dus deels verwoven.

Het compileren van de broncode gebeurt doormiddel van een Makefile.
Deze gebruikt gcc als compiler.
In een terminal moet de Makefile aangeroepen worden met "make".
Dit zal alles gaan compileren en builden.
Een uitvoerbaar bestand genaamd "Run_Dronard" zal worden gemaakt.
Vervolgens kan "make clean" worden aanroepen om alle .o bestanden te verwijderen.
Dit is nodig als er opnieuw moet worden gecompileerd.
Als het .o bestand al bestaat zal het compileren worden overgeslagen.



# Hoofdmap
De volgende mappen staan in de hoofd map:

* Dronard_v0.13 - _De map met de broncode_
* ...

# 1. Broncode map - Dronard_v0.13
In deze map staan twee deelmappen:

* UI_Functions - _Bevatten codes voor de user interface_
* Dronard - _Bevat de rest van de codes_

De volgende bestanden staan in de broncode map:

* main.c - _De main waarin alles wordt aangeroepen_
* main.h - _De header van de main_
* Makefile - _De Makefile voor het compileren van alles_

De main bestaat uit 4 threads, inclusief the main thread.
Deze worden parallel uitgevoerd op de Raspberry Pi 2 met 4 CPU's:

* ROS thread - _Geen bijdragen_
* User interface thread - _David_
* Ultrasoon thread - _Mike, Susan en Arlene_
* Main thread - _David_







Deze readme dient voor het overzicht geven van waar aan gewerkt wordt
op dit moment en om aan te geven wat door wie gemaakt wordt en ontworpen

Iedereen is op dit moment bezig met zijn eigen deel.
Susan en Arlene zijn bezig met het ultrasoon, deel coderen en verslaggeving
voor dit project. 
Mike en Titus zijn bezig met het maken voor de code van het vinden van het
slachtoffer, de hardware is vandaag (11-6-2015) redelijk werkend gekregen
Martijn en David zijn bezig de hoofdcode voor de raspberry pi verder uit te
breiden, half bezig tegelijk de code in het verslag te verwerken. Verder ook
met het proberen van ROS en pthreads op de raspberry pi indien dit nodig moet
zijn om MAVROS goed te laten werken of voor een andere functionaliteit.

In deze zip bestand komt versie 6 van de dronard code, hierin staat de main
Daaronder staan de twee sub bestanden van mavlink functies en usb functies
In de usb functies staan de codes voor het openen van de px4 en het sluiten
van de px4. In de mavlink functies, staan alle mavlink functies, deze functies
zijn gebaseerd op map die er ook bij word gevoegd van alle mavlink functies.

Verder wordt er de huidige code van de ultrasoon bord bijgevoegd, deze moet
nog in de hoofdcode worden bijgevoegd en worden getest.
Daarnaast zit er een test functie bij voor pthread.

In het conceptverslag wordt op dit moment hard aan gewerkt om die weer up to
date te krijgen en af te hebben voor de tweede oplevering.

De tools die gebruikt worden zijn raspberry pi 2, Met daarop Geany wordt
gebruikt om de hoofdcode te testen en te gebruiken. De build command staat in
de main.c

