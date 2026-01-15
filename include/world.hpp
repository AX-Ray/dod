#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <typeinfo>
#include <stdexcept>
#include <immintrin.h>

namespace dod {
        
    class IStorage {
    public:        
        virtual void resize(size_t size) = 0;
        virtual size_t size() const = 0;
        virtual const std::type_info& type() const = 0;
        virtual ~IStorage() = default;
    };


    template<typename T> 
    class Storage : public IStorage {
    private:
        std::vector<T> data;
        
    public:
        Storage(size_t size = 0) : data(size) {}
        
        T* data_ptr() {
            return data.data();
        }

        const T* data_ptr() const { 
            return data.data();
        }
        
        void resize(size_t size) override {
            data.resize(size);
        }
        
        size_t size() const override {
            return data.size();
        }
        
        const std::type_info& type() const override {
            return typeid(T);
        }
    };


    class World {
    private:        
        std::map<std::string, std::unique_ptr<IStorage>> storages;
        size_t entity_count;
        
    public:      
        World(size_t count = 0) : entity_count(count) {}
    
        template<typename T> 
        void create_storage(const std::string& name) {
            storages[name] = std::make_unique<Storage<T>>(entity_count);
        }

        template<typename T> 
        T* get_storage_data(const std::string& name) { 
            auto it = storages.find(name);
            if (it == storages.end()) {
                throw std::runtime_error("Не найдено " + name);
            }

            auto* storage = dynamic_cast<Storage<T>*>(it->second.get());
            if (!storage) {
                throw std::runtime_error("Типы не совпадают " + name);
            }
            
            return storage->data_ptr();
        }
        
        template<typename T> 
        const T* get_storage_data(const std::string& name) const { 
            auto it = storages.find(name);
            if (it == storages.end()) {
                throw std::runtime_error("Не найдено " + name);
            }

            auto* storage = dynamic_cast<const Storage<T>*>(it->second.get());
            if (!storage) {
                throw std::runtime_error("Типы не совпадают " + name);
            }
            
            return storage->data_ptr();
        }

        size_t size() const {
            return entity_count;
        }
        
        void resize(size_t new_size) {
            entity_count = new_size;
            for (auto& [name, storage] : storages) {
                storage->resize(new_size);
            }
        }
        
        void add_entity() {
            entity_count++;
            for (auto& [name, storage] : storages) {
                storage->resize(entity_count);
            }
        }
        
        bool has_storage(const std::string& name) const {
            return storages.find(name) != storages.end();
        }
        
        template<typename T>
        bool is_storage_type(const std::string& name) const {
            auto it = storages.find(name);
            if (it == storages.end()) return false;
            return it->second->type() == typeid(T);
        }
    };
}