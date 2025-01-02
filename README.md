# Tension Device
#### Client Name: Chris Anderson

## Project Requirements
The client did a prototype in order to enhance the existing product as mentioned in Section **Reference Device** below. The prototype, however, didn't turn out well and had multiple issues. Listed in points below are the reuqirements and expectations of the new Tension Device:
- The device should have an on screen display, preferably an OLED with dimensions similar to the **Reference Device** or as suitable to allow easy and clear visibility of all readings.
- The device should have two load cells to measure tension accurately. The load cells should be mounted using a small form factor screw terminal but test pads given separately as well for testing:
    - Tension bar 1: Measure tension accurately from 0g to 1 kg in 1g increments.
    - Tension bar 2: (Second tension bar for accuracy) 0g to 1 kg in 1g increments.
- Show the tension reading on a screen.
- Switch between nM and gF button using button.
- USB-C powered/program upload.
- Battery to power the device when direct power is not available. The battery should be chargeable via USB-C.
- Wifi and/or Bluetooth to stream the data off the device.
- Suitable and cost effective ESP32 based module / chipset. Module is preferred due to certification issues.
- A 5v DC motor for pulling the thread at constant speed. The motor should also be mounted using a small form factor screw terminal but test pads given separately as well for testing.
- Minimize BOM cost and PCB footprint to the best of possibility.
- There should be a Tare Button
- There should be a ON/OFF button to control the Motor.
- Screw terminal blocks for the load cells and the Motor.
- The device **dimensions** aren't very specific but it should be smaller than 3" x 5" (the smaller the better). Rectangular shape is preferred.
- The board should have 4 x mounting holes M3 size on all 4 ends for mechanical requirements.
- The device will function primarily in two modes:
    - Mode 1: Read both sensors and display value on screen/wireless at the same time.
    - Mode 2: Show the difference between the two sensors on display/wireless.

### Reference Device
#### Concept Image
![image](https://github.com/user-attachments/assets/986d34ca-adaf-40dc-a1e7-1d7a29dcd14d)

#### Problems with Existing Device
- Screen is hard to read.
- No Wifi/Bluetooth.
- No motor for driving the pull.
- Only one load cell.
