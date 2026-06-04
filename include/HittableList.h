/**
 * @file HittableList.h
 * @brief Container for a collection of hittable scene objects.
 * @author Katarzyna Pi¹tek
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
  * 
  * @param objects - collection of pointers to scene primitives.
  */
class HittableList : public Hittable {
    std::vector<std::shared_ptr<Hittable>> objects;

public:
    HittableList() = default;

    /**
     * @brief Constructor that initializes the list with a single object.
     *
     * @param obj - first object to add to the list.
     */
    explicit HittableList(std::shared_ptr<Hittable> obj) { 
        add(obj); 
    }

    void clear() { 
        objects.clear(); 
    }

    /**
     * @brief Appends an object to the list.
     *
     * @param obj - object to add.
     */
    void add(std::shared_ptr<Hittable> obj) { 
        objects.push_back(std::move(obj)); 
    }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const;
};
