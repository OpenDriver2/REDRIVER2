#ifndef DR2ROADS_H
#define DR2ROADS_H

#define IS_ROAD_SURFACE(surfid)				(((surfid) & 0xFFFFE000) != 0xFFFFE000)		// is any road surface

#define IS_STRAIGHT_SURFACE(surfid)			(((surfid) > -1) && ((surfid) & 0xFFFFE000) == 0 && (surfid & 0x1FFF) < NumDriver2Straights)
#define IS_CURVED_SURFACE(surfid)			(((surfid) > -1) && ((surfid) & 0xFFFFE000) == 0x4000 && (surfid & 0x1FFF) < NumDriver2Curves)
#define IS_JUNCTION_SURFACE(surfid)			(((surfid) > -1) && ((surfid) & 0xFFFFE000) == 0x2000 && (surfid & 0x1FFF) < NumDriver2Junctions)

#define GET_STRAIGHT(surfid)				(Driver2StraightsPtr + (surfid & 0x1FFF))
#define GET_CURVE(surfid)					(Driver2CurvesPtr + (surfid & 0x1FFF))
#define GET_JUNCTION(surfid)				(Driver2JunctionsPtr + (surfid & 0x1FFF))

// $DEPRECATED: as it's used to detect lane direction, use ROAD_LANE_DIR instead
#define IS_NARROW_ROAD(rd) \
	((*(ushort*)&(rd)->NumLanes & 0xFFFF) == 0xFF01)

// those macros can be applied to straights and junctions
#define ROAD_LANES_COUNT(rd)							((uint)rd->NumLanes & 0xF)					// lane count
#define ROAD_WIDTH_IN_LANES(rd)							(ROAD_LANES_COUNT(rd) * 2)					// width in lanes
#define ROAD_IS_AI_LANE(rd, lane)						((u_char)rd->AILanes >> (lane / 2) & 1U)	// lane AI driveable flag
#define ROAD_IS_LEFTMOST_LANE_PARKING(rd)				((rd->NumLanes & 0x40) != 0)				// allows parking on leftmost lane
#define ROAD_IS_RIGHTMOST_LANE_PARKING(rd)				((rd->NumLanes & 0x80) != 0)				// allows parking on rightmost lane
#define ROAD_LANE_DIRECTION_BIT(rd, lane)				((u_char)rd->LaneDirs >> (lane / 2) & 1U)	// direction bit
#define ROAD_SPEED_LIMIT(rd)							(((u_char)rd->NumLanes >> 4) & 3)			// speed limit id

#define ROAD_LANE_DIR(rd, lane) \
	(((u_char)rd->LaneDirs == 0xFF && rd->NumLanes == 1) ? (lane & 1) : ROAD_LANE_DIRECTION_BIT(rd, lane))

#define ROAD_IS_PARKING_ALLOWED_AT(rd, lane)\
	((ROAD_IS_LEFTMOST_LANE_PARKING(rd) && lane == 0) || (ROAD_IS_RIGHTMOST_LANE_PARKING(rd) && lane == ROAD_WIDTH_IN_LANES(rd) - 1))

extern ROAD_MAP_LUMP_DATA roadMapLumpData;

extern int NumTempJunctions;
extern DRIVER2_JUNCTION *Driver2JunctionsPtr;
extern ulong *Driver2TempJunctionsPtr;
extern int NumDriver2Junctions;

extern int NumDriver2Straights;
extern DRIVER2_STRAIGHT *Driver2StraightsPtr;

extern DRIVER2_CURVE *Driver2CurvesPtr;
extern int NumDriver2Curves;

extern short* RoadMapDataRegions[4];

extern void ProcessStraightsDriver2Lump(char *lump_file, int lump_size); // 0x000136C0

extern void ProcessCurvesDriver2Lump(char *lump_file, int lump_size); // 0x000136F4

extern void ProcessJunctionsDriver2Lump(char *lump_file, int lump_size, int fix); // 0x00013728

extern int MapHeight(VECTOR *pos); // 0x000137CC

extern int FindSurfaceD2(VECTOR *pos, VECTOR *normal, VECTOR *out, _sdPlane **plane); // 0x00012EF4

extern int sdHeightOnPlane(VECTOR *pos, _sdPlane *plane); // 0x000130D4

extern int GetSurfaceIndex(VECTOR *pos); // 0x0001380C

extern _sdPlane * FindRoadInBSP(_sdNode *node, _sdPlane *base); // 0x000138F0

extern int RoadInCell(VECTOR *pos); // 0x0001322C

extern _sdPlane * sdGetCell(VECTOR *pos); // 0x0001346C

extern short * sdGetBSP(_sdNode *node, XYPAIR *pos); // 0x00013848


#endif
