![Photo of setup](setup.jpg)

Pictured components:

  * 2 × Arduino Pro Mini

  * 2 × IR photo transistor: LTR-4206E (940 nm)

  * 2 × IR LED: TSAL6200 (940 nm, angle of half intensity: ϕ = ± 17°)

  * 2 × Current limiting resitor for IR LED: 100 Ω

To run the example, power the Arduinos and monitor the serial console of one of
them.

Note that the LED may as well emit infrared light in all directions, even back
into the photo transistor at the same end. If a sender receives its own signal,
MultiTrans ignores that.
