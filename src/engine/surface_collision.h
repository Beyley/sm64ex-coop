#ifndef SURFACE_COLLISION_H
#define SURFACE_COLLISION_H

#include <PR/ultratypes.h>

#include "types.h"

#define LEVEL_BOUNDARY_MAX  0x2000
#define CELL_SIZE           0x400       

#define CELL_HEIGHT_LIMIT   20000.f
#define FLOOR_LOWER_LIMIT  -11000.f

struct WallCollisionData
{
    /*0x00*/ f32 x, y, z;
    /*0x0C*/ f32 offsetY;
    /*0x10*/ f32 radius;
    /*0x14*/ s16 unk14;
    /*0x16*/ s16 numWalls;
    /*0x18*/ struct Surface *walls[4];
};

struct FloorGeometry
{
    f32 unused[4]; // possibly position data?
    f32 normalX;
    f32 normalY;
    f32 normalZ;
    f32 originOffset;
};

s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius);
s32 find_wall_collisions(struct WallCollisionData *colData);
f32 find_ceil(f32 posX, f32 posY, f32 posZ, struct Surface **pceil);
f32 find_floor_height_and_data(f32 xPos, f32 yPos, f32 zPos, struct FloorGeometry **floorGeo);
f32 find_floor_height(f32 x, f32 y, f32 z);
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor);
f32 find_water_level(f32 x, f32 z);
f32 find_poison_gas_level(f32 x, f32 z);
void debug_surface_list_info(f32 xPos, f32 zPos);
void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos);

#endif // SURFACE_COLLISION_H
