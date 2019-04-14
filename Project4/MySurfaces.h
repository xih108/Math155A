#pragma once

// 
// MySurfaces.h   ---  Header file for MySurfaces.cpp.
// 
//   Sets up and renders 
//     - the ground plane, and
//     - the surface of rotation
//   for the Math 155A project #4.
//
//

//
// Function Prototypes
//
void MySetupSurfaces();             // Called once, before rendering begins.
void MyRemeshSurfaces();            // Called when mesh changes, must update resolutions.
void MyRemeshFloor();               // Update resolution of the ground plane
void MyRemeshCircularSurf();        // Update resolution of the surface of rotation.

void RemeshFloorDemo();             // Fixed size example of rendering the plane
void RemeshCircularDemo();          // Fixed size example of circular rendering

void MyRenderSurfaces();            // Called to render the two surfaces
void MyRenderFloor();               // Renders the meshed floor
void MyRenderCircularSurf();        // Renders the meshed circular surface

void RenderFloorDemo();             // Fixed size example of rendering the plane
void RenderCircularDemo();          // Fixed size example of circular rendering


