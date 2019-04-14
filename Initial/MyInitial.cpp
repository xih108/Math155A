//
//  MyInitial.cpp
//
//   Sets up and renders the initial (alphabet letter)
//   for the Math 155A project.
//
//   Comes supplied with some code for a growing and shrinking
//      cylinder and a revolving ellipsoid.
//
//  THIS FILE IS WHAT YOU WILL MODIFY FOR PROJECT #3.
//  IT WILL ALSO BE USED FOR PROJECTS #4 and #5.
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust paths as needed.
#include "LinearR4.h"		
#include "GlGeomSphere.h"
#include "GlGeomCylinder.h"

// Enable standard input and output via printf(), etc.
// Put this include *after* the includes for glew and GLFW!
#include <stdio.h>

#include "MyInitial.h"
#include "LetterProj.h"
//#include "SurfaceProj.h"      // Replace previous line with this line for Project #4

// ***********
// Animation Controls.  
//     Optional: you may customize these for Project #3.
// ***********

// YOU MAY WISH TO RE-DO THIS FOR YOUR CUSTOM ANIMATION.  
double animateIncrement = 0.005;   // Make bigger to speed up animation, smaller to slow it down.
double currentTime = 0.0;         // Current "time" for the animation.
double maxTime = 1.0;             // Time cycles back to 0 after reaching maxTime

// These two variables control whether running or paused.
//  IT IS OPTIONAL TO INCLUDE THIS FUNCTIONALITY IN YOUR PROGRAMMING ASSIGNMENT
bool spinMode = true;
bool singleStep = false;


// These objects take care of generating and loading VAO's, VBO's and EBO's,
//    rendering ellipsoids and cylinders
GlGeomSphere unitSphere;
GlGeomCylinder unitCylinder;

// **********************
// This sets up a sphere and a cylinder needed for the "Initial" (the 3-D alphabet letter)
//  This routine is called only once, for the first initialization.
// **********************
void MySetupInitialGeometries() {
    // Initialize the sphere and cylinder, and give them the vertPos, vertNormal, and vertTexCoords locations.
    MyRemeshGeometries();
    unitSphere.InitializeAttribLocations(vPos_loc,vNormal_loc,vTexcoords_loc);
    unitCylinder.InitializeAttribLocations(vPos_loc, vNormal_loc, vTexcoords_loc);

    check_for_opengl_errors();
}

// *********************
// This is called when geometric shapes are initialized.
// And is called again whenever the mesh resolution changes.
// ********************
void MyRemeshGeometries() {
    unitSphere.Remesh(meshRes, meshRes);              // Number of slices and stacks both set to meshRes
    unitCylinder.Remesh(meshRes, meshRes, meshRes);   // Number of slices, stacks and rings all set to meshRes
}

// *************************************
// Render the initial (3D alphabet letter)
// THIS CODE IS THE CORE PART TO RE_WRITE FOR YOUR 155A PROJECT
// ************
void MyRenderInitial() {
    // Compute the "currentTime" for the animation.
    //    As initially implemented, CurrentTime goes from 0.0 to 1.0, and then back to 0.0
    //    THIS IS SPECIFIC TO THE ANIMATION IN THE DEMO.
    //    FOR PROJECT 3 YOU MAY DO SOMETHING DIFFERENT, FOR INSTANCE, SIMILAR TO WHAT SolarProg.cpp DID.
    //  
    if (spinMode) {
        currentTime += animateIncrement;
        if (currentTime >= maxTime) {
            currentTime = currentTime - floor(currentTime/maxTime);  // Floor function = round down to nearest integer
		}
        if (singleStep) {
            spinMode = false;       // If in single step mode, turn off future animation
        }
    }

    // Render the letter "X" (Sam's initial) with two cylinders,
    //    Plus a revolving ellip soid.
   
    // Setup the main Model view matrix
	LinearMapR4 mat1 = viewMatrix;
	mat1.Mult_glTranslate(-2.5, 0.0, -2.5);   // Center of front right quadrant of ground plane
	
	LinearMapR4 mat2 = mat1;
	double revolve = currentTime * PI2;
	mat2.Mult_glTranslate(-1.5, 6, 0.0);
	mat2.Mult_glTranslate(0.0,  - (1-currentTime) * 2.7 , 0.0);   // Position cylinder 
	mat2.Mult_glRotate(revolve, 0.0, 1.0, 0.0);
	mat2.Mult_glScale(0.5, (1 - currentTime) * 2.7, 0.5);     // It is a very flat cylinder
	mat2.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.0f);    
	unitCylinder.Render();

	LinearMapR4 low1 = mat1;
	low1.Mult_glTranslate(-1.5, currentTime*2.7, 0.0);   // Position cylinder 
	low1.Mult_glRotate(revolve, 0.0, 1.0, 0.0);
	low1.Mult_glScale(0.5, currentTime*2.7, 0.5);     // It is a very flat cylinder
	low1.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.0f);
	unitCylinder.Render();

	LinearMapR4 horizontal = mat1;
	double rotateangle = currentTime * PI;
	horizontal.Mult_glTranslate(0.0, 3.0, 0.0);
	horizontal.Mult_glRotate(PI / 2, 0.0, 0.0, 1.0);
	horizontal.Mult_glScale(0.1+0.4*currentTime, 1, 0.1+0.4*currentTime);
	horizontal.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	glVertexAttrib3f(vColor_loc, 1.0f, 0.5f, 0.0f);     // Make the cylinder magenta-ish
	unitCylinder.Render();


	LinearMapR4 mat4 = mat1;                               // Back to the main Modelview matrix
	mat4.Mult_glTranslate(-1.5, 0.3, 0);
	mat4.Mult_glTranslate(0.0 , currentTime*5.4, 0.0);  // Rotate 30 degrees
	mat4.Mult_glScale(0.5, 0.3, 0.5);          // Scale the cylinder, to thiner, flater and taller 
	glVertexAttrib3f(vColor_loc, 0.6f, 0.4f, 1.0f);
	mat4.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	unitCylinder.Render();


	LinearMapR4 mat3 = mat1;
	mat3.Mult_glTranslate(1.5, 6,0.0);
	mat3.Mult_glTranslate(0.0, -currentTime*2.7, 0.0);
	mat3.Mult_glRotate(revolve, 0.0, -1.0, 0.0);
	mat3.Mult_glScale(0.5, currentTime*2.7, 0.5);
	mat3.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.0f);
	unitCylinder.Render();

	LinearMapR4 low2 = mat1;
	low2.Mult_glTranslate(1.5, (1-currentTime)*2.7, 0.0);   // Position cylinder 
	low2.Mult_glRotate(revolve, 0.0, 1.0, 0.0);
	low2.Mult_glScale(0.5, (1-currentTime)*2.7, 0.5);     // It is a very flat cylinder
	low2.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.0f);
	unitCylinder.Render();


	LinearMapR4 mat5 = mat1;                               // Back to the main Modelview matrix
	mat5.Mult_glTranslate(1.5, 5.7, 0);
	mat5.Mult_glTranslate(0.0, -currentTime*5.4, 0.0);  // Rotate 30 degrees
	mat5.Mult_glScale(0.5, 0.3, 0.5);          // Scale the cylinder, to thiner, flater and taller 
	glVertexAttrib3f(vColor_loc, 0.6f, 0.4f, 1.0f);
	mat5.DumpByColumns(matEntries);
	glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
	unitCylinder.Render();
    

}








