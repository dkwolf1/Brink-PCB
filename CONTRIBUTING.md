# Contributing

Issues and pull requests are welcome for documentation corrections, measured hardware findings, and firmware improvements.

For a hardware report, include the PCB revision, relevant schematic reference, component or connector, appliance model, and measurements. Describe the viewing direction when discussing RJ12 pin numbers. Mark clearly whether a result comes from a schematic, a bench test, or a connected appliance.

For firmware changes, explain the GPIO and relay mapping, active-high or active-low behaviour, and what happens during cold boot, reset, and loss of power or Wi-Fi. Test without a connected Brink appliance first. Do not include Wi-Fi credentials, API keys, OTA keys, private addresses, or generated firmware binaries in a pull request.

Keep one change per pull request when practical. State which checks you performed and which parts remain untested.
