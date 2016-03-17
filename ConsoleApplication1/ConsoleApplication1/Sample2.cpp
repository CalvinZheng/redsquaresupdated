// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4446E194_24C7_420A_85E4_E0E52DC5FF93__INCLUDED_)
#define AFX_STDAFX_H__4446E194_24C7_420A_85E4_E0E52DC5FF93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream>
#include <algorithm>
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


#ifdef _WIN32 
#include <windows.h>
#include <stdio.h>		// printf
#include <string.h>		// string handling
#include <stdlib.h>		// exit() function
#include <time.h>		// needed for time functions
#include <conio.h>
#include <cstdio>
#include <string>
#include <math.h> //by me
#endif
#include <math.h> //by me
#ifdef LINUX
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>   
#include <memory.h>
#include <time.h>
#include <sys/types.h>
#endif

#ifdef MAC
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4446E194_24C7_420A_85E4_E0E52DC5FF93__INCLUDED_)

#include <glew.h>
#include <ATC3DG.h>
#include <Bird.h>
#include "GLUT/glut.h"  
#include <iostream>
using namespace std;
string fileOutput;
#include <glfw3.h>
#include "stereoproj.c"

#define TIME_BETWEEN_CASES				1		//60=>1s // 120 => 1s
#define OCLUDE_COS_THRESH				0.9999

double EYE_OFFSET = 15;

float randomChoiceTimer = 0;
double averageReds[2], peakReds[2], averageRedsCounter[2];

unsigned char *frameBuffer;

#define DRAW_SIDE_PLANES				1
#define GAMMA_CORRECTION				2
double RANDOM_CHOICE_TIMER = 4 + TIME_BETWEEN_CASES; //3d frames (3s)	
#define DIST_THRESH						25

#define DEMO_MODE					0
static bool paused = false;

//#define IOD								65//64.7   70
/*#define CUBE_OFFSET						140.0
#define CUBE_SIZE_RANGE					50.0
#define CUBE_SIZE_AVERAGE				80.0
#define CUBE_SIZE_LEVELS				3.0
#define CUBE_FRONT_DEPTH_RANGE			0.0
#define CUBE_FRONT_DEPTH_AVERAGE		0.0
//#define CUBE_DEPTH_DIFF_RANGE			0.0
#define CUBE_DEPTH_DIFF_AVERAGE			3//100.0

//#define CUBE_LOW_DEPTH_THRESH			10.0

double rotations[3] = { 10, 45, 90 };
//#define CUBE_ROTATION_RANGE				25
#define CUBE_ROTATION_RATE				1		//means every n frames it will rotate by 1 degree
*/

#define PROJECTION_ADJUSTMENT_AVERAGE	1//0.55
#define PROJECTION_ADJUSTMENT_RANGE		0.0//3
#define TYPE_STEREO						0
#define TYPE_TRACKER					1
#define TYPE_ROTATE						2
#define NO_TRACKING_DISTANCE			624.0 //800.0//350.
#define NO_TRACKING_HEIGHT				0.0
#define EYE_OFFSET_RATIO				0.25
#define FixedLevels						true
#define LINE_WIDTH						5.0
//#define SLIDER_SENSITIVITY				2.2
#define TRACKING_ACCEPTABLE_RANGE_X		300.0
#define TRACKING_ACCEPTABLE_RANGE_Y		300.0
#define TRACKING_CLOSE_Z				500 //300
#define TRACKING_FAR_Z					800 //900
#define BEGINING_DELAY					60
#define TILT_THRESH 1200	
#define ROTATE_ALL_POINTS 0 //(-15*PI/180)	
#define STEP_DECREASE 1	
#define STEP_DOWN_UP_RATIO 0.2845	
#define STEP_INITIAL 0.5 //5	
#define EXIT_CONDITION 14 //10 //14	
#define N_LAST_REVERSALS 6
#define INIT_DEPTH_DIFFERENCE 7
#define BLOCK_BEGINNING 1
#define sizeRange 0.8
#define DEPTH_WARP_INTENSITY 2
#define DEPTH_WARP_MID 1
#define MAX_DEPTH_DIFF 100
#define SCALE_FOR_LOG 0.8

bool disabled, tooFar, tilted, not_moving, rest, randomChoiceFlag = false, answer = false;
static int block_beginning = 0;
double IOD = 65;
int mcount = 0;

ofstream fout, fout2, fout3, fout4;
ofstream out;

pair<int, int> resolution(1920, 1080);

#define SCREEN_ASPECT_RATIO 1.7778    //  1920 columns x 1080 rows  (38 cm x 21.5 cm)  
#define ESCAPE_KEY			27


#define RANDOM_OFFSET		15//7

//int startEnd = 0;

//    Make the transparency mask. 

#define maskWidth         128 
#define numBlurWidths      32
#define PI (3.141592653589793)


#define MM_PER_MODELUNIT_INIT 1.0
int mmPerModelUnit = MM_PER_MODELUNIT_INIT;

#define NUMBER_OF_EACH_CASE		1
bool experimentOptions[8][3] = { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 0, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };

double randNumber()
{
	double rd;
#ifdef _WIN32
	rd = (double)(rand()) / RAND_MAX;
#else
	rd = drand48();
#endif
	return rd;
}

int caseNumber = -1;
int chosenStairCase = -1;
#define RANDOM_DOT_SIZE					10
static GLubyte  texturesh[RANDOM_DOT_SIZE][RANDOM_DOT_SIZE][4];
int numSurf = 0;
int showClutter = 1;
int drawOne = 1;
int thickness = 20;

int keyg;

class Point3D{
public:
	float x, y, z;
};

class Square3D{
public:
	float x, y, z;
	int rotX, rotY, rotZ;
	GLubyte albedoR;
	GLubyte albedoG;
	GLubyte albedoB;
	GLubyte alpha;

};

//  Our scene will have many squares in it. 
//

#define MAX_DENSITY	15
//#define numSquares  (density*density*density)  
#define MAXNUMSQUARES MAX_DENSITY*MAX_DENSITY*MAX_DENSITY

GLuint	texName, texture2;

//   The following are in mm measured from origin which is at center of the screen, 
//   with z positive coming out of the screen.

#define zClosest    30 //0       //   the screen is at z = 0  (-100 is behind the screen)
#define xRange	    220 //250//200//400 //260     //500   [-xRange, xRange]
#define yRange	    190 //220 //190 //170//250 //170     //300   [-yRange, yRange]
#define zRange		225   //   Farthest z will be   zClosest - zRange   (could be myScreen.height)
#define zMid	   (zClosest - zRange/2)
#define zFocalPlane  zMid  

//  The scene consists a surface (sin Gabor) and clutter.  

Square3D surf[MAX_DENSITY*MAX_DENSITY];
Square3D p[MAXNUMSQUARES];

//reserved for shuffling and re-sorting experiment blocks
std::array<int,9> foo = {1,2,3,4,5,6,7,8,9};
std::array<array<double,2>,9> thresholdResults;			
bool myFunc(array<double,2> a, array<double,2> b)
	{ return a[0]<b[0];}

double	size = 6;   //  square size in model units (which as of mid-Aug'12 was mm  since mmPerModelUnit was 1. 

double	spin = 0;
double  jitterscale = 1.0;
int		surfOnly = 0;
int frameCount = 0;

#define MAX_NUM_STAIRCASES	150 //24
#define MAX_CASES			10000 //2000
int NUM_STAIRCASES = 24;

int timerBetweenCases;
//int moveTimer;

double alpha = 1.0;

class StairCase{
public:
	bool flag2down;
	bool reducedStep;
	double sumResults;
	int numResults;
	double reversalResults[MAX_CASES];
	int type[3];
	bool headMotion;
	bool tunnel;
	bool trans;
	int plcov;
	int lastCaseNumber;
	double initialD, initialX, initialY, initialZ, initialh, initialAvgX, initialAvgY, initialAvgZ;
	double dX, dY, dZ, dh, dAvgX, dAvgY, dAvgZ;
	double alpha, size;
	int numReversals;
	void initialize(double s, double al, bool tr, int plc, int t[3], double iD, bool tun, bool h, double iX, double iY, double iZ, double ih, double iAvgX, double iAvgY, double iAvgZ){
		flag2down = false;
		reducedStep = false;
		sumResults = 0;
		numResults = 0;
		tunnel = tun;
		alpha = al;
		size = s;
		numReversals = 0;
		lastCaseNumber = -1;
		type[0] = t[0];
		type[1] = t[1];
		type[2] = t[2];
		headMotion = h;
		initialD = iD;
		initialX = iX;
		initialY = iY;
		initialZ = iZ;
		initialh = ih;
		initialAvgX = iAvgX;
		initialAvgY = iAvgY;
		initialAvgZ = iAvgZ;
		trans = tr;
		plcov = plc;
	}
	void setStep(double x, double y, double z, double h, double avgX, double avgY, double avgZ){
		dX = x;
		dY = y;
		dZ = z;
		dh = h;
		dAvgX = avgX;
		dAvgY = avgY;
		dAvgZ = avgZ;
	}
}stairCases[MAX_NUM_STAIRCASES];

class TestCase{
public:
	bool swap;//swap the two rectangles so it looks random
	int rotation;//frames passed since the start of testcase
	int type[3];//stereo, rotation, tracking
	bool headMotion;//whether or not to force head motion
	bool showed;//already showed this test case
	double projectionAdjustment;//experimental
	bool result;//whether the rectangle chosen as closer was actually closer
	//bool trans;
	bool chosen;//chose left or right 

	//int rotateNum;//the speed of rotation, see array rotations
	double blueGreenX;//distance between the two blue and green rectangles along X axis
	double blueGreenY;//distance between the two blue and green rectangles along Y axis
	double depthDiff;//distance between the two red squares along Z axis
	double heightZ; // HILL HEIGHT - reserved for nurbs
	double avgX;
	double avgY;
	double avgZ;
	int density;
	bool tunnel;
	int plcov;
	int numSquares;
	double offsetX[2];
	double offsetY[2], alpha;
	int stairCase;
	TestCase(){
	}
	void initialize(double al, bool tr, int plc, int t[3], int D, bool tun, bool h, double iX, double iY, double iZ, double hh, double iAvgX, double iAvgY, double iAvgZ, int gSCN){
		stairCase = gSCN;
		swap = randNumber()<0.5;
		tunnel = tun;
		//trans = tr;
		plcov = plc;
		//swap=false;
		type[0] = t[0];
		type[1] = t[1];
		type[2] = t[2];
		showed = false;
		density = D;
		//if (density<2) density = 2;
		//if (density >= MAX_DENSITY) density = MAX_DENSITY;
		//density = MAX_DENSITY;// by me to make it dense
		numSquares = density*density*density;
		headMotion = h;
		rotation = 0;
		for (int i = 0; i<3; i++)
			type[i] = t[i];
		projectionAdjustment = PROJECTION_ADJUSTMENT_AVERAGE*(1 + PROJECTION_ADJUSTMENT_RANGE / 2 - randNumber()*PROJECTION_ADJUSTMENT_RANGE);
		avgX = iAvgX;
		avgY = iAvgY;
		avgZ = iAvgZ;
		blueGreenX = iX;
		blueGreenY = iY;
		depthDiff = iZ;
		heightZ = hh;
		alpha = al;

	}
	bool increase(TestCase reference, bool flag2down, int d, double dX, double dY, double dZ, double dh, double dAvgX = 0, double dAvgY = 0, double dAvgZ = 0){
		/*if (reference.result && !flag2down)
		{
		flag2down = true;
		blueGreenX=reference.blueGreenX;
		blueGreenY=reference.blueGreenY;
		depthDiff = reference.depthDiff;
		//heightZ = reference.heightZ;
		}
		else */
		{
			flag2down = false; //reserved for 1 up / 2 down staircases
			//blueGreenX = reference.blueGreenX + ((reference.result ^ (reference.blueGreenX<0)) ? -dX : dX);
			//blueGreenY = reference.blueGreenY + ((reference.result ^ (reference.blueGreenY<0)) ? -dY : dY);

			//update stimulus level
			double newZ = reference.depthDiff * ((reference.result ^ (reference.depthDiff<0)) ? SCALE_FOR_LOG:pow(1.0/SCALE_FOR_LOG,1.0/STEP_DOWN_UP_RATIO ));
			if (newZ<0) newZ = -newZ;
			if (!stairCases[chosenStairCase].reducedStep)
			if (newZ == 0 || (newZ<0 && depthDiff>0) || (newZ>0 && depthDiff<0))
			{
				stairCases[chosenStairCase].dZ /= STEP_DECREASE;
				stairCases[chosenStairCase].reducedStep = true;
			}
			depthDiff = newZ;

			

			if (depthDiff>zRange / 2)
				depthDiff = zRange / 2;
			if (depthDiff<-zRange / 2)
				depthDiff = -zRange / 2;
		}
		/*density=reference.density+d;
		if(density<2) density =2;
		if(density>=MAX_DENSITY) density=MAX_DENSITY;
		numSquares=density*density*density;*/
		return flag2down;
	}
	void saveToFile(){
		fout << "Staircase: " << chosenStairCase << " numReversals: " << stairCases[chosenStairCase].numReversals << " BP: " << stairCases[chosenStairCase].plcov <<  " Stereo: " << type[TYPE_STEREO] << " Tracking: " << type[TYPE_TRACKER] << " HeadMotion: " << headMotion << " Density: " << density << " depthDiff (dist): " << depthDiff << " dZ: " << stairCases[chosenStairCase].dZ << " result: " << result << " p[0].x= " << p[0].x << " p[1].x= " << p[1].x << " p[0].z= " << p[0].z << " p[1].z= " << p[1].z << " alpha " << alpha << " key=" << keyg << endl;
		
	}
}testCases[MAX_CASES];

void specialKeys(int key, int x, int y);

DOUBLE_POSITION_ANGLES_RECORD mean(DOUBLE_POSITION_ANGLES_RECORD r1, DOUBLE_POSITION_ANGLES_RECORD r2)
{
	DOUBLE_POSITION_ANGLES_RECORD r;
	r.x = (r1.x + r2.x) / 2;
	r.y = (r1.y + r2.y) / 2;
	r.z = (r1.z + r2.z) / 2;
	r.a = (r1.a + r2.a) / 2;
	r.e = (r1.e + r2.e) / 2;
	r.r = (r1.r + r2.r) / 2;
	return r;
}

DOUBLE_POSITION_ANGLES_RECORD normalizeAndMultiply(DOUBLE_POSITION_ANGLES_RECORD r1, double s)
{
	DOUBLE_POSITION_ANGLES_RECORD r;
	double magnitude = sqrt((r1.x*r1.x) + (r1.y*r1.y) + (r1.z*r1.z));
	r.x = r1.x / magnitude*s;
	r.y = r1.y / magnitude*s;
	r.z = r1.z / magnitude*s;
	r.a = r1.a;
	r.e = r1.e;
	r.r = r1.r;
	return r;
}

DOUBLE_POSITION_ANGLES_RECORD subtract(DOUBLE_POSITION_ANGLES_RECORD r1, DOUBLE_POSITION_ANGLES_RECORD r2)
{
	DOUBLE_POSITION_ANGLES_RECORD r;
	r.x = r1.x - r2.x;
	r.y = r1.y - r2.y;
	r.z = r1.z - r2.z;
	r.a = (r1.a + r2.a) / 2;
	r.e = (r1.e + r2.e) / 2;
	r.r = (r1.r + r2.r) / 2;
	return r;
}

DOUBLE_POSITION_ANGLES_RECORD add(DOUBLE_POSITION_ANGLES_RECORD r1, DOUBLE_POSITION_ANGLES_RECORD r2)
{
	DOUBLE_POSITION_ANGLES_RECORD r;
	r.x = r1.x + r2.x;
	r.y = r1.y + r2.y;
	r.z = r1.z + r2.z;
	r.a = (r1.a + r2.a) / 2;
	r.e = (r1.e + r2.e) / 2;
	r.r = (r1.r + r2.r) / 2;
	return r;
}

clock_t told[2] = { 0, 0 };

static float gettime(int index = 0, bool changetold = true)
{
	clock_t tnew, ris;
	tnew = clock();
	if (index == 0 && changetold == false)
		return tnew;
	ris = tnew - told[index];
	if (index == 1 && changetold == true)
	{
		told[index] = tnew;
		return 0;
	}

	if ((ris / (float)CLOCKS_PER_SEC)>((index == 0) ? 2 : 0))
	{
		if (index == 0)
			told[index] = tnew;
		return(ris / (float)CLOCKS_PER_SEC);
	}
	return 0;
}

float pzMax = -1000;
float pzMaxAfter = -1000;


GLfloat ctlpoints[4][4][3];/*={
						   {{-1.5, 1.0, -1.5},  {-0.5, 1.0,-1.5 }, {0.5, 1.0, -1.5 },   {1.5, 1.0,-1.5}},
						   {{-1.5, 1.0, -0.5},  {-0.5, 2.0,-0.5 }, {0.5, 2.0, -0.5 },   {1.5, 1.0,-0.5}},
						   {{-1.5, 1.0,  0.5},  {-0.5, 2.0, 0.5 }, {0.5, 2.0,  0.5 },   {1.5, 1.0, 0.5}},
						   {{-1.5, 1.0,  1.5},  {-0.5, 1.0, 1.5 }, {0.5, 1.0,  1.5 },   {1.5, 1.0, 1.5}}
						   };*/
int showPoints = 0;

GLUnurbsObj *theNurb;
GLuint texture[1]; // Attention: Don't do texture[0], because it doesn't work


GLfloat texpts[2][2][2] =
{
	{ { 0.0f, 0.0f }, { 0.0f, 1.0f } },
	{ { 1.0f, 0.0f }, { 1.0f, 1.0f } }
};

GLfloat height = 5.0;


#define imageWidth 256/2
#define imageHeight 256/2
GLubyte image[3 * imageWidth*imageHeight];

void makeImage(void)
{
	int i, j;
	float ti, tj;


	for (int i = 0; i<256 / 2; i++){
		for (int j = 0; j<256 / 2; j++){
			GLubyte c = (rand());// % 32768) / 32768.0;//(((i&0x5)==0)^((j&0x5)==0))*255;
			c = (((i & 0x6) == 0) ^ ((j & 0x6) == 0)) * 255;
			//if (c==0) c == 255;
			image[3 * (imageHeight*i + j)] = c;
			image[3 * (imageHeight*i + j) + 1] = c;
			image[3 * (imageHeight*i + j) + 2] = c;
		}
	}
}

// for nurbs surface - not needed for red squares experiment
void init_surface(GLfloat h)
{
	int u, v;
	for (u = 0; u < 4; u++) {
		for (v = 0; v < 4; v++) {
			ctlpoints[u][v][0] = 2.0*((GLfloat)u - 1.5);
			ctlpoints[u][v][1] = 2.0*((GLfloat)v - 1.5);

			//clip ends of square
			ctlpoints[0][0][0] = (ctlpoints[0][1][0] + ctlpoints[1][0][0]) / 2.0;
			ctlpoints[0][0][1] = (ctlpoints[0][1][1] + ctlpoints[1][0][1]) / 2.0;
			ctlpoints[0][0][2] = (ctlpoints[0][1][2] + ctlpoints[1][0][2]) / 2.0;

			ctlpoints[0][3][0] = (ctlpoints[0][2][0] + ctlpoints[1][3][0]) / 2.0;
			ctlpoints[0][3][1] = (ctlpoints[0][2][1] + ctlpoints[1][3][1]) / 2.0;
			ctlpoints[0][3][2] = (ctlpoints[0][2][2] + ctlpoints[1][3][2]) / 2.0;

			ctlpoints[3][0][0] = (ctlpoints[3][1][0] + ctlpoints[2][0][0]) / 2.0;
			ctlpoints[3][0][1] = (ctlpoints[3][1][1] + ctlpoints[2][0][1]) / 2.0;
			ctlpoints[3][0][2] = (ctlpoints[3][1][2] + ctlpoints[2][0][2]) / 2.0;

			ctlpoints[3][3][0] = (ctlpoints[3][2][0] + ctlpoints[2][3][0]) / 2.0;
			ctlpoints[3][3][1] = (ctlpoints[3][2][1] + ctlpoints[2][3][1]) / 2.0;
			ctlpoints[3][3][2] = (ctlpoints[3][2][2] + ctlpoints[2][3][2]) / 2.0;

			if ((u == 1 || u == 2) && (v == 1 || v == 2))
				ctlpoints[u][v][2] = h;
			else
				ctlpoints[u][v][2] = 0.0;
		}
	}
	// ctlpoints[4][4][3] = 

}

/*double x, y, r, sizerand, sdrand, zrand, urand, power = 3.0;
int nodraw[256];
int in = 0;
*/

//const int TextureSize = 64;
//GLubyte image[TextureSize*TextureSize*3];

void initializeScene(){
	if (DEMO_MODE){//rest til user presses ' '
		RANDOM_CHOICE_TIMER = 1;// 4 + TIME_BETWEEN_CASES
		paused = true;
	}


	glEnable(GL_FRAMEBUFFER_SRGB);
	mcount = 0;

	double jitter;
	int density = testCases[caseNumber].density;
	double Zoffset = rand() % (RANDOM_OFFSET * 4) - RANDOM_OFFSET * 2;
	testCases[caseNumber].avgZ += Zoffset;
	for (int i = 0; i<MAXNUMSQUARES; i++)	{

		//   xyz positions are in mm,  not in model units

		//		generate z values uniformly from far to near

		jitter = ((rand() % 128) - 63.5) / 128;
		p[i].x = (((i / density) % density) - (density / 2.0 - 0.5) + jitterscale*jitter)*  0.85*xRange / density;
		jitter = ((rand() % 128) - 63.5) / 128;
		p[i].y = ((i % density) - (density / 2.0 - 0.5) + jitterscale*jitter)* 0.85*yRange / density;
		jitter = ((rand() % 128) - 63.5) / 128;
		//cout<<p[i].x<<endl;

		/*urand = ((double)rand() / (RAND_MAX));
		sizerand = ((double)rand() / (RAND_MAX));
		sdrand = ((double)rand() / (RAND_MAX));
		*/
		
		
		
		p[i].z = zMid + (i / (density*density) - density / 2.0 + jitterscale*jitter)*zRange / (density);
		//cout<<p[i].z<<endl;

		//for 2 red squares
		if (i == 0 || i == 1)
		{
			p[i].x = testCases[caseNumber].blueGreenX;
			p[i].y = testCases[caseNumber].blueGreenY;
			//p[i].z = testCases[caseNumber].depthDiff;
			p[i].z = testCases[caseNumber].depthDiff / 2.0;//each square translated by half the depth, but in total their depth difference = depthDiff
			if (p[i].z > MAX_DEPTH_DIFF / 2)
				p[i].z = MAX_DEPTH_DIFF / 2;
			if (p[i].z < -MAX_DEPTH_DIFF / 2)
				p[i].z = -MAX_DEPTH_DIFF / 2;

			p[i].x *= ((i == 0)) ? 1 : -1;
			p[i].y *= ((i == 0)) ? 1 : -1;
			p[i].z *= ((i == 0) ^ (testCases[caseNumber].swap) ? 1 : -1);
			p[i].x += testCases[caseNumber].avgX;
			p[i].y += testCases[caseNumber].avgY;
			p[i].z += testCases[caseNumber].avgZ;
			testCases[caseNumber].offsetX[i] = rand() % (RANDOM_OFFSET * 2) - RANDOM_OFFSET;
			testCases[caseNumber].offsetY[i] = rand() % (RANDOM_OFFSET * 2) - RANDOM_OFFSET;
			p[i].x += testCases[caseNumber].offsetX[i];
			p[i].y += testCases[caseNumber].offsetY[i];
			//p[i].z+=Zoffset;
		}

		
		//cout<<p[i].z<<endl;
		GLubyte randGray;
		if (testCases[caseNumber].plcov == 1){//plc

			randGray = (GLubyte)(p[i].z + 255.0 - 30.0);//(GLubyte)(100 + rand()%136);//(p[i].z + 255.0);// (20 + rand()%236);
			if ((p[i].z + 255.0)>255) randGray = 255;
			if ((p[i].z + 255.0)<0) randGray = 0;
			/*p[i].albedoR = 255.0*pow(randGray/255.0, 2.0); //apply nonlinear correction so cue is more noticeable, see function drawBlurredSquare
			p[i].albedoG = 255.0*pow(randGray / 255.0, 2.0);
			p[i].albedoB = 255.0*pow(randGray / 255.0, 2.0);
			*/

		}
		else if (testCases[caseNumber].plcov == 0){//random
			randGray = (GLubyte) (20 + rand()%236); //208.0;// 255.0 / 2.0; // (5 + rand() % 250);
			p[i].albedoR = randGray;
			p[i].albedoG = randGray;
			p[i].albedoB = randGray;
		}
		else { //uniform
			randGray = (GLubyte) 208.0;// 255.0 / 2.0; // (5 + rand() % 250);
			p[i].albedoR = randGray;
			p[i].albedoG = randGray;
			p[i].albedoB = randGray;
		}
		//alpha
		double ralpha = testCases[caseNumber].alpha*255.0;

		//carve tunnels by setting alpha to 0 for squares within 2.5 cm radius circle 
		if(testCases[caseNumber].tunnel==1 && ((pow(p[i].x-p[0].x,2)+pow(p[i].y-p[0].y,2)<=25*25)||(pow(p[i].x-p[1].x,2)+pow(p[i].y-p[1].y,2)<=25*25)))
			 ralpha = 0;
		
			
		GLubyte randAlpha = (GLubyte)ralpha;//191.25;//p[i].z + 255.0;//191.25;//2;//0.75*255;//p[i].z + 255.0; //(GLubyte) (20 + rand()%236);//128;//(GLubyte) rand()/RAND_MAX;
		
		
		//check for 2 red squares
		p[i].albedoR = (i == 0) ? 255 : ((i == 1) ? 255 : randGray);
		p[i].albedoG = (i == 0) ? 0 : ((i == 1) ? 0 : randGray);
		p[i].albedoB = (i == 0) ? 0 : ((i == 1) ? 0 : randGray);


		

		//set alpha
		p[i].alpha = (i == 0) ? 255 : ((i == 1) ? 255 : randAlpha);
		


		//  depth dependent
		// p[i].albedo = (GLubyte) (i*255.0/numSquares);

		/*p[i].rotX = rand() % 70;
		p[i].rotZ = rand() % 180;
		float rotatedY = p[i].y*cos(ROTATE_ALL_POINTS) - p[i].z*sin(ROTATE_ALL_POINTS);
		float rotatedZ = p[i].y*sin(ROTATE_ALL_POINTS) + p[i].z*cos(ROTATE_ALL_POINTS);
		p[i].y = rotatedY + yRange / 8;
		p[i].z = rotatedZ;
		p[i].z += zMid;*/
		p[i].rotX = rand() % 70;
		p[i].rotZ = rand() % 180;
		
		/*if (pzMax<p[i].z && i<density*density*density)
		{
			pzMax = p[i].z;
			cout << "pzMax: " << pzMax << endl;
		}
		*/ //part of Shayan's code

		

	}

	


	//glGenTextures(1, &texture2);
	//glBindTexture(GL_TEXTURE_2D, texName);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	makeImage();
	glEnable(GL_TEXTURE_2D); // Active the texture
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256 / 2, 256 / 2, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// when texture area is small, bilinear filter the closest mipmap
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the original
	//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// the texture wraps over at the edges (repeat)
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	/*theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);*/

}

//  not necessary to define a Screen class.  We will only have one instance of Screen object. 

class Screen{
public:
	double width, height;
	Point3D position;        // Important: the position of the screen is represented by the position of the lower left corner of the screen.
};

Screen myScreen;

static GLdouble viewer[2][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } }; /* initial viewer location */
static GLdouble pastviewers[120][3];
static int nowPosViewer = 0;


void draw3DGrid(double height, int numGridLinesDepth, int numGridLinesHeightWidth);

void display(int view);


int				toggleBlur = 0;
double	scaleForBlur = 1.0*(maskWidth - 2 * numBlurWidths) / maskWidth;
static double   tmpMask[maskWidth][maskWidth];
static GLubyte  mask[maskWidth][numBlurWidths*maskWidth][4];

void makeBlurMask(void)
{
	int i, j, b, c, ii, jj;

	//  Compute all possible blur profiles, ramping down 


	c = 255;
	for (b = 0; b < numBlurWidths; b++){
		for (i = 0; i < maskWidth; i++) {
			for (j = 0; j < maskWidth; j++) {
				mask[i][b*maskWidth + j][0] = (GLubyte)c;
				mask[i][b*maskWidth + j][1] = (GLubyte)c;
				mask[i][b*maskWidth + j][2] = (GLubyte)c;
				mask[i][b*maskWidth + j][3] = (GLubyte)0;
			}
		}

		// set the alpha channel to 1 for the central square of size maskWidth-2*numBlurWidths

		for (i = numBlurWidths; i < maskWidth - numBlurWidths; i++) {
			for (j = numBlurWidths; j < maskWidth - numBlurWidths; j++) {
				mask[i][b*maskWidth + j][3] = (GLubyte)c;
			}
		}
	}

	//*   hacky way of computing convolution to get blur;   convolve with a square (not disk)

	for (b = 1; b < numBlurWidths; b++){
		for (i = 0; i < maskWidth; i++)
		for (j = 0; j < maskWidth; j++)
			tmpMask[i][j] = 0.0;
		for (i = b; i < maskWidth - b; i++)
		for (j = b; j < maskWidth - b; j++)
		for (ii = -b; ii <= b; ii++)
		for (jj = -b; jj <= b; jj++){
			tmpMask[i][j] += 1.0*mask[i + ii][j + jj][3];
		}
		for (i = 0; i < maskWidth; i++) {
			for (j = 0; j < maskWidth; j++) {
				mask[i][b*maskWidth + j][3] = (GLubyte)(tmpMask[i][j] / (2 * b + 1) / (2 * b + 1));
			}
		}
	}

}


double nx = 0.0;
double planeAngle = 0;
double ny = 0.0; // = 1/2.0;
double nz = 1.0; //  = sqrt(3.0)/2;


void drawBlurredSquare(GLfloat x, GLfloat y, GLfloat z, int rotX, int rotZ, GLfloat albedoR, GLfloat albedoG, GLfloat albedoB, GLfloat alpha, GLfloat size, GLfloat b, bool green, bool blue)
//x y z are the coordinates of the center. The square is in the x-y plane.
{//out<<z-zMid<<endl;
	glDisable(GL_CULL_FACE);                           //   shows both sides of the texture

	//	if (size<0) size *= -1; //??????


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//i added
	glPushMatrix();
	//glScaled(0.85,0.85,0.85);
	//glTranslatef(0,0,zMid);
	//glRotated(-15,1,0,0);
	//glTranslatef(x, y, z - zMid);
	glTranslatef(x, y, z);

	if (!green&&!blue)
	{
		glRotatef(rotZ, 0.0, 0.0, 1.0);
		glRotatef(rotX, 1.0, 0.0, 0.0);
	}
	int  drawRedBand = 0;
	/*if ((x*nx + y*ny + (z - zMid) *nz > 0) && (x*nx + y*ny + (z - zMid) *nz < 2*thickness)){
	oor3f(1.0, 0.0, 0.0);
	drawRedBand = 1;
	}
	else*/
	/*
	if ((x*nx + y*ny + (z - zMid) *nz > -2 * thickness) && (x*nx + y*ny + (z - zMid) *nz < 0) && !drawOne)
	{
	glColor4f(0.0, 1.0, 0.0, 1.0);
	drawRedBand = 1;
	}
	else  {
	

	 /*apply nonlinear correction 
	if albedo >=0.6 apply correction via power law,
	otherwise, let intensities fall off linearly
	*/
	GLfloat aR, aG, aB, a;

	if (albedoR>=0.6){
		aR = pow(albedoR, 3.0);
		aG = pow(albedoG, 3.0);
		aB = pow(albedoB, 3.0);
	}
	else{
		aR = albedoR * 0.3;
		aG = albedoG * 0.3;
		aB = albedoB * 0.3;
	}
	a = alpha;
	glColor4f(aR, aG, aB, a);

	
		glDisable(GL_TEXTURE_2D);
		//glScaled(scaleForBlur, scaleForBlur, scaleForBlur);

		glBegin(GL_QUADS);
		glVertex3f(-size / 2, -size / 2, 0.0);
		glVertex3f(-size / 2, +size / 2, 0.0);
		glVertex3f(size / 2, size / 2, 0.0);
		glVertex3f(size / 2, -size / 2, 0.0);
		glEnd();
		glEnable(GL_TEXTURE_2D);

	
	glPopMatrix();

}

/* read framebuffer
{
if (i == 0)
glReadBuffer(GL_BACK_LEFT);
if (i == 1)
glReadBuffer(GL_BACK_RIGHT);
glReadPixels(0, 0, resolution.first, resolution.second, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer);
for (int j = 0; j<resolution.first*resolution.second * 4; j += 4)
if (frameBuffer[j]>0 && frameBuffer[j + 1] == 0 && frameBuffer[j + 2] == 0 && frameBuffer[j + 3] > 0)//rgba
{
if (j % 4 == 0 && i == 0 && idealObserverDecision == -1 && !stairCases[chosenStairCase].type[TYPE_TRACKER])
{
int X = (j / 4) % resolution.first;
int Y = j / 4 / resolution.first;

}
}
}*/

void quickSort(Square3D arr[], int left, int right)
{
	int i = left, j = right;
	Square3D tmp;
	float pivot = arr[(left + right) / 2].z;

	/* partition */
	while (i <= j) {
		while (arr[i].z < pivot)
			i++;
		while (arr[j].z > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}
GLfloat angle = 0, angle2 = 0, angle3 = 0;

void drawSomeBlurredSquares(int view)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//i added
	
	GLfloat q;
	GLfloat gain = 3;//0.25;	
	GLfloat rot = 30; //was 30 before
	//  This square has a z value of 0.  It lies in the screen plane.
	//
	// drawBlurredSquare(0.5, -0.3, 0, 0.2, 0.1);

	double  pupil = 8.0 / mmPerModelUnit;    		//  say eye's aperture is 3 mm (convert to model units)

	int    b;
	double blurWidth;
	bool discard = false;

	nx = sin(planeAngle);
	nz = cos(planeAngle);

	




	
	if (DRAW_SIDE_PLANES){

		glColor3f(pow(0.0, 2.2), pow(0.1, 2.2), pow(0.3, 2.2)); //no gamma correction
		double depth = 0;//zClosest+zRange/2
		double length = xRange / 3.3;
		glBegin(GL_QUADS);
		//glTexCoord2f(-100, 0.0); 
		glVertex3f(-2 * length, -1000, depth);
		//glTexCoord2f(b*1.0/numBlurWidths,1.0);          
		glVertex3f(-2 * length, +1000, depth);
		//glTexCoord2f((b+1)*1.0/numBlurWidths,1.0);
		glVertex3f(-length, +1000, depth);
		//glTexCoord2f((b+1)*1.0/numBlurWidths, 0.0);
		glVertex3f(-length, -1000, depth);
		glEnd();
		glBegin(GL_QUADS);
		//glTexCoord2f(-100, 0.0); 
		glVertex3f(2 * length, -1000, depth);
		//glTexCoord2f(b*1.0/numBlurWidths,1.0);          
		glVertex3f(2 * length, +1000, depth);
		//glTexCoord2f(b+1)*1.0/numBlurWidths,1.0);
		glVertex3f(+length, +1000, depth);
		//glTexCoord2f((b+1)*1.0/numBlurWidths, 0.0);
		glVertex3f(+length, -1000, depth);
		glEnd();


	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);


	glPushMatrix();
	
	
	//  to rotate around the center of the volume, we need to translate the center to the origin
	glTranslatef(0, 0, 60);
	glTranslatef(0.0, 0.0, zMid);
	glRotatef(spin / 3.1415 * 180, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -zMid);


	glScalef(1, 1, 0.8); //z range = 18 cm instead of 22.5 cm?


	//sort back to front
			quickSort(p, 2, testCases[caseNumber].numSquares - 1);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//i added
			
			//First Render red squares as is to keep comparisons correct in Shayan's original code
			for (int i = 0; i < 2; i++)
			{
			
				drawBlurredSquare(p[i].x, p[i].y, p[i].z, p[i].rotX, p[i].rotZ, p[i].albedoR / 255.0, p[i].albedoG / 255.0, p[i].albedoB / 255.0, p[i].alpha / 255.0, 12, b*toggleBlur, i == 0, i == 1);
			
			}
			//render CLUTTER back to front
			for (int i = 2; i < testCases[caseNumber].numSquares; i++)
			{
				
				drawBlurredSquare(p[i].x, p[i].y, p[i].z, p[i].rotX, p[i].rotZ, p[i].albedoR / 255.0, p[i].albedoG / 255.0, p[i].albedoB / 255.0, p[i].alpha / 255.0, 12, b*toggleBlur, i == 0, i == 1);
					
			}
			
		
		//glEnable(GL_DEPTH_TEST);


	glPopMatrix();


}

void enableFog()
{
	GLfloat density_old = 30;
	GLfloat fogColor[4] = { 0.4, 0.4, 0.4, 1.0 };

	//glEnable (GL_DEPTH_TEST);		//enable the depth testing
	glEnable(GL_FOG);				 //enable the fog
	glFogi(GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
	glFogfv(GL_FOG_COLOR, fogColor); //set the fog color to our color chosen above
	glFogf(GL_FOG_DENSITY, density_old); //set the density to the value above
	glHint(GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
	glFogf(GL_FOG_END, 8000);
}

void updateFrustum(int view)
{
	double left, right, bottom, top, nearPlane, farPlane;

	//  Define the near plane (in the eye/viewer's coordinate system !) 
	//  to be a fixed distance from the eye/viewer, namely 50 mm (5 cm).
	//  The far plane is placed at a distance of 10 metres away.

	nearPlane = 1;//viewer[view][2]/mmPerModelUnit-CUBE_FRONT_DEPTH_AVERAGE-CUBE_FRONT_DEPTH_RANGE/2-1;
	farPlane = (viewer[view][2] + 500.0) / mmPerModelUnit;

	//  We will render the image onto a small rectangle in this near plane, namely the
	//  rectangle defined by the projection of the physical screen toward the eye.
	//  Note:  "viewer" is the eye.  Its position is in model coordinate system, whose origin
	//  is at the center of the screen.  The values of "viewer" were computed in updateTrackerPosition().
	//
	//  To understand the expressions below, first consider the case that viewer[0] = viewer[1] = 0.
	//  In this case, left < 0,  right > 0, bottom < 0, top > 0.
	//  Next, if viewer[0] > 0, then the viewer has moved to the right (X+) in the model coordinates.
	//  Thus, the projection of the screen will move to the left in the projection plane, as viewed
	//  from the viewer.  Hence, left will decrease in value.
	//  Similar reasoning holds for right, bottom, top...

	left = nearPlane * (-0.5 * myScreen.width / mmPerModelUnit - (viewer[view][0])*testCases[caseNumber].projectionAdjustment) / viewer[view][2];
	right = nearPlane * (0.5 * myScreen.width / mmPerModelUnit - (viewer[view][0])*testCases[caseNumber].projectionAdjustment) / viewer[view][2];
	bottom = nearPlane * (-0.5 * myScreen.height / mmPerModelUnit - viewer[view][1] * testCases[caseNumber].projectionAdjustment) / viewer[view][2];
	top = nearPlane * (0.5 * myScreen.height / mmPerModelUnit - viewer[view][1] * testCases[caseNumber].projectionAdjustment) / viewer[view][2];

	//JOHNNY LEE'S CODE
	/*
	left =   nearPlane *(-0.5 * SCREEN_ASPECT_RATIO + viewer[0])  / viewer[2];
	right =  nearPlane * (0.5 * SCREEN_ASPECT_RATIO + viewer[0])  / viewer[2];
	bottom = nearPlane *(-0.5 - viewer[1]) / viewer[2];
	top =    nearPlane * (0.5 - viewer[1]) / viewer[2];
	*/

	// MIKE commented out:   cout <<"L:"<<left<<"\tR:"<<right<<"\tB:"<<bottom<<"\tT:"<<top<<"\tn:"<<nearPlane<<endl<<endl;

	// cout <<"DL:"<<viewer[0]-left<<"\tDR:"<<viewer[0]-right<<"\tDB:"<<viewer[1]-bottom<<"\tDT:"<<viewer[1]-top<<endl<<endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, nearPlane, farPlane);

	glMatrixMode(GL_MODELVIEW);
	//glRotated(clock()*1e-3, 1, 2, 3);

}


///---------------------------------    TRACKER CODE ---------------------------------------------

void  errorHandler(int errorCode){
	cout << "Error: " << errorCode << endl;
}

void initializeTracker()
{

	//
	// First initialize the system
	//
	int errorCode = InitializeBIRDSystem();
	if (errorCode != BIRD_ERROR_SUCCESS)
	{
		int size = 10000;
		char *buffer = new char[10000];
		GetErrorText(errorCode, buffer, size, VERBOSE_MESSAGE);
		cout << buffer << endl;
		delete buffer;
		errorHandler(errorCode); // user supplied error handler
	}

	//
	// Turn on the transmitter.
	// We turn on the transmitter by selecting the
	// transmitter using its ID
	//
	USHORT id = 0;
	errorCode = SetSystemParameter(SELECT_TRANSMITTER, &id, sizeof(id));
	if (errorCode != BIRD_ERROR_SUCCESS)
	{
		errorHandler(errorCode);
	}

	//
	// Use METRIC reporting
	//
	BOOL bufferMetric = true;			// set metric reporting = true
	BOOL *pBufferMetric = &bufferMetric;
	printf("METRIC: %d\n", bufferMetric);
	errorCode = SetSystemParameter(METRIC, pBufferMetric, sizeof(bufferMetric));
	if (errorCode != BIRD_ERROR_SUCCESS) errorHandler(errorCode);

	//
	// MAXIMUM_RANGE
	//
	// NOTE: Only 2 values are currently supported and they are 36/72 inches
	// Any other value will generate an error
	//
	double bufferMax = 72.0;
	double *pBufferMax = &bufferMax;
	printf("MAXIMUM_RANGE: %5.2f\n", bufferMax);
	errorCode = SetSystemParameter(MAXIMUM_RANGE, pBufferMax, sizeof(bufferMax));
	if (errorCode != BIRD_ERROR_SUCCESS) errorHandler(errorCode);

	//
	// HEMISPHERE
	//

	HEMISPHERE_TYPE buffer, *pBuffer = &buffer;
	buffer = LEFT;
	int sensorID = 0;
	errorCode = SetSensorParameter(sensorID, HEMISPHERE, pBuffer, sizeof(buffer));
	if (errorCode != BIRD_ERROR_SUCCESS) errorHandler(errorCode);
	printf("HEMISPHERE: %4x\n", buffer);

}


void updateTrackerPosition()
{
	//
	// Get a record from sensor #0.
	// The default record type is DOUBLE_POSITION_ANGLES

	bool error = false;
	int errorCode;
	USHORT sensorID = 0;
	DOUBLE_POSITION_ANGLES_RECORD record;
	DOUBLE_POSITION_ANGLES_RECORD record1;
	DOUBLE_POSITION_ANGLES_RECORD record2;

	errorCode = GetAsynchronousRecord(sensorID, &record1, sizeof(record1));
	if (errorCode != BIRD_ERROR_SUCCESS)
	{
		//errorHandler(errorCode);
		error = true;
	}
	sensorID = 1;
	errorCode = GetAsynchronousRecord(sensorID, &record2, sizeof(record2));
	if (errorCode != BIRD_ERROR_SUCCESS)
	{
		//errorHandler(errorCode);
		error = true;
	}
	record = mean(record1, record2);
	//record1=mean(record,record1);
	//record2=mean(record,record2);
	record1 = add(record, normalizeAndMultiply(subtract(record1, record), IOD / 2));
	record2 = add(record, normalizeAndMultiply(subtract(record2, record), IOD / 2));


	double x_offset = -cos(record.a*PI / 180)*cos(record.e*PI / 180)*EYE_OFFSET;
	double y_offset = -sin(record.a*PI / 180)*cos(record.e*PI / 180)*EYE_OFFSET;
	double z_offset = +sin(record.e*PI / 180)*EYE_OFFSET;
	record.x += x_offset;
	record.y += y_offset;
	record.z += z_offset;
	record1.x += x_offset;
	record1.y += y_offset;
	record1.z += z_offset;
	record2.x += x_offset;
	record2.y += y_offset;
	record2.z += z_offset;
	//cout<<sqrt((record1.x-record2.x)*(record1.x-record2.x)+(record1.y-record2.y)*(record1.y-record2.y)+(record1.z-record2.z)*(record1.z-record2.z))<<endl;

	//  MIKE COMMENTED OUT
	// cout <<"raw_x:"<< record.x<< "\traw_x:"<< record.x<<"\traw_y:" << record.y <<"\traw_y:" << record.y << "\traw_z:" << record.z << endl;

	//  MIKE:
	//  Transmitter is aligned with cable pointing parallel to the optical axis,
	//  and positioned directly to the left of the viewer.  
	//  The  record.z direction is up.
	//  The  record.x direction is away from the screen.  
	//  The  record.y direction is to the right of the viewer.
	//
	//  Thus, the viewer's +x axis is the  record.y direction.
	//        the viewer's +y axis is the  record.z direction
	//        the viewer's -z axis is the  -record.x direction
	//
	//  myScreen.position.{x,y,z} is the center of the screen, measured in mm with respect to 
	//  world coordinate system, which has its origin at the transmitter.
	//  We write the viewer[] coordinates in terms of an XYZ world coordinate frame 
	//  where +X is to the right, +Y is up, and Z+ is toward the viewer.  
	//  The origin is at the center of the screen. 

	viewer[0][0] = (record1.y - myScreen.position.x) / mmPerModelUnit;  //x
	viewer[0][1] = (record1.z - myScreen.position.y) / mmPerModelUnit;  //y
	viewer[0][2] = (-record1.x - myScreen.position.z) / mmPerModelUnit;  //z

	viewer[1][0] = (record2.y - myScreen.position.x) / mmPerModelUnit;  //x
	viewer[1][1] = (record2.z - myScreen.position.y) / mmPerModelUnit;  //y
	viewer[1][2] = (-record2.x - myScreen.position.z) / mmPerModelUnit;  //z

	if (testCases[caseNumber].type[TYPE_TRACKER] == true && (viewer[0][0]<-TRACKING_ACCEPTABLE_RANGE_X / 2 || viewer[1][0]>TRACKING_ACCEPTABLE_RANGE_X / 2
		|| viewer[0][1]<-TRACKING_ACCEPTABLE_RANGE_Y / 2 || viewer[1][1]>TRACKING_ACCEPTABLE_RANGE_Y / 2
		|| viewer[0][2]<TRACKING_CLOSE_Z || viewer[1][2]>TRACKING_FAR_Z))
	{
		tooFar = true;
		disabled = true;
	}

	if (pastviewers[nowPosViewer][0]<-9999)
		disabled = true;
	double dist = 0;
	for (int i = 0; i<60 - 1; i++)
		dist += sqrt(pow((double)pastviewers[i % 60][0] - (double)pastviewers[(i + 1) % 60][0], 2) + pow((double)pastviewers[i % 60][1] - (double)pastviewers[(i + 1) % 60][1], 2) + pow((double)pastviewers[i % 60][2] - (double)pastviewers[i + 1][2], 2));
	//dist=sqrt(pow((viewer[0][0]+viewer[1][0])/2-0,2)+pow((viewer[0][1]+viewer[1][1])/2-NO_TRACKING_HEIGHT,2)+pow((viewer[0][2]+viewer[1][2])/2-NO_TRACKING_DISTANCE,2));
	if (/*testCases[caseNumber].headMotion &&*/((testCases[caseNumber].type[TYPE_TRACKER] || testCases[caseNumber].type[TYPE_STEREO] == 2) && dist<DIST_THRESH))
	{
		not_moving = true;
		disabled = true;
	}
	if (/*testCases[caseNumber].headMotion &&*/(testCases[caseNumber].type[TYPE_STEREO] == 1 && testCases[caseNumber].type[TYPE_TRACKER] == 0) && dist>200)
	{
		not_moving = false;
		disabled = true;
	}
	//printf("%d\n",dist);
	pastviewers[nowPosViewer][0] = record.x;
	pastviewers[nowPosViewer][1] = record.y;
	pastviewers[nowPosViewer][2] = record.z;
	nowPosViewer = (nowPosViewer + 1) % 120;

	int view = 0;
	double dx = viewer[view][0] + (viewer[1 - view][0] - viewer[view][0])*viewer[view][2] / (viewer[view][2] - viewer[1 - view][2]);
	double dy = viewer[view][1] + (viewer[1 - view][1] - viewer[view][1])*viewer[view][2] / (viewer[view][2] - viewer[1 - view][2]);
	//no head tilting
	if (sqrt(dx*dx + dy*dy)<TILT_THRESH)
	{
		//disabled = true;
		//tilted = true;
	}

	if (testCases[caseNumber].type[TYPE_STEREO] == false)
	{
		viewer[0][0] = (record.y - myScreen.position.x) / mmPerModelUnit;  //x
		viewer[0][1] = (record.z - myScreen.position.y) / mmPerModelUnit;  //y
		viewer[0][2] = (-record.x - myScreen.position.z) / mmPerModelUnit;  //z

		viewer[1][0] = (record.y - myScreen.position.x) / mmPerModelUnit;  //x
		viewer[1][1] = (record.z - myScreen.position.y) / mmPerModelUnit;  //y
		viewer[1][2] = (-record.x - myScreen.position.z) / mmPerModelUnit;  //z
	}

	if (!rest)
	{
		/*for (int i = 0; i<2; i++)
		for (int j = 0; j<3; j++)
		fout2 << (double)viewer[i][j] << " ";
		fout2 << endl;*/
	}

	if (testCases[caseNumber].type[TYPE_TRACKER] == false || error)
	{
		//fout2 << "static" << endl;
		viewer[0][0] = -IOD / 2;
		viewer[0][1] = -sin(ROTATE_ALL_POINTS)*NO_TRACKING_DISTANCE;//NO_TRACKING_HEIGHT;
		viewer[0][2] = cos(ROTATE_ALL_POINTS)*NO_TRACKING_DISTANCE;
		viewer[1][0] = IOD / 2;
		viewer[1][1] = -sin(ROTATE_ALL_POINTS)*NO_TRACKING_DISTANCE;//NO_TRACKING_HEIGHT;
		viewer[1][2] = cos(ROTATE_ALL_POINTS)*NO_TRACKING_DISTANCE;
	}

}
void turnOffTransmitter()
{
	//
	// Turn off the transmitter before exiting
	// We turn off the transmitter by "selecting" a transmitter with an id of "-1"
	//
	int errorCode;
	int id = -1;
	errorCode = SetSystemParameter(SELECT_TRANSMITTER, &id, sizeof(id));
	if (errorCode != BIRD_ERROR_SUCCESS) errorHandler(errorCode);
}

//static bool paused = false;

float t2 = gettime(1, true);
float first = true;

void stereoDisplay(void)
{
	if (first)
	{
		gettime(1, true);
		first = false;
	}
	disabled = false;
	tilted = false;
	tooFar = false;
	not_moving = false;
	testCases[caseNumber].rotation++;
	frameCount++;
	block_beginning++;
	updateTrackerPosition();
	/*if (gettime(1,false)<BLOCK_BEGINNING)
	{
	glClearColor(1,0,0,1);
	disabled=true;
	}
	else*/
	//{
	//randomChoiceFlag = false;
	glClearColor(0, 0, 0, 1);
	//}
	float t = gettime();
	if (t != 0)
	{
		if (!disabled&&!rest)
			randomChoiceTimer++;
		if (disabled) //|| rest) //by me commented out
			gettime(1, true);
		cout << "CaseNumber: " << caseNumber << "\t\t" << "fps: " << frameCount / t << endl;
		frameCount = 0;
	}
	//if (paused)
	//	gettime(1, true);
	//glClearColor(1,0,0,1);
	//glDrawBuffer(GL_BACK_LEFT);
	//	if(frameCount%2==0)
	//	{
	glDrawBuffer(GL_BACK_LEFT);
	display(0);
	glFlush();
	//	}
	//glFlush();
	//glDrawBuffer(GL_BACK_RIGHT);
	//if(frameCount%2==1)
	//	{
	glDrawBuffer(GL_BACK_RIGHT);
	if (testCases[caseNumber].type[TYPE_STEREO] > 0)
		display(1);
	else
		display(0);
	glFlush();
	//	}
	//count red pixels
	//ideal observer decides here
	int reds[2] = { 0, 0 };
	int redsleft = 0;
	int redsright = 0;
	//bool skip = false;
	/*if (gettime(1, false)<TIME_BETWEEN_CASES)
	cout << "timer set" << endl;
	cout << gettime(1, false) << " ";*/
	if (!disabled && gettime(1, false)>TIME_BETWEEN_CASES)
	{
		for (int i = 0; i<2; i++)
		{
			if (i == 1 && stairCases[chosenStairCase].type[TYPE_STEREO] == 0)
				continue;
			//	int leftxmin = 10000, leftxmax = -10000, leftymin = 10000, leftymax = -10000;
			//	int rightxmin = 10000, rightxmax = -10000, rightymin = 10000, rightymax = -10000;
			if (i == 0)
				glReadBuffer(GL_BACK_LEFT);
			if (i == 1)
				glReadBuffer(GL_BACK_RIGHT);
			glReadPixels(0, 0, resolution.first, resolution.second, GL_RGBA, GL_UNSIGNED_BYTE, frameBuffer);
			for (int j = 0; j<resolution.first*resolution.second * 4; j += 4)
				/*if (frameBuffer[j]>0 && frameBuffer[j + 1] == 0 && frameBuffer[j + 2] == 0 && frameBuffer[j + 3]>0)//rgba
				{
				if (j % 4 == 0 && i == 0 && idealObserverDecision == -100000 && !stairCases[chosenStairCase].type[TYPE_TRACKER])
				{
				int redX = (j / 4) % resolution.first;
				int redY = j / 4 / resolution.first;
				if (redX<resolution.first / 2)
				{
				redsleft++;
				POSLeftX += abs(redX - resolution.first / 2);
				POSLeftY += abs(redY - resolution.second / 2);
				POSLeftNum++;
				if (redX<leftxmin) leftxmin = redX;
				if (redX>leftxmax) leftxmax = redX;
				if (redY<leftymin) leftymin = redY;
				if (redY>leftymax) leftymax = redY;
				}
				else
				{
				redsright++;
				POSRightX += abs(redX - resolution.first / 2);
				POSRightY += abs(redY - resolution.second / 2);
				POSRightNum++;
				if (redX<rightxmin) rightxmin = redX;
				if (redX>rightxmax) rightxmax = redX;
				if (redY<rightymin) rightymin = redY;
				if (redY>rightymax) rightymax = redY;
				}
				}
				if (j % 4 == 0 && i == 0 && stairCases[chosenStairCase].type[TYPE_TRACKER])
				{
				int redX = (j / 4) % resolution.first;
				int redY = j / 4 / resolution.first;
				if (redX<resolution.first / 2)
				{
				trackingreds[0]++;
				POSLeftX += abs(redX - resolution.first / 2);
				POSLeftY += abs(redY - resolution.second / 2);
				POSLeftNum++;
				}
				else
				{
				trackingreds[1]++;
				POSRightX += abs(redX - resolution.first / 2);
				POSRightY += abs(redY - resolution.second / 2);
				POSRightNum++;
				}
				}
				reds[i]++;
				}
				if ((stairCases[chosenStairCase].type[TYPE_STEREO] == 0 || i == 1) && idealObserverDecision == -100000 && !stairCases[chosenStairCase].type[TYPE_TRACKER])
				{
				POSLeftX /= POSLeftNum;
				POSLeftY /= POSLeftNum;
				POSRightX /= POSRightNum;
				POSRightY /= POSRightNum;
				int leftSize = max(leftxmax - leftxmin, leftymax - leftymin);
				int rightSize = max(rightxmax - rightxmin, rightymax - rightymin);
				if (abs(POSLeftY)>abs(POSRightY))
				POSVerticalIdealObserverDecision = 0;
				else
				POSVerticalIdealObserverDecision = 1;
				if (POSLeftX*POSLeftX + POSLeftY*POSLeftY>POSRightX*POSRightX + POSRightY*POSRightY)
				POSCenterIdealObserverDecision = 0;
				else
				POSCenterIdealObserverDecision = 1;
				//if(leftSize>rightSize)
				if (redsleft>redsright)
				idealObserverDecision = 0;
				else
				idealObserverDecision = 1;
				int idealCorrect;
				if (idealObserverDecision == 1){
				if (p[0].z>p[1].z)
				idealCorrect = true;
				else
				idealCorrect = false;
				}
				if (idealObserverDecision == 0){
				if (p[0].z>p[1].z)
				idealCorrect = true;
				else
				idealCorrect = false;
				}
				cout << POSVerticalIdealObserverDecision << POSCenterIdealObserverDecision << endl;
				if (idealCorrect != idealObserverDecision)
				{
				if (POSVerticalIdealObserverDecision == 0) {
				POSVerticalIdealObserverDecision = 1;
				}
				else
				if (POSVerticalIdealObserverDecision == 1)
				{
				POSVerticalIdealObserverDecision = 0;
				}
				if (POSCenterIdealObserverDecision == 0) {
				POSCenterIdealObserverDecision = 1;
				}
				else
				if (POSCenterIdealObserverDecision == 1)
				{
				POSCenterIdealObserverDecision = 0;
				}
				}
				fout3 << chosenStairCase << "," << leftSize << "," << rightSize << "," << idealCorrect << "," << POSVerticalIdealObserverDecision << "," << POSCenterIdealObserverDecision << "," << stairCases[chosenStairCase].hideSizes << "," << stairCases[chosenStairCase].initialD << "," << redsleft << "," << redsright << "," << testCases[caseNumber].tunnel << ",";
				//skip = true;
				}
				else{
				//if(i==0 && idealObserverDecision==-1)
				//	fout3<<"x"<<","<<"x"<<","<<"x"<<","<<"x"<<","<<stairCases[chosenStairCase].hideSizes<<","<<stairCases[chosenStairCase].initialD<<",";
				}*/
				averageReds[i] += reds[i];
			averageRedsCounter[i]++;
			if (peakReds[i]<reds[i])
				peakReds[i] = reds[i];
		}
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	if (gettime(1, false)>RANDOM_CHOICE_TIMER)
	{
		//skip = false;
		specialKeys((randNumber()>0.5) ? GLUT_KEY_LEFT : GLUT_KEY_RIGHT, 0, 0);
		randomChoiceFlag = true;
	}

}
void drawSphere(void)
{
	glTranslatef(viewer[0][0], viewer[0][1], -5);
	glutSolidSphere(5, 30, 30);
}

void display(int view)
{
	//disabled = false;
	//paused = false;
	if (1){ //!paused){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//  Update viewer position in modelview matrix.
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//  Set lookat such that the camera origin is the viewer and the camera
		//  is looking in the Z direction.  This ensures that the projection plane 
		//  is a constant Z plane.  

		gluLookAt((viewer[view][0])*testCases[caseNumber].projectionAdjustment, viewer[view][1] * testCases[caseNumber].projectionAdjustment, viewer[view][2], (viewer[view][0])*testCases[caseNumber].projectionAdjustment, viewer[view][1] * testCases[caseNumber].projectionAdjustment, 0.0, 0.0, 1.0, 0.0);

		// Update Projection Matrix
		updateFrustum(view);
		glColor3f(0, 0, 1);
		//glutSolidSphere(0.5, 50, 50);
		glDisable(GL_TEXTURE_2D);
		//glutSolidSphere(1, 10, 10);
		glPushMatrix();
		glTranslatef(0, 0, -myScreen.height / 2);
		glScalef(SCREEN_ASPECT_RATIO, 1, 1);
		//glutWireCube(myScreen.height);
		glPopMatrix();
		//draw3DCubes();
		glColor3f(0, 1, 0);
		//glutSolidCube(myScreen.width/2);
		glPushMatrix();
		glPushMatrix();
		glPushMatrix();
		string str = to_string((int)sqrt(pow(testCases[caseNumber].blueGreenX, 2) + pow(testCases[caseNumber].blueGreenY, 2)));
		glTranslatef(-130, -50, 0);//-170,-50
		glScalef(0.05, 0.05, 0.05);
		for (int i = 0; i < str.length(); i++)
		{
			//glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
		}
		glPopMatrix();
		glTranslatef(-130, -60, 0);//-170,-50
		glScalef(0.05, 0.05, 0.05);
		str = to_string((int)testCases[caseNumber].blueGreenY);
		for (int i = 0; i < str.length(); i++)
		{
			//glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
		}
		glPopMatrix();
		glTranslatef(-170, +80, 0);
		glScalef(0.1, 0.1, 0.1);
		static int didItJustNow = false;
		if (caseNumber % 100 == 99 && !didItJustNow)
		{
			didItJustNow = true;
			rest = true;
			fout << "rest" << endl;
			//fout2 << "rest" << endl;
		}
		if (caseNumber % 100 != 99)
			didItJustNow = false;
		glColor3f(1, 0, 0);
		if (paused)
			gettime(1, true);
		if (DEMO_MODE){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'D');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'm');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');

			if (testCases[caseNumber].plcov){
				glPushMatrix();
				glTranslatef(0, -200, 0);//-170,-50
				glutStrokeCharacter(GLUT_STROKE_ROMAN, 'P');
				glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
				glPopMatrix();
				//glTranslatef(-130, -60, 0);//-170,-50

			}
			if (testCases[caseNumber].alpha < 1.0){
				glPushMatrix();
				glTranslatef(0, -400, 0);//-170,-50
				//glutStrokeCharacter(GLUT_STROKE_ROMAN, 'P');
				glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');
				glPopMatrix();
				//glTranslatef(-130, -60, 0);//-170,-50

			}
		}

		if (rest)
		{
			gettime(1, true);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'R');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
		}
		if (tilted)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'D');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'n');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, '\'');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'T');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'i');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'u');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
		}
	
	/*	if (not_moving &&!rest)
		{
			
			//glRasterPos2i(-150, 90);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'M');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'v');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
		}
		*/
		if (testCases[caseNumber].type[TYPE_STEREO] == 1 && testCases[caseNumber].type[TYPE_TRACKER] == 0 && disabled&&!tooFar){
			glPushMatrix();
			//glScalef(0.4, 0.5, 0.4);
			//glTranslatef(-140, -110, 0);
			//glRasterPos2i(-150, 90);
			//glScalef(0.2, 0.2, 0.2);
			//glTranslatef(-700, 350, 0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'D');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'n');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'M');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'v');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
			glPopMatrix();


		}
		if (/*(testCases[caseNumber].type[TYPE_TRACKER]||testCases[caseNumber].type[TYPE_STEREO]==2)*/not_moving&& !rest&&!tooFar){// && gettime(1, false) >0.1){
			glPushMatrix();
			//glScalef(0.4, 0.5, 0.4);
			//glTranslatef(-140, -110, 0);
			//glRasterPos2i(-150, 90);
			//glScalef(0.2, 0.2, 0.2);
			//glTranslatef(-700, 350, 0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'M');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'v');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
			glPopMatrix();
			//moveTimer++;
		}
		
		if (tooFar)
		{
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'u');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 't');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'f');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ' ');

			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'b');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'u');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'n');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
			glutStrokeCharacter(GLUT_STROKE_ROMAN, 's');
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		//drawSphere();
		timerBetweenCases++;
		if (DEMO_MODE){
			if (paused || !disabled && gettime(1, false) > TIME_BETWEEN_CASES)
			{
				drawSomeBlurredSquares(view);
			}
			else{
				gettime(0, false);
				//return;
			}

		}
		else{
			
			if (paused || !disabled && gettime(1, false)>TIME_BETWEEN_CASES)
			{
				drawSomeBlurredSquares(view);
			}
			else
			{
				glPushMatrix();
				glDisable(GL_TEXTURE_2D);

				
				glTranslatef(-30, 0, 0);


			//if time runs out
				if(randomChoiceFlag){//disabled or random choice
					


					glutStrokeCharacter(GLUT_STROKE_ROMAN, 'x');
				}
				


				glPopMatrix();
			}
		}
		//glFlush();
		//glutSwapBuffers();
	}
}



static GLfloat theta[] = { 0.0, 0.0, 0.0 };

int axis;

void endExperiment(){
	for (int i = 0; i<NUM_STAIRCASES; i++)
	if (stairCases[i].numResults != 0)
	{
		double lastReversals = 0;
		int count = 0;
		fout << "StairCase " << i << " : NumResults: " << stairCases[i].numResults << " result: " << stairCases[i].sumResults / stairCases[i].numResults << endl;
		fout << "\t\tnumReversals: " << stairCases[i].numReversals;
		for (int j = 0; j<stairCases[i].numReversals; j++)
		{
			if (stairCases[i].numReversals - j <= N_LAST_REVERSALS)
			{
				lastReversals += log(stairCases[i].reversalResults[j]);
				count++;
			}
			fout << " " << stairCases[i].reversalResults[j];
		}
		fout << " last " << count << " : " << lastReversals / count;
		thresholdResults[i][0] = foo[i];
		thresholdResults[i][1] = exp(lastReversals / count);

		//fout4 << exp(lastReversals / count) << endl;
		fout << endl;
	}
	/*re-sort experiment block thresholds so they are easy to transfer to a 
	spreadsheet in a consistent order for each subject*/
	/*The sorted order is:
	1. Random, no stereo, no MP
	2. Random, stereo don't move
	3. Random, stereo move
	4. Random, MP
	5. Random, stereo + MP
	6. Baseline, stereo + MP
	7. PLC, stereo + MP
	8. Uniform Transparent, stereo + MP
	9. Tunneling, Stereo + MP
	See file tracking_log.txt for shuffled order
	*/
	std::sort(thresholdResults.begin(),thresholdResults.end(),myFunc);
	for(int ii=0;ii<thresholdResults.size();ii++)
	{
		fout4 << thresholdResults[ii][1]<<endl;
	}

	/*double hideIdeal = 0, nohideIdeal = 0, hideSubject = 0, nohideSubject = 0;
	double hideCenterIdeal = 0, nohideCenterIdeal = 0, hideVerticalIdeal = 0, nohideVerticalIdeal = 0;
	int totalHide = 0, totalNoHide = 0;
	for (int i = 0; i<caseNumber; i++)
	{
	if (stairCases[testCases[i].stairCase].hideSizes)
	{
	hideSubject += (int)testCases[i].result;
	hideIdeal += (int)testCases[i].idealObserverDecision;
	totalHide++;


	hideCenterIdeal += (int)testCases[i].POSCenterIdealObserverDecision;
	hideVerticalIdeal += (int)testCases[i].POSVerticalIdealObserverDecision;
	}
	else
	{
	nohideSubject += (int)testCases[i].result;
	nohideIdeal += (int)testCases[i].idealObserverDecision;
	nohideCenterIdeal += (int)testCases[i].POSCenterIdealObserverDecision;
	nohideVerticalIdeal += (int)testCases[i].POSVerticalIdealObserverDecision;
	totalNoHide++;
	}

	}
	fout4 << "percentages(hide nohide)" << endl << hideIdeal << endl << nohideIdeal << endl << hideSubject << endl << nohideSubject << endl;
	fout4 << "center and vertical" << endl << hideCenterIdeal << endl << nohideCenterIdeal << endl << hideVerticalIdeal << endl << nohideVerticalIdeal << endl;
	fout4 << "totalCases(hide,nohide,total) " << endl << totalHide << endl << totalNoHide << endl << caseNumber << endl;
	*/
	fout << "\n total number of trials: " << caseNumber;
	turnOffTransmitter();
	fout.close();
	fout2.close();
	//fout3.close();
	fout4.close();
	exit(0);
}

 
void specialKeys(int key, int x, int y)
{
	//moveTimer = 0;
	//keyg=key;
	bool first = true;

	if (rest)
		return;
	if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT || key == GLUT_KEY_UP)
	{

		randomChoiceTimer = 0;
		if (randomChoiceFlag == false && (disabled || gettime(1, false) <= TIME_BETWEEN_CASES))
		{
			gettime(1, true);
			return;
		}
		gettime(1, true);
		randomChoiceFlag = false;
		//commented out by me
		//fout<<"Average Reds: "<<averageReds[0]/averageRedsCounter[0]<<" "<<averageReds[1]/averageRedsCounter[1]<<" Peak Reds: "<<((peakReds[0]>peakReds[1])?peakReds[0]:peakReds[1])<<endl;
		//fout2 << "Average Reds: " << averageReds[0] / averageRedsCounter[0] << " " << averageReds[1] / averageRedsCounter[1] << " Peak Reds: " << ((peakReds[0]>peakReds[1]) ? peakReds[0] : peakReds[1]) << endl;
		averageReds[0] = 0;
		averageReds[1] = 0;
		peakReds[0] = 0;
		peakReds[1] = 0;
		averageRedsCounter[0] = 0;
		averageRedsCounter[1] = 0;
		//randomChoiceTimer = 0;
		//if (disabled)
		//	return;

		timerBetweenCases = 0;
		gettime(1, true);


		if (caseNumber == -1){ //initialize staircases
						
			/*foo is an array with integers 1 to 9, where each number is associated with one of our nine conditions.
			We shuffle it so order of blocks is randomized for each subject (see the for loop below)
			*/
			 // obtain a time-based seed:
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

			shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
	

			int densities[] = { 7, 0, 11, 15 }; //{ 8, 11 };//{ 4, 11 };// 6, 10, 12

		
			double sizes[] = { 12, 24 };//{ 24, 12 };// 45, 22, 11, 8
			double opacities[] = { 0.1, 0.4, 1 };
			int count = 0; //staircase count
			int s = 0;//size index, deprecated
			


			for (int& cond: foo){

				int tr = 1; //deprecated var
				int plc = 0;
				int d = 2;
				int tunnel = 0;
				int stereo = 0, headTracking = 0;		
				
				// SELECT A CONDITION/STAIRCASE
					if(cond == 1){//no cue, random
						plc = 0;
						d = 2;
						tunnel = 0;
						alpha = 1;
						
						stereo=0;
						headTracking=0;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
					
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++; //increase staircase count
				
					}

					else if(cond == 2){//stereo
						plc = 0;
						d = 2;
						tunnel = 0;
						alpha = 1;
						
						stereo=1;
						headTracking=0;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
					
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;
				
					}
					else if(cond == 3){//stereo move
						plc = 0;
						d = 2;
						tunnel = 0;
						alpha = 1;
					
						stereo=2;
						headTracking=0;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
					
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;
				
					}
					else if(cond == 4){ //MP
						plc = 0;
						d = 2;
						tunnel = 0;
						alpha = 1;
						
						stereo=0;
						headTracking=1;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
				
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;
				
					}
					else if(cond == 5){ //ST + MP, random
						plc = 0;
						d = 2;
						tunnel = 0;
						alpha = 1;
					
						stereo=1;
						headTracking=1;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
				
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;
				
					}
					else if(cond == 6){//baseline, set alpha = 0 for all squares
						d = 2;
						tunnel = 0;
						stereo = 1;
						headTracking = 1;
						alpha = 0;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
					
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;

					}
					if(cond == 7){//PLC
						plc = 1;
						d = 2;
						tunnel = 0;
						alpha = 1;
						stereo = 1;
						headTracking = 1;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
				
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;

					}
					if(cond == 8){//TRANSPARENT UNI
						plc = 2;
						d = 2;
						tunnel = 0;
						alpha = 0.4;
						stereo = 1;
						headTracking = 1;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], 0, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
				
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;

					}
					if(cond == 9){//TUNNELING
						plc = 0;
						d = 2;
						tunnel = 1;
						alpha = 1;
						stereo = 1;
						headTracking = 1;
						int type[3] = { stereo, headTracking, 0 };
					fout2 << "T" << tunnel << "_D" << densities[d] << "_PL" << plc << "_a" << alpha << "_S" << stereo << "_HT" << headTracking << endl;
					stairCases[count].initialize(sizes[s], alpha, tr, plc, type, densities[d], tunnel, 0, yRange / 6, 0, INIT_DEPTH_DIFFERENCE, 6, 0, 0, zClosest - zRange / 2);
				
					stairCases[count].setStep(0, 0, STEP_INITIAL, 5, 0, 0, 0);//2
					count++;

					}
		
			NUM_STAIRCASES = count;
			}
		}
		else{ //check if correct
			bool correct = false;
			if (key == GLUT_KEY_RIGHT){
				testCases[caseNumber].chosen = true;
				keyg = 22;
				if (p[0].z>p[1].z)
					
					correct = true;
				else
					correct = false;
			}
			else if (key == GLUT_KEY_LEFT){
				testCases[caseNumber].chosen = false;
				keyg = 11;
				if (p[0].z<p[1].z)
					
					correct = true;
				else
					correct = false;
			}
			
			testCases[caseNumber].result = correct;
			
			if (stairCases[chosenStairCase].lastCaseNumber != -1){
				if (correct != testCases[stairCases[chosenStairCase].lastCaseNumber].result && !stairCases[chosenStairCase].flag2down)
					//	if(correct!=testCases[stairCases[chosenStairCase].lastCaseNumber].result) //signal reversal	is this good for 1 up/2 down?
				{
					//first = false;

					/*if (!stairCases[chosenStairCase].reducedStep && stairCases[chosenStairCase].numReversals == 1)
					{
						stairCases[chosenStairCase].dZ /= STEP_DECREASE;
						//stairCases[chosenStairCase].dh /= STEP_DECREASE;
						//cout << "\n step decrease " << stairCases[chosenStairCase].dZ << endl;
						stairCases[chosenStairCase].reducedStep = true;
					}*/



					//	stairCases[chosenStairCase].reversalResults[stairCases[chosenStairCase].numReversals] = abs(p[0].z - p[1].z);// testCases[caseNumber].depthDiff);

					//record reversal result
					stairCases[chosenStairCase].reversalResults[stairCases[chosenStairCase].numReversals] = abs(testCases[caseNumber].depthDiff); //2 * pow(abs(testCases[caseNumber].depthDiff) / DEPTH_WARP_MID, DEPTH_WARP_INTENSITY)*DEPTH_WARP_MID;
					if (stairCases[chosenStairCase].reversalResults[stairCases[chosenStairCase].numReversals] > MAX_DEPTH_DIFF || stairCases[chosenStairCase].reversalResults[stairCases[chosenStairCase].numReversals] < -MAX_DEPTH_DIFF)
						stairCases[chosenStairCase].reversalResults[stairCases[chosenStairCase].numReversals] = MAX_DEPTH_DIFF;


					stairCases[chosenStairCase].numReversals++;
					stairCases[chosenStairCase].sumResults += testCases[caseNumber].depthDiff; //CHECK THIS!! abs(p[0].z - p[1].z);
					stairCases[chosenStairCase].numResults++;
				}
			}
			testCases[caseNumber].saveToFile();
			stairCases[chosenStairCase].lastCaseNumber = caseNumber;
		}
		printf("case number %d done.\n", caseNumber);
		caseNumber++;
		bool fin = true;
		for (int i = 0; i<NUM_STAIRCASES; i++)
		{
			if (stairCases[i].numReversals<EXIT_CONDITION)
			{
				fin = false;
				break;
			}
		}
		if (caseNumber>MAX_CASES - 1 || fin){
			endExperiment();
			
		}
		/*do{
			chosenStairCase = (int)(randNumber()*(NUM_STAIRCASES));

		} while (stairCases[chosenStairCase].numReversals >= EXIT_CONDITION);
		*/

		//stay on staircase until we reach man num reversals, we now work with blocks
		if(chosenStairCase<0)
			chosenStairCase = 0;
		if (stairCases[chosenStairCase].numReversals >= EXIT_CONDITION ){
			chosenStairCase++;
		}
	
		testCases[caseNumber].initialize(stairCases[chosenStairCase].alpha, stairCases[chosenStairCase].trans, stairCases[chosenStairCase].plcov, stairCases[chosenStairCase].type, stairCases[chosenStairCase].initialD, stairCases[chosenStairCase].tunnel, stairCases[chosenStairCase].headMotion, stairCases[chosenStairCase].initialX, stairCases[chosenStairCase].initialY, stairCases[chosenStairCase].initialZ, stairCases[chosenStairCase].initialh, stairCases[chosenStairCase].initialAvgX, stairCases[chosenStairCase].initialAvgY, stairCases[chosenStairCase].initialAvgZ, chosenStairCase);
	
		if (stairCases[chosenStairCase].lastCaseNumber != -1){
			stairCases[chosenStairCase].flag2down = testCases[caseNumber].increase(testCases[stairCases[chosenStairCase].lastCaseNumber], stairCases[chosenStairCase].flag2down, 0, stairCases[chosenStairCase].dX, stairCases[chosenStairCase].dY, stairCases[chosenStairCase].dZ, stairCases[chosenStairCase].dh);

		}
		initializeScene();
	}
	// else correct = false;

}



void keys(unsigned char key, int x, int y)
{
	if (key == ' ') {
		if (rest && !paused)
			rest = false;
		else
			paused = !paused;
		//rest = true;
		/*	if (paused = false){
		return;
		gettime(1, true);
		}*/
	}
	//	cout << paused << endl;
	if (key == '1') drawOne = 1;
	if (key == '2') drawOne = 0;

	if (key == 'r') planeAngle -= 3.1415 / 2 / 90;
	if (key == 'R') planeAngle += 3.1415 / 2 / 90;  // 2 degree increment

	if (key == 'f') surfOnly = 1;


	if (key == 'F') surfOnly = 0;

	if (key == 's')  spin += 3.1415 / 2 / 90;
	if (key == 'S')  spin -= 3.1415 / 2 / 90;

	if (key == 'j') { jitterscale += 0.05; initializeScene(); }
	if (key == 'J') if (jitterscale > 0) { jitterscale -= 0.05; initializeScene(); }

	if (key == 'c') { showClutter = 1; }
	if (key == 'C') { showClutter = 0; }

	if (key == 't') thickness--;
	if (key == 'T') thickness++;

	if (key == '[') mmPerModelUnit -= 10;
	if (key == ']') mmPerModelUnit += 10;

	if (key == '+') IOD++;
	if (key == '-') IOD--;

	/*if(key == 13)
	{
	double r=randNumber();
	caseNumber++;
	initializeScene();
	}*/

	if (key == ESCAPE_KEY){
		endExperiment();
		
	}

	if (key == '0'){
		//paused = false;// !paused;
		rest = false;
	}

	/*if(key == 'b'){
	toggleBlur = (toggleBlur+1)%2;
	}*/
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

/*void init(void)
{
	for (int i = 0; i<120; i++)
		pastviewers[i][0] = -10000;
	glEnable(GL_DEPTH_TEST);

	//   Here is code for doing texture mapping.

	glEnable(GL_TEXTURE_2D);
	makeBlurMask();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
	//					GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
	//					GL_NEAREST);	
	//	
	//  MIKE:  linear interpolation will run slower than nearest interpolation

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, maskWidth*numBlurWidths,
		maskWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		mask);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLfloat light_position[] = { 0.0, 1100.0, 1.0, 1.0 };
	GLfloat white_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diff_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat spec_light[] = { 1.0, 1.0, 1.0, 1.0 };
	glShadeModel(GL_SMOOTH);

	GLfloat mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}*/



int main(int argc, char **argv)
{
	

	/*  MIKE:

	There are three coordinate systems to think about:

	1.)  The virtual world coordinate system, or "model".  The origin is defined to be the center
	of the physical screen.  X+,Y+,Z+ are to the right, up, and out of the screen.
	We convert to its units (from mm) by dividing by mmPerModelUnit.

	2.)   The eye/viewer coordinate system.  The axes of the eye are parallel to the axes of the
	model.  But the eye/viewer moves over time and so 1 and 2 are related by a translation.

	3.)   The transmitter/tracker coordinate system.  Its origin is defined near the center of the
	transmitter.   The xyz axes *should* be parallel the axes of the model, so that we can transform
	between 1 and 3 by a translation only.  	 In our setup, the xyz's values measured by the tracker
	must be swapped and sign flipped so that the XYZ axes are indeed parallel.
	See the updateTrackerPosition method for details.

	*/
	rest = false;
	averageReds[0] = 0;
	averageReds[1] = 0;
	peakReds[0] = 0;
	peakReds[1] = 0;
	averageRedsCounter[0] = 0;
	averageRedsCounter[1] = 0;
	/*
	myScreen.width = 525;//383;    // 383 mm,   Since mmPerModelUnit is 120, the screen is about ___x___ model units
	myScreen.height = 295;//215.4;    // 215.4 mm

	myScreen.position.x = -650; //-640;  // mm, was -600
	myScreen.position.y = 200;// 215; //170;  //mm, was 300
	myScreen.position.z = -1260;//-1290;//-1000;  // -1075 -1170;  //  that is, relative to the tracker, it is over a metre in the -Z direction

	//myScreen.width = 521;    // 383 mm,   Since mmPerModelUnit is 120, the screen is about ___x___ model units
	//myScreen.height = 294;    // 215.4 mm

	//myScreen.position.x = -590 - 50;  // -640 mm, was -600
	myScreen.position.y = 280;// 270;// +150 - 50;  //170+150=books mm, was 300
	//myScreen.position.z = -1250;  // -1075 -1170;  //  that is, relative to the tracker, it is over a metre in the -Z direction
	fout.open("log.txt");
	fout2.open("tracking_log.txt");
	out.open("out.txt");
	*/

	myScreen.width = 521;    // 383 mm,   Since mmPerModelUnit is 120, the screen is about ___x___ model units
	myScreen.height = 294;    // 215.4 mm

	myScreen.position.x = -590 - 50;  // -640 mm, was -600
	myScreen.position.y = 295 + 150 - 50;  //170+150=books mm, was 300
	myScreen.position.z = -1250;  // -1075 -1170;  //  that is, relative to the tracker, it is over a metre in the -Z direction

	time_t randTime = time(0);
	string f1 = "log";
	f1 += to_string(randTime) + ".txt";
	fout.open(f1);
	//f1 = "fast_output";
	//f1 += to_string(randTime) + ".csv";
	//fout3.open(f1);
	fout2.open("tracking_log.txt");
	f1 = "thresholds";
	f1 += to_string(randTime) + ".csv";
	fout4.open(f1);

	//time_t randTime = time(0);
	srand(randTime);
	//com. by me
	//fout<<"rand seed: "<<randTime<<endl;

	int skipped = 0;
	int caseCount = 0;

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	/*vec4 pixcol = texture2D(tex, gl_TexCoord[0].xy);
	vec4 colors[3]; colors[0] = vec4(0.,0.,1.,1.); colors[1] = vec4(1.,1.,0.,1.);
	colors[2] = vec4(1.,0.,0.,1.);
	float lum = (pixcol.r+pixcol.g+pixcol.b)/3.;
	int ix = (lum < 0.5)? 0:1;
	vec4 thermal = mix(colors[ix],colors[ix+1],(lum-float(ix)*0.5)/0.5);*/
	for (int i = 0; i<RANDOM_DOT_SIZE; i++)
	for (int j = 0; j<RANDOM_DOT_SIZE; j++)
	{
		float r = 100 + (rand()*UINT_MAX) % 100;
		texturesh[i][j][0] = r;
		r = 100 + (rand()*UINT_MAX) % 100;
		texturesh[i][j][1] = r;
		r = 100 + (rand()*UINT_MAX) % 100;
		texturesh[i][j][2] = r;
		texturesh[i][j][3] = 255;
	}

	initializeTracker();
	glutInit(&argc, argv);
	//GLboolean	gbStereoEnabled = 0;
	//glGetBooleanv(GL_STEREO, &gbStereoEnabled);
	//if (gbStereoEnabled == 0)
	//	cout << "no stereo" << endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH| GLUT_STEREO);
	glutInitWindowSize(resolution.first, resolution.second);//1440,900
	frameBuffer = new unsigned char[resolution.first*resolution.second * 4];
	glutCreateWindow("clutteredScene");

	glutFullScreen(); //fullscreen
	ShowCursor(false);
	glutReshapeFunc(myReshape);
	//Antialiasing

	glEnable(GL_LINE_SMOOTH);


	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glLineWidth(LINE_WIDTH);

	//enableFog();   

	//init();
	specialKeys(GLUT_KEY_LEFT, 0, 0);

	glutDisplayFunc(stereoDisplay);
	glutKeyboardFunc(keys);
	glutSpecialFunc(specialKeys);




	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 1;
}
