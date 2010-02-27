#ifndef RADIALBASISFUNCTION_H
#define RADIALBASISFUNCTION_H

#include <vector>

class RadialBasisFunction
{
public:
    RadialBasisFunction();
    virtual std::vector<double> sample(std::vector<double> xs) const = 0;
    virtual unsigned int getDim() const = 0;
};

#endif // RADIALBASISFUNCTION_H
