#ifndef GENERIC_FACTORY_HPP
#define GENERIC_FACTORY_HPP

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

template <
    typename ProductType, 
    typename TypeId = std::string, 
    typename CreatorType = std::function<std::unique_ptr<ProductType>()>>
class GenericFactory
{
    std::unordered_map<TypeId, CreatorType> creators_;

public:
    bool register_creator(TypeId id, CreatorType creator)
    {
        bool is_inserted;
        std::tie(std::ignore, is_inserted) = creators_.insert(std::make_pair(std::move(id), std::move(creator)));

        return is_inserted;
    }

    std::unique_ptr<ProductType> create(const TypeId& id)
    {
        auto& creator = creators_.at(id);

        return creator();
    }
};

#endif // GENERIC_FACTORY_HPP
