# Hardware, aansluitingen en testpunten

Deze notities horen bij de aangeleverde revisie van **11 oktober 2026** in [`hardware/rev-2026-10-11/`](../hardware/rev-2026-10-11/). Het PDF-schema is een export; een bewerkbaar EasyEDA-bronproject was niet meegeleverd.

## Drie onafhankelijke kanalen

| Kanaal | Connector | GPIO voor X2 pin 3 | GPIO voor X2 pin 4 | GPIO voor X2 pin 5 |
| --- | --- | ---: | ---: | ---: |
| Renovent | CN3 | 26 | 27 | 19 |
| Elan boven | CN2 | 32 | 23 | 22 |
| Elan beneden | CN1 | 33 | 25 | 14 |

Volgens het projectschema wordt X2-pin 2 per toestel gebruikt als gemeenschappelijk contact aan de **contactzijde** van de relais. De maakcontacten schakelen die referentie afzonderlijk naar pin 3, 4 of 5. Pin 1 wordt in dit ontwerp niet gebruikt. Pin 6 is de filterlijn. Controleer dit op jouw toestelrevisie en kabel; deze tabel is geen universele RJ12-standaard.

| Contacttoestand | Pin 2–3 | Pin 2–4 | Pin 2–5 |
| --- | --- | --- | --- |
| Alle relais uit | Open | Open | Open |
| Eerste contact | Gesloten | Open | Open |
| Tweede contact | Open | Gesloten | Open |
| Derde contact | Open | Open | Gesloten |

De labels `position 1` t/m `position 4` in de YAML benoemen deze vier combinaties. Verifieer op het toestel welke Brink-stand en welk werkelijk luchtdebiet daarbij horen.

## Voor assemblage en aansluiting

1. Vergelijk schema, PCB-lagen, Gerbers en onderdelenlijst. Controleer met name connectororiëntatie, pin 1, footprints, polariteit en de keuze van de relaismodules.
2. Meet iedere ader van de 6P6C/RJ12-kabel van stekker tot stekker. Leg de kijkrichting vast. Kleur en zichtbare volgorde zijn onvoldoende.
3. Meet de spanning en polariteit van de filterlijn ten opzichte van de bijbehorende toestelreferentie. Controleer de optocoupler-ingang en de juiste keuze van de Elan-filterbron met de jumpers.
4. Test de print eerst met een geschikte laagspanningsvoeding zonder Brink-toestellen. Controleer 5 V, 3,3 V, warmteontwikkeling, relaispolariteit en GPIO-niveaus tijdens cold boot, reset en wifi-uitval.
5. Meet met een multimeter per relais welk contactpaar echt sluit. De PCB gebruikt aansluitingen voor een achtkanaals en een aparte enkelvoudige relaismodule; kabelvolgorde en active-high/active-low gedrag moeten met de gekozen modules overeenkomen.
6. Sluit één toestel tegelijk aan. Controleer elke stand en het gedrag als de ESP of relaisvoeding wegvalt.

## Status van extra functies

Het ontwerp voorziet onder meer in twee filterdetectiekanalen (Renovent plus één geselecteerde Elan-zone), een 5V-spanningsmeting, status-LED's, een buzzeruitgang en een gereserveerde PWM-uitgang. De meegeleverde YAML implementeert vooral de negen relais en enkele ESP-sensoren; deze extra PCB-functies zijn daarmee nog geen geteste softwarefuncties.
