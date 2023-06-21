/*
 * ladrc.c
 *
 *  Created on: 2022年4月17日
 *      Author: Sun Lee
 */

#include "ladrc.h"

void LADRC(LADRC_t* p)
{
    //先计算td
    float fh = LADRC_fst(p->v1 - p->v, p->v2, p->r, p->h);
    p->v1 += p->h * p->v2;
    p->v2 += p->h * fh;

    //计算控制量
    p->b01 = 3 * p->w0;
    p->b02 = 3 * p->w0 * p->w0;
    p->b03 = p->w0 * p->w0 * p->w0;

    p->e = p->z1 - p->y;
    //更新中间量
    p->z1 = p->z1 + p->h * (p->z2 - p->b01 * p->e);
    p->z2 = p->z2 + p->h * (p->z3 - p->b02 * p->e + p->b * p->u);
    p->z3 = p->z3 - p->h * p->b03 * p->e;

    p->e1 = p->v1 - p->z1;
    p->e2 = p->v2 - p->z2;
    //p->e1 = p->v - p->z1;
    //p->e2 = 0 - p->z2;
    p->u0 = p->kp * p->e1 + p->kd * p->e2;
    p->u = p->u0 - p->z3 / p->b;
}

//和上面那个只有最后俩行不同
void LADRC_fal_kd(LADRC_t* p, float d_line)
{
    //先计算td
    p->v1 += p->h * p->v2;
    p->v2 += p->h * LADRC_fst(p->v1 - p->v, p->v2, p->r, p->h);

    //计算控制量
    float w0_2 = p->w0 * p->w0;
    float w0_3 = w0_2 * p->w0;
    p->b01 = 3 * p->w0;
    p->b02 = 3 * w0_2;
    p->b03 = w0_3;

    p->e = p->z1 - p->y;
    //更新中间量
    p->z1 = p->z1 + p->h * (p->z2 - p->b01 * p->e);
    p->z2 = p->z2 + p->h * (p->z3 - p->b02 * p->e + p->b * p->u);
    p->z3 = p->z3 - p->h * p->b03 * p->e;

    p->e1 = p->v1 - p->z1;
    p->e2 = p->v2 - p->z2;


    p->u0 = p->kp * p->e1 + p->kd * LADRC_fal(p->e2, 0.25, d_line);
    p->u = p->u0 - p->z3 / p->b;
}

void LADRC_GetDefultConfig(LADRC_t* p)
{
    memset(p, 0, sizeof(LADRC_t));
    p->b = 1.0f;
}

float LADRC_sign(float x)
{
    if (x < 0)
    {
        return -1.0f;
    }
    else
    {
        return 1.0f;
    }
}

float LADRC_fst(float x1, float x2, float r, float h)
{
    float d = r * h * h;
    float a0 = h * x2;
    float y = x1 + a0;
    float a1 = sqrt(d * (d + 8 * fabs(y)));
    float a2 = a0 + LADRC_sign(y) * (a1 - d) * 0.5f;
    float sy = (LADRC_sign(y + d) - LADRC_sign(y - d)) * 0.5f;
    float a = (a0 + y - a2) * sy + a2;
    float sa = (LADRC_sign(a + d) - LADRC_sign(a - d)) * 0.5f;
    return -r * (a / d - LADRC_sign(a)) * sa - r * LADRC_sign(a);
}

float LADRC_fal(float e, float a, float e_line)
{
    float e_abs = fabs(e);
    if (e_abs < e_line)
    {
        return e;
    }
    else
    {
        return powf(e_abs, a) * powf(e_line, 1 - a) * LADRC_sign(e);
    }
}
