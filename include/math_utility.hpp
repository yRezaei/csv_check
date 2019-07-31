#ifndef MATH_UTILITY_HPP_
#define MATH_UTILITY_HPP_

namespace math_util::interpolation
{

inline float linear(float v1, float v2, float ratio)
{
    return (v1 * (1.0f - ratio) + v2 * ratio);
}
} // namespace math_util

#endif // !MATHEMATICS_HPP_