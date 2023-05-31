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
            mChildren(hasChildren ? new hexVector<object_ptr_t>() : nullptr)
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

        bool GameObject::onAttach(GameObject* const)
        {
            // @TODO: GameObject::onAttach()
            return false;
        }

        void GameObject::onDetach(GameObject* const)
        {
            // @TODO: GameObject::onDetach()
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool GameObject::attachObject(GameObject* const)
        {
            if (!mChildren)
                return false;

            // @TODO: GameObject::attachObject()
            return false;
        }

        void GameObject::detachObject(GameObject* const)
        {
            if (!mChildren)
                return;

            // @TODO: GameObject::detachObject()
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
