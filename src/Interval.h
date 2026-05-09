#pragma once

#include <limits>

class Interval {
    double minVal;
    double maxVal;

public:
    Interval() : minVal(+std::numeric_limits<double>::infinity()),
        maxVal(-std::numeric_limits<double>::infinity()) {
    }

    Interval(double min, double max) : minVal(min), maxVal(max) {}

    double getMin() const { 
        return minVal; 
    }

    double getMax() const { 
        return maxVal; 
    }

    double size() const { 
        return maxVal - minVal; 
    }

    bool contains(double x) const { 
        return minVal <= x && x <= maxVal; 
    }

    bool surrounds(double x) const { 
        return minVal < x && x < maxVal; 
    }

    double clamp(double x) const {
        if (x < minVal) 
            return minVal;
        if (x > maxVal) 
            return maxVal;
        return x;
    }

    static const Interval empty;
    static const Interval universe;
};

