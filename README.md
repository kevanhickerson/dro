# Digital Readout (DRO)

The goal is to be able to create a usable, and fairly cheap 
DRO that can be used for a lathe, milling machine, or whatever
you desire.

The main hardware will be an arduino with a rotary encoder
connected to a rack and pinion. The pinion gear will be mounted
to the rotary encoder and held stationary while the rack will be
mounted to the object that moves.

## Calculating The Distance
We can calculate the distance travelled by figuring out the 
circumference of the gear, and dividing that by the number
of pulses that your rotary encoder has per rotation (ppr).

circumference = 2 * pi * radius

If your gear had a radius of 5mm, we can plug that into the
formula and get a circumference of 31.42mm.

We can then divide our circumference by our ppr, and get the
distance travelled per pulse (dpp).

dpp = circumference / ppr

If your rotary encoder had a ppr of 20, we can take 31.42 / 20
to get 1.571mm/pulse. This means that your rack will travel
1.571mm for each pulse that the rotary encoder sends back to the
arduino.

## Resolution
You can see from the previous example that we might not have the
resolution that we desire. While 1.571mm being our smallest 
possible increment would be perfectly fine if we were travelling
a large distance, it's less than ideal when we talk about
machining. In those cases, you might be dealing with values
down to 0.025mm or smaller.

We can increase our resolution in 2 ways. We can get a different
rotary encoder that has more ppr. Or we can change the gearing
for the pinion gear.

If we increased the ppr to 1024, then we get ~0.03068mm/pulse.

If we decrease the radius of the pinion to 2.5mm (and keep 20
ppr), then we get ~0.785mm/pulse.

If neither one of those is an option, we can introduce an
intermediate shaft between the rack and pinion with additional
gears to act at as a multiplier. A small gear connected to the
rack spinning a larger gear (which is connected to the pinion)
twice the radius of the small gear will be the equivalent of
reducing the pinion gear's radius by half.