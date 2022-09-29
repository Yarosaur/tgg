#ifndef __PROJECTS_TGG_RESOURCE_HOLDER_HPP__
#define __PROJECTS_TGG_RESOURCE_HOLDER_HPP__

#include <map>
#include <memory>
#include <string>

template <typename T>
class ResourceHolder
{
private:
  int current_id_;
  std::map<std::string, std::pair<int, std::shared_ptr<T>>> resources_;

public:
  int                Add    (const std::string& file_path);
  void               Remove (int id);
  std::shared_ptr<T> Get    (int id);
};

#include "resource_holder.inl"

#endif
