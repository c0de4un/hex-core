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
#ifndef HEX_CORE_GAME_OBJECT_HPP
    #include <hex/core/objects/GameObject.hpp>
#endif /// !HEX_CORE_GAME_OBJECT_HPP

// Include hex::core::PositionComponent
#ifndef HEX_CORE_POSITION_COMPONENT_HPP
    #include <hex/core/components/PositionComponent.hpp>
#endif /// !HEX_CORE_POSITION_COMPONENT_HPP

// Include hex::core::RotationComponent
#ifndef HEX_CORE_ROTATION_COMPONENT_HPP
    #include <hex/core/components/RotationComponent.hpp>
#endif /// !HEX_CORE_ROTATION_COMPONENT_HPP

// Include hex::core::ScaleComponent
#ifndef HEX_CORE_SCALE_COMPONENT_HPP
    #include <hex/core/components/ScaleComponent.hpp>
#endif /// !HEX_CORE_SCALE_COMPONENT_HPP

// Include hex::core::ColorComponent
#ifndef HEX_CORE_COLOR_COMPONENT_HPP
    #include <hex/core/components/ColorComponent.hpp>
#endif /// !HEX_CORE_COLOR_COMPONENT_HPP

// Include hex::core::ECoreComponents
#ifndef HEX_CORE_COMPONENTS_HPP
    #include <hex/core/components/ECoreComponents.hpp>
#endif /// !HEX_CORE_COMPONENTS_HPP

#ifdef HEX_LOGGING

    // Include hex::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// !HEX_LOGGING

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GameObject
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTORS & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        GameObject::GameObject(
            const ecs_TypeID typeId,
            const bool hasChildren,
            const hexString* const pName
        )
            :
            Entity(typeId),
            mName(pName),
            mChildrenMutex(hasChildren ? new hexMutex() : nullptr),
            mChildren(hasChildren ? new hexVector<object_ptr_t>() : nullptr),
            mParent(nullptr)
        {
        }

        GameObject::~GameObject() noexcept
        {
            if (mChildren)
            {
                delete mChildrenMutex;
                delete mChildren;
            }

            delete mName;
        }


        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexString GameObject::getName() const noexcept
        {
            return mName ? *mName : "";
        }

        glm::vec3 GameObject::getPosition()
        {
            auto _position(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::POSITION)
            ));

            hexPositionComponent* const positionComponent(
                static_cast<hexPositionComponent*>(_position.get())
            );

            return positionComponent ? positionComponent->mValue : glm::vec3(0.0f, 0.0f, 0.0f);
        }

        glm::vec3 GameObject::getRotation()
        {
            auto _rotation(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::ROTATION)
            ));

            hexRotationComponent* const rotationComponent(
                static_cast<hexRotationComponent*>(_rotation.get())
            );

            return rotationComponent ? rotationComponent->mValue : glm::vec3(0.0f, 0.0f, 0.0f);
        }

        glm::vec3 GameObject::getScale()
        {
            auto _scale(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::SCALE)
            ));

            hexScaleComponent* const scaleComponent(
                static_cast<hexScaleComponent*>(_scale.get())
            );

            return scaleComponent ? scaleComponent->mValue : glm::vec3(0.0f, 0.0f, 0.0f);
        }

        void GameObject::setPosition(const glm::vec3 pos, const bool affectChildren)
        {
            auto _component(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::POSITION)
            ));

            hexPositionComponent* const positionComponent(
                static_cast<hexPositionComponent*>(_component.get())
            );

            if (!positionComponent)
                return;

            hexLock componentLock(positionComponent->mMutex);
            const glm::vec3 _offset(pos - positionComponent->mValue);
            positionComponent->mValue = pos;
            componentLock.unlock();

            if (!affectChildren)
                return;

            const auto               _childrenCount(countChildren());
            GameObject::object_ptr_t child_ptr(nullptr);
            for (size_t childIndex = 0; childIndex < _childrenCount; childIndex++)
            {
                child_ptr = getNextChild(childIndex);
                if (!child_ptr.get())
                    continue;

                child_ptr->Move(_offset, true);
            }
        }

        void GameObject::setRotation(const glm::vec3 rot, const bool affectChildren)
        {
            auto _component(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::ROTATION)
            ));

            hexRotationComponent* const rotationComponent(
                static_cast<hexRotationComponent*>(_component.get())
            );

            if (!rotationComponent)
                return;

            hexLock componentLock(rotationComponent->mMutex);
            const glm::vec3 _offset(rot - rotationComponent->mValue);
            rotationComponent->mValue = rot;
            componentLock.unlock();

            if (!affectChildren)
                return;

            const auto               _childrenCount(countChildren());
            GameObject::object_ptr_t child_ptr(nullptr);
            for (size_t childIndex = 0; childIndex < _childrenCount; childIndex++)
            {
                child_ptr = getNextChild(childIndex);
                if (!child_ptr.get())
                    continue;

                child_ptr->Rotate(_offset, true);
            }
        }

        void GameObject::setScale(const glm::vec3 scale, const bool affectChildren)
        {
            auto _component(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::SCALE)
            ));

            hexScaleComponent* const scaleComponent(
                static_cast<hexScaleComponent*>(_component.get())
            );

            if (!scaleComponent)
                return;

            hexLock componentLock(scaleComponent->mMutex);
            const glm::vec3 _offset(scale - scaleComponent->mValue);
            scaleComponent->mValue = scale;
            componentLock.unlock();

            if (!affectChildren)
                return;

            const auto               _childrenCount(countChildren());
            GameObject::object_ptr_t child_ptr(nullptr);
            for (size_t childIndex = 0; childIndex < _childrenCount; childIndex++)
            {
                child_ptr = getNextChild(childIndex);
                if (!child_ptr.get())
                    continue;

                child_ptr->Scale(_offset, true);
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GameObject.PROTECTED: GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexShared<GameObject> GameObject::getNextChild(const size_t index)
        {
            if (!mChildren)
                return hexShared<GameObject>(nullptr);

            hexLock lock(*mChildrenMutex);

            if (mChildren->empty())
                return hexShared<GameObject>(nullptr);

            if (index >= mChildren->size())
                return hexShared<GameObject>(nullptr);

            return (*mChildren)[index];
        }

        size_t GameObject::countChildren()
        {
            if (!mChildren)
                return 0;

            hexLock lock(*mChildrenMutex);

            return mChildren->size();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool GameObject::onAttach(GameObject* const parent)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(parent && "GameObject::onAttach: parent is null");
            assert(mParent.isEmpty() && "GameObject::onAttach: already attached");
#endif // DEBUG

            if (!mParent.isEmpty())
                return false;

            mParent = parent;

            return true;
        }

        void GameObject::onDetach(GameObject* const parent)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(parent && "GameObject::onDetach: parent is null");
#endif // DEBUG

            if (mParent.get() != parent)
                return;

            mParent = nullptr;
        }

        void GameObject::Move(const glm::vec3 offset, const bool affectChildren)
        {
            auto _component(getComponent(
                static_cast<ecs_TypeID>(hexECoreComponents::POSITION)
            ));

            hexPositionComponent* const positionComponent(
                static_cast<hexPositionComponent*>(_component.get())
            );

            if (!positionComponent)
                return;

            hexLock componentLock(positionComponent->mMutex);
            positionComponent->mValue += offset;
            componentLock.unlock();

            if (!affectChildren)
                return;

            const auto               _childrenCount(countChildren());
            GameObject::object_ptr_t child_ptr(nullptr);
            for (size_t childIndex = 0; childIndex < _childrenCount; childIndex++)
            {
                child_ptr = getNextChild(childIndex);
                if (!child_ptr.get())
                    continue;

                child_ptr->Move(offset, true);
            }
        }

        void GameObject::Rotate(const glm::vec3 offset, const bool affectChildren)
        {
            // @TODO: GameObject::Rotate()
        }

        void GameObject::Scale(const glm::vec3 scale, const bool affectChildren)
        {
            // @TODO: GameObject::Scale()
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool GameObject::attachObject(GameObject* const pChild)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(pChild && "GameObject::attachObject: pChild is null");
            assert(pChild->mParent.isEmpty() && "GameObject::attachObject: pChild already attached");
#endif // DEBUG

            if (!mChildren)
                return false;

            if (!pChild->onAttach(this))
                return false;

            auto& children(*mChildren);

            hexLock lock(*mChildrenMutex);
            for (auto child_ptr : children)
            {
                if (!child_ptr.get())
                {
                    child_ptr.reset(pChild);
                    return true;
                }
            }

            children.push_back(GameObject::object_ptr_t(pChild));

            return true;
        }

        bool GameObject::detachObject(GameObject* const pChild)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(pChild && "GameObject::detachObject: pChild is null");
            assert(pChild->mParent.get() == this && "GameObject::detachObject: pChild is attached to other parent");
            assert(mChildren && "GameObject::detachObject: this object don't have children");
            assert(!pChild->mParent.isEmpty() && "GameObject::detachObject: child is already detached");
#endif // DEBUG

            if (!mChildren)
                return false;

            if (pChild->mParent.get() != this)
                return false;

            auto& children(*mChildren);

            hexLock lock(*mChildrenMutex);
            for (auto child_ptr : children)
            {
                if (child_ptr.get() == pChild)
                {
                    pChild->onDetach(this);
                    child_ptr.reset(nullptr);
                    return true;
                }
            }

            return false;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
