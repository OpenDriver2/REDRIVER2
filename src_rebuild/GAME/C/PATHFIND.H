#ifndef PATHFIND_H
#define PATHFIND_H


extern tNode popNode(); // 0x000E7000

extern void WunCell(VECTOR *pbase); // 0x000E7194

extern void InvalidateMap(); // 0x000E735C

extern void BloodyHell(); // 0x000E74B0

extern int blocked(tNode *v1, tNode *v2); // 0x000E76C4

extern void setDistance(tNode *n, unsigned short dist); // 0x000E90A4

extern void iterate(); // 0x000E7814

extern void InitPathFinding(); // 0x000E7BD0

extern int getInterpolatedDistance(VECTOR *pos); // 0x000E7CA8

extern void addCivs(); // 0x000E822C

extern void UpdateCopMap(); // 0x000E836C

extern int getHeadingToPlayer(int vx, int vy, int vz); // 0x000E8F00


#endif
