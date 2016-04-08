#include "stdafx.h"
#include "Mesh.h"
#include <math.h>
#include <iostream>
using namespace std;
#define PI			3.1415926
#define	COLORNUM		13
#define	COLORNUM2		14


float	ColorArr[COLORNUM2][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts=8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set( fSize, fSize, fSize);
	pt[2].set( fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set( fSize, -fSize, fSize);
	pt[6].set( fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);

	numFaces= 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for(i = 0; i<face[5].nVerts ; i++)
		face[5].vert[i].colorIndex = 5;

}


void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}

void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			float x = pt[iv].x;
			float y = pt[iv].y;
			float z = pt[iv].z;
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

// Draw color with light
void Mesh::Draw() {
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(face[f].facenorm.x, face[f].facenorm.y, face[f].facenorm.z);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ){
	int i;
	numVerts = 8;
	pt = new Point3[numVerts];
	double x = 0;
	double y = 0;
	double z = 0;
	//upper
	x = -fSizeX / 2;
	y = fSizeY / 2;
	z = fSizeZ / 2;
	pt[0].set(x,y,z);

	x = fSizeX / 2;
	y = fSizeY / 2;
	z = fSizeZ / 2;
	pt[1].set(x, y, z);

	x = fSizeX / 2;
	y = fSizeY / 2;
	z = -fSizeZ / 2;
	pt[2].set(x, y, z);

	x = -fSizeX / 2;
	y = fSizeY / 2;
	z = -fSizeZ / 2;
	pt[3].set(x, y, z);

	//below
	x = -fSizeX / 2;
	y = -fSizeY / 2;
	z = fSizeZ / 2;
	pt[4].set(x, y, z);

	x = fSizeX / 2;
	y = -fSizeY / 2;
	z = fSizeZ / 2;
	pt[5].set(x, y, z);

	x = fSizeX / 2;
	y = -fSizeY / 2;
	z = -fSizeZ / 2;
	pt[6].set(x, y, z);

	x = -fSizeX / 2;
	y = -fSizeY / 2;
	z = -fSizeZ / 2;
	pt[7].set(x, y, z);

	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 4;
	face[0].vert[2].vertIndex = 7;
	face[0].vert[3].vertIndex = 3;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 1;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 6;
	face[1].vert[3].vertIndex = 2;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 4;
	face[3].vert[1].vertIndex = 5;
	face[3].vert[2].vertIndex = 6;
	face[3].vert[3].vertIndex = 7;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 0;
	face[4].vert[1].vertIndex = 4;
	face[4].vert[2].vertIndex = 5;
	face[4].vert[3].vertIndex = 1;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 7;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 2;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	// calculate norm vertor
	this->CalculateFacesNorm();
}

void Mesh::CreatePlane(float size) {
	numVerts = 4;
	pt = new Point3[numVerts];
	numFaces = 1;
	face = new Face[numFaces];
	pt[0].set(size, size, 0);
	pt[1].set(-size, size, 0);
	pt[2].set(-size, -size, 0);
	pt[3].set(size, -size, 0);

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;

	this->CalculateFacesNorm();
}

void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius){
	numVerts = 2 * nSegment + 2;
	pt = new Point3[numVerts];
	numFaces = 3 * nSegment;
	face = new Face[numFaces];

	pt[0].set(0, fHeight / 2, 0);
	pt[numVerts - 1].set(0, -fHeight / 2, 0);

	int colour_val = -1;

	float x = 0;
	float y = 0;
	float z = 0;

	int run = 1;
	float c = PI / 180;
	float angel = 360 / nSegment;
	for (float phi = 0; phi < 360; phi+=angel){
		pt[run].set(fRadius*cos(c*phi), fHeight/2, fRadius*sin(c*phi));
		run++;
	}

	for (float phi = 0; phi < 360; phi += angel){
		pt[run].set(fRadius*cos(c*phi), -fHeight/2, fRadius*sin(c*phi));
		run++;
	}


	//upper
	for (int i = 0; i < nSegment; i++){
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == 0){
			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = 1;
			face[i].vert[2].vertIndex = 2;
		}
		else if (i == (nSegment - 1)){
			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = 1;
		}
		else{
			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = face[i - 1].vert[2].vertIndex+1;
		}
		this->GetColour(colour_val);
		for (int k = 0; k < face[i].nVerts; k++){
			face[i].vert[k].colorIndex = colour_val;
		}
	}
	//below
	for (int i = nSegment; i < 2*nSegment; i++){
		face[i].nVerts = 3;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == nSegment){
			face[i].vert[0].vertIndex = numVerts - 1;
			face[i].vert[1].vertIndex = nSegment + 1;
			face[i].vert[2].vertIndex = nSegment + 2;
		}

		else if (i == (2*nSegment - 1)){
			face[i].vert[0].vertIndex = numVerts - 1;
			face[i].vert[1].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = nSegment + 1;
		}
		else{
			face[i].vert[0].vertIndex = numVerts - 1;
			face[i].vert[1].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = face[i - 1].vert[2].vertIndex + 1;
		}
		this->GetColour(colour_val);
		for (int k = 0; k < face[i].nVerts; k++){
			face[i].vert[k].colorIndex = colour_val;
		}
	}

	//surround
	run = 1;
	for (int i = 2*nSegment; i < 3 * nSegment; i++){
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == 2*nSegment){
			face[i].vert[0].vertIndex = run;
			face[i].vert[1].vertIndex = run + 1;
			face[i].vert[2].vertIndex = nSegment + run + 1;
			face[i].vert[3].vertIndex = nSegment + run;
		}
		else if (i == (3*nSegment - 1)){
			face[i].vert[0].vertIndex = face[i - 1].vert[1].vertIndex;
			face[i].vert[1].vertIndex = face[2*nSegment].vert[0].vertIndex;
			face[i].vert[2].vertIndex = face[2 * nSegment].vert[3].vertIndex;
			face[i].vert[3].vertIndex = face[i - 1].vert[2].vertIndex;
		}
		else{
			face[i].vert[0].vertIndex = face[i - 1].vert[1].vertIndex;
			face[i].vert[1].vertIndex = face[i - 1].vert[1].vertIndex + 1;
			face[i].vert[2].vertIndex = face[i - 1].vert[2].vertIndex + 1;
			face[i].vert[3].vertIndex = face[i - 1].vert[2].vertIndex;
		}
		this->GetColour(colour_val);
		for (int k = 0; k < face[i].nVerts; k++){
			face[i].vert[k].colorIndex = colour_val;
		}
		run++;
	}
	// calculate norm vertor
	this->CalculateFacesNorm();
}

void Mesh::CreateSphere(int nSlice, int nStack, float radius){
	int colour_val = -1;
	int i, j;
	double phi; //
	double theta; //long
	float p[31][31][3]; //Vertex
	int count = -2;
	if (nSlice > 30) nSlice = 30;
	if (nStack > 30) nStack = 30;
	
	//create faces
	if (nSlice == 1){
		numFaces = 0;
	}
	else{
		numFaces = nSlice*nStack;
	}
	face = new Face[numFaces];
	//create points
	if (nSlice == 1){
		numVerts = nStack + 1;
	}
	else{
		numVerts = nSlice*(nStack - 1) + 2;
	}

	pt = new Point3[numVerts];
	
	int run = 0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float x = 0;
	float y = 0;
	float z = 0;
	//Vertex
	bool firstTime = true;
//	Points_For_Sphere(pt, nSlice, nStack, radius, run);


	//for (int i = 0; i <= nSlice; i++)
	//{
	//	phi = 2.0 * PI * (double)i / (double)nSlice;
	//	if (firstTime){
	//		for (int j = 0; j <= nStack; j++)
	//		{
	//			theta = PI * (double)j / (double)nStack;
	//			x = (float)(radius * sin(theta) * cos(phi));//x
	//			z = (float)(radius * sin(theta) * sin(phi));//z
	//			y = (float)(radius * cos(theta));           //y
	//			pt[run].set(x, y, z);
	//			run++;
	//		}
	//		firstTime = false;
	//	}
	//	else{
	//		for (int j = 1; j < nStack; j++)
	//		{
	//			theta = PI * (double)j / (double)nStack;
	//			x = (float)(radius * sin(theta) * cos(phi));//x
	//			z = (float)(radius * sin(theta) * sin(phi));//z
	//			y = (float)(radius * cos(theta));           //y
	//			pt[run].set(x, y, z);
	//			run++;
	//		}
	//	}
	//}
	for (i = 0; i < nSlice; i++)
	{
		phi = 2.0 * PI * (double)i / (double)nSlice;
		for (j = 0; j <= nStack; j++)
		{
			theta = PI * (double)j / (double)nStack;
			p[i][j][0] = (float)(radius * sin(theta) * cos(phi));//x
			p[i][j][2] = (float)(radius * sin(theta) * sin(phi));//z
			p[i][j][1] = (float)(radius * cos(theta));           //y
		}
	}

	for (i = 0; i < nSlice; i++)
	{
		if (firstTime){
			for (j = 0; j <= nStack; j++){
				pt[run].set(p[i][j][0], p[i][j][1], p[i][j][2]);
				run++;
			}
			firstTime = false;
		}
		else{
			for (j = 1; j < nStack; j++){
				pt[run].set(p[i][j][0], p[i][j][1], p[i][j][2]);
				run++;
			}
			firstTime = false;
		}
	}

	//numVerts = numVerts - count;
	int start = 0;
	//Top(j=0)
	int pos = 0;
	i = 0; //pos of Slice
	for (pos = 0; pos < nSlice; pos++)
	{
		face[pos].nVerts = 3;
		face[pos].vert = new VertexID[face[pos].nVerts];
		face[pos].vert[0].vertIndex = 0;
		if (i == 0){
			start = pos;
			face[pos].vert[1].vertIndex = 1;
			face[pos].vert[2].vertIndex = nStack + 1;
		}
		else if (i == (nSlice - 1)){
			face[pos].vert[1].vertIndex = face[pos - 1].vert[2].vertIndex;
			face[pos].vert[2].vertIndex = face[start].vert[1].vertIndex;
		}
		else{
			face[pos].vert[1].vertIndex = face[pos - 1].vert[2].vertIndex;
			face[pos].vert[2].vertIndex = face[pos - 1].vert[2].vertIndex + nStack - 1;
		}
		this->GetColour(colour_val);
		for (int k = 0; k < face[pos].nVerts; k++){
			face[pos].vert[k].colorIndex = colour_val;
		}
		i++;
	}
	//Bottom
	j = nStack - 1;
	i = 0; //pos of Slice
	for (; pos < 2*nSlice; pos++)
	{

		face[pos].nVerts = 3;
		face[pos].vert = new VertexID[face[pos].nVerts];
		face[pos].vert[0].vertIndex = nStack;
		if (i == 0){
			start = pos;
			face[pos].vert[1].vertIndex = nStack - 1;;
			face[pos].vert[2].vertIndex = nStack +(nStack-1);
		}
		else if (i == (nSlice - 1)){
			face[pos - 1].vert[2].vertIndex;
			face[start].vert[1].vertIndex;
			face[pos].vert[1].vertIndex = face[pos - 1].vert[2].vertIndex;
			face[pos].vert[2].vertIndex = face[start].vert[1].vertIndex;
		}
		else{
			face[pos].vert[1].vertIndex = face[pos - 1].vert[2].vertIndex;
			face[pos].vert[2].vertIndex = face[pos - 1].vert[2].vertIndex + nStack - 1;
		}
		this->GetColour(colour_val);
		for (int k = 0; k < face[pos].nVerts; k++){
			face[pos].vert[k].colorIndex = colour_val;
		}
		i++;
	}

	i = 0;
	while (pos < numFaces){
		for (int stack = 1; stack < nStack - 1; stack++){
			i = 0;
			while (i < nSlice){
				face[pos].nVerts = 4;
				face[pos].vert = new VertexID[face[pos].nVerts];
				if (i == 0){
					start = pos;
					face[pos].vert[0].vertIndex = stack;
					face[pos].vert[1].vertIndex = stack + 1;
					face[pos].vert[3].vertIndex = stack + nStack;
					face[pos].vert[2].vertIndex = stack + nStack + 1;
				}
				else if (i == (nSlice - 1)){
					face[pos].vert[0].vertIndex = face[pos - 1].vert[3].vertIndex;
					face[pos].vert[1].vertIndex = face[pos - 1].vert[2].vertIndex;
					face[pos].vert[3].vertIndex = face[start].vert[0].vertIndex;
					face[pos].vert[2].vertIndex = face[start].vert[1].vertIndex;
				}
				else{
					face[pos].vert[0].vertIndex = face[pos - 1].vert[3].vertIndex;
					face[pos].vert[1].vertIndex = face[pos - 1].vert[2].vertIndex;
					face[pos].vert[3].vertIndex = face[pos - 1].vert[3].vertIndex + nStack - 1;
					face[pos].vert[2].vertIndex = face[pos - 1].vert[3].vertIndex + nStack;
				}
				this->GetColour(colour_val);
				for (int k = 0; k < face[pos].nVerts; k++){
					face[pos].vert[k].colorIndex = colour_val;
				}
				pos++;
				i++;

			}
		}
	}
	// calculate norm vertor
	this->CalculateFacesNorm();
}


int Mesh::GetColour(int& colour){
	if (colour > COLORNUM){
		colour = 0;
		return colour;
	}
	else{
		colour++;
		return colour;
	}
}

void Mesh::Points_For_Sphere(Point3* pt,int nSlice, int nStack,int radius,int& run){
	bool firstTime = true;
	float x = 0;
	float y = 0;
	float z = 0;
	double phi = 0;
	double theta = 0;

	for (int i = 0; i <= nSlice; i++)
	{
		phi = 2.0 * PI * (double)i / (double)nSlice;
		if (firstTime){
			for (int j = 0; j <= nStack; j++)
			{
				theta = PI * (double)j / (double)nStack;
				x = (float)(radius * sin(theta) * cos(phi));//x
				z = (float)(radius * sin(theta) * sin(phi));//z
				y = (float)(radius * cos(theta));           //y
				pt[run].set(x, y, z);
				run++;
			}
			firstTime = false;
		}
		else{
			for (int j = 1; j < nStack; j++)
			{
				theta = PI * (double)j / (double)nStack;
				x = (float)(radius * sin(theta) * cos(phi));//x
				z = (float)(radius * sin(theta) * sin(phi));//z
				y = (float)(radius * cos(theta));           //y
				pt[run].set(x, y, z);
				run++;
			}
		}

	}
}

void Mesh::CreateGeometryShape_Large(float R1, float R2,float Height,float distance){
	float C1[3];
	float C2[3];
	int colour_val = -1;
	float D1[3];
	float D2[3];
	float p[8];
	C1[0] = 0;
	C1[1] = 0;
	C1[2] = R1;
	C2[0] = R1 + R2 + distance;
	C2[1] = 0;
	C2[2] = R2;
/*
	C1[0] = 2;
	C1[1] = 4;
	C1[2] = R1;
	C2[0] = 1;
	C2[1] = 1;
	C2[2] = R2;*/
	float xA = 0;
	float yA = 0;
	TangentLine_Get_Through(C1, C2, xA, yA);
	TangentLine(C1, C2, xA, yA, D1, D2);
	float a1 = D1[0];
	float b1 = D1[1];
	float c1 = D1[2];
	float a2 = D2[0];
	float b2 = D2[1];
	float c2 = D2[2];
	TangentLine_Cut_Circle(C1, C2, xA, yA, D1, D2, p);
	

	float c = PI / 180;
	int split = 50;
	float angel = 0;
	float x_cal = 0;
	float y_cal = 0;

	numVerts = 4 * split;
	numFaces = 2 * (split - 1) + 4;
	pt = new Point3[numVerts];
	face = new Face[numFaces];
	int run = 0;

	if (R1 < R2){
		float v1_x = p[0] - xA;
		float v1_y = p[1] - yA;
		float cos_val = abs(v1_x) / (sqrt(v1_x*v1_x + v1_y*v1_y));
		float phi_start = 180 * c - (90 * c - acos(cos_val));

		for (float i = 0; i<split; i++){
			angel = phi_start + i * 2 * (180 * c - phi_start) / split;
			x_cal = C1[0] + R1*cos(angel);
			y_cal = C1[1] + R1*sin(angel);
			pt[run].set(x_cal, 0, y_cal);
			run++;
		}

		for (float i = 0; i<split; i++){
			angel = phi_start + i * 2 * (180 * c - phi_start) / split;
			x_cal = C1[0] + R1*cos(angel);
			y_cal = C1[1] + R1*sin(angel);
			pt[run].set(x_cal, Height, y_cal);
			run++;
		}

		v1_x = p[2] - xA;
		v1_y = p[3] - yA;
		cos_val = abs(v1_x) / (sqrt(v1_x*v1_x + v1_y*v1_y));
		phi_start = (90 * c - acos(cos_val));

		for (float i = 0; i<split; i++){
			angel = (180 * c - phi_start) - i * 2 * (180 * c - phi_start) / split;
			x_cal = C2[0] + R2*cos(angel);
			y_cal = C2[1] + R2*sin(angel);
			pt[run].set(x_cal, 0, y_cal);
			run++;
		}

		for (float i = 0; i<split; i++){
			angel = (180 * c - phi_start) - i * 2 * (180 * c - phi_start) / split;
			x_cal = C2[0] + R2*cos(angel);
			y_cal = C2[1] + R2*sin(angel);
			pt[run].set(x_cal, Height, y_cal);
			run++;
		}
/*		run = 0;
		while (run != 400){
			cout << pt[run].x <<" " << pt[run].y <<" " << pt[run].z<<endl;
			run++;
		}	*/	
	}
	else if (R1>R2){

		//similar with R1<R2

		float v1_x = p[0] - xA;
		float v1_y = p[1] - yA;
		float cos_val = abs(v1_x) / (sqrt(v1_x*v1_x + v1_y*v1_y));
		float phi_start = (90 * c - acos(cos_val));

		for (float i = 0; i<split; i++){
			angel = phi_start + i * 2 * (180 * c - phi_start) / split;
			x_cal = C1[0] + R1*cos(angel);
			y_cal = C1[1] + R1*sin(angel);
			pt[run].set(x_cal, 0, y_cal);
			run++;
		}

		for (float i = 0; i<split; i++){
			angel = phi_start + i * 2 * (180 * c - phi_start) / split;
			x_cal = C1[0] + R1*cos(angel);
			y_cal = C1[1] + R1*sin(angel);
			pt[run].set(x_cal, Height, y_cal);
			run++;
		}

		v1_x = p[2] - xA;
		v1_y = p[3] - yA;
		cos_val = abs(v1_x) / (sqrt(v1_x*v1_x + v1_y*v1_y));
		phi_start = (90 * c - acos(cos_val));

		for (float i = 0; i<split; i++){
			angel = (phi_start) - i * 2 * (phi_start) / split;
			x_cal = C2[0] + R2*cos(angel);
			y_cal = C2[1] + R2*sin(angel);
			pt[run].set(x_cal, 0, y_cal);
			run++;
		}

		for (float i = 0; i<split; i++){
			angel = (phi_start) - i * 2 * (phi_start) / split;
			x_cal = C2[0] + R2*cos(angel);
			y_cal = C2[1] + R2*sin(angel);
			pt[run].set(x_cal, Height, y_cal);
			run++;
		}
	}
	else{
		float phi_start = (90 * c);

		for (float i = 0; i<split; i++){
			angel = phi_start + i * 2 * (180 * c - phi_start) / split;
			x_cal = C1[0] + R1*cos(angel);
			y_cal = C1[1] + R1*sin(angel);
			pt[run].set(x_cal, 0, y_cal);
			run++;
		}

		for (float i = 0; i<split; i++){
			angel = phi_start + i * 2 * (180 * c - phi_start) / split;
			x_cal = C1[0] + R1*cos(angel);
			y_cal = C1[1] + R1*sin(angel);
			pt[run].set(x_cal, Height, y_cal);
			run++;
		}

		phi_start = (90 * c);

		for (float i = 0; i<split; i++){
			angel = (phi_start)-i * 2 * (phi_start) / split;
			x_cal = C2[0] + R2*cos(angel);
			y_cal = C2[1] + R2*sin(angel);
			pt[run].set(x_cal, 0, y_cal);
			run++;
		}

		for (float i = 0; i<split; i++){
			angel = (phi_start)-i * 2 * (phi_start) / split;
			x_cal = C2[0] + R2*cos(angel);
			y_cal = C2[1] + R2*sin(angel);
			pt[run].set(x_cal, Height, y_cal);
			run++;
		}
	}


	//Start create points and faces
	run = 0;
	for (int i = 0; i < split - 1; i++){
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == 0){
			face[i].vert[0].vertIndex = 0;
			face[i].vert[1].vertIndex = 1;
			face[i].vert[3].vertIndex = split;
			face[i].vert[2].vertIndex = split + 1;
		}
		else if (i == split - 3){
			face[i].vert[0].vertIndex = face[i - 1].vert[1].vertIndex;
			face[i].vert[1].vertIndex = face[i - 1].vert[1].vertIndex + 1;
			face[i].vert[3].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = face[i - 1].vert[2].vertIndex + 1;
		}
		else {
			face[i].vert[0].vertIndex = face[i - 1].vert[1].vertIndex;
			face[i].vert[1].vertIndex = face[i - 1].vert[1].vertIndex + 1;
			face[i].vert[3].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = face[i - 1].vert[2].vertIndex + 1;
		}
		this->GetColour(colour_val);
		for (int k = 0; k<face[i].nVerts; k++)
			face[i].vert[k].colorIndex = colour_val;

	}

	for (int i = split - 1; i < 2 * split - 2; i++){
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		if (i == split - 1){
			face[i].vert[0].vertIndex = 2 * split;
			face[i].vert[1].vertIndex = 2 * split + 1;
			face[i].vert[3].vertIndex = 3 * split;
			face[i].vert[2].vertIndex = 3 * split + 1;
		}
		else {
			face[i].vert[0].vertIndex = face[i - 1].vert[1].vertIndex;
			face[i].vert[1].vertIndex = face[i - 1].vert[1].vertIndex + 1;
			face[i].vert[3].vertIndex = face[i - 1].vert[2].vertIndex;
			face[i].vert[2].vertIndex = face[i - 1].vert[2].vertIndex + 1;
		}
		this->GetColour(colour_val);
		for (int k = 0; k<face[i].nVerts; k++)
			face[i].vert[k].colorIndex = colour_val;
	}

	face[2 * split - 2].nVerts = 4;
	face[2 * split - 2].vert = new VertexID[face[2 * split - 2].nVerts];
	face[2 * split - 2].vert[0].vertIndex = split - 1;
	face[2 * split - 2].vert[1].vertIndex = 2 * split - 1;
	face[2 * split - 2].vert[3].vertIndex = 3 * split - 1;
	face[2 * split - 2].vert[2].vertIndex = 4 * split - 1;
	this->GetColour(colour_val);
	for (int k = 0; k<face[2 * split - 2].nVerts; k++)
		face[2 * split - 2].vert[k].colorIndex = colour_val;

	face[2 * split - 1].nVerts = 4;
	face[2 * split - 1].vert = new VertexID[face[2 * split - 2].nVerts];
	face[2 * split - 1].vert[0].vertIndex = 0;
	face[2 * split - 1].vert[1].vertIndex = split;
	face[2 * split - 1].vert[2].vertIndex = 3 * split;
	face[2 * split - 1].vert[3].vertIndex = 2 * split;

	this->GetColour(colour_val);
	for (int k = 0; k < face[2 * split - 1].nVerts; k++)
		face[2 * split - 1].vert[k].colorIndex = colour_val;


	face[2 * split].nVerts = 2 * split;
	face[2 * split].vert = new VertexID[face[2 * split].nVerts];
	run = 0;
	for (int i = split; i < 2 * split; i++){
		face[2 * split].vert[run].vertIndex = i;
		run++;
	}
	for (int i = 4 * split - 1; i > 3 * split - 1; i--){
		face[2 * split].vert[run].vertIndex = i;
		run++;
	}
	this->GetColour(colour_val);
	for (int k = 0; k < face[2 * split].nVerts; k++)
		face[2 * split].vert[k].colorIndex = colour_val;



	face[2 * split + 1].nVerts = 2 * split;
	face[2 * split + 1].vert = new VertexID[face[2 * split + 1].nVerts];

	run = 0;
	for (int i = 0; i < split; i++){
		face[2 * split + 1].vert[run].vertIndex = i;
		run++;
	}
	for (int i = 3 * split - 1; i > 2 * split - 1; i--){
		face[2 * split + 1].vert[run].vertIndex = i;
		run++;
	}
	this->GetColour(colour_val);
	for (int k = 0; k < face[2 * split + 1].nVerts; k++)
		face[2 * split + 1].vert[k].colorIndex = colour_val;
	// calculate norm vertor
	this->CalculateFacesNorm();
}


// Tim 2 cap diem ma duong tiep tuyen cat 2 duong tron
void Mesh::TangentLine_Cut_Circle(float C1[3], float C2[3], float x, float y, float *D1, float *D2, float* p){
	float heso_a = (-D1[1])*(-D1[1]) + 1;
	float heso_b = 2 * (-D1[1])*(-D1[2] - C1[0]) - 2 * (C1[1]);
	float heso_c = (-D1[2] - C1[0])*(-D1[2] - C1[0]) + C1[1] * C1[1] - C1[2] * C1[2];
	float fillForFull=0;
	SolveQuadFormula(heso_a, heso_b, heso_c, p[1], fillForFull);
	p[0] = -D1[1] * p[1] - D1[2];

	heso_a = (-D1[1])*(-D1[1]) + 1;
	heso_b = 2 * (-D1[1])*(-D1[2] - C2[0]) - 2 * (C2[1]);
	heso_c = (-D1[2] - C2[0])*(-D1[2] - C2[0]) + C2[1] * C2[1] - C2[2] * C2[2];
	SolveQuadFormula(heso_a, heso_b, heso_c, p[3], fillForFull);
	p[2] = -D1[1] * p[3] - D1[2];

	heso_a = (-D2[1])*(-D2[1]) + 1;
	heso_b = 2 * (-D2[1])*(-D2[2] - C1[0]) - 2 * (C1[1]);
	heso_c = (-D2[2] - C1[0])*(-D2[2] - C1[0]) + C1[1] * C1[1] - C1[2] * C1[2];
	SolveQuadFormula(heso_a, heso_b, heso_c, p[5], fillForFull);
	p[4] = -D2[1] * p[5] - D2[2];

	heso_a = (-D2[1])*(-D2[1]) + 1;
	heso_b = 2 * (-D2[1])*(-D2[2] - C2[0]) - 2 * (C2[1]);
	heso_c = (-D2[2] - C2[0])*(-D2[2] - C2[0]) + C2[1] * C2[1] - C2[2] * C2[2];
	SolveQuadFormula(heso_a, heso_b, heso_c, p[7], fillForFull);
	p[6] = -D2[1] * p[7] - D2[2];
}


//pt khoang cach tu C1 den duong thang: a(x-xA) + b*(y-yA)=0
void Mesh::TangentLine(float C1[3], float C2[3], float xA, float yA, float *D1, float *D2){
	float first = (C1[0] - xA) / C1[2];
	float second = (C1[1] - yA) / C1[2];
	//float third = ;
	D1[0] = D2[0] = 1;
	float heso_a = second*second - 1;
	float heso_b = 2 * first*second;
	float heso_c = first*first - 1;
	float val1 = 0;
	float val2 = 0;
	SolveQuadFormula(heso_a, heso_b, heso_c, D1[1], D2[1]);
	D1[2] = -D1[0] * xA - D1[1] * yA;
	D2[2] = -D2[0] * xA - D2[1] * yA;
}
	

//Tiep tuyen chung ngoai se di qua diem co toa do (x;y)
void Mesh::TangentLine_Get_Through(float C1[3], float C2[3], float& x, float& y){
	float ratio = C1[2] / C2[2];
	x = (ratio*C2[0] - C1[0]) / (ratio - 1);
	y = (ratio*C2[1] - C1[1]) / (ratio - 1);
}

void Mesh::SolveQuadFormula(float a, float b, float c, float& val1, float& val2){
	float delta = b*b - 4 * a*c;
	val1 = (-b + sqrt(abs(delta))) / (2 * a);
	val2 = (-b-sqrt(abs(delta)))/(2*a);
}


//////////////////////////////////////////////LAB 3/////////////////////////////////////////////////////////////////

void Mesh::SetColor(int colorIdx){
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}


void Mesh::CreateMixShape(int nSegment, float fHeight, float fDistance, float fRadius1, float fRadius2)
{
	int i, j;
	float phi, phiup, x, y;

	phiup = 180 / nSegment;
	phi = -90;

	numVerts = nSegment * 4;
	pt = new Point3[numVerts];


	for (i = 0; i<nSegment; i++) {
		x = fDistance + fRadius1*cos((phi + phiup*i)*PI / 180);
		y = fRadius1*sin((phi + phiup*i)*PI / 180);
		pt[i].set(x, 0, y);
		pt[i + nSegment].set(x, fHeight, y);
	}

	phi = 90;
	for (i = nSegment * 2; i<nSegment * 3; i++) {
		x = fRadius2*cos((phi + phiup*i)*PI / 180);
		y = fRadius2*sin((phi + phiup*i)*PI / 180);
		pt[i].set(x, 0, y);
		pt[i + nSegment].set(x, fHeight, y);
	}

	numFaces = nSegment * 2 + 4;
	face = new Face[numFaces];

	//Body
	for (i = 0; i<nSegment; i++) {
		if (i + 1 == nSegment){
			face[2 * nSegment].nVerts = 4;
			face[2 * nSegment].vert = new VertexID[face[2 * nSegment].nVerts];
			face[2 * nSegment].vert[0].vertIndex = i;
			face[2 * nSegment].vert[1].vertIndex = nSegment * 2;
			face[2 * nSegment].vert[2].vertIndex = nSegment * 3;
			face[2 * nSegment].vert[3].vertIndex = nSegment * 2 - 1;
			for (j = 0; j<face[nSegment * 2].nVerts; j++)
				face[nSegment * 2].vert[j].colorIndex = 1;
		}
		else {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = i;
			face[i].vert[1].vertIndex = i + 1;
			face[i].vert[2].vertIndex = i + nSegment + 1;
			face[i].vert[3].vertIndex = i + nSegment;
			for (j = 0; j<face[i].nVerts; j++)
				face[i].vert[j].colorIndex = i;
		}

	}

	for (i = nSegment; i<2 * nSegment; i++) {
		if (i + 1 == 2 * nSegment){
			face[2 * nSegment + 1].nVerts = 4;
			face[2 * nSegment + 1].vert = new VertexID[face[2 * nSegment + 1].nVerts];
			face[2 * nSegment + 1].vert[0].vertIndex = i + nSegment;
			face[2 * nSegment + 1].vert[1].vertIndex = 0;
			face[2 * nSegment + 1].vert[2].vertIndex = nSegment;
			face[2 * nSegment + 1].vert[3].vertIndex = i + nSegment * 2;
			for (j = 0; j<face[nSegment * 2].nVerts; j++)
				face[nSegment * 2].vert[j].colorIndex = 1;
		}
		else {
			face[i].nVerts = 4;
			face[i].vert = new VertexID[face[i].nVerts];
			face[i].vert[0].vertIndex = i + nSegment;
			face[i].vert[1].vertIndex = i + nSegment + 1;
			face[i].vert[2].vertIndex = i + 2 * nSegment + 1;
			face[i].vert[3].vertIndex = i + 2 * nSegment;
			for (j = 0; j<face[i].nVerts; j++)
				face[i].vert[j].colorIndex = i;
		}
	}
	//top
	face[nSegment * 2 + 2].nVerts = 2 * nSegment;
	face[nSegment * 2 + 2].vert = new VertexID[face[nSegment * 2 + 2].nVerts];
	j = 0;
	for (i = nSegment; i<2 * nSegment; i++) {
		face[nSegment * 2 + 2].vert[j].vertIndex = i;
		face[nSegment * 2 + 2].vert[j].colorIndex = 13;
		j++;
	}
	for (i = 3 * nSegment; i<4 * nSegment; i++) {
		face[nSegment * 2 + 2].vert[j].vertIndex = i;
		face[nSegment * 2 + 2].vert[j].colorIndex = 13;
		j++;
	}
	//bottom
	face[nSegment * 2 + 3].nVerts = 2 * nSegment;
	face[nSegment * 2 + 3].vert = new VertexID[face[nSegment * 2 + 3].nVerts];
	j = 0;
	for (i = 0; i<nSegment; i++) {
		face[nSegment * 2 + 3].vert[j].vertIndex = i;
		face[nSegment * 2 + 3].vert[j].colorIndex = 13;
		j++;
	}
	for (i = 2 * nSegment; i<3 * nSegment; i++) {
		face[nSegment * 2 + 3].vert[j].vertIndex = i;
		face[nSegment * 2 + 3].vert[j].colorIndex = 13;
		j++;
	}
}

void Mesh::CalculateFacesNorm()
{
	for (int i = 0; i < this->numFaces; i++)
	{
		Face* face = &this->face[i];
		float normx = 0, normy = 0, normz = 0;
		for (int j = 0; j <= face->nVerts; j++)
		{
			VertexID id = face->vert[(j % face->nVerts)];
			VertexID next = face->vert[(j + 1) % face->nVerts];
			int index = id.vertIndex;
			int nextidx = next.vertIndex;
			float x = pt[index].x, nextx = pt[nextidx].x,
				y = pt[index].y, nexty = pt[nextidx].y,
				z = pt[index].z, nextz = pt[nextidx].z;
			// Martin Newell algorithm
			normx += (y - nexty) * (z + nextz);
			normy += (x + nextx) * (z - nextz);
			normz += (x - nextx) * (y + nexty);
			
		}
		face->facenorm.x = normx;
		face->facenorm.y = normy;
		face->facenorm.z = normz;
		face->facenorm.normalize();
		printf("%d ", face->vert[0].vertIndex);
	}
}

void Mesh::setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}
