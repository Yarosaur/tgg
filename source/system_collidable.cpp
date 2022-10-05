#include "../include/system_collidable.hpp"
#include "../include/component_transform.hpp"
#include "../include/component_instance_id.hpp"


SCollidable::SCollidable() 
{
    std::bitset<32> default_collisions; 
    default_collisions.set((int)CollisionLayer::kDefault); 
    collision_layers_.insert(
	std::make_pair(CollisionLayer::kDefault, default_collisions));
    
    std::bitset<32> tile_collisions;
    collision_layers_.insert(std::make_pair(CollisionLayer::kTile, tile_collisions));
    
    std::bitset<32> player_collisions;
    player_collisions.set((int) CollisionLayer::kDefault);
    player_collisions.set((int) CollisionLayer::kTile);
    collision_layers_.insert(std::make_pair(CollisionLayer::kPlayer, player_collisions));
}


void SCollidable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
    for (auto obj : objects)
    {
	auto collider { obj->GetComponent<CBoxCollider>() };
	if (collider)
	{
	    CollisionLayer layer { collider->GetLayer() };
	    auto           itr   { collidables_.find(layer) };
	    if (itr != collidables_.end())
	    {
		collidables_[layer].push_back(collider);
	    }
	    else
	    {
		std::vector<std::shared_ptr<CBoxCollider>> objs;
		objs.push_back(collider);
		collidables_.insert(std::make_pair(layer, objs));
	    }
	}
    }
}


void SCollidable::ProcessRemovals()
{
    for (auto& layer : collidables_)
    {
	auto itr { layer.second.begin() };
	while (itr != layer.second.end())
	{
	    if ((*itr)->GetOwner()->IsQueuedForRemoval())
	    {
		itr = layer.second.erase(itr);
	    }
	    else
	    {
		++itr;
	    }
	}
    }
}


void SCollidable::Update()
{
    collision_tree_.DrawDebug();
    collision_tree_.Clear();
    for (auto iter { collidables_.begin() }; iter != collidables_.end(); ++iter)
    {
	for (auto collidable : iter->second)
	{
	    collision_tree_.Insert(collidable);
	}
    }
    Resolve();
}


void SCollidable::Resolve()
{
    for (auto iter_maps { collidables_.begin() }; iter_maps != collidables_.end(); ++iter_maps)
    {
        // If this layer collides with nothing then no need to 
        // perform any further checks.
	if(collision_layers_[iter_maps->first] == 0)
	{
	    continue;
	}
	
	for (auto collidable : iter_maps->second)
	{
            // If this collidable is static then no need to check if 
            // it's colliding with other objects.
	    if (!collidable->GetOwner()->GetComponent<CTransform>()->IsMovable())
	    {
		continue;
	    }
	    
	    std::vector<std::shared_ptr<CBoxCollider>> collisions 
		= collision_tree_.Search(collidable->GetCollidable());
	    
	    for (auto collision : collisions)
	    {
                // Make sure we do not resolve collisions between the same object.
		if (collidable->GetOwner()->GetComponent<CInstanceID>()->GetID() 
		    == collision->GetOwner()->GetComponent<CInstanceID>()->GetID())
		{
		    continue;
		}
		
		bool layers_collide = 
		    collision_layers_[collidable->GetLayer()][((int)collision->GetLayer())];
		if(layers_collide)
		{
		    Manifold m = collidable->Intersects(collision);
		    if(m.colliding)
		    {
			Debug::DrawRect(collision->GetCollidable(), sf::Color::Red);
			Debug::DrawRect(collidable->GetCollidable(), sf::Color::Red);
			
			if(!collision->GetOwner()->GetComponent<CTransform>()->IsMovable())
			{
			    collidable->ResolveOverlap(m);
			}
			else
			{
                            //TODO: How should we handle collisions when both 
                            // objects are not static?
                            // We could implement rigidbodies and mass.
			    collidable->ResolveOverlap(m); 
			}
		    }
		}
	    }
	}
    }
}
