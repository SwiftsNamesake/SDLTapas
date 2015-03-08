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
void Draw::plane(GLenum primitive, size_t ia, size_t ib, size_t ic, GLColor color, float a, float b, float c, float da, float db) {

	// Draws a plane using the deprecated OpenGL immediate mode API
	//

	//SDL_Log("Drawing coloured plane.\n");

	float vertices[][3] = {{ a - da/2, b - db/2, c },
	                       { a + da/2, b - db/2, c },
	                       { a + da/2, b + db/2, c },
	                       { a - da/2, b + db/2, c }};

	glBegin(primitive);
	  glColor4f(color.r, color.g, color.b, color.a);  

	  glVertex3f(vertices[0][ia], vertices[0][ib], vertices[0][ic]);
	  glVertex3f(vertices[1][ia], vertices[1][ib], vertices[1][ic]);
	  glVertex3f(vertices[2][ia], vertices[2][ib], vertices[2][ic]);
	  glVertex3f(vertices[3][ia], vertices[3][ib], vertices[3][ic]);
	glEnd();

}


void Draw::plane(GLenum primitive, size_t ia, size_t ib, size_t ic, GLuint texture, float a, float b, float c, float da, float db) {

	// Draws a plane using the deprecated OpenGL immediate mode API
	//

	// TODO: Normals (?)

	//SDL_Log("Drawing textured plane.\n");

	// TODO: How are static variables that depend on function arguments treated?
	float vertices[][3] = {{ a - da/2, b - db/2, c },
	                       { a + da/2, b - db/2, c },
	                       { a + da/2, b + db/2, c },
	                       { a - da/2, b + db/2, c }};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(primitive);
	  glTexCoord2f(0.0f, 1.0f);
	  glVertex3f(vertices[0][ia], vertices[0][ib], vertices[0][ic]);

	  glTexCoord2f(1.0f, 1.0f);
	  glVertex3f(vertices[1][ia], vertices[1][ib], vertices[1][ic]);

	  glTexCoord2f(1.0f, 0.0f);
	  glVertex3f(vertices[2][ia], vertices[2][ib], vertices[2][ic]);

	  glTexCoord2f(0.0f, 0.0f);
	  glVertex3f(vertices[3][ia], vertices[3][ib], vertices[3][ic]);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}


// TODO: Make sure the indeces are correct (especially w.r.t. texture coordinates)
void Draw::planeXY(GLenum primitive, GLColor color, float dx, float dy) { plane(primitive, 0, 1, 2, color, 0.0f, 0.0f, 0.0f, dx, dy); }
void Draw::planeXZ(GLenum primitive, GLColor color, float dx, float dz) { plane(primitive, 0, 2, 1, color, 0.0f, 0.0f, 0.0f, dx, dz); }
void Draw::planeYZ(GLenum primitive, GLColor color, float dy, float dz) { plane(primitive, 2, 0, 1, color, 0.0f, 0.0f, 0.0f, dy, dz); }

void Draw::planeXY(GLenum primitive, GLuint texture, float dx, float dy) { plane(primitive, 0, 1, 2, texture, 0.0f, 0.0f, 0.0f, dx, dy); }
void Draw::planeXZ(GLenum primitive, GLuint texture, float dx, float dz) { plane(primitive, 0, 2, 1, texture, 0.0f, 0.0f, 0.0f, dx, dz); }
void Draw::planeYZ(GLenum primitive, GLuint texture, float dy, float dz) { plane(primitive, 2, 0, 1, texture, 0.0f, 0.0f, 0.0f, dy, dz); }


void Draw::cube(GLenum primitive, GLColor front, GLColor back, GLColor top, GLColor bottom, GLColor left, GLColor right, float dx, float dy, float dz) {

	// Renders a cube (or box) in immediate-mode
	// Should return a buffer instead.
	// TODO: Add colour, texture, alpha, etc.

	// No floating-point colour type?
	/*
	static SDL_Color front  = { 0,   0,   0,   255 };
	static SDL_Color back   = { 114, 0,   30,  255 };
	static SDL_Color left   = { 189, 130, 226, 255 };
	static SDL_Color right  = { 54,  160, 163, 255 };
	static SDL_Color top    = { 0,   137, 2,   255 };
	static SDL_Color bottom = { 7,   229, 242, 255 };
	*/

	//glBegin(primitive);

	// plane XY
	plane(primitive, 0, 1, 2, front, 0.0f, 0.0f,  dz/2, dx, dy); // Front
	plane(primitive, 0, 1, 2, back,  0.0f, 0.0f, -dz/2, dx, dy); // Back

	// plane XZ
	plane(primitive, 0, 2, 1, top,    0.0f, 0.0f,  dy/2, dx, dz); // Top
	plane(primitive, 0, 2, 1, bottom, 0.0f, 0.0f, -dy/2, dx, dz); // Bottom

	// Plane YZ
	plane(primitive, 2, 0, 1, left,  0.0f, 0.0f, -dz/2, dy, dz); // Left
	plane(primitive, 2, 0, 1, right, 0.0f, 0.0f,  dz/2, dy, dz); // Right

	//glEnd();

}


void Draw::cube(GLenum primitive, GLuint front, GLuint back, GLuint top, GLuint bottom, GLuint left, GLuint right, float dx, float dy, float dz) {

	//

	// plane XY
	plane(primitive, 0, 1, 2, front, 0.0f, 0.0f, dz/2, dx, dy); // Front
	plane(primitive, 0, 1, 2, back, 0.0f, 0.0f, -dz/2, dx, dy); // Back

	// plane XZ
	plane(primitive, 0, 2, 1, top, 0.0f, 0.0f, dy/2, dx, dz); // Top
	plane(primitive, 0, 2, 1, bottom, 0.0f, 0.0f, -dy/2, dx, dz); // Bottom

	// Plane YZ
	plane(primitive, 2, 0, 1, left, 0.0f, 0.0f, -dz/2, dy, dz); // Left
	plane(primitive, 2, 0, 1, right, 0.0f, 0.0f, dz/2, dy, dz); // Right


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


void Draw::cylinder(GLenum primitive, GLColor color, float radius, float height) {
	
	//
	const int segments = 18;
	float theta  = 360.0f / segments;
	
	glBegin(primitive);
	
	for (int segment = 0; segment <= segments; ++segment) {
		//
		float x = radius*cosine(theta*segment), z = radius*sine(theta*segment);
		glColor4f(color.r, color.g, color.b, color.a);
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


void Draw::spiral(GLenum primitive, GLColor color, float radius, float dy, float inclination, float revolutions) {

	// Renders a one-dimensional spiral
	// TODO: Come up with a better name for dy/revolution (height) (done; cf. inclination)

	int segments = 18;           // Segments per revolution
	float delta  = 360.0f/segments; // Internal angle of a single segment

	glBegin(primitive);
	
	for (int segment = 0; segment <= segments * revolutions; ++segment) {
		float y = inclination * segment/segments;
		glColor4f(color.r, color.g, color.b, color.a); // TODO: Function for SDL_Color
		glVertex3f(radius*cosine(segment*delta), y,    radius*sine(segment*delta));
		glVertex3f(radius*cosine(segment*delta), y+dy, radius*sine(segment*delta));
	}

	glEnd();

}