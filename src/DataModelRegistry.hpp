#pragma once

#include <unordered_map>

#include <QtCore/QString>

#include "NodeDataModel.hpp"

/// Base abstract class for Model Registry items
class RegistryItem
{
public:
  RegistryItem() {}

  virtual ~RegistryItem() {}

  virtual std::unique_ptr<NodeDataModel> create() const = 0;
};

//------------------------------------------------------------------------------

/// Not yet in C++11
template<typename T, typename ... Args>
std::unique_ptr<T> make_unique( Args&& ... args )
{
  return std::unique_ptr<T>( new T( std::forward<Args>(args) ... ) );
}


//------------------------------------------------------------------------------

/// Encapsulate templated concrete Model type T
template<typename T>
class RegistryItemImpl : public RegistryItem
{

public:

  /// Gives derived classes the ability to create instances of T
  std::unique_ptr<NodeDataModel> create() const override
  { return make_unique<T>(); }
};

//------------------------------------------------------------------------------

namespace std
{
template<>
struct hash<QString>
{
  inline
  size_t operator()(QString const& s) const
  {
    return qHash(s);
  }
};
}

//------------------------------------------------------------------------------

/// Class uses static map for storing models (name, model)
class DataModelRegistry
{

public:

  using RegistryItemPtr     = std::unique_ptr<RegistryItem>;
  using RegisteredModelsMap =
          std::unordered_map<QString, RegistryItemPtr>;

public:

  template<typename ModelType>
  static void registerModel(QString const &modelName)
  {
    if (_registeredModels.count(modelName) == 0)
    {
      _registeredModels[modelName] =
        make_unique < RegistryItemImpl < ModelType >> ();
    }
  }

  static std::unique_ptr<NodeDataModel>
  create(QString const &modelName);

  static RegisteredModelsMap const &registeredModels();

private:

  static RegisteredModelsMap _registeredModels;
};
