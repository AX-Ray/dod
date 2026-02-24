# dod.hpp - Data-Oriented Design Toolkit / Инструментарий Data-Oriented Design

---

## 📖 Description / Описание

**EN:** A single-header C++ library for Data-Oriented Design (DOD), implementing the concept of "worlds" - efficient storage and management of multiple objects of the same type.

**RU:** Однозаголовочная C++ библиотека для Data-Oriented Design (DOD), реализующая концепцию "миров" - эффективного хранения и управления множеством однотипных объектов.

---

## 🎯 The World Concept / Концепция World

**EN:** In traditional OOP, we describe an object class and create multiple instances. In DOD, we think differently: we have a **world** that contains many objects of the same type. Their properties are stored not in scattered objects, but in dense arrays-storages.

**RU:** В традиционном ООП мы описываем класс объекта и создаем множество экземпляров. В DOD мы мыслим иначе: у нас есть **мир (World)**, который содержит множество однотипных объектов. Их свойства хранятся не в разрозненных объектах, а в плотных массивах-хранилищах (Storages).

```cpp
// EN: Instead of this / RU: Вместо этого:
std::vector<Ball> balls;  // Array of objects / Массив объектов

// EN: We do this / RU: Мы делаем так:
dod::World balls(10);
balls.create_storage<float>("x");
balls.create_storage<float>("y");
balls.create_storage<float>("vx");
balls.create_storage<float>("vy");
```

## 📦 Features / Особенности
**EN:**

Single-header - just one file world.hpp

Zero-cost abstractions - direct memory access via pointers

Type-safe - runtime type checking

SIMD-friendly - data stored in dense arrays

Minimalism - only what's needed for DOD

**RU:**

Single-header - всего один файл world.hpp

Zero-cost абстракции - прямой доступ к памяти через указатели

Type-safe - проверка типов во время выполнения

SIMD-friendly - данные хранятся в плотных массивах

Минимализм - только то, что нужно для DOD

## 💡 Usage Examples / Примеры использования
Example 1: Particle Simulation / Пример 1: Симуляция частиц
**EN:** A simple particle system using the World concept:

**RU:** Простая система частиц с использованием концепции World:

```cpp
struct ParticleSystem {
    dod::World world;
    
    ParticleSystem(size_t count) : world(count) {
        world.create_storage<float>("x");
        world.create_storage<float>("y");
        world.create_storage<float>("vx");
        world.create_storage<float>("vy");
        world.create_storage<float>("mass");
    }
    
    void update(float dt) {
        float* x = world.get_storage_data<float>("x");
        float* y = world.get_storage_data<float>("y");
        float* vx = world.get_storage_data<float>("vx");
        float* vy = world.get_storage_data<float>("vy");
        
        for (size_t i = 0; i < world.size(); ++i) {
            x[i] += vx[i] * dt;
            y[i] += vy[i] * dt;
        }
    }
};
```

