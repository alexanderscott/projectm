/*
 * RovastarFractopiaFrantic.hpp
 *
 *  Created on: Jun 18, 2008
 *      Author: pete
 */

#include "Pipeline.hpp"
#include "math.h"
#include "MilkdropCompatability.hpp"
#include <stdlib.h>


class RovastarDriftingChaos : public Pipeline
{
public:

	Delta delta;
	PerPixelZoom zoom;
	Rotation rotate;
	Shape shape1, shape2, shape3;

	RovastarDriftingChaos(int mesh_x, int mesh_y) : Pipeline(mesh_x, mesh_y),
		delta(mesh_x,mesh_y,0,0),
		rotate(mesh_x,mesh_y,0.5,0.5,0),
		zoom(mesh_x, mesh_y, 1, 1)
	{
		screenDecay = 1.0;
		textureWrap = 0;

		videoEchoOrientation = 0;
		videoEchoZoom = 1.0;
		videoEchoAlpha = 1.0;

		drawables.push_back(&shape1);
		drawables.push_back(&shape2);
		drawables.push_back(&shape3);

		perPixelTransforms.push_back(&zoom);
		perPixelTransforms.push_back(&delta);
		perPixelTransforms.push_back(&rotate);


		shape1.sides = 3;
		shape1.radius=0.550000;
		shape1.a = 0.1;
		shape1.a2 = 0.9;
		shape1.border_r = 1.0;
		shape1.border_g = 1.0;
		shape1.border_b = 1.0;
		shape1.border_a = 0.2;

		shape2.sides = 32;
		shape2.radius=0.40000;
		shape2.a = 1.0;
		shape2.a2 = 0.3;
		shape2.border_r = 1.0;
		shape2.border_g = 1.0;
		shape2.border_b = 1.0;
		shape2.border_a = 0.2;

		shape3.sides = 4;
		shape3.radius=0.40000;
		shape3.a = 0.6;
		shape3.a2 = 0.4;
		shape3.border_r = 1.0;
		shape3.border_g = 1.0;
		shape3.border_b = 1.0;
		shape3.border_a = 0.2;

	}

	float xamptarg, q8, oldq8, q7, xpos, ypos,xdir, xspeed, xamp, yamp, yamptarg,yspeed,ydir;

	virtual void Render()
	{

		float volume = 0.15*(bass+bass_att+treb+treb_att+mid+mid_att);

		xamptarg = if_milk(equal(frame%15,0),min(0.5*volume*bass_att,0.5),xamptarg);
		xamp = xamp + 0.5*(xamptarg-xamp);

		xdir = if_milk(above(abs(xpos),xamp),-sign(xpos),if_milk(below(abs(xspeed),0.1),2*above(xpos,0)-1,xdir));
		float xaccel =  xdir*xamp - xpos - xspeed*0.055*below(abs(xpos),xamp);
		xspeed += xdir*xamp - xpos - xspeed*0.055*below(abs(xpos),xamp);
		xpos = xpos + 0.001*xspeed;
		delta.dx = xpos*0.005;
		yamptarg = if_milk(equal(frame%15,0),min(0.3*volume*treb_att,0.5),yamptarg);
		yamp +=  0.5*(yamptarg-yamp);
		ydir = if_milk(above(abs(ypos),yamp),-sign(ypos),if_milk(below(abs(yspeed),0.1),2*above(ypos,0)-1,ydir));

		float yaccel = ydir*yamp - ypos - yspeed*0.055*below(abs(ypos),yamp);
		yspeed += ydir*yamp - ypos - yspeed*0.055*below(abs(ypos),yamp);
		ypos = ypos + 0.001*yspeed;

		delta.dy = ypos*0.005;
		rotate.angle = 10*(delta.dx-delta.dy);

		q8 =oldq8+ 0.0003*(powf(1+1.2*bass+0.4*bass_att+0.1*treb+0.1*treb_att+0.1*mid+0.1*mid_att,6)/fps);
		oldq8 = q8;
		q7 = 0.003*(powf(1+1.2*bass+0.4*bass_att+0.1*treb+0.1*treb_att+0.1*mid+0.1*mid_att,6)/fps);

		shape1.ang = time*1.4;
				shape1.x = 0.5 + 0.08*cos(time*1.3) + 0.03*cos(time*0.7);
				shape1.y = 0.5 + 0.08*sin(time*1.4) + 0.03*sin(time*0.7);
				shape1.r = 0.5 + 0.5*sin(q8*0.613 + 1);
				shape1.g = 0.5 + 0.5*sin(q8*0.763 + 2);
				shape1.b = 0.5 + 0.5*sin(q8*0.771 + 5);
				shape1.r2 = 0.5 + 0.5*sin(q8*0.635 + 4);
				shape1.g2 = 0.5 + 0.5*sin(q8*0.616+ 1);
				shape1.b2 = 0.5 + 0.5*sin(q8*0.538 + 3);

				shape2.ang = time*1.7;
				shape2.x = 0.5 + 0.08*cos(time*1.1) + 0.03*cos(time*0.7);
				shape2.y = 0.5 + 0.08*sin(time*1.1) + 0.03*sin(time*0.7);
				shape2.r = 0.5 + 0.5*sin(q8*0.713 + 1);
				shape2.g = 0.5 + 0.5*sin(q8*0.563 + 2);
				shape2.b = 0.5 + 0.5*sin(q8*0.654 + 5);
				shape2.r2 = 0.5 + 0.5*sin(q8*0.885 + 4);
				shape2.g2 = 0.5 + 0.5*sin(q8*0.556+ 1);
				shape2.b2 = 0.5 + 0.5*sin(q8*0.638 + 3);

				shape3.ang = time*1.24;
				shape3.x = 0.5 - 0.08*cos(time*1.07) + 0.03*cos(time*0.7);
				shape3.y = 0.5 - 0.08*sin(time*1.33) + 0.03*sin(time*0.7);
				shape3.g = 0.5 + 0.5*sin(q8*0.713 + 1);
				shape3.b = 0.5 + 0.5*cos(q8*0.563 + 2);
				shape3.r = 0.5 + 0.5*sin(q8*0.654 + 5);
				shape3.r2 = 0.5 + 0.5*cos(q8*0.885 + 4);
				shape3.g2 = 0.5 + 0.5*cos(q8*0.556+ 1);
				shape3.b2 = 0.5 + 0.5*sin(q8*0.638 + 3);


		for (int x = 0; x < mesh_x; x++)
			for (int y = 0; y < mesh_y; y++)
			{
				float xval=x/(float)(mesh_x-1);
				float yval=-((y/(float)(mesh_y-1))-1);

				float rad=hypot ( ( xval-.5 ) *2, ( yval-.5 ) *2 ) * .7071067;
				zoom.zoom[x][y] = 1+0.05*rad;
			}
	}

};