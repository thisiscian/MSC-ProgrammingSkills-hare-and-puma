#include <cstdlib>

template<class T>
class DistributionBase
{
  public:

  virtual T operator()(size_t x, size_t y) const = 0;
};


class DoubleDistribution: public DistributionBase<double>
{
  public:

  DoubleDistribution(double p): _p(p) {}

  double operator()(size_t x, size_t y) const
  {
    return _p*y + x;
  }

  private:
  double _p;
};

class BoolDistribution: public DistributionBase<bool>
{
  public:
  BoolDistribution(double p): _p(p) {}

  bool operator()(size_t x, size_t y)
  {
    return (x==y);
  }

  private:
  double _p;
};
