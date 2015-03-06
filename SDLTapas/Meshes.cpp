/*
* Meshes.cpp
*
* See header for more information
*
*/



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#include "Meshes.h"
#include "Utilities.h"

using namespace Utilities;



//-----------------------------------------------------------------------------------------------------------
// Geometry
//-----------------------------------------------------------------------------------------------------------
void Draw::cube(GLenum primitive, float dx, float dy, float dz) {

	// Renders a cube (or box) in immediate-mode
	// Should return a buffer instead.
	// TODO: Add colour, texture, alpha, etc.

	// No floating-point colour type?
	float front[]  = { 0.0f,   0.0f,  0.0f },
	      back[]   = { 0.45f,  0.0f,  0.12f },
		  left[]   = { 0.743f, 0.51f, 0.89f },
		  right[]  = { 0.215f, 0.63f, 0.64f },
		  top[]    = { 0.0f,   0.54f, 0.01f },
		  bottom[] = { 0.03f,  0.9f,  0.95f };

	// Front
	glBegin(primitive);
	  glColor3f(front[0], front[1], front[2]);
	  glNormal3d(0.0, 0.0, 1.0);

	  glVertex3f(-dx/2,  dy/2, dz/2);
	  glVertex3f( dx/2,  dy/2, dz/2);
	  glVertex3f( dx/2, -dy/2, dz/2);
	  glVertex3f(-dx/2, -dy/2, dz/2);
	glEnd();

	// Back
	glBegin(primitive);
	  glColor3f(back[0], back[1], back[2]);
	  glNormal3d(0.0, 0.0, -1.0);

	  glVertex3f(-dx/2,  dy/2, -dz/2);
	  glVertex3f( dx/2,  dy/2, -dz/2);
	  glVertex3f( dx/2, -dy/2, -dz/2);
	  glVertex3f(-dx/2, -dy/2, -dz/2);
	glEnd();

	// Left
	glBegin(primitive);
	  glColor3f(left[0], left[1], left[2]);
	  glNormal3d(-1.0, 0.0, 0.0);

	  glVertex3f(-dx/2,  dy/2,  dz/2);
	  glVertex3f(-dx/2,  dy/2, -dz/2);
	  glVertex3f(-dx/2, -dy/2, -dz/2);
	  glVertex3f(-dx/2, -dy/2,  dz/2);
	glEnd();

	// Right
	glBegin(primitive);
	  glColor3f(right[0], right[1], right[2]);
	  glNormal3d(1.0, 0.0, 0.0);

	  glVertex3f(dx/2,  dy/2,  dz/2);
	  glVertex3f(dx/2,  dy/2, -dz/2);
	  glVertex3f(dx/2, -dy/2, -dz/2);
	  glVertex3f(dx/2, -dy/2,  dz/2);
	glEnd();

	// Top
	glBegin(primitive);
	  glColor3f(top[0], top[1], top[2]);
	  glNormal3d(0.0, 1.0, 1.0);

	  glVertex3f(-dx/2, dy/2, -dz/2);
	  glVertex3f(-dx/2, dy/2,  dz/2);
	  glVertex3f( dx/2, dy/2,  dz/2);
	  glVertex3f( dx/2, dy/2, -dz/2);
	glEnd();

	// Bottom
	glBegin(primitive);
	  glColor3f(bottom[0], bottom[1], bottom[2]);
	  glNormal3d(0.0, -1.0, 0.0);

	  glVertex3f(-dx/2, -dy/2, -dz/2);
	  glVertex3f(-dx/2, -dy/2,  dz/2);
	  glVertex3f( dx/2, -dy/2,  dz/2);
	  glVertex3f( dx/2, -dy/2, -dz/2);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}


void Draw::sphere(GLenum primitive, float radius) {

	//
	using namespace Utilities;

	//
	// TODO: Normals
	// TODO: Spheroids and partial spheres
	// TODO: Texture and colours
	// TODO: Shading
	// TODO: Plenty of room for optimisation (eg. unit sphere + scaling, using indices, etc.)
	// TODO: Abandon legacy APIs (ie. immediate mode; cf. related TODO item)
	const float resolution = 5.0f;        // TODO: Better name (?)
	const float dx = radius / resolution; // The distance between adjacent circles

	// TODO: Use the same number of longitudinal and latitudinal segments (?)
	const int segments = 18;             // For now. Juicy, delicious segments.
	const float angle = 360.0f/segments; // Internal angle of a segment (degrees)

	float radiusLeft  = sqrt(radius*radius);         // Radius of the left-hand circle
	float radiusRight = sqrt(radius*radius - dx*dx); // Radius of the right-hand circle

	// TODO: Modify dx so that the vertices are more evenly spaced along the surface of the sphere
	/*
	for (float x = -radius; x < radius; x += dx) {

	//
	radiusLeft  = sqrt(radius*radius - x*x);
	radiusRight = sqrt(radius*radius - (x+dx)*(x+dx));

	static GLenum primitives[] = { GL_TRIANGLE_STRIP, GL_LINE_STRIP };

	glBegin(primitives[Events::primitiveIndex]);
	glColor3f(static_cast<int>((radius + x)/dx)%2, 0.0f, static_cast<int>(1 + (radius + x)/dx)%2);
	for (int segment = 0; segment <= segments; ++segment) {
	glVertex3f(x,    radiusLeft  * sine(segment*angle),  radiusLeft  * cosine(segment*angle));
	glVertex3f(x+dx, radiusRight * sine(segment*angle),  radiusRight * cosine(segment*angle));
	}
	glEnd();

	}
	*/

	const float dTheta = 180.0f/segments;

	for (int xSegment = 0; xSegment <= segments; ++xSegment) {

		//
		float theta = xSegment * dTheta;
		float rightX = radius * cosine(theta);
		float leftX = radius * cosine(theta+dTheta);

		radiusLeft = sqrt(radius*radius - leftX*leftX);
		radiusRight = sqrt(radius*radius - rightX*rightX);


		glBegin(primitive);
		
		glColor3f(static_cast<float>(static_cast<int>((radius + leftX)/dx)%2), 0.0f, static_cast<float>(static_cast<int>(1 + (radius + leftX)/dx)%2));
		for (int segment = 0; segment <= segments; ++segment) {
			glVertex3f(leftX, radiusLeft  * sine(segment*angle), radiusLeft  * cosine(segment*angle));
			glVertex3f(rightX, radiusRight * sine(segment*angle), radiusRight * cosine(segment*angle));
		}

		glEnd();

	}

}


void Draw::grid(float length) {

	//
	// TODO: General-purpose (no hard-coding)
	// Semi-transparent planes
	// Actual grid (rather than just axes)

	glBegin(GL_LINES);
	// X-axis (red)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-length, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);

	// Y-axis (green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -length, 0.0f);
	glVertex3f(0.0f, length, 0.0f);

	// Z-axis (blue)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -length);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();

}


void Draw::cylinder(GLenum primitive, float radius, float height) {
	
	//
	const int segments = 18;
	float theta  = 360.0f / segments;
	
	glBegin(primitive);
	
	for (int segment = 0; segment <= segments; ++segment) {
		//
		float x = radius*cosine(theta*segment), z = radius*sine(theta*segment);
		glColor3f(0.2f, 0.35f, 0.65f);
		glVertex3f(x, -height/2, z);
		glVertex3f(x,  height/2, z);
	}

	glEnd();

}


void Draw::cone(GLenum primitive, float radius, float height) {

	//
	int segments = 18;
	float theta = 360.0f / segments;

	glBegin(primitive);

	for (int segment = 0; segment <= segments; ++segment) {
		glColor3f(0.2f, 0.35f, 0.65f);
		glVertex3f(radius*cosine(theta*segment), -height/2, radius*sine(theta*segment));
		glVertex3f(0.0f,                          height/2, 0.0f);
	}

	glEnd();

}


void Draw::pyramid(GLenum primitive, float dx, float dz, float height) {

	//
	static float colours[][3] = {{ 0.0f,   0.0f,  0.0f },
	                             { 0.45f,  0.0f,  0.12f },
		                         { 0.743f, 0.51f, 0.89f },
		                         { 0.215f, 0.63f, 0.64f },
		                         { 0.0f,   0.54f, 0.01f }};


	glBegin(primitive);
	  glColor3f(colours[0][0], colours[0][1], colours[0][2]);

	  glVertex3f(-dx/2, -height/2, dz/2);
	  glVertex3f( dx/2, -height/2, dz/2);
	  glVertex3f( 0.0f,  height/2, 0.0f);
	glEnd();


	glBegin(primitive);
	  glColor3f(colours[1][0], colours[1][1], colours[1][2]);

	  glVertex3f(-dx/2, -height/2, -dz/2);
	  glVertex3f( dx/2, -height/2, -dz/2);
	  glVertex3f( 0.0f,  height/2,  0.0f);
	glEnd();


	glBegin(primitive);
	  glColor3f(colours[2][0], colours[2][1], colours[2][2]);

	  glVertex3f(-dx/2, -height/2, -dz/2);
	  glVertex3f(-dx/2, -height/2,  dz/2);
	  glVertex3f( 0.0f,  height/2,  0.0f);
	glEnd();


	glBegin(primitive);
	  glColor3f(colours[3][0], colours[3][1], colours[3][2]);

	  glVertex3f(dx/2, -height/2, -dz/2);
	  glVertex3f(dx/2, -height/2,  dz/2);
	  glVertex3f(0.0f,  height/2,  0.0f);
	glEnd();


	//
	glBegin(GL_QUADS);
	  glColor3f(colours[4][0], colours[4][1], colours[4][2]);

	  glVertex3f(-dx/2, -height/2, -dz/2);
	  glVertex3f( dx/2, -height/2, -dz/2);
	  glVertex3f( dx/2, -height/2,  dz/2);
	  glVertex3f(-dx/2, -height/2,  dz/2);
	glEnd();


}


void Draw::spiral(GLenum primitive, float radius, float height, float revolutions) {

	// Renders a one-dimensional spiral
	// TODO: Come up with a better name for dy/revolution (height)

	int segments = 18;           // Segments per revolution
	float delta  = 360/segments; // Internal angle of a single segment

	glBegin(primitive);
	
	for (int segment = 0; segment <= segments * revolutions; ++segment) {
		float dy = height * segment/segments;
		glColor3f(0.00f, 0.30f, 0.45f);
		glVertex3f(cosine(segment*delta), dy, sine(segment*delta));
	}

	glEnd();

}