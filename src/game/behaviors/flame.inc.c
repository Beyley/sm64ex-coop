// flame.inc.c

void bhv_small_piranha_flame_loop(void) {
    struct Object* player = nearest_player_to_object(o);
    int angleToPlayer = obj_angle_to_object(o, player);

    f32 sp2C;

    if ((u16)(o->oBehParams >> 16) == 0) {
        if (o->oTimer > 0) {
            obj_mark_for_deletion(o);
        } else {
            sp2C = random_float() - 0.5f;
            o->header.gfx.scale[1] = o->header.gfx.scale[2] * (1.0f + 0.7f * sp2C);
            o->header.gfx.scale[0] = o->header.gfx.scale[2] * (0.9f - 0.5f * sp2C);

            o->oAnimState = random_u16();
        }
    } else {
        cur_obj_update_floor_and_walls();
        if (approach_f32_ptr(&o->oSmallPiranhaFlameStartSpeed, o->oSmallPiranhaFlameEndSpeed, 0.6f)) {
            cur_obj_rotate_yaw_toward(angleToPlayer, 0x200);
        }

        obj_compute_vel_from_move_pitch(o->oSmallPiranhaFlameStartSpeed);
        cur_obj_move_standard(-78);
        spawn_object_with_scale(o, o->oSmallPiranhaFlameModel, bhvSmallPiranhaFlame,
                                0.4f * o->header.gfx.scale[0]);

        if (o->oTimer > o->oSmallPiranhaFlameUnk100) {
            spawn_object_relative_with_scale(1, 0, o->oGraphYOffset, 0, o->header.gfx.scale[0], o,
                                             o->oSmallPiranhaFlameModel, bhvFlyguyFlame);
            o->oSmallPiranhaFlameUnk100 = random_linear_offset(8, 15);
            o->oTimer = 0;
        }

        obj_check_attacks(&sPiranhaPlantFireHitbox, o->oAction);
        o->oSmallPiranhaFlameUnk104 += o->oSmallPiranhaFlameStartSpeed;

        if (o->oSmallPiranhaFlameUnk104 > 1500.0f || (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_IN_WATER))) {
            obj_die_if_health_non_positive();
        }
    }

    o->oGraphYOffset = 15.0f * o->header.gfx.scale[1];
}

void bhv_fly_guy_flame_loop(void) {
    cur_obj_move_using_fvel_and_gravity();

    if (approach_f32_ptr(&o->header.gfx.scale[0], 0.0f, 0.6f)) {
        obj_mark_for_deletion(o);
    }

    cur_obj_scale(o->header.gfx.scale[0]);
}
