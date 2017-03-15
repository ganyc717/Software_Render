#pragma once

const float CubeL = 0.5;

float cube_vertex[] = {
-CubeL,-CubeL,-CubeL,
CubeL,-CubeL,-CubeL,
CubeL,-CubeL,CubeL,

CubeL,-CubeL,CubeL,
-CubeL,-CubeL,CubeL,
-CubeL,-CubeL,-CubeL,

-CubeL,-CubeL,-CubeL,
CubeL,-CubeL,-CubeL,
CubeL,CubeL,CubeL,

CubeL,CubeL,-CubeL,
-CubeL,CubeL,-CubeL,
-CubeL,-CubeL,-CubeL,

CubeL,-CubeL,-CubeL,
CubeL,-CubeL,CubeL,
CubeL,CubeL,-CubeL,

CubeL,CubeL,-CubeL,
CubeL,CubeL,CubeL,
CubeL,-CubeL,CubeL,

-CubeL,-CubeL,-CubeL,
-CubeL,-CubeL,CubeL,
-CubeL,CubeL,-CubeL,

-CubeL,CubeL,-CubeL,
-CubeL,CubeL,CubeL,
-CubeL,-CubeL,CubeL,

-CubeL,CubeL,-CubeL,
CubeL,CubeL,-CubeL,
-CubeL,CubeL,CubeL,

-CubeL,CubeL,CubeL,
CubeL,CubeL,CubeL,
CubeL,CubeL,-CubeL,

-CubeL,CubeL,CubeL,
CubeL,CubeL,CubeL,
-CubeL,-CubeL,CubeL,

-CubeL,-CubeL,CubeL,
CubeL,-CubeL,CubeL,
CubeL,CubeL,CubeL,
};










/*
float cube_vertex[] = {
	3.0,0.0,3.0,
	6.0,0.0,3.0,
	6.0,0.0,6.0,

	6.0,0.0,6.0,
	3.0,0.0,6.0,
	3.0,0.0,3.0,

	3.0,0.0,3.0,
	6.0,0.0,3.0,
	6.0,3.0,3.0,

	6.0,3.0,3.0,
	3.0,3.0,3.0,
	3.0,0.0,3.0,

	6.0,0.0,3.0,
	6.0,0.0,6.0,
	6.0,3.0,3.0,

	6.0,3.0,3.0,
	6.0,3.0,6.0,
	6.0,0.0,6.0,

	3.0,0.0,3.0,
	3.0,0.0,6.0,
	3.0,3.0,3.0,

	3.0,3.0,3.0,
	3.0,3.0,6.0,
	3.0,0.0,6.0,

	3.0,3.0,3.0,
	6.0,3.0,3.0,
	3.0,3.0,6.0,

	3.0,3.0,6.0,
	6.0,3.0,6.0,
	6.0,3.0,3.0,

	3.0,3.0,6.0,
	6.0,3.0,6.0,
	3.0,0.0,6.0,

	3.0,0.0,6.0,
	6.0,0.0,6.0,
	6.0,3.0,6.0,
};
*/
float cube_texcoord[] = {
	0.0,0.0,  0.0,1.0,  1.0,1.0,
	1.0,1.0,  1.0,0.0,  0.0,0.0,

	0.0,0.0,  0.0,1.0,  1.0,1.0,
	1.0,1.0,  1.0,0.0,  0.0,0.0,

	0.0,0.0,  0.0,1.0,  1.0,1.0,
	1.0,1.0,  1.0,0.0,  0.0,0.0,

	0.0,0.0,  0.0,1.0,  1.0,1.0,
	1.0,1.0,  1.0,0.0,  0.0,0.0,

	0.0,0.0,  0.0,1.0,  1.0,1.0,
	1.0,1.0,  1.0,0.0,  0.0,0.0,

	0.0,0.0,  0.0,1.0,  1.0,1.0,
	1.0,1.0,  1.0,0.0,  0.0,0.0,
};

/*
const float cube[] = {
3.0,0.0,3.0,
6.0,0.0,3.0,
6.0,0.0,6.0,
3.0,0.0,6.0,
3.0,3.0,3.0,
6.0,3.0,3.0,
6.0,3.0,6.0,
3.0,3.0,6.0
};*/

/*
const float cube[] = {
	3.0,0.0,3.0,
	6.0,0.0,3.0,
	6.0,0.0,6.0,
	3.0,0.0,6.0,
	3.0,3.0,3.0,
	6.0,3.0,3.0,
	6.0,3.0,6.0,
	3.0,3.0,6.0
};

const float cube_texcoord[] = {
	0.0,0.0,
	0.0,1.0,
	1.0,1.0,
	1.0,0.0,
};

const int cube_vertex_index[] = {
	0,1,2,
	2,3,0,
	0,1,5,
	5,4,0,
	1,2,5,
	5,6,2,
	0,3,4,
	4,7,3,
	4,5,7,
	7,6,5,
	7,6,3,
	3,2,6
};

const int cube_texcoord_index[]
{
	0,1,2,
	2,3,0,
	0,1,2,
	2,3,0,
	0,1,2,
	2,3,0,
	0,1,2,
	2,3,0,
	0,1,2,
	2,3,0,
	0,1,2,
	2,3,0
}*/