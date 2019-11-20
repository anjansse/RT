#include "RT.h"

t_vec       vec_x_mat(t_vec v, double m[4][4])
{
    t_vec   new;
    double  w;

    new.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
    new.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
    new.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
    w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
    if (w != 1 && w)
    {
        new.x /= w;
        new.y /= w;
        new.z /= w;
    }
    return (new);
}

t_vec       dir_x_mat(t_vec v, double m[4][4])
{
    t_vec   new;

    new.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
    new.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
    new.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];

    return (new);
}
