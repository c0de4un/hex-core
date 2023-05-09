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
            mIDStorageMutex(),
            mIDStorages()
        {
        }

        ComponentsManager::~ComponentsManager() noexcept
        {
            this->deleteIDStorages();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ComponentsManager::comp_storage_t* ComponentsManager::getIDStorageByTypeID(const ecs_TypeID typeID)
        {
            hexLock lock(mIDStorageMutex);

            ComponentsManager::comp_storage_t* storage(nullptr);

            auto pos(mIDStorages.find(typeID));
            if (pos == mIDStorages.end())
            {
                storage = new ComponentsManager::comp_storage_t();

                mIDStorages.insert(
                    std::pair<ecs_TypeID, ComponentsManager::comp_storage_t*>(
                        typeID,
                        storage
                    )
                );
            }
            else
                storage = pos->second;

            return storage;
        }

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
            assert(mInstance && "ComponentsManager::Initialize: already terminated");
#endif // DEBUG

            delete mInstance;
            mInstance = nullptr;
        }

        ecs_ObjectID ComponentsManager::generateID(const ecs_TypeID typeID)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "ComponentsManager::generateID: not initialized");
#endif // DEBUG

            ComponentsManager::comp_storage_t* const idStorage(
                mInstance->getIDStorageByTypeID(typeID)
            );

            return idStorage->reserve();
        }

        void ComponentsManager::releaseID(const ecs_TypeID typeID, const ecs_ObjectID id)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "ComponentsManager::releaseID: not initialized");
#endif // DEBUG

            ComponentsManager::comp_storage_t* const idStorage(
                mInstance->getIDStorageByTypeID(typeID)
            );

            idStorage->put(id);
        }

        void ComponentsManager::deleteIDStorages() noexcept
        {
            hexLock lock(mIDStorageMutex, true);
            try { lock.lock(); }
            catch (...) { /** void */ }

            auto       iter(mIDStorages.begin());
            const auto end_iter(mIDStorages.cend());
            while (iter != end_iter)
            {
                delete iter->second;
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
