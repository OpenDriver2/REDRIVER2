#include "driver2.h"
#include "pathfind.h"
#include "system.h"
#include "cop_ai.h"
#include "objcoll.h"
#include "dr2roads.h"
#include "players.h"
#include "cars.h"
#include "camera.h"
#include "felony.h"
#include "map.h"

#define DEBUG_PATHFINDING_VIEW	0

#if DEBUG_PATHFINDING_VIEW && !defined(PSX)
#include "SDL.h"
#include <stdint.h>
#endif

struct tNode
{
	int vx, vy, vz;
	u_short dist;
	u_short ptoey;	// just a padding. 
};

struct XZDIR
{
	short dx, dz;
};

// Fast Marching method
ushort distanceCache[16384];
char omap[128][16];				// obstacle map 128x128 (bit field)
int dunyet[32][2];				// scanned cell map (32x32, multi-level bitfield)
int pathIterations;

int pathFrames;
int DoExtraWorkForNFrames;

VECTOR searchTarget;
int playerTargetDistanceSq;

int distanceReturnedLog[8];
int distLogIndex;
int lastDistanceFound;

tNode heap[201];		// 198 + 3 extra?
u_int numHeapEntries = 0;

XZDIR ends[6][2] = {
	{
		{0, 0},
		{512, 0}
	},

	{
		{0, 0},
		{256, 512 }
	},

	{
		{256, 512},
		{512, 0}
	},

	{
		{256, 512},
		{-256, 512}
	},

	{
		{256, 512},
		{0, 1024}
	},
	{
		{256, 512 },
		{512, 1024}
	}
};

XZDIR dirs[6] = {
	{
		512,0
	},
	{
		256,-512
	},
	{
		-256,-512
	},
	{
		-512,0
	},
	{
		-256,512
	},
	{
		256,512
	},
};

// cx, cz in range of 0..128
#define OMAP_V(cx, cz)						omap[((cx) & 127)][((cz) & 127) >> 3]
#define OMAP_GETVALUE(cx, cz)				(OMAP_V(cx,cz) >> ((cz) & 7) & 1)

// cx, cz in range of 0...128
// FIXME: really bad
#define DONEMAP_V(cx, cz)					dunyet[((cx) & 31)][((cz) & 1)]
#define DONEMAP_GETVALUE(cx, cz, x, i)		(3 << ((cz) & 30) & (((((cx) & 63) >> 5 | (cz) & 2) ^ (i)) << ((cz) & 30) ^ (x)))

#define DISTMAP_V(px, py, pz)				distanceCache[((px) >> 2 & 16256 | (pz) >> 9 & 127) ^ ((py) & 1) * 8256 ^ ((py) & 2) << 12]

// [A] sets obstacle map bit
inline void OMapSet(int cellX, int cellZ, int val)
{
	u_char prev = OMAP_V(cellX, cellZ);
	int bit = (1 << (cellZ & 7));
	OMAP_V(cellX, cellZ) = prev ^ bit & (prev ^ (val ? 0xFF : 0));
}

// [A] debug obstacle map display with new debug window
void DebugDisplayObstacleMap()
{
#if DEBUG_PATHFINDING_VIEW && !defined(PSX)
	static SDL_Window* occlusionWindow;
	static SDL_Surface* occlSurface;
	static SDL_Texture* occlTexture;
	static SDL_Surface* windowSurf;

	if (!occlusionWindow)
	{
		occlusionWindow = SDL_CreateWindow("Data Graphics View", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_TOOLTIP);
		occlSurface = SDL_CreateRGBSurface(0, 128, 128, 24, 0xFF, 0xFF, 0xFF, 0);
	}

	SDL_LockSurface(occlSurface);

	int pos_x = player[0].pos[0] >> 8;
	int pos_z = player[0].pos[2] >> 8;
	int pos_y = player[0].pos[1];

	tNode n;
	n.vx = player[0].pos[0];
	n.vz = player[0].pos[2];
	n.vy = pos_y;
	//n.vy = MapHeight((VECTOR*)&n);

	for (int i = 0; i < 128; i++)
	{
		unsigned char* rgbLine = (unsigned char*)occlSurface->pixels + 128 * i * 3;

		for (int j = 0; j < 128; j++)
		{
			int px = pos_x + i - 64;
			int pz = pos_z + j - 64;

			if (OMAP_GETVALUE(px,pz))
			{
				rgbLine[j * 3] = 128;
				rgbLine[j * 3 + 1] = 128;
				rgbLine[j * 3 + 2] = 32;
			}
			else
			{
				rgbLine[j * 3] = 0;
				rgbLine[j * 3 + 1] = 0;
				rgbLine[j * 3 + 2] = 0;
			}

			//local_v0_152 = dunyet[(bPos.vx >> 10 & 0x1fU)][((bPos.vz >> 10) & 1)];

			// NEW METHOD
			// int val = dunyet[px >> 2 & 0x1f][pz >> 6 & 1]; // dunyet[px >> 2 & 0x1f][pz >> 2 & 1];
			// val = val >> (pz >> 2 & 0x1f) & 1;

			n.vx = px << 8;
			n.vz = pz << 8;
			n.vy = 0;// MapHeight((VECTOR*)&n);

			int dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (n.vy & 1U) * 0x2040 ^ (n.vy & 2U) << 0xc];// distanceCache[((pos_x+i & 127) * 128) + (j + pos_z & 127)];

			int prev = DONEMAP_V(px >> 2, pz >> 2);
			int val = DONEMAP_GETVALUE(px >> 2, pz >> 2, prev, 0);

			if (val != 0)
				rgbLine[j * 3] = 128;

			if (rgbLine[j * 3] == 0 && rgbLine[j * 3 + 2] == 0)
				rgbLine[j * 3 + 1] = dist / 64;
		}
	}

	SDL_UnlockSurface(occlSurface);

	windowSurf = SDL_GetWindowSurface(occlusionWindow);

	SDL_Rect rect;
	rect.x = 1;
	rect.y = 1;
	rect.w = 511;
	rect.h = 511;

	SDL_BlitScaled(occlSurface, NULL, windowSurf, &rect);
	SDL_UpdateWindowSurface(occlusionWindow);

	SDL_FreeSurface(windowSurf);
#endif
}

// [D] [T]
void popNode(tNode* __return_storage_ptr__)
{
	int num;
	int child;
	ushort d;
	int here;
	tNode res;
	ushort lastDist;

	here = 1;
	res = heap[here];

	if (numHeapEntries > 1) 
	{
		lastDist = heap[numHeapEntries].dist;

		while (true) 
		{
			child = here * 2;
			
			// [A] not sure yet but skipping this check causes memory overflow
			// it doesn't makes much sense to increase heap size either as it works the same.
			if (child + 1 >= 201)
				break;
			
			d = heap[child].dist;

			if (child >= numHeapEntries - 2 || d > heap[child + 1].dist)
			{
				d = heap[child + 1].dist;
				child++;
			}

			if ((numHeapEntries - 2 < child) || (lastDist <= d))
				break;

			copyVector(&heap[here], &heap[child]);
			heap[here].dist = d;

			here = child;
		}

		heap[here] = heap[numHeapEntries];
	}

	numHeapEntries--;

	*__return_storage_ptr__ = res;
}

// [D] [T]
void WunCell(VECTOR* pbase)
{
	VECTOR v[2];
	int height1;
	int i, j;

#if ENABLE_GAME_FIXES
	// start with the base (player) height
	height1 = pbase->vy;

	pbase->vx += 512;
	pbase->vz += 512;

	v[0].vy = MapHeight(pbase);

	pbase->vx -= 512;
	pbase->vz -= 512;

	// if base height differs from map height too much (we are on bridge etc)
	// we then use base height to ensure that obstacles are locally correct
	if (ABS(height1 - v[0].vy) > 100)
		v[0].vy = height1;

	v[0].vy += 32;
	v[1].vy = v[0].vy;

	// [A] definitely better code
	// new 16 vs old 12 passes but map is not leaky at all
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			v[0].vx = pbase->vx + i * 256 + 128;
			v[0].vz = pbase->vz + j * 256 + 128;

			OMapSet(v[0].vx >> 8, v[0].vz >> 8, CellAtPositionEmpty(&v[0], 128) == 0);
		}
	}
#else
	pbase->vx = pbase->vx + 512;
	pbase->vz = pbase->vz + 512;

	height1 = MapHeight(pbase);

	v[0].vy = height1 + 60;

	pbase->vx = pbase->vx - 512;
	pbase->vz = pbase->vz - 512;
	v[1].vy = v[0].vy;

	for (i = 0; i < 2; i++) 
	{
		if (i != 0)
			pbase->vx += 512;

		v[0].vx = pbase->vx;
		v[0].vz = pbase->vz;

		for (j = 0; j < 6; j++)
		{
			int dx, dz;
			v[0].vx = pbase->vx + ends[j][0].dx;
			v[0].vz = pbase->vz + ends[j][0].dz;

			v[1].vx = pbase->vx + ends[j][1].dx;
			v[1].vz = pbase->vz + ends[j][1].dz;

			dx = v[0].vx + v[1].vx >> 1;
			dz = v[0].vz + v[1].vz >> 1;

			OMapSet(dx >> 8, dz >> 8, lineClear(&v[0], &v[1]) == 0);
		}

		if (i != 0)
			pbase->vx -= 512;
	}
#endif
}

// [A] function that invalidates map at ends
// fixes bug with not being able to update navigation cells
void InvalidateMapEnds()
{
	int x, z;
	int tile;
	int i;
	XZPAIR pos;
	pos.x = (player[0].pos[0] & ~1023) >> 10;
	pos.z = (player[0].pos[2] & ~1023) >> 10;

	for(i = 0; i < 32; i++)
	{
		x = pos.x + 15 + i;
		z = pos.z + 16;
		
		tile = DONEMAP_V(x, z);
		DONEMAP_V(x, z) = tile ^ DONEMAP_GETVALUE(x, z, tile, 3);

		x = pos.x + 16;
		z = pos.z + 15 + i;

		tile = DONEMAP_V(x, z);
		DONEMAP_V(x, z) = tile ^ DONEMAP_GETVALUE(x, z, tile, 3);
	}
}

// [D] [T]
void InvalidateMap(void)
{
	int dir;
	int p, q;
	int count;
	int px, pz;
	VECTOR bPos;
	int tile, i;

	q = 0;
	p = 0;
	dir = 0;

	bPos.vx = player[0].pos[0] & ~1023;
	bPos.vz = player[0].pos[2] & ~1023;

	for(count = 0; count < 1024; count++)
	{
		px = bPos.vx >> 10;
		pz = bPos.vz >> 10;
	
		tile = DONEMAP_V(px, pz);
		i = DONEMAP_GETVALUE(px, pz, tile, 3);

		DONEMAP_V(px, pz) = tile ^ i;
		
		if (dir == 0)
		{
			bPos.vx += MAP_CELL_SIZE / 2;
			dir = (++p + q == 1) ? 1 : dir;
		}
		else if (dir == 1)
		{
			bPos.vz += MAP_CELL_SIZE / 2;
			dir = (p == ++q) ? 2 : dir;
		}
		else if (dir == 2)
		{
			bPos.vx -= MAP_CELL_SIZE / 2;
			dir = (--p + q == 0) ? 3 : dir;
		}
		else
		{
			bPos.vz -= MAP_CELL_SIZE / 2;
			dir = (p == --q) ? 0 : dir;
		}
	}
}


u_int cellsThisFrame;
u_int cellsPerFrame = 4;

// [D] [T]
void BloodyHell(void)
{
	VECTOR bPos;
	int dir;
	int p, q;
	int px, pz;
	u_int howMany;
	int count;
	int tile, i;

	cellsThisFrame = 0;
	
	// [A] really it should be based on player's height
	bPos.vy = player[0].pos[1];
	bPos.vx = player[0].pos[0] & ~1023;
	bPos.vz = player[0].pos[2] & ~1023;

	howMany = cellsPerFrame;

	if (CameraCnt < 4)
		howMany = cellsPerFrame + 20;
	
	if (CameraCnt < 8)
		howMany += 4;

	q = 0;
	p = 0;
	dir = 0;

#if ENABLE_GAME_FIXES
	InvalidateMapEnds();
#endif

	for (count = 0; count < 840; count++)
	{
		if (count == 200)
			howMany--;

		px = bPos.vx >> 10;
		pz = bPos.vz >> 10;

		tile = DONEMAP_V(px, pz);
		i = DONEMAP_GETVALUE(px, pz, tile, 0);

		if (i != 0)
		{
			DONEMAP_V(px, pz) = tile ^ i;
			WunCell(&bPos);

			if (++cellsThisFrame >= howMany)
				return;
		}

		if (dir == 0)
		{
			bPos.vx += MAP_CELL_SIZE / 2;
			dir = (++p + q == 1) ? 1 : dir;
		}
		else if (dir == 1)
		{
			bPos.vz += MAP_CELL_SIZE / 2;
			dir = (p == ++q) ? 2 : dir;
		}
		else if (dir == 2)
		{
			bPos.vx -= MAP_CELL_SIZE / 2;
			dir = (--p + q == 0) ? 3 : dir;
		}
		else
		{
			bPos.vz -= MAP_CELL_SIZE / 2;
			dir = (p == --q) ? 0 : dir;
		}
	}
}

int slowWallTests = 0;

// [D] [T]
int blocked(tNode* v1, tNode* v2)
{
	int x, z;

	if (slowWallTests != 0)
		return lineClear((VECTOR*)v1, (VECTOR*)v2) == 0;

	x = v1->vx + v2->vx >> 9;
	z = v1->vz + v2->vz >> 9;

	int prev = DONEMAP_V(x >> 2, z >> 2);
	int val = DONEMAP_GETVALUE(x >> 2, z >> 2, prev, 0);
	
	if (val != 0)
		return 1;

	return OMAP_GETVALUE(x, z);
}

// [D] [T]
void setDistance(tNode* n, ushort dist)
{
	n->dist = dist | 1;	// valid bit for this frame

	DISTMAP_V(n->vx, n->vy, n->vz) = dist | 1;
}

// [A]
void pushNode(tNode* startNode, ushort dist);

// [D] [T]
int iterate(void)
{
	tNode pathNodes[8];

	int dist;
	tNode* nbr;
	int dir;
	tNode itHere;

	ushort nl, nr;
	int a;
	u_int pnode;
	u_int parent;
	u_int i;
	int r;

	if (numHeapEntries == 0)
		return 0;

	popNode(&itHere);
	nbr = pathNodes;

	// check directions
	for(dir = 0; dir < 6; dir++, nbr++)
	{
		nbr->vx = itHere.vx + dirs[dir].dx;
		nbr->vy = itHere.vy;
		nbr->vz = itHere.vz + dirs[dir].dz;

		dist = DISTMAP_V(nbr->vx, nbr->vy, nbr->vz);

		nbr->dist = dist;

		if ((dist & 1) == 0)
		{
			if (blocked(&itHere, nbr) == 0)
			{
				if (ABS(nbr->vy - itHere.vy) < 201)
				{
					nbr->dist = 0;
					continue;
				}
			}
	
			nbr->dist = 1;
		}
		else if (dist <= itHere.dist - 288)
		{
			nbr->dist = 1;
		}
	}
	
	// now we have distance let's compute the rest of the map
	for(dir = 0; dir < 6; dir++)
	{
		// visited?
		if (pathNodes[dir].dist != 0)
			continue;

		if (dir != 5)
			nr = pathNodes[dir + 1].dist;
		else
			nr = pathNodes[0].dist;

		if (dir != 0)
			nl = pathNodes[dir - 1].dist;
		else
			nl = pathNodes[5].dist;

		// uhhmm... distance function selection?
		if (nl < 2)
		{
			if (nr < 2)
				dist = itHere.dist + 256;
			else
				dist = (nr + itHere.dist >> 1) + 221;
		}
		else if (nr < 2)
		{
			dist = (nl + itHere.dist >> 1) + 221;
		}
		else
		{
			r = nr - nl;
			dist = 0x10000 - (r * r) / 3;

			if (dist < 0)
			{
				dist = 0;
			}
			else
			{
				a = (dist >> 9) + 128;
				dist = dist / a + a >> 1;
			}

			dist += itHere.dist;
		}

		pushNode(&pathNodes[dir], dist);
	}

	return numHeapEntries > 0;
}

// [D] [T]
void InitPathFinding(void)
{
	int i;

	setMem16((ushort*)distanceCache, 0xfffe, sizeof(distanceCache) / sizeof(short));
	ClearMem((char*)omap, sizeof(omap));
	ClearMem((char*)dunyet, sizeof(dunyet));
	InvalidateMap();

	lastDistanceFound = 18000;

	for (i = 0; i < 8; i++)
		distanceReturnedLog[i++] = 18000;

	pathFrames = 80;
	DoExtraWorkForNFrames = 6;
	distLogIndex = 0;
	searchTarget.vx = 0;
	searchTarget.vy = -12367;
	searchTarget.vz = 0;
	playerTargetDistanceSq = 0;
	//pathFrames = 0;
	pathIterations = 129;
}

extern int sdLevel; // D2ROADS

// [D] [T]
int getInterpolatedDistance(VECTOR* pos)
{
	int x, res;
	int dist, min;
	int a,b,c;
	int fx, fz;
	tNode n;
	VECTOR sp;

	// WHY?
	n.vx = ((pos->vx + (pos->vz >> 1 & 511)) >> 9) * 512 - ((pos->vz & 512) >> 1);
	n.vy = pos->vy;
	n.vz = (pos->vz >> 9) << 9;

	if (OMAP_GETVALUE(n.vx >> 8, n.vz >> 8) != 0)
	{
		n.vy = MapHeight((VECTOR*)&n);
		n.vy = n.vy ^ (n.vy ^ sdLevel) & 3;
	}
	else
	{
		n.vy = 0;
	}

	fz = pos->vz - n.vz;
	fx = (pos->vx - n.vx) + (fz >> 1);

	sp.vx = n.vx + 256;
	sp.vz = n.vz + 512;

	n.dist = DISTMAP_V(n.vx, n.vy, n.vz);
	a = n.dist;

	n.vx = sp.vx;
	n.vz = sp.vz;

	if (OMAP_GETVALUE(sp.vx >> 8, sp.vz >> 8) != 0)
	{
		n.vy = MapHeight((VECTOR*)&n);
		n.vy = n.vy ^ (n.vy ^ sdLevel) & 3;
	}
	else
	{
		n.vy = 0;
	}

	n.dist = DISTMAP_V(n.vx, n.vy, n.vz);
	b = n.dist;
	
	if (a < b)
		min = a;
	else
		min = b;

	if (fz < fx)
	{
		n.vx = sp.vx + 256;
		n.vz = sp.vz - 512;
		
		if (OMAP_GETVALUE(n.vx >> 8, n.vz >> 8) != 0)
		{
			n.vy = MapHeight((VECTOR*)&n);
			n.vy = n.vy ^ (n.vy ^ sdLevel) & 3;
		}
		else
		{
			n.vy = 0;
		}
	
		dist = DISTMAP_V(n.vx, n.vy, n.vz);
		
		if (min < dist)
			c = min;
		else
			c = dist;
	
		c += 341;
		
		if (c > 0xffff)
			c = 0xffff;
		else if (a > c)
			a = c;

		if (b > c)
			b = c;

		x = dist - a;
	
		if (c < dist)
		{
			x = c - a;
			dist = c;
		}
		
		x = x * fx;
		res = (b - dist) * fz;
	}
	else
	{
		n.vx = sp.vx - 512;
		n.vz = sp.vz;

		if (OMAP_GETVALUE(n.vx >> 8, n.vz >> 8) != 0)
		{
			n.vy = MapHeight((VECTOR*)&n);
			n.vy = n.vy ^ (n.vy ^ sdLevel) & 3;
		}
		else
		{
			n.vy = 0;
		}

		dist = DISTMAP_V(n.vx, n.vy, n.vz);
		
		if (min < dist)
			c = min;
		else
			c = dist;

		c += 341;

		if (c > 0xffff)
			c = 0xffff;
		else if (a > c)
			a = c;

		if (b > c)
			b = c;

		x = dist - a;
	
		if (c < dist)
		{
			x = c - a;
			dist = c;
		}
		
		x = x * fz;
		res = (b - dist) * fx;
	}

	a = a + (x + res >> 9);
	
	lastDistanceFound = a ^ (a & 1 ^ a) & 1;

	return lastDistanceFound;
}

// [D] [T]
void addCivs(void)
{
	unsigned char bits;
	int rx, rz;
	int x, z, vx, vz;
	int vx2, vz2;
	CAR_DATA* cp;

	cp = car_data;
	do {
		if (cp->controlType == CONTROL_TYPE_CIV_AI)
		{
			rx = cp->hd.oBox.radii[2].vx;
			rz = cp->hd.oBox.radii[2].vz;
			
			x = cp->hd.oBox.location.vx;
			z = cp->hd.oBox.location.vz;
	
			vx = x + rx >> 8;
			vz = z + rz >> 8;

			bits = 3 << (vz & 6);

			OMAP_V(vx, vz) ^= bits;
			OMAP_V(vx+1, vz) ^= bits;

			vx2 = x - rx >> 8;
			vz2 = z - rz >> 8;
			
			if ((vx ^ (vz & 0x7e) << 8) == vx2 && 
				(vz2 & 0x7e) != 0 || (vz2 & 0x7e << 8) != 1)
			{
				bits = 3 << (vz2 & 6);

				OMAP_V(vx2, vz2) ^= bits;
				OMAP_V(vx2+1, vz2) ^= bits;
			}
		}

		cp++;
	} while (cp < &car_data[MAX_CARS - 1]);
}

// [A]
void pushNode(tNode* node, ushort dist)
{
	int i;
	u_int pnode, parent;

	if (numHeapEntries == 198)
		return;

	setDistance(node, dist);

	// up heap
	i = numHeapEntries + 1;

	pnode = i;
	parent = i >> 1;

	while (parent != 0 && dist < heap[parent].dist)
	{
		heap[i] = heap[parent];

		pnode = parent;
		parent >>= 1;
	}

	heap[pnode] = *node;
	numHeapEntries++;
}

// [A]
void pushSeedNode(tNode* startNode)
{
	u_short dist;
	int i, dx, dz;

	if (numHeapEntries == 198)
		return;

	dx = startNode->vx - searchTarget.vx;
	dz = startNode->vz - searchTarget.vz;

	dist = SquareRoot0(	dx * dx + dz * dz ) >> 1;

	pushNode(startNode, dist);
}

// [D] [T]
void UpdateCopMap(void)
{
	int i, d;
	int dx, dy, dz;
	int maxret, res;
	tNode startNode;

	BloodyHell();

	// quickly invalidate and do extra
	if (player_position_known == 1 || CameraCnt == 6)
	{
		pathFrames = 0;
		setMem16((ushort*)distanceCache, 0xfffe, 0x4000);
		DoExtraWorkForNFrames = 3;
	}

	if (pathFrames != 0)
	{
		int iterations;

		// add cars
		addCivs();

		iterations = cellsThisFrame;

		if (iterations > 6)
			iterations = 6;

		i = pathIterations - iterations * 4 * 4 - iterations * 5;

		if (DoExtraWorkForNFrames != 0)
		{
			DoExtraWorkForNFrames--;
			i += 60;
		}

		if (i < 36)
			i = 36;

		while (--i >= 0)
		{
			if (!iterate())
			{
				pathFrames = 0;
				break;
			}
		}

		DebugDisplayObstacleMap();
		
		// remove cars
		addCivs();
	}
	
	if(pathFrames == 0)
	{
		// restart from new search target position
		if (player[0].playerType == 1 && (CopsCanSeePlayer != 0 || numActiveCops == 0))
		{
			CAR_DATA* cp;
			cp = &car_data[player[0].playerCarId];

			searchTarget.vx = cp->hd.where.t[0] + FIXEDH(cp->st.n.linearVelocity[0]) * 8;
			searchTarget.vy = cp->hd.where.t[1] + FIXEDH(cp->st.n.linearVelocity[1]) * 4;
			searchTarget.vz = cp->hd.where.t[2] + FIXEDH(cp->st.n.linearVelocity[2]) * 8;
		}
		else if (searchTarget.vy == -12367)
		{
			searchTarget.vx = player[0].pos[0];
			searchTarget.vy = player[0].pos[1];
			searchTarget.vz = player[0].pos[2];
		}

		// step up distance frame (and invalidate by setting bit 1)
		for (i = 0; i < 16384; i++)
		{
			d = distanceCache[i] + 8192;

			if ((d & 1) != 0)
				d ^= 1;

			if (d > 0xfffe)
				d = 0xfffe;

			distanceCache[i] = d;
		}
		
		startNode.vx = ((searchTarget.vx + (searchTarget.vz >> 1 & 511)) >> 9) * 512 - ((searchTarget.vz & 512) >> 1);
		startNode.vz = (searchTarget.vz >> 9) << 9;
		startNode.vy = searchTarget.vy;
		
		numHeapEntries = 0;

		// pick the height
		if(OMAP_GETVALUE(startNode.vx >> 8, startNode.vz >> 8) != 0)
		{
			res = MapHeight((VECTOR*)&startNode);
			startNode.vy = res ^ (res ^ sdLevel) & 3;
		}
		else
		{
			startNode.vy = 0;
		}

		dx = searchTarget.vx - startNode.vx;
		dz = searchTarget.vz - startNode.vz;

		if (dz < dx + dz / 2)
		{
			pushSeedNode(&startNode);

			startNode.vx += 256;
			startNode.vz += 512;
			
			pushSeedNode(&startNode);

			startNode.vx += 256;
			startNode.vz -= 512;

			pushSeedNode(&startNode);
		}
		else
		{
			pushSeedNode(&startNode);

			startNode.vx += 256;
			startNode.vz += 512;
	
			pushSeedNode(&startNode);
			
			startNode.vx -= 512;
			
			pushSeedNode(&startNode);
		}
	}

	pathFrames++;

	maxret = 0;
	for(i = 0; i < 8; i++)
	{
		if (distanceReturnedLog[i] > maxret)
			maxret = distanceReturnedLog[i];
	}

	if (pathFrames > 250 ||		 // [A] was (pathFrames < pathFrames)
		heap[1].dist - maxret > 3000) 
	{
		pathFrames = 0;
	}

	dx = searchTarget.vx - player[0].pos[0] >> 4;
	dy = searchTarget.vy - player[0].pos[1] >> 4;
	dz = searchTarget.vz - player[0].pos[2] >> 4;

	playerTargetDistanceSq = dx * dx + dy * dy + dz * dz;
}

// [D] [T]
int getHeadingToPlayer(int vx, int vy, int vz)
{
	int d1, d2, d3;
	int playerHereDistSq;
	int dx, dy, dz;
	int val;
	VECTOR pos;

	dx = vx - player[0].pos[0] >> 4;
	dy = vy - player[0].pos[1] >> 4;
	dz = vz - player[0].pos[2] >> 4;

	val = 4004;

	playerHereDistSq = (dx * dx + dy * dy + dz * dz);

	if (playerTargetDistanceSq * 2 <= playerHereDistSq * 3)
	{
		pos.vy = vy;

		pos.vx = vx - 128;
		pos.vz = vz - 128;

		d1 = getInterpolatedDistance(&pos);

		pos.vx = vx + 128;
		pos.vz = vz - 128;
		d2 = getInterpolatedDistance(&pos);

		pos.vz = vz + 128;
		pos.vx = vx;
		d3 = getInterpolatedDistance(&pos);

		if (d3 > 61440)
		{
			ReplayLog_Fnarr_He_Said_Log(0x3e9);

			dx = lastKnownPosition.vx - pos.vx;
			dz = lastKnownPosition.vz - pos.vz;

			return ratan2(dx, dz) + 4096;
		}

		val = 0xbbb;

		if (d3 > 1536)
		{
			ReplayLog_Fnarr_He_Said_Log(0x7d2);

			return ratan2((d1 - d2) * 2, d1 + d2 - d3 * 2) & 0xfff;
		}
	}

	ReplayLog_Fnarr_He_Said_Log(val);

	dx = player[0].pos[0] - vx;
	dz = player[0].pos[2] - vz;

	return ratan2(dx, dz) + 4096;
}
