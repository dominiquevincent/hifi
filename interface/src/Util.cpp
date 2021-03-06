//
//  util.cpp
//  interface
//
//  Created by Philip Rosedale on 8/24/12.
//  Copyright (c) 2012 High Fidelity, Inc. All rights reserved.
//

#include "InterfaceConfig.h"
#include <iostream>
#include <glm/glm.hpp>
#include <cstring>
#include "world.h"
#include "Util.h"

//  Return the azimuth angle in degrees between two points.
float azimuth_to(glm::vec3 head_pos, glm::vec3 source_pos) {
    return atan2(head_pos.x - source_pos.x, head_pos.z - source_pos.z) * 180.0f / PIf;
}

//  Return the angle in degrees between the head and an object in the scene.  The value is zero if you are looking right at it.  The angle is negative if the object is to your right.   
float angle_to(glm::vec3 head_pos, glm::vec3 source_pos, float render_yaw, float head_yaw) {
    return atan2(head_pos.x - source_pos.x, head_pos.z - source_pos.z) * 180.0f / PIf + render_yaw + head_yaw;
}

void render_vector(glm::vec3 * vec)
{
    //  Show edge of world 
    glDisable(GL_LIGHTING);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    //  Draw axes
    glColor3f(1,0,0);
    glVertex3f(-1,0,0);
    glVertex3f(1,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,-1,0);
    glVertex3f(0, 1, 0);
    glColor3f(0,0,1);
    glVertex3f(0,0,-1);
    glVertex3f(0, 0, 1);
    // Draw vector
    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    glVertex3f(vec->x, vec->y, vec->z);
    // Draw marker dots for magnitude    
    glEnd();
    float particle_attenuation_quadratic[] =  { 0.0f, 0.0f, 2.0f }; // larger Z = smaller particles

    glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, particle_attenuation_quadratic );
    
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(vec->x,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,vec->y,0);
    glColor3f(0,0,1);
    glVertex3f(0,0,vec->z);
    glEnd();

}

void render_world_box()
{
    //  Show edge of world 
    glDisable(GL_LIGHTING);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(WORLD_SIZE,0,0);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0, WORLD_SIZE, 0);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0, 0, WORLD_SIZE);
    glEnd();
}

double diffclock(timeval *clock1,timeval *clock2)
{
	double diffms = (clock2->tv_sec - clock1->tv_sec) * 1000.0;
    diffms += (clock2->tv_usec - clock1->tv_usec) / 1000.0;   // us to ms
    
	return diffms;
}

void drawtext(int x, int y, float scale, float rotate, float thick, int mono,
              char const* string, float r, float g, float b)
{
    //
    //  Draws text on screen as stroked so it can be resized
    //
    int len, i;
    glPushMatrix();
    glTranslatef( static_cast<float>(x), static_cast<float>(y), 0.0f);
    glColor3f(r,g,b);
    glRotated(180+rotate,0,0,1);
    glRotated(180,0,1,0);
    glLineWidth(thick);
    glScalef(scale, scale, 1.0);
    len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
        if (!mono) glutStrokeCharacter(GLUT_STROKE_ROMAN, int(string[i]));
        else glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, int(string[i]));
	}
    glPopMatrix();

}


void drawvec3(int x, int y, float scale, float rotate, float thick, int mono, glm::vec3 vec, 
              float r, float g, float b)
{
    //
    //  Draws text on screen as stroked so it can be resized
    //
    char vectext[20];
    sprintf(vectext,"%3.1f,%3.1f,%3.1f", vec.x, vec.y, vec.z);
    int len, i;
    glPushMatrix();
    glTranslatef(static_cast<float>(x), static_cast<float>(y), 0);
    glColor3f(r,g,b);
    glRotated(180+rotate,0,0,1);
    glRotated(180,0,1,0);
    glLineWidth(thick);
    glScalef(scale, scale, 1.0);
    len = (int) strlen(vectext);
	for (i = 0; i < len; i++)
	{
        if (!mono) glutStrokeCharacter(GLUT_STROKE_ROMAN, int(vectext[i]));
        else glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, int(vectext[i]));
	}
    glPopMatrix();
    
} 
