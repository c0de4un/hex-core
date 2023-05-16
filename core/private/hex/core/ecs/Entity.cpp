/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// HEADER
#ifndef HEX_ECS_ENTITY_HPP
    #include <hex/core/ecs/Entity.hpp>
#endif /// !HEX_ECS_ENTITY_HPP

// Include hex::ecs::Component
#ifndef HEX_ECS_COMPONENT_HPP
    #include <hex/core/ecs/Component.hpp>
#endif /// !HEX_ECS_COMPONENT_HPP

// Include hex::ecs::EntitiesManager
#ifndef HEX_ECS_ENTITIES_MANAGER_HPP
    #include <hex/core/ecs/EntitiesManager.hpp>
#endif /// !HEX_ECS_ENTITIES_MANAGER_HPP

// Include hex::ecs::ComponentsManager
#ifndef HEX_ECS_COMPONENTS_MANAGER_HPP
    #include <hex/core/ecs/ComponentsManager.hpp>
#endif /// !HEX_ECS_COMPONENTS_MANAGER_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Entity
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTORS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Entity::Entity(const ecs_TypeID typeId)
            :
            mTypeID(typeId),
            mID(ecs_Entities::generateEntityID(typeId)),
            mComponentsMutex(),
            mComponents()
        {
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Entity::~Entity() noexcept
        {
            ecs_Entities::releaseEntityID(mTypeID, mID);

            releaseComponents();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void Entity::releaseComponents()
        {
            const size_t  componentsCount(mComponents.size());
            for (size_t i = 0; i < componentsCount; i++)
            {
                hexShared<ecsComponent>& component(mComponents.at(i));

                ComponentsManager::releaseComponent(component);
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.IEntity
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ecs_TypeID Entity::getTypeID() const noexcept
        {
            return mTypeID;
        }

        ecs_ObjectID Entity::getID() const noexcept
        {
            return mID;
        }

        void Entity::addComponent(hexShared<ecsComponent> pComponent)
        {
            hexLock lock(mComponentsMutex);

            const size_t  componentsCount(mComponents.size());
            for (size_t i = 0; i < componentsCount; i++)
            {
                hexShared<ecsComponent>& component(mComponents.at(i));
                if (!component.get())
                {
                    component.reset(pComponent.get()); // Copy
                    return;
                }
            }

            mComponents.push_back(pComponent); // Copy
        }

        void Entity::removeComponent(const ecs_TypeID typeId, const ecs_ObjectID id)
        {
            hexLock lock(mComponentsMutex);

            ecsComponent* component_rawPtr(nullptr);
            const size_t  componentsCount(mComponents.size());
            for (size_t i = 0; i < componentsCount; i++)
            {
                hexShared<ecsComponent>& component(mComponents.at(i));
                component_rawPtr = component.get();
                if (component_rawPtr
                    && component_rawPtr->mTypeID == typeId
                    && component_rawPtr->mID == id)
                {
                    component.reset();
                    break;
                }
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
