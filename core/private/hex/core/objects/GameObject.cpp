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
