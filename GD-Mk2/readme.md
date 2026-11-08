# GD-Mk2

## Briefing
Mk2 is a smaller, lighter version of the V1 with more compact metal gearboxes instead of the printed ones and a much smaller 6s lipo instead of the huge LiFePo4 pack that I used to run these on. It's also based on the ESP32 instead of the arduino nano for increased speed and bluetooth capacity along with finer PWM control. 

## Key changes
 - Microcontroller
    Swapped th arduino nano to esp32. Integrated WiFi and Bluetooth, finer PWM, more CPU speed and Ram along with removing the strange timing issues that the arduino had with the bluetooth chip I used. 

 - Power system
    I don't have that badass 6s LiFePo4 pack anymore, so now it's using a smaller, lighter 6s battery pack. Gave the vehicle much less runtime as a result
 - Drivetrain
    The older suspension shaft holders had poor durability and can be only printed in an orientation (without a ludicrous amount opf supports) that gave them this structural weakness. The new shaft holders are simpler, way more durable and much more material-efficient.

    The older printed transmission was also far too bulky for a revision that's supposed to be the "smaller, lighter one". The vehicle now uses a metal planetary gearbox. Hence the updated motor mount and sprocket design to fit the 10mm shafts.
 - misc
    Designed and added a front carry handle to make carrying it easier. Expecially for long distances.