#ifndef PATHFIND_H
#define PATHFIND_H

extern void iterate(); // 0x000E7814

extern void InitPathFinding(); // 0x000E7BD0

extern int getInterpolatedDistance(VECTOR *pos); // 0x000E7CA8

extern void UpdateCopMap(); // 0x000E836C

extern int getHeadingToPlayer(int vx, int vy, int vz); // 0x000E8F00

#endif
