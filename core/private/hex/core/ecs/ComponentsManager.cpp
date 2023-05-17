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
#ifndef HEX_ECS_COMPONENTS_MANAGER_HPP
    #include <hex/core/ecs/ComponentsManager.hpp>
#endif /// !HEX_ECS_COMPONENTS_MANAGER_HPP

// Include hex::ecs::Component
#ifndef HEX_ECS_COMPONENT_HPP
    #include <hex/core/ecs/Component.hpp>
#endif /// !HEX_ECS_COMPONENT_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ComponentsManager
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ComponentsManager* ComponentsManager::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ComponentsManager::ComponentsManager()
            :
            BaseManager()
        {
        }

        ComponentsManager::~ComponentsManager() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void ComponentsManager::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("ComponentsManager::Initialize");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance && "ComponentsManager::Initialize: already initialized");
#endif // DEBUG

            if (mInstance)
                return;

            mInstance = new ComponentsManager();
        }

        void ComponentsManager::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("ComponentsManager::Terminate");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "ComponentsManager::Terminate: already terminated");
#endif // DEBUG

            delete mInstance;
            mInstance = nullptr;
        }

        ecs_ObjectID ComponentsManager::generateComponentID(const ecs_TypeID typeID)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "ComponentsManager::generateComponentID: not initialized");
#endif // DEBUG

            if (!mInstance)
                return ECS_INVALID_OBJECT_ID;

            return mInstance->generateID(typeID);
        }

        void ComponentsManager::releaseComponentID(const ecs_TypeID typeID, const ecs_ObjectID id) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "ComponentsManager::releaseComponentID: not initialized");
#endif // DEBUG

            if (!mInstance)
                return;

            try
            {
                mInstance->releaseID(typeID, id);
            }
            catch (...)
            {
                // void
            }
        }

        void ComponentsManager::releaseComponent(hexShared<ecsComponent> pComponent)
        {
            hexLock componentLock(pComponent->mMutex); // Possible dead-lock, users must be careful

            pComponent->mDisabled = true; // Let users know, that Component marked for removal and shouldn't be used

            releaseComponentID(pComponent->mTypeID, pComponent->mID);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
