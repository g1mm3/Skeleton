#pragma once
#include <cstdint>

#define CONVERT_WORLD_TO_SCREEN_POS_FUNC 0x70CE30

bool IsGTAMenuActive()
{
    return (int)(*(uint8_t*)0x0BA67A4);
}

D3DXVECTOR2 ConvertGlobalXYZToWindowScreenXY(D3DXVECTOR3 world)
{
    typedef void(__cdecl* CWorld__ConvertGlobalXYZToScreenXY)(D3DXVECTOR3* world, D3DXVECTOR3* screen, float* mulX,
        float* mulY, bool unk, bool unk2);
    D3DXVECTOR3 screen;
    float mulX, mulY;
    (CWorld__ConvertGlobalXYZToScreenXY(CONVERT_WORLD_TO_SCREEN_POS_FUNC))(&world, &screen, &mulX, &mulY, false,
        false);
    return { screen.x, screen.y };
}

struct actor_info
{
#pragma pack( 1 )
    BYTE                        deleted[34];
    unsigned short              modelID;
    BYTE                        deleted1[30];
    uint8_t                     flags;                              // 66 immunities
    uint8_t                     __unknown_67[1];                    // 67
    BYTE                        deleted2[12];                       // 68

    float                       spin[3];                            // 80
    float                       speed_rammed[3];                    // 92
    float                       spin_rammed[3];                     // 104
    uint8_t                     __unknown_116[60];                  // 116
    void                        *__unknown_176;                     // 176 - pointer to a "entry node info" pool item
    void                        *__unknown_180;                     // 180 - pointer to a "ptr node Double" pool item

    //collision data
    DWORD                       collision_flags;
    /*
        184 - 2nd byte = currently colliding 1/0, or actively
        running against (0x2), 3rd byte = type colliding with
        (1 = road, 4=pavement, 35 = object, 3f=car).. unsure about 3rd byte
        nuck notes: 186 is used to tell if a surface is "steep" too,
        actually any slight angle at all
    */

    void                       *last_touched_object;                // 188 - You can touch roads - those are considered buildings
    void                       *last_collided_object;               // 192 - pointer to object last collided with (on foot, not jetpack)
    uint8_t                     __unknown_196[16];                  // 196
    float                       speed;                              // 212
    float                       collision_time_216;                 // 216 - collision timer?
    void                       *collision_current_obj;              // 220 - pointer to current thing colliding with
    uint8_t                     collision_something[12];            // 224 - related to collision
    float                       collision_last_coord[3];            // 236 - coordination of last collision
    //end of collision data

    uint8_t                     __unknown_248[100];                 // 248
                                                                    // 252 - animation related
    uint8_t                     animation_state;                    // 348
    uint8_t                     __unknown_349[7];                   // 349
    float                       step_pos[3];                        // 356 - coordinates, last foot step
    float                       step_pos_before[3];                 // 368 - coordinates, foot step before last one
    uint8_t                     __unknown_380[752];                 // 380

    BYTE                        deleted3[16];                       // 1132
                                                                    // 1148 - animations base
    struct animation_base*      animBase;
    BYTE                        deleted4[4];

    uint8_t                     __unknown_1156[8];                  // 1156

    // relative body-part-positions
    void                        *pNeck;
    /*
        1164 - void* pNeck
        (pChest?)
        - 4 unknown
        - float height
        - float front/back
        - float left/right
        - void* pObject
        (same struct for the following body-part-pointers [except pLeft/RightArm])
    */

    void                        *pHead;                             // 1168
    void                        *pLeftArm;                          // 1172
    void                        *pRightArm;                         // 1176
    void                        *pLeftLowArm;                       // 1180
    void                        *pRightLowArm;                      // 1184
    void                        *pLeftLeg;                          // 1188
    void                        *pRightLeg;                         // 1192
    void                        *pLeftLowLeg;                       // 1196
    void                        *pRightLowLeg;                      // 1200
    void                        *pRightMidLeg;                      // 1204
    void                        *pLeftMidLeg;                       // 1208
    void                        *pLeftMidArm;                       // 1212
    void                        *pRightMidArm;                      // 1216
    void                        *pLeftShoulder;                     // 1220
    void                        *pRightShoulder;                    // 1224
    void                        *pChest;                            // 1228
    void                        *pMouth;                            // 1232
    // end of body-part-positions

    uint8_t                     runningStyle;                       /* 1236 - 0x36 = cj, 0x8A = rollerskate,
                                                                    0x7F = woozie, 0x75 = crash.. etc. */
    uint8_t                     __unknown_1237[7];                  // 1237
    float                       runspeed;                           // 1244
    uint8_t                     __unknown_1248[36];                 // 1248
    uint16_t                    muzzle_flash;                       // 1284
    uint8_t                     __unknown_1286[6];                  // 1286

    BYTE                        deleted5[32];                       // 1292 - Inverse Kinematics
    uint8_t                     __unknown_1324[4];                  // 1324

    uint32_t                    actorState;                         // 1328 - ACTOR_STATE_*
    uint32_t                    runState;                           // 1332 - ACTOR_MSTATE_*
    uint8_t                     __unknown_1336[8];                  // 1336
    float                       hitpoints;                          // 1344
    float                       hitpoints_max;                      // 1348 - hmm, does not seem to be right.. it's set to "100.1318519" or something like that
    float                       armor;                              // 1352
    uint8_t                     __unknown_1356[12];                 // 1356

                                                                    // 1360 and 1364 are using in resetting on-foot position when re-standing up

    float                       fCurrentRotation;                   // 1368
    float                       fTargetRotation;                    // 1372
    float                       fRotationSpeed;                     // 1376
    float                       fRotationCalculation;               // 1380 - is 0.1 when target rotation reached

    union
    {
        BYTE                    deleted6[4];                        // 1384 - touching a CEntitySAInterface
        struct vehicle_info*    vehicle_contact;                    // 1384 - standing on top of vehicle
    };

    float                       vehicle_contact_dist[3];            // 1388 - distance to the middle of the car standing on
    float                       fPlaneAnglesContactEntity[3];       /* 1400 - Angles of the plane of the contact entity the actor is
                                                                    standing on (?) */
    void                        *item_contact;                      // 1412 - standing on top of vehicle/object/building/...
    float                       fUnknown_1416;                      // 1416 - only changing when slightly under map

    union
    {
        //CEntitySAInterface    *CurrentObjective;                  // 1420 - usually current vehicle's entity
        DWORD                   vehicleDw;
        struct vehicle_info*    vehicle;
    };

    uint8_t                     __unknown_1424[8];                  // 1424
    uint8_t                     actor_lock;                         // 1432
    uint8_t                     __unknown_1433[7];                  // 1433
    BYTE                        deleted7[364];                      // 1440
    uint8_t                     __unknown_1804[12];                 // 1804
    uint8_t                     weapon_slot;                        // 1816
    uint8_t                     __unknown_1817[3];                  // 1817
    void                        *ptr_autoAimTarget;                 // 1820 - weapon target
    float                       fImpactPos_close[3];                // 1824 - last impact point of close range weapon [fist/knife/csaw/etc.]
    uint8_t                     __unknown_1836[20];                 // 1836
    uint32_t                    weapon_model;                       // 1856
    uint8_t                     __unknown_1860[28];                 // 1860
    uint32_t                    weapon_hit_type;                    // 1888 - last hit by this weapon
    struct actor_info           *weapon_hit_by;                     // 1892 - last hit by this object (usually an actor)
    uint8_t                     __unknown_1889[92];                 // 1896
};                                                                  // 1988

bool IsOnScreen(actor_info* pedHandle)
{
    return ((bool(__thiscall*)(actor_info*))0x534540)(pedHandle);
}

void GetBonePosition(actor_info* pedHandle, D3DXVECTOR3& outPosition, unsigned int boneId, bool updateSkinBones = true)
{
    ((void(__thiscall*)(actor_info*, D3DXVECTOR3&, unsigned int, bool))0x5E4280)(pedHandle, outPosition, boneId, updateSkinBones);
}