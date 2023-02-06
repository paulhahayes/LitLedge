# Introduction

This project embeds a LED strip and photoelectric sensors inside a skateboard ledge, resulting in a dynamic and interactive visual experience for skateboarders. The LED strip is positioned underneath the ledge, illuminating as the skater slides and adding a mesmerizing effect to their tricks. The photoelectric sensors track the position and direction of the skater and, together with a queue data structure, control the lighting output.
Features

By using the FastLED library for Arduino, the code is highly customizable, allowing for a wide range of visual effects and patterns to be created. This library provides an extensive set of functions and features that simplify the process of controlling an LED strip, including advanced color correction, noise reduction, and support for multiple LED chipsets. With the use of the FastLED library, the possibilities for customizing the LED strip are virtually endless, allowing the project to be tailored to the specific needs and preferences of each user.

youtube link coming
 
 
 
 
# Materials

<ul>
  <li>Arduino uno board</li>
  <li>Programmable LED strip WS2812b</li>     
   <li>x12 Photoelectric sensors</li>
 <li>5v Power supply</li>
 <li>Wires</li>
  <li>Skateboard ledge</li>
</ul> 
    


# Setup

    DATA PIN = 12

Note: I am currently working on an interface to load entire color palettes and patterns but have not yet finished this code. For now, to change the color of the strip, use the variable CRGB colorActive = CRGB( 255, 90, 0); to either put RGB values between 0-255 or refer to https://fastled.io/docs/3.1/struct_c_r_g_b.html for more details.
  

