/**
 * @file HittableList.h
 * @brief Container for a collection of hittable scene objects.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include <vector>
#include <memory>
#include "Hittable.h"

 /**
  * @class HittableList
  * @brief An ordered list of Hittable objects treated as a single scene.
  * 
  * @details
  * Iterates over all stored objects and returns the closest intersection within the valid ray interval.
  */
class HittableList : public Hittable {
    std::vector<std::shared_ptr<Hittable>> objects; ///< Collection of pointers to scene primitives.

public:
    HittableList() = default;

    /**
     * @brief Constructor that initializes the list with a single object.
     *
     * @param obj First object to add to the list.
     */
    explicit HittableList(std::shared_ptr<Hittable> obj) { 
        add(obj); 
    }

    /**
     * @brief Clears all objects from the list.
     */
    void clear() { 
        objects.clear(); 
    }

    /**
     * @brief Appends an object to the list.
     *
     * @param obj Object to add.
     */
    void add(std::shared_ptr<Hittable> obj) { 
        objects.push_back(std::move(obj)); 
    }

    /**
     * @brief Tracks the closest intersection among all objects in the list.
     *
     * @param r Ray to test against.
     * @param rayT Valid interval of the ray parameter t.
     * @param rec Output record filled with the closest intersection data.
     * @return True if any object is hit within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const;
};
