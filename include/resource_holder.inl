//#include "resource_holder.hpp"


template <typename T>
int ResourceHolder<T>::Add(const std::string& file_path)
{
  // Check
  auto it { resources_.find(file_path) };
  if (it != resources_.end())
  {
      return it->second.first;
  }

  // Load new resource
  auto resource { std::make_shared<T>() };
  if (!resource->loadFromFile(file_path))
  {
    return -1;
  }
  
  // Insert new resource
  resources_.insert(std::make_pair(file_path, std::make_pair(current_id_, resource)));
  
  return current_id_++;
}


template <typename T>
void ResourceHolder<T>::Remove(int id)
{
  for (auto it {resources_.begin()}; it != resources_.end(); ++it)
  {
    if (it->second.first == id)
    {
      resources_.erase(it->first);
    }
  }
}


template <typename T>
std::shared_ptr<T> ResourceHolder<T>::Get(int id)
{
    for (auto it {resources_.begin()}; it != resources_.end(); ++it)
      {
	if (it->second.first == id)
	  {
	    return it->second.second;
	  }
      }
    return nullptr;
}
