#ifndef GAUSSIANBASISFUNCTION_H
#define GAUSSIANBASISFUNCTION_H

#include <vector>

#include "radialbasisfunction.h"

class GaussianBasisFunction : public RadialBasisFunction
{
public:
    GaussianBasisFunction();
    std::vector<double> sample(std::vector<double> xs) const;
    unsigned int getDim() const;
};

#endif // GAUSSIANBASISFUNCTION_H
