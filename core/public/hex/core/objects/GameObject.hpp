/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_GAME_OBJECT_HPP
#define HEX_CORE_GAME_OBJECT_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::ecs::Entity
#ifndef HEX_ECS_ENTITY_HPP
    #include <hex/core/ecs/Entity.hpp>
#endif /// !HEX_ECS_ENTITY_HPP

// Include hex::string
#ifndef HEX_CORE_CFG_STRING_HPP
    #include <hex/core/cfg/hex_string.hpp>
#endif /// !HEX_CORE_CFG_STRING_HPP

// Include hex::atomic
#ifndef HEX_CORE_CFG_ATOMIC_HPP
    #include <hex/core/cfg/hex_atomic.hpp>
#endif /// !HEX_CORE_CFG_ATOMIC_HPP

// Include hex::core::WeakPointer
#ifndef HEX_CORE_WEAK_POINTER_HPP
    #include <hex/core/memory/WeakPointer.hpp>
#endif /// !HEX_CORE_WEAK_POINTER_HPP

// Include hex::glm
#ifndef HEX_CORE_CFG_GLM_HPP
    #include <hex/core/cfg/hex_glm.hpp>
#endif /// !HEX_CORE_CFG_GLM_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// GameObject
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        HEX_API class GameObject : public ecsEntity
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // META
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            HEX_CLASS

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // ALIASES
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            using object_ptr_t = hexShared<GameObject>;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTANTS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            const hexString* const mName;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        private:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DELETED
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            GameObject(const GameObject&)            = delete;
            GameObject& operator=(const GameObject&) = delete;
            GameObject(GameObject&&)                 = delete;
            GameObject& operator=(GameObject&&)      = delete;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        protected:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTANTS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            static constexpr const unsigned char LOADING_SATE_NONE      = 0;
            static constexpr const unsigned char LOADING_SATE_LOADING   = 0;
            static constexpr const unsigned char LOADING_SATE_LOADED    = 0;
            static constexpr const unsigned char LOADING_SATE_UNLOADING = 0;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // FIELDS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            hex_atomic<unsigned char>      mLoadingState;
            hexMutex                       mLoadingStateMutex;
            hexMutex * const               mChildrenMutex;
            hexVector<object_ptr_t>* const mChildren;
            hexWeak<GameObject>            mParent;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            explicit GameObject(
                const ecs_TypeID typeId,
                const bool hasChildren,
                const hexString* const pName = nullptr
            );

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // GETTERS & SETTERS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            hexShared<GameObject> getNextChild(const size_t index);
            size_t countChildren();

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual bool onAttach(GameObject* const);
            virtual void onDetach(GameObject* const);

            virtual bool onLoad();
            virtual void onUnload();

            bool loadAttachedObjects();
            void unloadAttachedObjects();

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual ~GameObject() noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // GETTERS & SETTERS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            hexString getName() const noexcept;

            glm::vec3 getPosition();
            glm::vec3 getRotation();
            glm::vec3 getScale();

            void setPosition(const glm::vec3 pos, const bool affectChildren);
            void setRotation(const glm::vec3 rot, const bool affectChildren);
            void setScale(const glm::vec3 scale, const bool affectChildren);

            bool isLoaded() const noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            bool attachObject(GameObject* const);
            bool detachObject(GameObject* const);

            void Move(const glm::vec3 offset, const bool affectChildren);
            void Rotate(const glm::vec3 offset, const bool affectChildren);
            void Scale(const glm::vec3 scale, const bool affectChildren);

            bool Load();
            void Unload();

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

    }

}

using hexGameObject = hex::core::GameObject;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_GAME_OBJECT_HPP
