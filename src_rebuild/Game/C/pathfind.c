#include "driver2.h"
#include "pathfind.h"
#include "system.h"
#include "cop_ai.h"
#include "objcoll.h"
#include "dr2roads.h"
#include "players.h"
#include "cars.h"
#include "camera.h"

#include <stdint.h>

#include "map.h"
#include "SDL.h"

struct tNode
{
	int vx;
	int vy;
	int vz;
	u_short dist;
	u_short ptoey;
};

struct XZDIR
{
	short dx;
	short dz;
};

ushort distanceCache[16384];
char omap[128][16];				// obstacle map
int dunyet[32][2];				// scanned cell map
int pathIterations;

int pathFrames;
int DoExtraWorkForNFrames;

VECTOR searchTarget;
int playerTargetDistanceSq;

int distanceReturnedLog[8];
int distLogIndex;
int lastDistanceFound;

tNode heap[201];
unsigned int numHeapEntries = 0;

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
#define OMAP_V(cx, cz)						omap[((cx) & 0x7f)][((cz) & 0x7f) >> 3]
#define OMAP_GETVALUE(cx, cz)				(OMAP_V(cx,cz) >> ((cz) & 7) & 1)

// cx, cz in range of 0...128
// FIXME: really bad
#define DONEMAP_V(cx, cz)					dunyet[(cx & 0x1fU)][(cz & 1)]
#define DONEMAP_GETVALUE(cx, cz, x, i)		(3 << (cz & 0x1e) & ((((cx & 0x3fU) >> 5 | cz & 2) ^ i) << (cz & 0x1e) ^ x))

#define DISTMAP_V(px, py, pz)				distanceCache[(px >> 2 & 0x3f80U | pz >> 9 & 0x7fU) ^ (py & 1) * 0x2040 ^ (py & 2) << 0xc]

// [A] sets obstacle map bit
inline void OMapSet(int cellX, int cellZ, int val)
{
	unsigned char prev = OMAP_V(cellX, cellZ);
	int bit = (1 << (cellZ & 7));
	OMAP_V(cellX, cellZ) = prev ^ bit & (prev ^ (val ? 0xFF : 0));
}

// [A] debug obstacle map display with new debug window
void DebugDisplayObstacleMap()
{
#if defined(_DEBUG) && 0
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
	n.vy = MapHeight((VECTOR*)&n);

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
			n.vy = MapHeight((VECTOR*)&n);

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
tNode* popNode(tNode* __return_storage_ptr__)
{
	uint child;
	ushort d;
	uint here;
	tNode res;

	res = heap[1];

	if (numHeapEntries > 1)
	{
		here = 1;

		while (true)
		{
			child = here + 1;

			d = heap[child].dist;

			if (child >= numHeapEntries - 2 || d > heap[child + 1].dist)
			{
				d = heap[child + 1].dist;
				child = child + 1;
			}

			if (child > numHeapEntries - 2 || d >= heap[numHeapEntries].dist)
				break;

			heap[here] = heap[child];

			here = child;
		}

		heap[here] = heap[numHeapEntries];
	}

	numHeapEntries--;

	*__return_storage_ptr__ = res;
	return __return_storage_ptr__;
}

// [D] [T]
void WunCell(VECTOR* pbase)
{
	VECTOR v[2];
	int height1;
	int i, j;

	// [A] hack with height map (fixes some bits in Havana)
	height1 = MapHeight(pbase);
	
	pbase->vx += 512;
	pbase->vz += 512;

	v[0].vy = MapHeight(pbase);

	pbase->vx -= 512;
	pbase->vz -= 512;

	if (height1 - v[0].vy > 100)
		v[0].vy = height1;

	v[0].vy += 32;
	v[1].vy = v[0].vy;

	// [A] definitely better code
	// new 16 vs old 12 passes but map is not leaky at all#
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			v[0].vx = pbase->vx + i * 256 + 128;
			v[0].vz = pbase->vz + j * 256 + 128;

			OMapSet(v[0].vx >> 8, v[0].vz >> 8, CellAtPositionEmpty(&v[0], 128) == 0);
		}
	}
}

// [A] function that invalidates map at ends
// fixes bug with not being able to update navigation cells
void InvalidateMapEnds()
{
	int x, z;
	int tile;
	int i;
	XZPAIR pos;
	pos.x = (player[0].pos[0] & 0xfffffc00) >> 10;
	pos.z = (player[0].pos[2] & 0xfffffc00) >> 10;

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
	int p;
	int q;
	int count;
	int px, pz;
	VECTOR bPos;
	int tile, i;

	q = 0;
	p = 0;
	dir = 0;

	bPos.vx = player[0].pos[0] & 0xfffffc00;
	bPos.vz = player[0].pos[2] & 0xfffffc00;

	count = 0;
	do
	{
		px = bPos.vx >> 10;
		pz = bPos.vz >> 10;
	
		tile = DONEMAP_V(px, pz);
		i = DONEMAP_GETVALUE(px, pz, tile, 3);

		DONEMAP_V(px, pz) = tile ^ i;
		
		if (dir == 0)
		{
			p++;
			bPos.vx += MAP_CELL_SIZE;

			if (p + q == 1)
				dir = 1;
		}
		else if (dir == 1)
		{
			q++;
			bPos.vz += MAP_CELL_SIZE;

			if (p == q)
				dir = 2;
		}
		else if (dir == 2)
		{
			p--;
			bPos.vx -= MAP_CELL_SIZE;

			if (p + q == 0)
				dir = 3;
		}
		else
		{
			q--;
			bPos.vz -= MAP_CELL_SIZE;
	
			if (p == q)
				dir = 0;
		}

		count++;
	}while (count < 1024);
}


unsigned int cellsThisFrame;
unsigned int cellsPerFrame = 4;

// [D] [T]
void BloodyHell(void)
{
	int dir;
	int p;
	int q;
	int px, pz;
	uint howMany;
	int count;
	VECTOR bPos;
	int tile, i;

	cellsThisFrame = 0;
	
	// [A] really it should be based on player's height
	bPos.vy = player[0].pos[1] ;

	bPos.vx = player[0].pos[0] & 0xfffffc00;
	bPos.vz = player[0].pos[2] & 0xfffffc00;

	howMany = cellsPerFrame;

	if (CameraCnt < 4)
		howMany = cellsPerFrame + 20;

	q = 0;
	
	if (CameraCnt < 8)
		howMany += 4;

	p = 0;
	dir = 0;
	count = 0;

	InvalidateMapEnds();

	do {
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

			cellsThisFrame++;

			if (howMany <= cellsThisFrame)
				return;
		}

		if (dir == 0)
		{
			p++;
			bPos.vx += MAP_CELL_SIZE;

			if (p + q == 1)
				dir = 1;
		}
		else if (dir == 1) 
		{
			q++;
			bPos.vz += MAP_CELL_SIZE;
			
			if (p == q)
				dir = 2;
		}
		else if (dir == 2)
		{
			p--;

			bPos.vx -= MAP_CELL_SIZE;

			if (p + q == 0)
				dir = 3;
		}
		else 
		{
			q--;
			bPos.vz -= MAP_CELL_SIZE;

			if (p == q)
				dir = 0;
		}

		count++;
	} while( count < 840 );
}

int slowWallTests = 0;

// [D] [T]
int blocked(tNode* v1, tNode* v2)
{
	int x, z, dmtile;

	if (slowWallTests != 0)
		return lineClear((VECTOR*)v1, (VECTOR*)v2) == 0;

	x = v1->vx + v1->vx >> 9;
	z = v1->vz + v2->vz >> 9;

	return OMAP_GETVALUE(x, z);
}

// [D] [T]
void setDistance(tNode* n, ushort dist)
{
	n->dist = dist | 1;	// valid bit for this frame

	distanceCache[(n->vx >> 2 & 0x3f80U | n->vz >> 9 & 0x7fU) ^ (n->vy & 1U) * 0x2040 ^ (n->vy & 2U) << 0xc] = dist | 1;
}

// [D] [T]
void iterate(void)
{
	tNode pathNodes[250];

	int dist;
	tNode* nbr;
	int dir;
	tNode itHere;

	ushort nr;
	ushort nl;
	int a;
	uint pnode;
	uint parent;
	uint i;
	int r;

	if (numHeapEntries == 0)
		return;

	popNode(&itHere);
	nbr = pathNodes;

	// check directions
	for(dir = 0; dir < 6; dir++)
	{
		nbr++;

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
					if ((dist & 1) == 0)
						nbr->dist = 0;

					continue;
				}
			}
	
			nbr->dist = 1;
		}
		else
		{
			if (dist <= itHere.dist - 288)
			{
				nbr->dist = 1;
			}
		}
	}

	// now we have distance let's compute the rest of the map
	for(dir = 0; dir < 6; dir++)
	{
		if (pathNodes[dir + 1].dist != 0)
			continue;

		if (dir != 5)
			nr = pathNodes[dir + 2].dist;
		else
			nr = pathNodes[1].dist;

		if (dir != 0)
			nl = pathNodes[dir].dist;
		else
			nl = pathNodes[6].dist;

		// uhhmm... distance function selection?
		if (nl < 2)
		{
			if (nr < 2)
				dist = itHere.dist + 256;
			else
				dist = (nr + itHere.dist >> 1) + 221;
		}
		else
		{
			if (nr < 2)
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
		}

		dist &= 0xffff;

		// store distance and get to the next lesser node
		if (numHeapEntries != 198)
		{
			setDistance(pathNodes + dir + 1, dist);
				
			i = numHeapEntries + 1;

			pnode = i;
			parent = i >> 1;
			
			while (parent != 0 && dist < heap[parent].dist)
			{
				heap[i] = heap[parent];

				pnode = parent;
				parent >>= 1;
			}

			heap[pnode] = pathNodes[dir + 1];
			numHeapEntries++;
		}
	}
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

	i = 0;
	do {
		distanceReturnedLog[i++] = 18000;
	} while (i < 8);

	pathFrames = 80;
	DoExtraWorkForNFrames = 6;
	distLogIndex = 0;
	searchTarget.vx = 0;
	searchTarget.vy = -12367;
	searchTarget.vz = 0;
	playerTargetDistanceSq = 0;
	pathFrames = 0;
	pathIterations = 129;
}

extern int sdLevel; // D2ROADS

// [D] [T]
int getInterpolatedDistance(VECTOR* pos)
{
	int res;
	int x;
	int dist;
	int min;
	int a,b,c;
	int fx;
	int fz;
	tNode n;
	VECTOR sp;

	// WHY?
	n.vx = ((pos->vx + (pos->vz >> 1 & 0x1ffU)) >> 9) * 512 - ((pos->vz & 0x200) >> 1);
	n.vy = pos->vy;
	n.vz = (pos->vz >> 9) << 9;

	if (OMAP_GETVALUE(n.vx >> 8, n.vz >> 8) != 0)
	{
		res = MapHeight((VECTOR*)&n);
		n.vy = res ^ (res ^ sdLevel) & 3;
	}
	else
	{
		n.vy = 0;
	}

	fz = pos->vz - n.vz;
	fx = (pos->vx - n.vx) + (fz >> 1);

	sp.vx = n.vx + 256;
	sp.vz = n.vz + 512;

	n.dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (n.vy & 1U) * 0x2040 ^ (n.vy & 2U) << 0xc];
	a = n.dist;

	n.vx = sp.vx;
	n.vz = sp.vz;

	if (OMAP_GETVALUE(sp.vx >> 8, sp.vz >> 8) != 0)
	{
		res = MapHeight((VECTOR*)&n);
		n.vy = res ^ (res ^ sdLevel) & 3;
	}
	else
	{
		n.vy = 0;
	}

	n.dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (n.vy & 1U) * 0x2040 ^ (n.vy & 2U) << 0xc];
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
			res = MapHeight((VECTOR*)&n);
			res = res ^ (res ^ sdLevel) & 3;
		}
		else
		{
			res = 0;
		}
	
		dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (res & 1) * 0x2040 ^ (res & 2) << 0xc];
		
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
			res = MapHeight((VECTOR*)&n);
			res = res ^ (res ^ sdLevel) & 3;
		}
		else
		{
			res = 0;
		}

		dist = distanceCache[(n.vx >> 2 & 0x3f80U | n.vz >> 9 & 0x7fU) ^ (res & 1) * 0x2040 ^ (res & 2) << 0xc];
		
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
			
			if ((vx ^ (vz & 0x7e) << 8) == vx2 && vz2 & 0x7e != 0 || 
				vz2 & 0x7e << 8 != 1)
			{
				bits = 3 << (vz2 & 6);

				OMAP_V(vx2, vz2) ^= bits;
				OMAP_V(vx2+1, vz2) ^= bits;
			}
		}

		cp++;
	} while (cp < &car_data[MAX_CARS - 1]);
}

// [D] [T]
void UpdateCopMap(void)
{
	int d;
	int dist;
	int dx, dy, dz;
	int i, maxret;
	int res;
	tNode startNode;
	uint pnode;
	uint parent;

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

		if (cellsThisFrame > 6)
			iterations = 6;

		i = pathIterations - (iterations * 4) * 4 - iterations * 5;

		if (DoExtraWorkForNFrames != 0)
		{
			DoExtraWorkForNFrames--;
			i += 60;
		}

		if (i < 36)
			i = 36;

		i -= 1;

		while (i-- >= 0)
		{
			iterate();
		}

		DebugDisplayObstacleMap();
		
		// remove cars
		addCivs();
	}
	else
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
		else if (searchTarget.vy == -0x304f)
		{
			searchTarget.vx = player[0].pos[0];
			searchTarget.vy = player[0].pos[1];
			searchTarget.vz = player[0].pos[2];
		}

		i = 0;

		// step up distance frame (and invalidate by setting bit 1)
		do {
			d = distanceCache[i] + 8192;

			if ((d & 1) != 0)
				d ^= 1;

			if (d > 0xfffe)
				d = 0xfffe;

			distanceCache[i] = d;
			i++;
		} while (i < 16384);

		startNode.vx = ((searchTarget.vx + (searchTarget.vz >> 1 & 0x1ffU)) >> 9) * 512 - ((searchTarget.vz & 0x200U) >> 1);
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
			dx = startNode.vx - searchTarget.vx;
			dz = startNode.vz - searchTarget.vz;
			
			dist = SquareRoot0(dx * dx + (dz) * (dz));
			dist = dist / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, dist);

				i = numHeapEntries + 1;

				pnode = i;
				parent = i >> 1;

				while (parent != 0 && dist < heap[parent].dist)
				{
					heap[i] = heap[parent];

					pnode = parent;
					parent >>= 1;
				}

				heap[pnode] = startNode;
				numHeapEntries++;
			}

			startNode.vx += 256;
			startNode.vz += 512;
			
			dist = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			dist = dist / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, dist);

				i = numHeapEntries + 1;

				pnode = i;
				parent = i >> 1;

				while (parent != 0 && dist < heap[parent].dist)
				{
					heap[i] = heap[parent];

					pnode = parent;
					parent >>= 1;
				}

				heap[pnode] = startNode;
				numHeapEntries++;
			}

			startNode.vx += 256;
			startNode.vz -= 512;
			
			dist = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			dist = dist / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, dist);

				i = numHeapEntries + 1;

				pnode = i;
				parent = i >> 1;

				while (parent != 0 && dist < heap[parent].dist)
				{
					heap[i] = heap[parent];

					pnode = parent;
					parent >>= 1;
				}

				heap[pnode] = startNode;
				numHeapEntries++;
			}
		}
		else
		{
			dx = startNode.vx - searchTarget.vx;
			dz = startNode.vz - searchTarget.vz;
			
			dist = SquareRoot0(dx * dx + dz * dz);
			dist = dist / 2 & 0xffff;
			
			if (numHeapEntries != 198)
			{
				setDistance(&startNode, dist);

				i = numHeapEntries + 1;

				pnode = i;
				parent = i >> 1;

				while (parent != 0 && dist < heap[parent].dist)
				{
					heap[i] = heap[parent];

					pnode = parent;
					parent >>= 1;
				}

				heap[pnode] = startNode;
				numHeapEntries++;
			}

			startNode.vx += 256;
			startNode.vz += 512;
	
			dist = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			dist = dist / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, dist);

				i = numHeapEntries + 1;

				pnode = i;
				parent = i >> 1;

				while (parent != 0 && dist < heap[parent].dist)
				{
					heap[i] = heap[parent];

					pnode = parent;
					parent >>= 1;
				}

				heap[pnode] = startNode;
				numHeapEntries++;
			}

			startNode.vx -= 512;
			
			dist = SquareRoot0((startNode.vx - searchTarget.vx) * (startNode.vx - searchTarget.vx) + (startNode.vz - searchTarget.vz) * (startNode.vz - searchTarget.vz));
			dist = dist / 2 & 0xffff;

			if (numHeapEntries != 198)
			{
				setDistance(&startNode, dist);

				i = numHeapEntries + 1;

				pnode = i;
				parent = i >> 1;

				while (parent != 0 && dist < heap[parent].dist)
				{
					heap[i] = heap[parent];

					pnode = parent;
					parent >>= 1;
				}

				heap[pnode] = startNode;
				numHeapEntries++;
			}
		}
	}

	pathFrames++;

	maxret = distanceReturnedLog[7];
	
	i = 6;
	do {
		
		if (maxret < distanceReturnedLog[i])
			maxret = distanceReturnedLog[i];

		i--;
	} while (i >= 0);

	if (pathFrames > 250 || heap[1].dist - maxret > 3000)  // [A] was (pathFrames < pathFrames)
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
