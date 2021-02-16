#include <BasicLinearAlgebra.h>
using namespace BLA;

float rotate(float angle, float desiredAngle) {
    Matrix<2,1> xa = {cos(angle), sin(angle)};
    Matrix<2,2> rot = {cos(-desiredAngle), -sin(-desiredAngle), sin(-desiredAngle), cos(-desiredAngle)};
    Matrix<2,1> delta_v = rot * xa;
    return atan2(delta_v(1), delta_v(0));
}

bool is_near_zero(float s) {
    return abs(s) < 1e-6;
}

float norm(Matrix<3> v) {
    return sqrt(v(0)*v(0) + v(1)*v(1) + v(2)*v(2));
}

Matrix<3> normalize(Matrix<3> v) {
    float nor = norm(v);
    if (nor == 0) return v;
    return v / nor;
}

Matrix<3,3> skew(Matrix<3> v) {
    Matrix<3,3> skew = {0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0};
    return skew;
}

Matrix<4,4> vec6_to_se3(Matrix<6> v) {
    auto W = v.Submatrix(Slice<0,3>(), Slice<0,1>());
    auto V = v.Submatrix(Slice<3,6>(), Slice<0,1>());
    Matrix<1,4> lastRow = {0,0,0,1};
    return (skew(W) || V) && lastRow;
}

Matrix<3> so3_to_vec(Matrix<3,3> so3) {
    Matrix<3> vec = {so3(2,1), so3(0,2), so3(1,0)};
    return vec;
}

Matrix<3,3> so3_to_SO3(Matrix<3,3> so3) {
    Matrix<3> w_theta = so3_to_vec(so3);
    float theta = norm(w_theta);
    Matrix<3,3> eye3 = {1,0,0, 0,1,0, 0,0,1};
    Matrix<3,3> SO3;
    if (is_near_zero(theta)) {
        SO3 = eye3;
    } else {
        Matrix<3,3> w_skew = so3 / theta;
        SO3 = eye3 + w_skew*sin(theta) + w_skew*w_skew*(1 - cos(theta)); // Rodriguez formula
    }
    return SO3;
}

Matrix<4,4> se3_to_SE3(Matrix<4,4> se3) {
    auto w_theta = so3_to_vec(se3.Submatrix(Slice<0,3>(), Slice<0,3>()));
    Matrix<4,4> SE3;
    if (is_near_zero(norm(w_theta))) {
        SE3 = {1,0,0,se3(0,3), 0,1,0,se3(1,3), 0,0,1,se3(2,3), 0,0,0,1};
    } else {
        float theta = norm(w_theta);
        Matrix<3,3> rot = se3.Submatrix(Slice<0,3>(), Slice<0,3>());
        Matrix<3,3> w_skew = rot / theta;
        Matrix<3,3> eye3 = {1,0,0, 0,1,0, 0,0,1};
        Matrix<3,3> rodriguez_plus = eye3*theta + w_skew*(1-cos(theta)) + w_skew*w_skew*(theta - sin(theta));
        Matrix<3> translation = rodriguez_plus * se3.Submatrix(Slice<0,3>(), Slice<3,4>()) / theta;
        Matrix<1,4> lastRow = {0,0,0,1};
        SE3 = (so3_to_SO3(rot) || translation) && lastRow;
    }
    return SE3;
}

Matrix<4,4> vec6_to_SE3(Matrix<6> v) {
    return se3_to_SE3(vec6_to_se3(v));
}