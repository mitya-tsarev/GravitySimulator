#include "../include/HermitBody.h"

HermitBody::HermitBody(const mathing::Vec4 &pos, const mathing::Vec4 &vel, const mathing::Vec4 &accel,
                       const mathing::Vec4 &jerk, double mass) : Body(pos, vel, accel, mass), jerk(jerk) {}

HermitBody::HermitBody() : HermitBody(mathing::Vec4(), mathing::Vec4(), mathing::Vec4(), mathing::Vec4(), 0) {}

HermitBody::HermitBody(const mathing::Vec4 &pos, const mathing::Vec4 &vel, double mass) : Body(pos, vel, mass) {}
