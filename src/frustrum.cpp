#include "frustrum.hpp"

namespace dragonslave {


Frustrum::Frustrum() { }


Frustrum::~Frustrum() { }


bool Frustrum::contains(const SphereBound& bound) const
{
    return 
        left.contains(bound) &&
        right.contains(bound) &&
        bottom.contains(bound) &&
        top.contains(bound) &&
        near.contains(bound) &&
        far.contains(bound);
}


void Frustrum::apply_projection_matrix(const glm::mat4& projection)
{
    float m00 = projection[0][0];
    float m01 = projection[0][1];
    float m02 = projection[0][2];
    float m03 = projection[0][3];
    float m10 = projection[1][0];
    float m11 = projection[1][1];
    float m12 = projection[1][2];
    float m13 = projection[1][3];
    float m20 = projection[2][0];
    float m21 = projection[2][1];
    float m22 = projection[2][2];
    float m23 = projection[2][3];
    float m30 = projection[3][0];
    float m31 = projection[3][1];
    float m32 = projection[3][2];
    float m33 = projection[3][3];
    left.a = m03 + m00;
    left.b = m13 + m10;
    left.c = m23 + m20;
    left.d = m33 + m30;
    right.a = m03 - m00;
    right.b = m13 - m10;
    right.c = m23 - m20;
    right.d = m33 - m30;
    bottom.a = m03 + m01;
    bottom.b = m13 + m11;
    bottom.c = m23 + m21;
    bottom.d = m33 + m31;
    top.a = m03 - m01;
    top.b = m13 - m11;
    top.c = m23 - m21;
    top.d = m33 - m31;
    near.a = m03 + m02;
    near.b = m13 + m12;
    near.c = m23 + m22;
    near.d = m33 + m32;
    far.a = m03 - m02;
    far.b = m13 - m12;
    far.c = m23 - m22;
    far.d = m33 - m32;
}


}
