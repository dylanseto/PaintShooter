Paintball Shooter Simulation

How to Compile & Run
============================
1. Integrated graphics are needed.
2. Open the .sln in Visual Studio 2015.
   a) For Visual Studio 2015, VS2015 binaries should be included in the lib folder.
   b) For Visual Studio 2013, the project should also be set to use Platform Toolset for Visual Studio 2013 (v120)
      and have the GLFW binary files replaced with the appropriate ones
      These can be downloaded at http://www.glfw.org/download.html
   c) Other Versions of visual studio as well as other IDEs are untested and should be used with that in mind.
3. Run with Local Windows Debugger.
4. Move around the sandbox with WASD.
5. Press X to toggle between free view and fps view.
   a) In free view, press 'Spacebar' to go up, 'Ctrl' to go down.
6. Hold left mouse button to apply a force to the shooter.
7. Release mouse button to shoot.

Known Issues/ TO-DO List
============================
- Issue: SPH is slow, neighbors should be calculated in one go.
- Issue: Paint will sometimes go through the box walls because they move too fast.
- TODO: Blending of paint colors: (1-r1-r2, 1-g1-g2, 1-b1-b2)
- TODO: Make it so that paint colors only specific particles