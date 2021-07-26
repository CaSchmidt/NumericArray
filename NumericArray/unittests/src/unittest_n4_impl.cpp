#include <N4/N4.h>

struct V4fTraits {
  static constexpr bool have_w = true;
};

using V4f = n4::Vector4f<V4fTraits>;

using n4::real_t;

void test_axpy(V4f& z,
               const real_t alpha, const V4f& x, const V4f& y)
{
  z = alpha*x + y;
}

void test_gemv(V4f& z,
               const real_t alpha, const n4::Matrix4f& A, const V4f& x,
               const real_t beta, const V4f& y)
{
  z = alpha*(A*x) + beta*y;
}

bool test_zero(const n4::Matrix4f& M)
{
  return M.isZero();
}

bool test_zero(const V4f& v)
{
  return v.isZero();
}

bool test_intersect(const real_t *min, const real_t *max,
                    const real_t *org, const real_t *dir,
                    const real_t tMax)
{
  const simd::simd_t _min = simd::load(min);
  const simd::simd_t _max = simd::load(max);
  const simd::simd_t _org = simd::load(org);
  const simd::simd_t _dir = simd::load(dir);
  return simd::intersectRayAABBox(_min, _max, _org, _dir, tMax);
}
