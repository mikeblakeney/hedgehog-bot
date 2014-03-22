#ifndef ADDRTYPES_H
#define ADDRTYPES_H

struct state_t {
	float x;
	float y;
	float theta;
};

struct diff_velocity
{
	float left;
	float right;
};

struct uni_velocity
{
	float v;
	float w;
};

enum wheel_direction {FORWARD, BACKWARD};

#endif
