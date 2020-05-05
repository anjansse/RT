# RT
RT is an advanced rendering project of school 42. it was implemented in C, and we used the SDL graphic library to render the scenes. Every formula was implemtented without the help of any external libraries.
Current objects that can be rendered are:
  - Spheres
  - Cones
  - Infinite plans
  - Cylinders

Material effects which can be used are:
  - Scattering
  - Reflection
  - Refraction

## Installation
Clone or download this repository and run make in command line while in the root of the repository. This command will build executables called './rtv1'.
If you don't possess SDL, simply run 'make sdl_install'.
If you possess SDL but the program can't locate it, run 'make sdl'.

## Usage
### Scene file composition
Camera: can only contain one in a scene, has a position and a direction propriety.
Light: can contain multiple in a scene, has a position, a direction and an intensity propriety.
Cone: can contain multiple in a scene, has a position, an axe vector, radius, color and a material propriety.
Infinite Plan: can contain multiple in a scene, has a distance to origin, normal, color, and a material propriety.
Sphere: can contain multiple in a scene, has a position, radius, color and material propriety.
Cylinder: can contain multiple in a scene, has a position, direction, radius, height, color and a material propriety.

### Run a scene
./rtv1 scenes/file
### Commands in scene
'A' and 'D' keys are used to navigate on the X axis by n unit.
'UP' and 'DOWN' arrow keys are used to navigate on the Y axis by n unit.
'W' and 'S' keys are used to navigate on the Z axis by n unit.
'+' and '-' keys are used to change the number of unit used to navigate.
'ESC' key is used to exit program properly.

## Screenshots


@Antoine: inspiration:
https://github.com/VolodymyrKuksa/RT#installation
https://github.com/wwatkins42/RT
https://github.com/ldehaudt/SimpleRaytracer
