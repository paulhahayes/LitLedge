Introduction

This project embeds a LED strip and photoelectric sensors inside a skateboard ledge, resulting in a dynamic and interactive visual experience for skateboarders. The LED strip is positioned underneath the ledge, illuminating as the skater slides and adding a mesmerizing effect to their tricks. The photoelectric sensors track the position and direction of the skater and, together with a queue data structure, control the lighting output.
Features

    Utilizes the FastLED library for Arduino, providing a highly customizable codebase for a wide range of visual effects and patterns.
    Extensive set of functions and features available, including advanced color correction, noise reduction, and support for multiple LED chipsets.
    Allows for extensive customization and personalization, tailoring the project to the specific needs and preferences of each user.

Materials

    Arduino uno board
    Programmable LED strip WS2812b
    x12 Photoelectric sensors
    5v Power supply
    Wires
    Skateboard ledge

Circuit Diagram
<coming soon>
Setup

    DATA PIN = 12

Note: I am currently working on an interface to load entire color palettes and patterns but have not yet finished this code. For now, to change the color of the strip, use the variable CRGB colorActive = CRGB( 255, 90, 0); to either put RGB values between 0-255 or refer to https://fastled.io/docs/3.1/struct_c_r_g_b.html for more details.
  

