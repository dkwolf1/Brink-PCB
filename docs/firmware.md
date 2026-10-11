# ESPHome-configuratie

De repository bevat al [`Wtw.yaml`](../Wtw.yaml). De nieuw aangeleverde configuratie staat afzonderlijk als [`firmware/esphome-web-d0df24.example.yaml`](../firmware/esphome-web-d0df24.example.yaml), zodat de bestaande firmware intact blijft. Het voorbeeld is niet op de nieuwe PCB gecompileerd of getest.

## Verschillen met het aangeleverde bestand

- Het lege veld `api.encryption.key` is vervangen door `!secret api_encryption_key`. Maak lokaal een eigen sleutel aan; de oorspronkelijke waarde was niet ingevuld.
- Het vaste thuisnetwerkadres (`manual_ip`) is verwijderd. DHCP is daardoor de uitgangspositie van dit voorbeeld.
- De verwijzingen naar `!secret wifi_ssid`, `!secret wifi_password` en `!secret wifi_ap_password` zijn behouden. Vul deze samen met `api_encryption_key` lokaal in via ESPHome-secrets en commit die gegevens niet.

Een invulvoorbeeld staat in [`firmware/secrets.example.yaml`](../firmware/secrets.example.yaml). Kopieer het in je lokale firmwaremap naar `secrets.yaml`. Dat laatste bestand wordt door [`firmware/.gitignore`](../firmware/.gitignore) uitgesloten.

## Voor het flashen controleren

1. Kies welke van de twee YAML-bestanden de basis is en pas de naam, netwerkgegevens en API-sleutel aan.
2. Controleer de GPIO-naar-relaismodule mapping aan de hand van schema én werkelijke bekabeling. Het bestand gebruikt GPIO 26/27/19, 33/25/14 en 32/23/22.
3. Controleer de signaalpolariteit. De switches in dit voorbeeld gebruiken `inverted: false`; sommige relaismodules zijn active-low.
4. Controleer hoe de relais zich tijdens opstarten en reset gedragen. De YAML bevat software-interlocks, maar geen bewezen hardware-interlock of complete fail-safe-configuratie.
5. Valideer de configuratie met jouw ESPHome-versie en test eerst zonder aangesloten Brink-toestel.

De filterindicatie, spanningsmeting, buzzer en gereserveerde PWM-uitgang in het PCB-ontwerp zijn niet automatisch geconfigureerd in dit YAML-voorbeeld.
