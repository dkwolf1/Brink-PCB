# Brink PCB

[English](README.md) · **Nederlands**

Een ESP32-controller voor de standeningangen van een **Brink Renovent Excellent 300/400** en twee zones van een **Brink Elan E**. De print bundelt drie aansluitingen, negen relaisaansturingen en voorzieningen voor filterindicatie. De bediening kan via ESPHome aan Home Assistant worden gekoppeld.

> **Projectstatus (11 oktober 2026)**  
> De bestaande ESPHome-opstelling met relais vormt de praktische basis. De hier gedeelde printontwerpen en extra PCB-functies zijn ontwerpbestanden; een volledig geassembleerde print, alle filtermetingen en het gedrag bij opstarten zijn nog niet als geheel gevalideerd. Controleer schema, componenten en werkelijke bedrading vóór gebruik.

## Wat vind je hier?

| Onderdeel | Inhoud |
| --- | --- |
| [`hardware/rev-2026-10-11/`](hardware/rev-2026-10-11/) | Schema, onderdelenlijst, Gerber-export en afbeeldingen van de PCB-lagen van de aangeleverde revisie |
| [`docs/artikelen/`](docs/artikelen/) | Drie Nederlandstalige artikelen over de Renovent, RJ12/ESPHome en de PCB |
| [`docs/hardware.md`](docs/hardware.md) | Aansluitingen, projectstatus en controles vóór assemblage |
| [`docs/firmware.md`](docs/firmware.md) | Uitleg over de meegeleverde ESPHome-configuratie |
| [`firmware/esphome-web-d0df24.example.yaml`](firmware/esphome-web-d0df24.example.yaml) | Opgeschoond voorbeeld van de aangeleverde configuratie |
| [`Wtw.yaml`](https://github.com/dkwolf1/Brink-PCB/blob/main/Wtw.yaml), [`arduino/`](https://github.com/dkwolf1/Brink-PCB/tree/main/arduino), [`web/`](https://github.com/dkwolf1/Brink-PCB/tree/main/web) | Bestaande firmware en webinterface uit deze repository |
| [`Pcb/`](https://github.com/dkwolf1/Brink-PCB/tree/main/Pcb) | Bestaande PCB-bestanden uit deze repository |

## Werking in het kort

Elke aansluiting gebruikt drie potentiaalvrije maakcontacten. Per toestel is steeds hoogstens één van de drie relais actief; met alle contacten open ontstaat een vierde logische toestand. De betekenis van die toestand en van de drie gesloten contacten hangt af van het aangesloten toestel en zijn instellingen. De ESP32 bestuurt de relais, maar vervangt de interne regeling en beveiligingen van Brink niet.

| Kanaal | PCB-aansluiting | GPIO's voor de drie contacten |
| --- | --- | --- |
| Renovent WTW | CN3 | 26, 27, 19 |
| Elan E boven | CN2 | 32, 23, 22 |
| Elan E beneden | CN1 | 33, 25, 14 |

Dit is de toewijzing van het **projectschema**, geen universele Brink-pinout. De ESPHome-configuratie noemt de standen `position 1` t/m `position 4`; die labels zijn niet automatisch gelijk aan de standnummers op ieder Brink-toestel. Zie [hardware en aansluitingen](docs/hardware.md) voor de meet- en testpunten.

## Aan de slag

1. Lees het [schema](hardware/rev-2026-10-11/schema.pdf), de [onderdelenlijst](hardware/rev-2026-10-11/onderdelenlijst.tsv) en de [hardware-notities](docs/hardware.md).
2. Controleer de werkelijke RJ12-kabel met een multimeter: bepaal de pinnummering en meet de doorverbindingen. Vertrouw niet op aderkleuren.
3. Controleer relaismodule, stuurpolariteit, voeding, contactvolgorde en opstartgedrag op de werkbank voordat je een toestel aansluit.
4. Kies een firmwarevariant. De bestaande [`Wtw.yaml`](https://github.com/dkwolf1/Brink-PCB/blob/main/Wtw.yaml) staat in de hoofdmap; het nieuw aangeleverde [ESPHome-voorbeeld](firmware/esphome-web-d0df24.example.yaml) staat apart. Lees eerst de [firmware-notities](docs/firmware.md).
5. Meet de betreffende X2-aansluiting op het eigen toestel en test daarna één kanaal tegelijk. De artikelen in [`docs/artikelen/`](docs/artikelen/) geven de achtergrond.

## Productiebestanden

De map [`hardware/rev-2026-10-11/`](hardware/rev-2026-10-11/) bevat een momentopname van één revisie. `gerber.zip` bevat de koper-, masker-, zeefdruk-, outline- en boorbestanden voor een PCB-fabrikant. `pcb-lagen-png.zip` bevat alleen afbeeldingen ter inspectie. De onderdelenlijst is tab-gescheiden en bevat voor meerdere componenten nog geen fabrikant- of leveranciersnummer: controleer voetafdrukken, waarden en beschikbaarheid voordat je bestelt.

Een native EasyEDA-bronbestand van deze revisie zat niet bij de aangeleverde bestanden. Het PDF-schema en de Gerbers zijn bruikbaar voor inzage en productie, maar niet gelijk aan een bewerkbaar schema/PCB-project.

## Veiligheid en grenzen

- De X2-aansluiting is een **laagspanningsinterface**. Sluit geen netspanning op de RJ12-lijnen aan.
- Verbind de Brink-referentie van de relaiscontacten niet automatisch met de ESP-GND.
- Een filterlijn die circa 24 V kan voeren, mag niet rechtstreeks op een ESP32-GPIO. De filterschakeling en polariteit moeten eerst op de echte installatie worden gemeten en gecontroleerd.
- Software-interlocks alleen garanderen geen veilige toestand tijdens reset, opstarten of bij een onjuist aangesloten relaismodule.
- Dit is een zelfbouwproject, geen door Brink goedgekeurde aanpassing. Montage aan een installatie vereist eigen verificatie van toestelversie, bedrading en werking.

## Licentie

De bestaande repository is gepubliceerd onder de [MIT-licentie](https://github.com/dkwolf1/Brink-PCB/blob/main/LICENSE). Het licentiebestand staat in de GitHub-repository; dit aanvulpakket vervangt het niet. Wil je de nieuwe hardwarebestanden en artikelen apart licentiëren, leg dan eerst per onderdeel de reikwijdte en rechthebbende vast. Voor een hardwaregerichte, permissieve licentie is CERN-OHL-P-2.0 een optie; voor eigen artikelen is CC BY 4.0 een optie.
