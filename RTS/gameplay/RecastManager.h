#pragma once
#include "../misc/ArrayT.h"
#include "OObject.h"
#include "Recast.h"
#include "DetourNavMeshQuery.h"
class RecastManager : public OObject {
protected:

	class dtNavMesh* navMesh;
	class dtNavMeshQuery* navQuery;
	class dtCrowd* crowd;
	class rcContext* recastContext;
	unsigned char* m_triareas;
	struct rcHeightfield* m_solid;
	struct rcCompactHeightfield* m_chf;
	struct rcContourSet* m_cset;
	struct rcPolyMesh* m_pmesh;
	struct rcPolyMeshDetail* m_dmesh;
	struct rcConfig m_cfg;
	dtQueryFilter m_filter;
	class InputGeom* m_geom;

	const int m_maxTiles = 128;
	const int m_maxPolysPerTile = 32768;
	float m_tileSize;

	unsigned int m_tileCol;
	float m_lastBuiltTileBmin[3];
	float m_lastBuiltTileBmax[3];
	float m_tileBuildTime;
	float m_tileMemUsage;
	int m_tileTriCount;

	// constants
	const float m_cellSize = 1.0f;
	const float m_cellHeight = 1.0f;

	const float m_agentMaxSlope = 1.0f;
	const float m_agentHeight = 1.0f;
	const float m_agentMaxClimb = 1.0f;
	const float m_agentRadius = 1.0f;
	const float m_edgeMaxLen = 1.0f;
	const float m_edgeMaxError = 64.0f;
	const float m_regionMinSize = 1.0f;
	const float m_regionMergeSize = 1.0f;
	const int32 m_vertsPerPoly = 6;


	const float m_detailSampleDist = 1.0f;
	const float m_detailSampleMaxError = 1.0f;

	enum PolyAreas : unsigned short
	{
		SAMPLE_POLYAREA_GROUND,
		SAMPLE_POLYAREA_WATER,
		SAMPLE_POLYAREA_ROAD,
		SAMPLE_POLYAREA_DOOR,
		SAMPLE_POLYAREA_GRASS,
		SAMPLE_POLYAREA_JUMP,
	};
	enum SamplePolyFlags
	{
		SAMPLE_POLYFLAGS_WALK = 0x01,		// Ability to walk (ground, grass, road)
		SAMPLE_POLYFLAGS_SWIM = 0x02,		// Ability to swim (water).
		SAMPLE_POLYFLAGS_DOOR = 0x04,		// Ability to move through doors.
		SAMPLE_POLYFLAGS_JUMP = 0x08,		// Ability to jump.
		SAMPLE_POLYFLAGS_DISABLED = 0x10,		// Disabled polygon
		SAMPLE_POLYFLAGS_ALL = 0xffff	// All abilities.
	};
	unsigned char* buildTileMesh(const int tx, const int ty, const float* bmin, const float* bmax, int& dataSize, class BuildContext* rcContext);
public:
	RecastManager(void);
	~RecastManager();
	void init(void);
	void update(float deltaTime);
	int32 add(Vector2 pos);
	void updateVelocity(int32 handle, Vector2 preferredVelocity);
	
	int findPath(const Vector3& startPos, const Vector3& endPos);
};