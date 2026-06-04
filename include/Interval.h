/**
 * @file Interval.h
 * @brief Closed real-valued interval [min, max] with utility methods.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include <limits>

 /**
  * @class Interval
  * @brief Represents a closed interval [minVal, maxVal] on the real line.
  * 
  * @details
  * Used primarily to define the valid range of the ray parameter t during intersection tests. The default constructor produces an empty interval.
  */
class Interval {
    double minVal; ///< Lower bound of the interval.
    double maxVal; ///< Upper bound of the interval.

public:
    /// @brief Constructs an empty interval (minVal > maxVal).
    Interval() : minVal(+std::numeric_limits<double>::infinity()),
        maxVal(-std::numeric_limits<double>::infinity()) {
    }
   
    /**
     * @brief Constructs an interval with explicit bounds.
     *
     * @param min Lower bound.
     * @param max Upper bound.
     */
    Interval(double min, double max) : minVal(min), maxVal(max) {}

    double getMin() const { 
        return minVal; 
    }

    double getMax() const { 
        return maxVal; 
    }

    /// @brief Returns the length of the interval (maxVal - minVal).
    double size() const { 
        return maxVal - minVal; 
    }

    /// @brief Returns true if x lies within [minVal, maxVal].
    bool contains(double x) const { 
        return minVal <= x && x <= maxVal; 
    }

    /// @brief Returns true if x lies strictly inside (minVal, maxVal).
    bool surrounds(double x) const { 
        return minVal < x && x < maxVal; 
    }

    /// @brief Clamps x to [minVal, maxVal].
    double clamp(double x) const {
        if (x < minVal) 
            return minVal;
        if (x > maxVal) 
            return maxVal;
        return x;
    }

    static const Interval empty; ///< Predefined empty interval.
    static const Interval universe; ///< Predefined interval covering all reals.
};

