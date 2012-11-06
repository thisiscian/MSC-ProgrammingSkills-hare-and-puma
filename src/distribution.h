#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <cstdlib>

template<class T>
class DistributionBase
{
  public:

  virtual T operator()(size_t x, size_t y) const = 0;
};


/*
 * DirectDistribution
 *  f(x,y) = a_x*x + a_y*y
 */
template<class T>
class DirectDistribution: public DistributionBase<T>
{
  public:

  DirectDistribution(T x_mul, T y_mul): _x_mul(x_mul), _y_mul(y_mul) {}

  T operator()(size_t x, size_t y) const
  {
    return _x_mul*x + _y_mul*y;
  }

  private:
  T _x_mul;
  T _y_mul;
};


/*
 * CheckerDistribution
 *  f(x,y) = {
 *            true if (x+y)%2 = 0
 *            false otherwise
 *           }
 */
class CheckerDistribution: public DistributionBase<bool>
{
  public:
  bool operator()(size_t x, size_t y) const
  {
    return ((x+y)%2 == 0);
  }

};


/*
 * RandomDistribution
 *  f(x,y) = random between min and max
 */
class RandomDistribution: public DistributionBase<double>
{
  public:
  // default distribution between 0 and 1
  RandomDistribution()
    : _min(0), _max(1), _rand_max(RAND_MAX)
  {
  }
  RandomDistribution(double min, double max)
    : _min(min), _max(max), _rand_max(RAND_MAX)
  {
  }

  double operator()(size_t x, size_t y) const
  {
    // rand()/_rand_max returns a value between 0 and 1
    // (0..1)*(_max - _min) returns a value between 0 and (_max - _min)
    // --> (rand()/_rand_max)*(_max - _min) + _min returns a value
    //      between _min and _max
    return rand()/_rand_max*(_max - _min) + _min;
  }

  private:
  double _rand_max;
  double _min;
  double _max;
};


/*
 * UniformDistribution<T>(T value)
 *  f(x,y) = value
 */
template<class T>
class UniformDistribution: public DistributionBase<T>
{
  public:
  UniformDistribution(T value): _value(value)
  {
  }

  T operator()(size_t x, size_t y) const
  {
    return _value;
  }

  private:
  T _value;
};

/*
 * FunctionDistribution<T>(T function(size_t i, size_t j))
 *  f(x,y) = function(x,y)
 */
template<class T>
class FunctionDistribution: public DistributionBase<T>
{
  public:

  FunctionDistribution(T (*value)(size_t,size_t)): _value(value)
  {
  }

  T operator()(size_t x, size_t y) const
  {
    return _value(x,y);
  }

  private:
  T (*_value)(size_t,size_t);
};

#endif
