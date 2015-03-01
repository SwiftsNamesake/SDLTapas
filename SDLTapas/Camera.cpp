/*
 * Camera.cpp
 *
 * See header for more information
 *
 */



//-----------------------------------------------------------------------------------------------------------
// We'll need these
//-----------------------------------------------------------------------------------------------------------
#include <SDL/SDL_opengl.h>
#include "Camera.h"



//-----------------------------------------------------------------------------------------------------------
// Classes
//-----------------------------------------------------------------------------------------------------------
//struct Camera::Camera {
//	// TODO: Rename fields, use vectors (?)
//	float rX = 0.0f, rY = 0.0f, rZ = 0.0f; // Rotation
//	float X = 0.0f, Y = 0.0f, Z = 0.0f;    // Translation
//};



//-----------------------------------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------------------------------
void Camera::aim(const Camera& camera) {

	// Namespace members seem to be directly accessible in the parameter declaration

	//
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Camera
	glTranslatef(camera.X, camera.Y, camera.Z);
	glRotatef(camera.rX, 1.0f, 0.0f, 0.0f);
	glRotatef(camera.rY, 0.0f, 1.0f, 0.0f);
	glRotatef(camera.rZ, 0.0f, 0.0f, 1.0f);

}


void Camera::look(Camera& camera, View view, float distance) {

	// Perpendicular and parallel directions
	// Make the camera look in a specific direction (towards view), at a given distance from the origin
	// TODO: Think carefully about the coordinate system and the effect of chaining transformations
	// TODO: Make sure the up-direction is still +Y

	// NOTE: Angles are in degrees
	// NOTE: Rotations are counter-clockwise
	// NOTE: The camera starts off looking in the negative Z direction (+Y is up, +X is right, -Z is forwards)

	// This function is still buggy

	camera.rX = 0.0f;
	camera.rY = 0.0f;
	camera.rZ = 0.0f;

	camera.X = 0.0f;
	camera.Y = 0.0f;
	camera.Z = 0.0f;

	if (view == FRONT) {
		camera.Z  = -distance;
		camera.rY =  180.0f;
	} else if (view == BACK) {
		camera.Z  = distance;
		camera.rY = 0.0f;
	} else if (view == UP) {
		camera.Y  = -distance;
		camera.rZ =  90.0f;
	} else if (view == DOWN) {
		camera.Y  = distance;
		camera.rZ = 270.0f;
	} else if (view == LEFT) {
		camera.X  = distance;
		camera.rY = 90.0f;
	} else if (view == RIGHT) {
		camera.X  = -distance;
		camera.rY =  270.0f;
	}

}